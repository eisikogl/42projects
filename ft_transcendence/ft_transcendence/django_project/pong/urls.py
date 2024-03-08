
from django.urls import path
from . import views
from pong import views

urlpatterns = [
    path('tournementlobby/<str:lobby_id>/', views.tournementlobby, name="tournementlobby"),
    path('createtournementlobby/', views.createtournementlobby, name="createtournementlobby"),
    path('lobby/#', views.ailobby, name="ailobby"),
    path('lobby/', views.lobby, name="lobby"),
    path('ai/<str:game_id>/', views.playai, name="playai"),
    path('', views.play2players, name="play2players"),
    path('<str:game_id>/', views.play, name="play"),
]