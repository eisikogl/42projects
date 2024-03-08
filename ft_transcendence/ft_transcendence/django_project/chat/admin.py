from django.contrib import admin
from .models import *


class RoomAdmin(admin.ModelAdmin):
    list_display = ('id', 'room_name')

admin.site.register(Room, RoomAdmin)

class GroupAdmin(admin.ModelAdmin):
    list_display = ('id', 'group_name', 'admin')

admin.site.register(Group, GroupAdmin)

admin.site.register(Message)
admin.site.register(GroupMessage)