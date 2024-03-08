from django.contrib import admin
from .models import CustomUserModel, HistoryLog
from django.contrib.auth.admin import UserAdmin

class CustomUserAdmin(UserAdmin):
    list_display = ('id', 'username', 'wins', 'losses', 'is_staff', 'is_superuser', 'is_active', 'is_online')
    fieldsets = (
        (None, {'fields': ('username', 'password', 'friends', 'friend_requests', 'blockList', 'is_online', 'invites', 'language')}),
        ('Oyun İstatistikleri', {'fields': ('wins', 'losses', 'elo')}),
        ('Yetkiler', {'fields': ('is_staff', 'is_superuser','is_active')}),
    )

class HistoryLogAdmin(admin.ModelAdmin):
    list_display = ('id', 'id1', 'id2', 'score1', 'score2', 'date')
    fieldsets = (
        (None, {'fields': ('id1', 'id2', 'score1', 'score2', 'date')}),
    )

admin.site.register(HistoryLog, HistoryLogAdmin)
admin.site.register(CustomUserModel, CustomUserAdmin)
