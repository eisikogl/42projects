
from django.urls import path
from . import views
from chat import views as chatviews
from pong import views as pongviews

urlpatterns = [
    path('sign-up/', views.sign_up, name="sign-up"),
    path('my-login/', views.my_login, name="my-login"),

    path('', views.dashboard, name="dashboard"),
    path('profile/<int:id>/', views.profile, name="profile"),
    path('profile/edit', views.editprofile, name="editprofile"),
    path('user-logout/', views.user_logout, name="user-logout"),
    path('dashboard/<int:user_id>/######', pongviews.private_lobby, name="sendinvite"),
    
    path('dm/<int:user_id>/', chatviews.dm, name="dm"),
    path('dm/<int:user_id>/#', chatviews.blockuser, name="block"),
    path('dm/<int:user_id>/##', chatviews.unblock, name="unblock"),
    path('profile/<int:user_id>/#', views.sendrequest, name="sendrequest"),

    path('profile/<int:user_id>/##', views.removefriend, name="removefriend"),
    path('dashboard/<int:user_id>/#', views.declinerequest, name="declinerequest"),
    path('dashboard/<int:user_id>/##', views.acceptrequest, name="acceptrequest"),

    path('dashboard/<str:username>/<int:lobby_id>/########', views.declineinvite, name="declineinvite"),
    path('dashboard/<str:username>/<int:lobby_id>/#######', views.acceptinvite, name="acceptinvite"),
    
    path('dashboard/<str:group_name>/<str:password>/####', chatviews.group, name="group"),
    path('leaderboard/', views.leaderboard, name="leaderboard"),
    path('group/<str:group_name>/', chatviews.grouppage, name="grouppage"),
]