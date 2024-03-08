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
        
        document.getElementById("tr_speaking").innerText = locale['speaking'][language]
        
        document.querySelectorAll("#tr_remove_friend").forEach(element => {
            element.innerText = locale['remove_friend'][language];
        });
        document.querySelectorAll("#tr_block").forEach(element => {
            element.innerText = locale['block'][language];
        });
        document.querySelectorAll("#tr_unblock").forEach(element => {
            element.innerText = locale['unblock'][language];
        });
        document.querySelectorAll("#tr_invite").forEach(element => {
            element.innerText = locale['invite'][language];
        });
        document.querySelectorAll("#chat-message-submit").forEach(element => {
            element.value = locale['send'][language];
        });
        document.querySelectorAll("#chat-message-submit-blocked").forEach(element => {
            element.value = locale['blocked'][language];
        });
        document.querySelectorAll("#tr_profile").forEach(element => {
        element.innerText = locale['profile'][language];
        });
    }
});