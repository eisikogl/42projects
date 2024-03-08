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
        
        document.getElementById("tr_founder").innerText = locale['founder'][language]
        
        document.querySelectorAll("#chat-message-submit").forEach(element => {
            element.value = locale['send'][language];
        });
        document.querySelectorAll("#chat-message-submit-blocked").forEach(element => {
            element.value = locale['blocked'][language];
        });
        document.querySelectorAll("#tr_dm").forEach(element => {
            element.innerText = locale['dm'][language];
        });
        document.querySelectorAll("#tr_invite").forEach(element => {
            element.innerText = locale['invite'][language];
        });
        document.querySelectorAll("#tr_profile").forEach(element => {
        element.innerText = locale['profile'][language];
        });
    }
});