from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('admin/', admin.site.urls),
    path("dm/", include("chat.urls")),
    path('', include('accounts.urls')),
    path('pong/', include('pong.urls')),
]