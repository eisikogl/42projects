document.addEventListener("DOMContentLoaded", () =>
{
    fetch(csvUrl)
    .then(response => response.text())
    .then(csvContent => {
    const rows = csvContent.trim().split('\n');
    const locale = {};
    
    rows.forEach(row => {
    const [msg_id, tr, en, es, fr] = row.split(',');
    locale[msg_id] = { tr, en, es, fr };
    });
    localize(locale)
    })
    .catch(error => {
    console.error('File read failed:', error);
    });
    
    
    function localize(locale)
    {
        language = document.getElementById("language").textContent.trim().replace(/^"|"$/g, '');
        document.getElementById("tr_leaderboard").innerText = locale['leaderboard'][language]
        document.getElementById("tr_logout").innerText = locale['logout'][language]
        document.getElementById("tr_tournement_header").innerText = locale['tournement_header'][language]
        document.getElementById("tr_groups_header").innerText = locale['groups_header'][language]
        document.getElementById("tr_group_search").placeholder = locale['group_search'][language]
        document.getElementById("tr_users_header").innerText = locale['users_header'][language]
        document.getElementById("tr_group_create_header").innerText = locale['group_create_header'][language]
        document.getElementById("tr_close").innerText = locale['close'][language]
        document.getElementById("tr_group_create").innerText = locale['group_create'][language]
        document.getElementById("tr_play_ai").innerText = locale['play_ai'][language]
        document.getElementById("tr_play_2_players").innerText = locale['play_2_players'][language]
        document.getElementById("tr_play_remote").innerText = locale['play_remote'][language]
        document.getElementById("tr_create_tournement").innerText = locale['create_tournement'][language]
        document.getElementById("tr_game_invites").innerText = locale['game_invites'][language]
        document.getElementById("tr_friend_requests").innerText = locale['friend_requests'][language]
        document.getElementById("tr_friends_header").innerText = locale['friends_header'][language]
        document.getElementById("tr_friend_search").placeholder = locale['friend_search'][language]
        
        
        document.querySelectorAll("#tr_tournement").forEach(element => {
            element.innerText = locale['tournement'][language];
        });
        document.querySelectorAll("#tr_dm").forEach(element => {
            element.innerText = locale['dm'][language];
        });
        document.querySelectorAll("#tr_invite").forEach(element => {
            element.innerText = locale['invite'][language];
        });
        document.querySelectorAll("#tr_accept").forEach(element => {
            element.innerText = locale['accept'][language];
        });
        document.querySelectorAll("#tr_decline").forEach(element => {
            element.innerText = locale['decline'][language];
        });
        document.querySelectorAll("#tr_group_name").forEach(element => {
            element.innerText = locale['group_name'][language];
        });
        document.querySelectorAll("#tr_group_password").forEach(element => {
            element.innerText = locale['password'][language];
        });
        document.querySelectorAll("#tr_enter_button").forEach(element => {
        element.innerText = locale['enter_button'][language];
        });
        document.querySelectorAll("#tr_profile").forEach(element => {
        element.innerText = locale['profile'][language];
        });
    }
});