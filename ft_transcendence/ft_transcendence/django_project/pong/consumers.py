# consumer.py
import json
import asyncio
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
from .models import *
from asgiref.sync import sync_to_async
from accounts.views import create_history_log
from accounts.models import CustomUserModel as User
from django.core import serializers
import random
from django.shortcuts import redirect

class LobbyConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_name = self.scope["url_route"]["kwargs"]["lobby_id"]
        self.room_group_name = f"lobby_{self.room_name}"
        
        user = self.scope['user']
        
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )

        await self.send_lobby_status()
        await self.accept()
        await self.track_user_presence(self.scope['user'].id)

    async def disconnect(self, close_code):
        await self.untrack_user_presence(self.scope['user'].id)

    @database_sync_to_async
    def track_user_presence(self, user_id):
        # Add user to active users
        user = User.objects.get(id=user_id)
        user.is_online = True
        user.save()

    @database_sync_to_async
    def untrack_user_presence(self, user_id):
        # Remove user from active users
        user = User.objects.get(id=user_id)
        user.is_online = False
        user.save()

    async def receive(self, text_data):
        text_data_json = json.loads(text_data)
        message_type = text_data_json.get('type')

    async def send_lobby_status(self):
        """
        Tüm kullanıcılara güncellenmiş lobby durumunu gönderir.
        """
        lobbies = await self.get_lobby_status()
        message = {
            'type': 'lobby_status',
            'content': lobbies,
        }
        await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type': 'send_message',
                'message': message,
            }
        )

    async def send_message(self, event):
        message = event['message']['content']
        type = event['message']['type']
        # Send the message to the connected client
        await self.send(text_data=json.dumps({
            'type': type,
            'message': message
        }))

    @database_sync_to_async
    def get_lobby_status(self):
        """
        Bekleyen lobileri getirir.
        """
        lobbies = LobbyRoom.objects.filter(is_full=False)
        if lobbies:
            # İlk lobiyi al
            first_lobby = lobbies.first()

            # İlk lobiyi döndür
            lobby_data = {
                'id': first_lobby.id,
                'creator': first_lobby.lobby_creator,
                'opponent': first_lobby.lobby_opponent,
                'full': first_lobby.is_full
            }
        else:
            lobby_data = None
        return lobby_data

    async def disconnect(self, close_code):
        user = self.scope['user']

        await self.channel_layer.group_discard(
            self.room_group_name,
            self.channel_name
        )

        # Tüm kullanıcılara güncellenmiş lobby durumunu gönder
        await self.send_lobby_status()

