from django.contrib.auth.forms import UserCreationForm, AuthenticationForm
from django import forms
from django.forms.widgets import PasswordInput, TextInput
from .models import CustomUserModel, HistoryLog
from django.core.exceptions import ValidationError
from django.utils.translation import gettext_lazy as _

class CustomUserCreationForm(UserCreationForm):
    class Meta(UserCreationForm.Meta):
        model = CustomUserModel
        fields = ['username', 'password1', 'password2']

    def clean_username(self):

        username = self.cleaned_data.get('username')
        if any(ord(char) > 127 for char in username):
            raise ValidationError(_('Username can only contain English characters.'), code='invalid_username')

        forbidden_usernames = ['admin', 'root', 'ai']
        if username.lower() in forbidden_usernames:
            raise ValidationError(_('This username is not allowed.'), code='invalid_username')

        if username.lower() != username:
            raise ValidationError(_('Username must be all lowercase.'), code='invalid_username')

        return username

    def clean_password1(self):
        password1 = self.cleaned_data.get("password1")
        
        if len(password1) < 8:
            raise ValidationError(_('Password must be at least 8 characters long.'), code='invalid_password')
        if password1.isdigit():
            raise ValidationError(_('Password cannot be entirely numeric.'), code='invalid_password')

        return password1
    

class CustomLoginForm(AuthenticationForm):
    username = forms.CharField(widget=TextInput())
    password = forms.CharField(widget=PasswordInput())

class HistoryLogCreationForm(forms.ModelForm):
    class Meta:
        model = HistoryLog
        fields = ['id1', 'id2', 'score1', 'score2']


