# models.py
from django.db import models
from .match import *
class pongGame(models.Model):
    room_code = models.CharField(max_length = 40)
    game_creator = models.CharField(max_length = 40)
    game_opponent = models.CharField(max_length = 40, blank=True, null=True)
    is_over = models.BooleanField(default=False)
    winner = models.CharField(max_length = 40, blank=True, null=True)

class LobbyRoom(models.Model):
    lobby_creator = models.CharField(max_length=40, null=False)
    lobby_opponent = models.CharField(max_length=40, blank=True, null=True)
    is_full = models.BooleanField(default=False)
    tournement = models.BooleanField(default=False)
    score1 = models.IntegerField(default=0)
    score2 = models.IntegerField(default=0)
    is_over = models.BooleanField(default=False)
    winner = models.CharField(max_length=40, null=True, blank=True)
    game = None

class TournementLobbyModel(models.Model):
    lobby_creator = models.CharField(max_length=40, null=False)
    player_2 = models.CharField(max_length=40, blank=True, null=True)
    player_3 = models.CharField(max_length=40, blank=True, null=True)
    player_4 = models.CharField(max_length=40, blank=True, null=True)

    lobby1id = models.IntegerField(default=0)
    lobby2id = models.IntegerField(default=0)
    lobby3id = models.IntegerField(default=0)

    count = models.IntegerField(default=0)
    is_full = models.BooleanField(default=False)
    is_started = models.BooleanField(default=False)

    lobby1score1 = models.IntegerField(default=0)
    lobby1score2 = models.IntegerField(default=0)
    lobby2score1 = models.IntegerField(default=0)
    lobby2score2 = models.IntegerField(default=0)

    finalplayer1 = models.CharField(max_length=40, blank=True, null=True)
    finalplayer2 = models.CharField(max_length=40, blank=True, null=True)
    finalscore1 = models.IntegerField(default=0)
    finalscore2 = models.IntegerField(default=0)
    game = None

