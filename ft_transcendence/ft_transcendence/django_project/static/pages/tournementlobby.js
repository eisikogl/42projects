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
        
        document.getElementById("tr_table").innerText = locale['table'][language]
        document.getElementById("tr_semifinals").innerText = locale['semifinals'][language]

        document.getElementById("s1_1").innerText = locale['not_played'][language]
        document.getElementById("s1_2").innerText = locale['not_played'][language]
        document.getElementById("s2_1").innerText = locale['not_played'][language]
        document.getElementById("s2_2").innerText = locale['not_played'][language]
        document.getElementById("f_1").innerText = locale['not_played'][language]
        document.getElementById("f_2").innerText = locale['not_played'][language]
        
        document.getElementById("tr_final").innerText = locale['final'][language]
        
        document.querySelectorAll("#playbutton").forEach(element => {
        element.innerText = locale['playbutton'][language];
        });
        document.querySelectorAll("#tr_profile").forEach(element => {
        element.innerText = locale['profile'][language];
        });
    }
});