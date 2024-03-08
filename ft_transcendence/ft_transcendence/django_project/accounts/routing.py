from django.urls import re_path

from . import consumers

websocket_urlpatterns = [
    re_path(r'ws/leaderboard/$', consumers.PresenceConsumer.as_asgi()),
    re_path(r'ws/dashboard/$', consumers.PresenceConsumer.as_asgi()),
    re_path(r'ws/profile/(?P<user_id>\w+)/$', consumers.PresenceConsumer.as_asgi()),
    re_path(r'ws/profile/edit/$', consumers.PresenceConsumer.as_asgi()),
]