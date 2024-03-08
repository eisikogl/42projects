document.addEventListener("DOMContentLoaded", () =>
{
const canvas = document.getElementById("pong");
const context = canvas.getContext("2d");
const defaultFontSize = 90;
const defaultTextColor = "#3a3c2f";

const net = {
    height: 10,
    width: 6,
    
    x: canvas.width/2 - 6/2, // update 6 if width changes
    y: 160,
    
    color: defaultTextColor
}

const player = {
    height: canvas.height/3.6,
    width: 15,
    offset: 50
}

const player1 = {
    x: player.offset,
    y: canvas.height/2 - player.height/2,
    
    right: player.offset + player.width,

    speed: 10,

    canHit: true,

    score: 0,
    scoreX: canvas.width/4,
    scoreY: canvas.height/5,
    
    color: defaultTextColor
}

const player2 = {
    x: canvas.width - player.offset - player.width,
    y: canvas.height/2 - player.height/2,

    speed: 10,

    canHit: true,

    score: 0,
    scoreX: 3*canvas.width/4,
    scoreY: canvas.height/5,

    color: defaultTextColor
}

const ball = {
    radius: 10,
    
    x: canvas.width/2,
    y: canvas.height/2,

    speed: 10,
    firstHit: false,

    velocityX: 10,
    velocityY: 10,
    
    color: defaultTextColor
}

function drawNet()
{
    const size = 60;
    for (let i = 0; i < canvas.height; i += size)
        drawText("i", net.x, net.y + i, net.color, size);
}

function drawBall(x, y, radius, color)
{
    context.fillStyle = color;
    context.beginPath();
    context.arc(x, y, radius, 0, 360, false);
    context.closePath();
    context.fill();
}

function drawRect(x, y, w, h, color)
{
    context.fillStyle = color;
    context.fillRect(x, y, w, h);
}

function drawText(score, x, y, color, size)
{
    context.fillStyle = color;
    context.font = `${size}px digit`
    context.fillText(score, x, y);
}

function render()
{
    context.clearRect(0, 0, canvas.width, canvas.height);
    drawText(player1.score, player1.scoreX, player1.scoreY, defaultTextColor, defaultFontSize);
    drawText(player2.score, player2.scoreX, player2.scoreY, defaultTextColor, defaultFontSize);
    drawNet();
    drawRect(player1.x, player1.y, player.width, player.height, player1.color);
    drawRect(player2.x, player2.y, player.width, player.height, player2.color);
    drawBall(ball.x, ball.y, ball.radius, ball.color);
}

function sendData(move)
{
    const data = {
        'player':me,
        'move':move,
    }
    socket.send(JSON.stringify(
    {
        'type': 'game_data',
        'data': data,
    }));
}


document.body.addEventListener("keydown", setKeys);
document.body.addEventListener("keyup", setKeys);
function setKeys(ev)
{
    if (ev.key === 'ArrowUp')
    {
        if (ev.type === 'keydown')
            sendData('up')
        ev.preventDefault();
    }
    else if (ev.key === 'ArrowDown')
    {
        if (ev.type === 'keydown')
            sendData('down')
        ev.preventDefault();
    }
    if (ev.key === 'ArrowDown' || ev.key === 'ArrowUp')
    {
        if (ev.type === 'keyup')
        {
            sendData('none')
            ev.preventDefault();
        }
    }
}



const player_1 = document.getElementById('player-1').textContent;
const player_2 = document.getElementById('player-2').textContent;
const requestPlayer = document.getElementById('request-player').textContent;
const requestID = document.getElementById('request-id').textContent;
console.log('Player 1: ' + player_1)
console.log('Player 2: ' + player_2)
console.log('Request Player: ' + requestPlayer)


let me;
if (requestPlayer == player_1)
    me = 'player1';
else
    me = 'player2';

render()

const gameID = JSON.parse(document.getElementById('game-id').textContent);
console.log("Game ID: " + gameID)

const socket = new WebSocket(
    'wss://'
    + window.location.host
    + '/ws/pong/'
    + gameID
    + '/'
);

function updatePos(data)
{
    player1.y = data.player1.y
    player2.y = data.player2.y
    ball.x = data.ball.x
    ball.y = data.ball.y
    player1.score = data.player1.score
    player2.score = data.player2.score
}

socket.onopen = function (event)
{
    console.log('socket baglandi')
    socket.send(JSON.stringify(
    {
        'type': 'lobby_status',
    }));
}

function endGame()
{
    if (document.getElementById("is-tournement").textContent == "true")
        document.getElementById("return").style.display = "block";
    document.getElementById("end_game").style.display = "block";
}

socket.onmessage = function (event) {
    const data = JSON.parse(event.data);
    type = data.type
    if (type === 'game_message') {
        if (data.data.end)
            endGame();
        updatePos(data.data)
        render();
        document.getElementById("versus").innerText = data.data.firstuser + " vs " + data.data.seconduser
    }
};
});
