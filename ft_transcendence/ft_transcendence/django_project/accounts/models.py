from django.contrib.auth.models import AbstractUser
from django.contrib.auth.base_user import BaseUserManager
from django.db import models
from django.utils import timezone
import csv

class CustomUserModel(AbstractUser):
    username = models.CharField(max_length = 40, unique = True)
    avatar = models.ImageField(default='static/avatars/default.png', upload_to='static/avatars/')
    wins = models.IntegerField(default=0)
    losses = models.IntegerField(default=0)
    elo = models.IntegerField(default=0)
    friends = models.JSONField(default=list, blank=True)
    friend_requests = models.JSONField(default=list, blank=True)
    blockList = models.JSONField(default=list, blank=True)
    is_online = models.BooleanField(default=False)
    invites = models.JSONField(default=list, blank=True)
    tournement_id = models.IntegerField(default=0)
    language = models.CharField(max_length=2,default="en")
    
    groups = models.ManyToManyField('auth.Group', related_name='custom_user_groups')
    # Add a related_name argument to resolve the clash with auth.User.user_permissions
    user_permissions = models.ManyToManyField('auth.Permission', related_name='custom_user_permissions')

    USERNAME_FIELD = 'username'
    REQUIRED_FIELDS = []

    def add_friend(self, friend_username):
        if friend_username not in self.friends:
            self.friends.append(friend_username)
            self.save()

    def remove_friend(self, friend_username):
        if friend_username in self.friends:
            self.friends.remove(friend_username)
            self.save()

class UserManager(BaseUserManager):
    
    def create_user(self, username, password = None, **extra_fields):
        if not (username and password):
            raise ValueError("Username and password required!")
        user = self.model(username = username, **extra_fields)
        user.set_password(password)
        user.save(using = self._db)
        return user
    
    def create_superuser(self, username, password = None, **extra_fields):
        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', True)
        extra_fields.setdefault('is_active', True)

        return self.create_user(username, password, **extra_fields)

# models.py
class HistoryLog(models.Model):
    username1 = models.CharField(max_length=40, default='noname1')
    username2 = models.CharField(max_length=40, default='noname2')
    id1 = models.IntegerField(null=False, default=0)
    id2 = models.IntegerField(null=False, default=0)
    score1 = models.IntegerField(null=True, default=0)
    score2 = models.IntegerField(null=True, default=0)
    date = models.DateTimeField(default=timezone.now)