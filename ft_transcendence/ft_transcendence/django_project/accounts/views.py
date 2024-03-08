from django.shortcuts import render, redirect
from . forms import CustomUserCreationForm, CustomLoginForm, HistoryLogCreationForm
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.shortcuts import get_object_or_404
from .models import HistoryLog
from chat.models import Group
from django.contrib.auth import get_user_model
from django.db import transaction
from pong.models import TournementLobbyModel
from django.utils.translation import gettext, activate

User = get_user_model()

def sign_up(request):

    form = CustomUserCreationForm()

    if request.method == 'POST':
        form = CustomUserCreationForm(request.POST)
        if form.is_valid():
            user = form.save()
            user.save()
            login(request, user)
            return redirect("dashboard")
    context = {'signupform': form}
    return render(request, 'sign-up.html', context=context)
    

def my_login(request):
    form = CustomLoginForm()
    if request.method == 'POST':
        form = CustomLoginForm(request, data=request.POST)
        if form.is_valid():
            username = form.cleaned_data.get('username')
            password = form.cleaned_data.get('password')
            
            user = authenticate(request, username=username, password=password)
            
            if user is not None:
                login(request, user)

                return redirect("dashboard")
            else:
                form.add_error(None, "Invalid username or password.")

    context = {
        'loginform': form,
    }
    return render(request, 'my-login.html', context)

@login_required(login_url='/my-login')
def user_logout(request):
    logout(request)
    return redirect("dashboard")

@login_required(login_url='/my-login')
def dashboard(request):
    query = request.GET.get('searchbar', '')  # 'searchbar' parametresini al, eğer yoksa boş bir string kullan
    friends = User.objects.filter(id__in=request.user.friends)
    #if query:
        #friends = friends.filter(username__icontains=query)
    friend_requests = User.objects.filter(id__in=request.user.friend_requests)
    groups = Group.objects.all()
    tournements = TournementLobbyModel.objects.all()
    users = User.objects.all()
    context = {
        'request':request,
        'users':users,
        'friends':friends,
        'friend_requests':friend_requests,
        'friend_request_count':friend_requests.count(),
        'invites':request.user.invites,
        'query': query,
        'groups':groups,
        'tournements': tournements,
    }
    return render(request, 'dashboard.html', context)
    
# views.py
def create_history_log(id1, id2, score1, score2):
    form_data = {
        'id1': id1,
        'id2': id2,
        'score1': score1,
        'score2': score2,
    }
    form = HistoryLogCreationForm(form_data)
    
    try:
        with transaction.atomic():
            if form.is_valid():
                history_log = form.save()
                username1 = User.objects.get(id=id1).username
                if id2 == -1:
                    username2 = "AI"
                else:
                    username2 = User.objects.get(id=id2).username
                history_log.username1 = username1
                history_log.username2 = username2
                history_log.save()
                print("Saved history log with id: ", history_log.id)
            else:
                print("Form is not valid. Errors: ", form.errors)
    except Exception as e:
        print("Error occurred while saving history log: ", str(e))

    return redirect('dashboard.html')

@login_required(login_url='/my-login')
def profile(request, id):
    user = get_object_or_404(User, id=id)

    matches = []
    try:
        matches1 = HistoryLog.objects.filter(id1=id)
        matches2 = HistoryLog.objects.filter(id2=id)
        matches.extend(matches1)
        matches.extend(matches2)
    except HistoryLog.DoesNotExist:
        print("Exception")
    
    is_friend = user.id in request.user.friends
    is_blocked = user.id in request.user.blockList
    is_request_send = request.user.id in user.friend_requests

    context = {
        'request':request,
        'language':request.user.language,
        'user':user,
        'matches':matches,
        'is_friend':is_friend,
        'is_blocked':is_blocked,
        'is_request_send':is_request_send,
    }
    return render(request, 'profile.html', context)



#def editprofile(request):
#    if request.method == 'POST':
#        username = request.POST.get('username').strip()
#        user = User.objects.filter(username=username).first()
#
#        # Kullanıcı adı değişikliği
#        if username and user is None:
#            request.user.username = username
#            request.user.save()
#
#        # Profil fotoğrafı değişikliği
#        profile_picture = request.FILES.get('profile_picture')
#        print(profile_picture)
#        if profile_picture:
#            request.user.avatar = profile_picture
#            request.user.save()
#
#        return redirect('profile', request.user.id)
#
#    return render(request, 'editprofile.html')

@login_required(login_url='/my-login')
def editprofile(request):
    if request.method == 'POST':
        username = request.POST.get('username').strip()
        profile_picture = request.FILES.get('profile_picture')
        error_message = None
        success_message = None
        # Check if username is provided and validate constraints
        if username:
            # Check if username already exists (case-sensitive)
            if User.objects.filter(username__iexact=username).first():
                error_message = "Username already exists."
            # Check if username contains only English letters
            elif not username.isascii() or not username.isalnum():
                error_message = "Username can only contain English letters and numbers."
            # Check if the username is in the restricted list
            elif username.lower() in ["admin", "ai", "root"]:
                error_message = "Username is not allowed."
            else:
                # Change the username
                request.user.username = username
                request.user.save()
        
        if profile_picture:
            request.user.avatar = profile_picture
            request.user.save()
            success_message = "Profile picture changed successfully."
        request.user.language = request.POST.get('language')
        request.user.save()

        if error_message or success_message:
            return render(request, 'editprofile.html', {'error_message': error_message, 'success_message': success_message, 'language':request.user.language})

        #elif error_message:
            #return render(request, 'editprofile.html', {'error_message': error_message})
        return redirect('profile', request.user.id)

    return render(request, 'editprofile.html', {'language':request.user.language})


def leaderboard(request):
    users = User.objects.all().order_by('-elo')
    context = {
        'request':request,
        'language':request.user.language,
        'users':users,
    }
    return render(request, 'leaderboard.html', context)


@login_required(login_url='/my-login')
def addfriend(request, user_id):
    user = User.objects.get(id=user_id)
    request.user.add_friend(user.id)
    user.add_friend(request.user.id)
    return redirect('profile', user.id)

@login_required(login_url='/my-login')
def removefriend(request, user_id):
    user = User.objects.get(id=user_id)
    request.user.remove_friend(user.id)
    user.remove_friend(request.user.id)
    return redirect('profile', user.id)

@login_required(login_url='/my-login')
def sendrequest(request, user_id):
    user = User.objects.get(id=user_id)
    if user:
        if user_id not in user.friend_requests:
            user.friend_requests.append(request.user.id)
            user.save()
    return redirect('dashboard')

@login_required(login_url='/my-login')
def acceptrequest(request, user_id):
    addfriend(request, user_id)
    declinerequest(request, user_id)
    return redirect('dashboard')

@login_required(login_url='/my-login')
def declinerequest(request, user_id):
    request.user.friend_requests.remove(user_id)
    request.user.save()
    return redirect('dashboard')

@login_required(login_url='/my-login')
def acceptinvite(request, username, lobby_id):
    request.user.invites.remove({'name':username, 'lobby':lobby_id})
    request.user.save()
    return redirect('play', lobby_id)

@login_required(login_url='/my-login')
def declineinvite(request, username, lobby_id):
    request.user.invites.remove({'name':username, 'lobby':lobby_id})
    request.user.save()
    return redirect('dashboard')