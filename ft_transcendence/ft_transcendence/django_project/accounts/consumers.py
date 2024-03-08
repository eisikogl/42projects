# consumers.py

import json
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
from accounts.models import CustomUserModel as User

class PresenceConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        # Accept connection
        await self.accept()
        # Add user to active users
        await self.track_user_presence(self.scope['user'].id)

    async def disconnect(self, close_code):
        # Remove user from active users
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