class GameRoom(AsyncWebsocketConsumer):
    games = {}

    async def connect(self):
        self.room_name = self.scope['url_route']['kwargs']['game_id']
        self.room_group_name = f"game_{self.room_name}"
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )

        if self.room_name not in self.games:
            self.games[self.room_name] = {
                'player_count': 0,
                'players': [],
                'game': None,
                'game_loop_task': None,
                'pause_game': asyncio.Event(),
            }

        game = self.games[self.room_name]
        if game['player_count'] < 2:
            game['players'].append(self.channel_name)
            game['player_count'] += 1

        if game['player_count'] == 2:
            lobby = await sync_to_async(LobbyRoom.objects.get)(id=self.room_name)
            if not lobby.is_full:
                lobby.is_full = True
                await sync_to_async(lobby.save)()
            if not game['game']:
                game['game'] = Game()
            game['pause_game'].set()
            if not game['game_loop_task']:
                game['game_loop_task'] = asyncio.create_task(self.game_loop(self.room_name))

        await self.accept()
        await self.track_user_presence(self.scope['user'].id)

    async def disconnect(self, close_code):
        game = self.games.get(self.room_name)
        if game:
            game['players'].remove(self.channel_name)
            game['player_count'] -= 1
            if game['player_count'] == 0:
                del self.games[self.room_name]
                lobby = await sync_to_async(LobbyRoom.objects.get)(id=self.room_name)
                if lobby and not lobby.tournement:
                    await sync_to_async(lobby.delete)()
            elif game['player_count'] == 1:
                game['pause_game'].clear()

        await self.channel_layer.group_discard(
            self.room_group_name,
            self.channel_name
        )
        await self.untrack_user_presence(self.scope['user'].id)

    @database_sync_to_async
    def track_user_presence(self, user_id):
        # Add user to active users
        user = User.objects.get(id=user_id)
        user.is_online = True
        user.save()

    @database_sync_to_async
    def untrack_user_presence(self, user_id):
        # Remove user from active users
        user = User.objects.get(id=user_id)
        user.is_online = False
        user.save()

    async def receive(self, text_data):
        text_data_json = json.loads(text_data)
        message = text_data_json.get('data')
        message_type = text_data_json.get('type')
        if message_type == 'game_data':
            game = self.games[self.room_name]['game']
            if game:
                await sync_to_async(game.updatePaddle)(message['player'], message['move'])

    async def game_loop(self, room_name):
        game = self.games[room_name]
        while True:
            if game['game']:
                try:
                    await asyncio.wait_for(game['pause_game'].wait(), timeout=5)
                except asyncio.TimeoutError:
                    lobby = await sync_to_async(LobbyRoom.objects.get)(id=room_name)
                    first_user = await sync_to_async(User.objects.get)(username=lobby.lobby_creator)
                    second_user = await sync_to_async(User.objects.get)(username=lobby.lobby_opponent)
                    player_1_score = await sync_to_async(game['game'].getPlayer1)()
                    player_1_score = player_1_score['score']
                    player_2_score = await sync_to_async(game['game'].getPlayer2)()
                    player_2_score = player_2_score['score']
                    lobby.score1 = player_1_score
                    lobby.score2 = player_2_score
                    await sync_to_async(create_history_log)(first_user.id, second_user.id, player_1_score, player_2_score)
                    me = self.scope['user']
                    if me.username == first_user.username:
                        lobby.winner = first_user.username
                        first_user.wins += 1
                        second_user.losses += 1
                        first_user.elo += 5
                        second_user.elo -= 5
                        if second_user.elo < 0:
                            second_user.elo = 0
                    else:
                        lobby.winner = second_user.username
                        second_user.wins += 1
                        first_user.losses += 1
                        second_user.elo += 5
                        first_user.elo -= 5
                        if first_user.elo < 0:
                            first_user.elo = 0
                    await sync_to_async(first_user.save)()
                    await sync_to_async(second_user.save)()
                    lobby.is_over = True
                    await sync_to_async(lobby.save)()
                    break

                ball_pos = await sync_to_async(game['game'].updateBall)()
                end = await sync_to_async(game['game'].getEnd)()
                if end:
                    lobby = await sync_to_async(LobbyRoom.objects.get)(id=room_name)
                    first_user = await sync_to_async(User.objects.get)(username=lobby.lobby_creator)
                    second_user = await sync_to_async(User.objects.get)(username=lobby.lobby_opponent)
                    player_1_score = await sync_to_async(game['game'].getPlayer1)()
                    player_1_score = player_1_score['score']
                    player_2_score = await sync_to_async(game['game'].getPlayer2)()
                    player_2_score = player_2_score['score']
                    lobby.score1 = player_1_score
                    lobby.score2 = player_2_score
                    await sync_to_async(create_history_log)(first_user.id, second_user.id, player_1_score, player_2_score)
                    if player_1_score > player_2_score:
                        lobby.winner = first_user.username
                        first_user.wins += 1
                        second_user.losses += 1
                        first_user.elo += player_1_score
                        second_user.elo -= player_1_score
                        if second_user.elo < 0:
                            second_user.elo = 0
                    else:
                        lobby.winner = second_user.username
                        second_user.wins += 1
                        first_user.losses += 1
                        second_user.elo += player_2_score
                        first_user.elo -= player_2_score
                        if first_user.elo < 0:
                            first_user.elo = 0
                    await sync_to_async(first_user.save)()
                    await sync_to_async(second_user.save)()
                    lobby.is_over = True
                    await sync_to_async(lobby.save)()
                    game['pause_game'].clear()
                lobby1 = await sync_to_async(LobbyRoom.objects.get)(id=room_name)
                await self.channel_layer.group_send(
                    f"game_{room_name}",
                    {
                        'type': 'game_message',
                        'data': {
                            'player1': await sync_to_async(game['game'].getPlayer1)(),
                            'player2': await sync_to_async(game['game'].getPlayer2)(),
                            'ball': ball_pos,
                            'end': end,
                            'firstuser':lobby1.lobby_creator,
                            'seconduser':lobby1.lobby_opponent,
                        }
                    }
                )
                if end:
                    break
            await asyncio.sleep(0.01)  # Adjust the sleep time as needed

    async def game_message(self, event):
        await self.send(text_data=json.dumps({
            'type': event['type'],
            'data': event['data'],
        }))

