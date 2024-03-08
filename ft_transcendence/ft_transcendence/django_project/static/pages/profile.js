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
        
        document.getElementById("tr_wins").innerText = locale['wins'][language]
        document.getElementById("tr_losses").innerText = locale['losses'][language]
        document.getElementById("tr_elo").innerText = locale['elo'][language]
        document.getElementById("tr_match_history").innerText = locale['match_history'][language]

        document.querySelectorAll("#tr_unblock").forEach(element => {
        element.innerText = locale['unblock'][language];
        });
        document.querySelectorAll("#tr_block").forEach(element => {
        element.innerText = locale['block'][language];
        });
        document.querySelectorAll("#tr_edit_profile").forEach(element => {
        element.innerText = locale['edit_profile'][language];
        });
        document.querySelectorAll("#tr_add_friend").forEach(element => {
        element.innerText = locale['add_friend'][language];
        });
        document.querySelectorAll("#tr_friend_request_send").forEach(element => {
        element.innerText = locale['friend_request_send'][language];
        });
        document.querySelectorAll("#tr_profile").forEach(element => {
        element.innerText = locale['profile'][language];
        });
    }
});