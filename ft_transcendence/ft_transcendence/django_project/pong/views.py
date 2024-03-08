# views.py
from django.shortcuts import render, redirect
from django.contrib.auth.decorators import login_required
from .models import *
from .consumers import *
from accounts.models import CustomUserModel as User

@login_required(login_url='/my-login')
def createtournementlobby(request):
    lobby = TournementLobbyModel.objects.create(lobby_creator = request.user.username)
    lobby.count += 1
    lobby.save()
    request.user.tournement_id = lobby.id
    request.user.save()
    return redirect("tournementlobby", lobby.id)

@login_required(login_url='/my-login')
def tournementlobby(request, lobby_id):
    lobby = TournementLobbyModel.objects.get(id = lobby_id)
    username = request.user.username
    if lobby.lobby_creator != username and lobby.player_2 != username and lobby.player_3 != username and lobby.player_4 != username:
        if lobby.is_full:
            print("User is not belong to this room")
            return redirect('dashboard')
        if not lobby.player_2:
            lobby.player_2 = username
        elif not lobby.player_3:
            lobby.player_3 = username
        elif not lobby.player_4:
            lobby.player_4 = username
        lobby.count += 1
        request.user.tournement_id = lobby.id
        request.user.save()
        print("set edildi")
        print(request.user.tournement_id)
        if lobby.player_4:
            lobby.is_full=True
        lobby.save()
    return render(request, "tournementlobby.html", {'request_id':request.user.id, 'myname': request.user.username, 'lobby':lobby, 'language':request.user.language})

@login_required(login_url='/my-login')
def lobby(request):
    lobby = None
    lobbies = LobbyRoom.objects.filter(is_full=False)
    for lob in lobbies:
        enemy = User.objects.get(username=lob.lobby_creator)
        if enemy.elo < request.user.elo + 50 and enemy.elo > request.user.elo - 50:
            lobby = lob
            break
    if lobby:
        if lobby.lobby_creator != request.user.username:
            lobby.lobby_opponent = request.user.username
            lobby.is_full = True
            lobby.save()
            return redirect('play', lobby.id)
    else:
        lobby = LobbyRoom.objects.create(lobby_creator=request.user.username)
        lobby.save()

        return redirect('play', lobby.id)
    return render(request, 'lobby.html', {'lobby_id': lobby.id})

@login_required(login_url='/my-login')
def ailobby(request):
    lobby = LobbyRoom.objects.create(lobby_creator=request.user.username, lobby_opponent="AI")
    lobby.save()

    return redirect('playai', lobby.id)

@login_required(login_url='/my-login')
def private_lobby(request, user_id):
    opponent = User.objects.get(id=user_id)
    print(opponent.username)
    lobby = LobbyRoom.objects.create(lobby_creator=request.user.username, lobby_opponent=opponent.username, is_full=True)
    if lobby:
        opponent.invites.append({
            'name':request.user.username,
            'lobby':lobby.id})
        opponent.save()
        return redirect('play', lobby.id)
    return render(request, 'lobby.html', {'lobby_id': lobby.id})

@login_required(login_url='/my-login')
def play(request, game_id):
    lobby = LobbyRoom.objects.filter(id=game_id).first()
    if not lobby:
        print("Room not found")
        return redirect("dashboard")
    if lobby.lobby_creator != request.user.username and lobby.lobby_opponent != request.user.username:
        print("You can't access this room")
        return redirect("dashboard")
    context = {
        'game_id': game_id,
        'request': request.user.username,
        'language': request.user.language,
        'request_id': request.user.id,
        'player1': lobby.lobby_creator,
        'player2': lobby.lobby_opponent,
        'is_tournement':lobby.tournement,
        'tournement_id':request.user.tournement_id,
    }
    return render(request, 'play.html', context)

@login_required(login_url='/my-login')
def playai(request, game_id):
    lobby = LobbyRoom.objects.filter(id=game_id).first()
    if not lobby:
        print("You can't access this room")
        print("geldi")
        return redirect("dashboard")
    if lobby.lobby_creator != request.user.username:
        print("You can't access this room")
        return redirect("dashboard")
    lobby.is_full = True
    lobby.save()
    context = {
        'game_id': game_id,
        'request': request.user.username,
        'language': request.user.language,
        'request_id': request.user.id,
        'player1': lobby.lobby_creator,
        'player2': lobby.lobby_opponent,
    }
    return render(request, 'playai.html', context)

@login_required(login_url='/my-login')
def play2players(request):
    context = {
        'request': request.user.username,
        'language': request.user.language,
        'request_id': request.user.id,
    }
    return render(request, 'play2players.html', context)