# chat/views.py
from django.shortcuts import render, redirect
from .models import Room, Group, GroupMessage
from accounts.models import CustomUserModel as User
from django.contrib.auth.decorators import login_required
from .models import Message
from . forms import GroupCreationForm
from django.contrib.auth.hashers import make_password, check_password


#@login_required(login_url='/my-login')
#def group(request, group_name, password):
#    hashed_password = make_password(password)
#    group = Group.objects.filter(group_name=group_name, password=hashed_password).first()
#
#    if not group:
#        group = Group.objects.filter(group_name=group_name).first()
#        if group:
#            return redirect('dashboard')
#        group = Group.objects.create(group_name=group_name, admin=request.user.username)
#        group.members.append(request.user.username)
#        group.password = hashed_password
#        group.save()
#    return redirect('grouppage', group_name)
@login_required(login_url='/my-login')
def group(request, group_name, password):
    group = Group.objects.filter(group_name=group_name).first()

    if not group:
        hashed_password = make_password(password)
        group = Group.objects.create(group_name=group_name, admin=request.user.username)
        group.members.append(request.user.username)
        group.password = hashed_password
        group.save()
        return redirect('grouppage', group_name)
    if check_password(password, group.password):
        group.members.append(request.user.username)
        return redirect('grouppage', group_name)
    return redirect('dashboard')
    

@login_required(login_url='/my-login')
def grouppage(request, group_name):
    group = Group.objects.get(group_name=group_name)
    messages=GroupMessage.objects.filter(group=group)

    query = request.GET.get('searchbar', '')  # 'searchbar' parametresini al, eğer yoksa boş bir string kullan
    members = User.objects.filter(username__in=group.members)
    if query:
        friends = friends.filter(username__icontains=query)

    context = {
        'group_id': group.id,
        'group_name':group.group_name,
        'request':request,
        'language':request.user.language,
        'messages':messages,
        'members':members,
    }
    return render(request, 'group.html', context)


@login_required(login_url='/my-login')
def dm(request, user_id):
    seconduser = User.objects.get(id=user_id)
    if request.user == seconduser:
        return redirect('dashboard')
    try:
        room = Room.objects.get(firstuser=request.user, seconduser=seconduser)
    except Room.DoesNotExist:
        try:
            room = Room.objects.get(firstuser=seconduser, seconduser=request.user)
        except Room.DoesNotExist:
            room = Room.objects.create(firstuser=request.user, seconduser=seconduser)
            room.room_name = room.firstuser.username + '-' + room.seconduser.username
            room.save()
    messages=Message.objects.filter(room=room)
    if request.user.id in seconduser.blockList or seconduser.id in request.user.blockList:
        is_blocked = True
    else:
        is_blocked = False
    if seconduser.id in request.user.blockList:
        i_blocked = True
    else:
        i_blocked = False
    context = {
        "room_id": room.id,
        "room":room,
        'messages':messages,
        'request':request,
        'language':request.user.language,
        'seconduser':seconduser,
        'is_blocked':is_blocked,
        'i_blocked':i_blocked,
    }
    return render(request, 'room.html', context)

@login_required(login_url='/my-login')
def blockuser(request, user_id):
    user = User.objects.get(id=user_id)
    if user.id not in request.user.blockList:
        request.user.blockList.append(user.id)
        request.user.save()
    return redirect('profile', user.id)

@login_required(login_url='/my-login')
def unblock(request, user_id):
    user = User.objects.get(id=user_id)
    if user.id in request.user.blockList:
        request.user.blockList.remove(user.id)
        request.user.save()
    return redirect('profile', user.id)