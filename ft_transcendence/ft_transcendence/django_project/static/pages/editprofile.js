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
        document.getElementById("tr_edit_profile").innerText = locale['edit_profile'][language]
        document.getElementById("tr_username").innerText = locale['username'][language]
        document.getElementById("tr_profile_picture").innerText = locale['profile_picture'][language]
        document.getElementById("tr_select_language").innerText = locale['select_language'][language]
        document.getElementById("tr_save").value = locale['save'][language]
        
        
        document.querySelectorAll("#tr_profile").forEach(element => {
            element.innerText = locale['profile'][language];
        });

    }
});