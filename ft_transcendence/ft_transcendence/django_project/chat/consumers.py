
# chat/consumers.py
import json

from channels.generic.websocket import AsyncWebsocketConsumer
from .models import Message, GroupMessage
from asgiref.sync import sync_to_async
from channels.db import database_sync_to_async
from accounts.models import CustomUserModel as User

class ChatConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_name = self.scope["url_route"]["kwargs"]["room_name"]
        self.room_group_name = "chat_%s" % self.room_name

        # Join room group
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )

        await self.accept()
        await self.track_user_presence(self.scope['user'].id)

    async def disconnect(self, close_code):
        # Leave room group
        await self.channel_layer.group_discard(self.room_group_name, self.channel_name)
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

    # Receive message from WebSocket
    async def receive(self, text_data):
        text_data_json = json.loads(text_data)
        message = text_data_json["message"]
        user = self.scope['user']

        create_message = sync_to_async(Message.objects.create)
        m = await create_message(sender=user.username, room_id=self.room_name, message=message)

        # Send message to room group
        await self.channel_layer.group_send(
            self.room_group_name, {"type": "chat_message", "message": message, 'user':user.username}
        )

    # Receive message from room group
    async def chat_message(self, event):
        message = event["message"]
        user = event['user']

        # Send message to WebSocket
        await self.send(text_data=json.dumps({"message": message, 'sender':user}))


class GroupConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.group_name = self.scope["url_route"]["kwargs"]["group_name"]
        self.group_group_name = "chat_%s" % self.group_name

        # Join group group
        await self.channel_layer.group_add(self.group_group_name, self.channel_name)

        await self.accept()
        await self.track_user_presence(self.scope['user'].id)


    async def disconnect(self, close_code):
        # Leave group group
        await self.channel_layer.group_discard(self.group_group_name, self.channel_name)
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

    # Receive message from WebSocket
    async def receive(self, text_data):
        text_data_json = json.loads(text_data)
        message = text_data_json["message"]
        user = self.scope['user']

        create_message = sync_to_async(GroupMessage.objects.create)
        m = await create_message(sender=user.username, group_id=self.group_name, message=message)

        # Send message to group group
        await self.channel_layer.group_send(
            self.group_group_name, {"type": "chat_message", "message": message, 'user':user.username}
        )

    # Receive message from group group
    async def chat_message(self, event):
        message = event["message"]
        user = event['user']

        # Send message to WebSocket
        await self.send(text_data=json.dumps({"message": message, 'sender':user}))