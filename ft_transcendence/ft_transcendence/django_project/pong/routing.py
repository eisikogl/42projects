from django.urls import re_path

from . import consumers

websocket_urlpatterns = [
    re_path(r'ws/pong/tournementlobby/(?P<lobby_id>\w+)/$', consumers.TournementLobby.as_asgi()),
    re_path(r'ws/pong/lobby/(?P<lobby_id>\w+)/$', consumers.LobbyConsumer.as_asgi()),
    re_path(r'ws/pong/(?P<game_id>\w+)/$', consumers.GameRoom.as_asgi()),
    re_path(r'ws/pong/ai/(?P<game_id>\w+)/$', consumers.AIGame.as_asgi()),
    re_path(r'/ws/pong/play2players/$', consumers.play2players.as_asgi()),
]