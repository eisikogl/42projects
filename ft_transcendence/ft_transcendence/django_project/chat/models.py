from django.db import models
from accounts.models import CustomUserModel

class Room(models.Model):
    firstuser = models.ForeignKey(CustomUserModel, on_delete=models.CASCADE, null=True, related_name='firstuser')
    seconduser = models.ForeignKey(CustomUserModel, on_delete=models.CASCADE, null=True ,related_name='seconduser')
    room_name = models.CharField(max_length=255)

    def __str__(self):
        return self.room_name

class Message(models.Model):
    room = models.ForeignKey(Room, on_delete=models.CASCADE)
    sender = models.CharField(max_length=255)
    message = models.TextField()

    def __str__(self):
        return str(self.room)

class Group(models.Model):
    group_name = models.CharField(max_length=40, unique = True)
    password = models.CharField(default='', blank=True)
    members = models.JSONField(default=list)
    admin = models.CharField(null=False)

    def __str__(self):
        return self.group_name

class GroupMessage(models.Model):
    group = models.ForeignKey(Group, on_delete=models.CASCADE)
    sender = models.CharField(max_length=255)
    message = models.TextField()

    def __str__(self):
        return str(self.group)