class TournementLobby(AsyncWebsocketConsumer):
    games = {}

    async def connect(self):
        self.room_name = self.scope["url_route"]["kwargs"]['lobby_id']
        self.room_group_name = f"tournementlobby_{self.room_name}"
        if self.room_name not in self.games:
            self.games[self.room_name] = {
                'admin':None,
                'player_count': 0,
                'players': [],
                'matches':[],
                'lobby': await sync_to_async(TournementLobbyModel.objects.get)(id=self.room_name),
            }
        
        game = self.games[self.room_name]
        
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )
        await self.accept()

        user = self.scope['user']
        if game['player_count'] < 4:
            if user.username not in game['players']:
                game['players'].append(user.username)
                game['player_count'] += 1
                if game['player_count'] == 1:
                    game['admin'] = user.username
        else:
            if game['lobby'].is_started:
                username = user.username
                lobby = game['lobby1']
                if username != lobby.lobby_creator and username != lobby.lobby_opponent:
                    lobby = game['lobby2']
                lobby = await sync_to_async(LobbyRoom.objects.get)(id=lobby.id)
                await self.gameEndRecieve()



        
        await self.track_user_presence(user.id)

        message = {
            'type': 'user_connected',
            'players': game['players'],
        }
        await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type': 'send_message',
                'message': message,
            }
        )
        
        if game['player_count'] == 4 and not game['lobby'].is_started:
            message = {
                'type':'lobby_full',
                'admin': game['admin'],
            }
            await self.channel_layer.group_send(
                self.room_group_name,
                {
                    'type': 'send_message',
                    'message': message,
                }
            )

    async def gameEndRecieve(self):
        game = self.games[self.room_name]
        lobby1 = await sync_to_async(LobbyRoom.objects.get)(id=game['lobby1'].id)
        lobby2 = await sync_to_async(LobbyRoom.objects.get)(id=game['lobby2'].id)
        if lobby1.is_over and lobby2.is_over and game['lobby3'] == -1:
            lobby3 = await sync_to_async(LobbyRoom.objects.create)(lobby_creator=lobby1.winner, lobby_opponent=lobby2.winner, tournement=True)
            game['lobby3'] = lobby3
        if game['lobby3'] == -1:
            message = {
                'type':'update_table',
                'lobby1':{
                    'id':lobby1.id,
                    'player1':lobby1.lobby_creator,
                    'player2':lobby1.lobby_opponent,
                    'score1':lobby1.score1,
                    'score2':lobby1.score2,
                },
                'lobby2':{
                    'id':lobby2.id,
                    'player1':lobby2.lobby_creator,
                    'player2':lobby2.lobby_opponent,
                    'score1':lobby2.score1,
                    'score2':lobby2.score2,
                },
                'lobby3':{
                    'id':-1,
                    'player1':-1,
                    'player2':-1,
                    'score1':-1,
                    'score2':-1,
                },
            }
        else:
            game['lobby3'] = await sync_to_async(LobbyRoom.objects.get)(id=game['lobby3'].id)
            if not game['lobby3'].winner:
                message = {
                    'type':'create_play_button',
                    'lobby1':{
                        'id':lobby1.id,
                        'player1':lobby1.lobby_creator,
                        'player2':lobby1.lobby_opponent,
                        'score1':lobby1.score1,
                        'score2':lobby1.score2,
                    },
                    'lobby2':{
                        'id':lobby2.id,
                        'player1':lobby2.lobby_creator,
                        'player2':lobby2.lobby_opponent,
                        'score1':lobby2.score1,
                        'score2':lobby2.score2,
                    },
                    'lobby3':{
                        'id':game['lobby3'].id,
                        'player1':game['lobby3'].lobby_creator,
                        'player2':game['lobby3'].lobby_opponent,
                        'score1':game['lobby3'].score1,
                        'score2':game['lobby3'].score2,
                    },
                }
            else:
                message = {
                    'type':'tournement_end',
                    'lobby1':{
                        'id':lobby1.id,
                        'player1':lobby1.lobby_creator,
                        'player2':lobby1.lobby_opponent,
                        'score1':lobby1.score1,
                        'score2':lobby1.score2,
                    },
                    'lobby2':{
                        'id':lobby2.id,
                        'player1':lobby2.lobby_creator,
                        'player2':lobby2.lobby_opponent,
                        'score1':lobby2.score1,
                        'score2':lobby2.score2,
                    },
                    'lobby3':{
                        'id':game['lobby3'].id,
                        'player1':game['lobby3'].lobby_creator,
                        'player2':game['lobby3'].lobby_opponent,
                        'score1':game['lobby3'].score1,
                        'score2':game['lobby3'].score2,
                        'winner':game['lobby3'].winner,
                    },
                }
        await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type': 'send_message',
                'message': message,
            }
        )

    async def send_message(self, event):
        message = event['message']
        type = event['message']['type']
        await self.send(text_data=json.dumps({
            'message': message
        }))

    async def disconnect(self, close_code):
        await self.untrack_user_presence(self.scope['user'].id)

    @database_sync_to_async
    def track_user_presence(self, user_id):
        # Add user to active users
        user = User.objects.get(id=user_id)
        user.is_online = True
        user.save()

    @database_sync_to_async
    def untrack_user_presence(self, user_id):
        # Remove user from active users
        user = User.objects.get(id=user_id)
        user.is_online = False
        user.save()

    async def receive(self, text_data):
        text_data_json = json.loads(text_data)
        message_type = text_data_json.get('type')
        if (message_type == 'startTournement'):
            game = self.games[self.room_name]
            game['lobby'].is_started = True
            self.matchmake()

            match1 = game['matches'][0]
            match2 = game['matches'][1]
            lobby1 = await sync_to_async(LobbyRoom.objects.create)(lobby_creator=match1[0], lobby_opponent=match1[1], tournement=True)
            lobby2 = await sync_to_async(LobbyRoom.objects.create)(lobby_creator=match2[0], lobby_opponent=match2[1], tournement=True)
            game['lobby1'] = lobby1
            game['lobby2'] = lobby2
            game['lobby3'] = -1
            message = {
                'type':'create_play_button',
                'lobby1':{
                    'id':lobby1.id,
                    'player1':lobby1.lobby_creator,
                    'player2':lobby1.lobby_opponent,
                    'score1':lobby1.score1,
                    'score2':lobby1.score2,
                },
                'lobby2':{
                    'id':lobby2.id,
                    'player1':lobby2.lobby_creator,
                    'player2':lobby2.lobby_opponent,
                    'score1':lobby2.score1,
                    'score2':lobby2.score2,
                },
                'lobby3':{
                    'id':-1,
                    'player1':-1,
                    'player2':-1,
                    'score1':-1,
                    'score2':-1,
                },
            }
            await self.channel_layer.group_send(
                self.room_group_name,
                {
                    'type': 'send_message',
                    'message': message,
                }
            )

    def matchmake(self):
        game = self.games[self.room_name]
        players = game['players']
        random.shuffle(players)  # Oyuncuları rastgele karıştır

        game['matches'].clear()
        match = (players[0], players[1]) # Match 1
        game['matches'].append(match)
        match = (players[2], players[3]) # Match 2
        game['matches'].append(match)
        print(self.games[self.room_name]['matches'])

