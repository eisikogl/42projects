from django.contrib import admin
from .models import *


class pongRoomAdmin(admin.ModelAdmin):
    list_display = ('id', 'game_creator', 'game_opponent','room_code')

admin.site.register(pongGame, pongRoomAdmin)

class LobbyRoomAdmin(admin.ModelAdmin):
    list_display = ('id', 'lobby_creator', 'lobby_opponent','is_full')

admin.site.register(LobbyRoom, LobbyRoomAdmin)

class TournementLobbyModelAdmin(admin.ModelAdmin):
    list_display = ('id', 'lobby_creator', 'player_2', 'player_3', 'player_4', 'is_full')
admin.site.register(TournementLobbyModel, TournementLobbyModelAdmin)