class AIGame(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_name = self.scope['url_route']['kwargs']['game_id']
        await self.accept()
        await self.track_user_presence(self.scope['user'].id)

    async def disconnect(self, close_code):
        lobby = await sync_to_async(LobbyRoom.objects.get)(id=self.room_name)
        if lobby:
            await sync_to_async(lobby.delete)()
        await self.untrack_user_presence(self.scope['user'].id)

    @database_sync_to_async
    def track_user_presence(self, user_id):
        # Add user to active users
        user = User.objects.get(id=user_id)
        user.is_online = True
        user.save()

    @database_sync_to_async
    def untrack_user_presence(self, user_id):
        # Remove user from active users
        user = User.objects.get(id=user_id)
        user.is_online = False
        user.save()

    async def receive(self, text_data):
        text_data_json = json.loads(text_data)
        type = text_data_json.get('type')
        score1 = text_data_json.get('score1')
        score2 = text_data_json.get('score2')
        if type == 'end_game':
            lobbyfilter = await sync_to_async(LobbyRoom.objects.filter)(id=self.room_name)
            lobby = await sync_to_async(lobbyfilter.first)()
            if lobby:
                lobby.is_over = True
                lobby.score1 = score1
                lobby.score2 = score2
                if score1 > score2:
                    lobby.winner = lobby.lobby_creator
                else:
                    lobby.winner = lobby.lobby_opponent
                await sync_to_async(lobby.save)()
                await sync_to_async(create_history_log)(self.scope['user'].id, -1, score1, score2)

class play2players(AsyncWebsocketConsumer):
    async def connect(self):
        await self.accept()
        await self.track_user_presence(self.scope['user'].id)

    async def disconnect(self, close_code):
        await self.untrack_user_presence(self.scope['user'].id)

    @database_sync_to_async
    def track_user_presence(self, user_id):
        # Add user to active users
        user = User.objects.get(id=user_id)
        user.is_online = True
        user.save()

    @database_sync_to_async
    def untrack_user_presence(self, user_id):
        # Remove user from active users
        user = User.objects.get(id=user_id)
        user.is_online = False
        user.save()
