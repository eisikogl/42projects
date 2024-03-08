document.addEventListener("DOMContentLoaded", () =>
{
const canvas = document.getElementById("pong");
const context = canvas.getContext("2d");
const defaultFontSize = 90;
const defaultTextColor = "#3a3c2f";
let wKey = false;
let sKey = false;
let upKey = false;
let downKey = false;

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

function checkCollision()
{
    // FRAME COLLISION
    if (ball.y + ball.radius >= canvas.height || ball.y - ball.radius <= 0)
        ball.velocityY = -ball.velocityY;
    if (ball.x + ball.radius >= canvas.width || ball.x - ball.radius <= 0)
    {
        score((ball.velocityX < 0 ? player2 : player1));
        ball.velocityX = -ball.velocityX;
    }
    // PADDLE COLLISION
    if (
        ball.x - ball.radius <= player1.right &&
        ball.y + ball.radius >= player1.y &&
        ball.y - ball.radius <= player1.y + player.height &&
        ball.x + ball.radius > player1.x &&
        player1.canHit
    ) {
        ball.velocityX = -ball.velocityX;
        player1.canHit = false;
        player2.canHit = true;
    }
    
    if (
        ball.x + ball.radius >= player2.x &&
        ball.y + ball.radius >= player2.y &&
        ball.y - ball.radius <= player2.y + player.height &&
        ball.x - ball.radius <= player2.x + player.width &&
        player2.canHit
    ) {
        ball.velocityX = -ball.velocityX;
        player2.canHit = false;
        player1.canHit = true;
    }
}

function resetBall()
{
    ball.x = canvas.width/2;
    ball.y = canvas.height/2
    ball.velocityX = 10
    ball.velocityY = (Math.random() == 0) ? 10 : -10;

    player1.canHit = true;
    player2.canHit = true;
}

function score(who)
{
    who.score++;
    resetBall();
}

function setKeys(ev)
{
    if (ev.key === 'W' || ev.key === 'w')
        wKey = ev.type === 'keydown';
    else if (ev.key === 'S' || ev.key === 's')
        sKey = ev.type === 'keydown';

    if (ev.key === 'ArrowUp')
    {
        upKey = ev.type === 'keydown';
        ev.preventDefault();
    }
    else if (ev.key === 'ArrowDown')
    {
        downKey = ev.type === 'keydown';
        ev.preventDefault();
    }
}

function movePaddle()
{
    if (wKey && player1.y > 0)
    {
        if (player1.y - player1.speed < 0)
            player1.y = 0;
        else
            player1.y -= player1.speed;
    }
    else if (sKey && player1.y + player.height < canvas.height)
    {
        if (player1.y + player.height + player1.speed > canvas.height)
            player1.y = canvas.height - player.height;
        else
            player1.y += player1.speed;
    }

    if (upKey && player2.y > 0)
    {
        if (player2.y - player2.speed < 0)
            player2.y = 0;
        else
            player2.y -= player2.speed;
    }
    else if (downKey && player2.y + player.height < canvas.height)
    {
        if (player2.y + player2.height + player2.speed > canvas.height)
            player2.y = canvas.height - player.height;
        else
            player2.y += player2.speed;
    }
}

function update()
{
    ball.x += ball.velocityX;
    ball.y += ball.velocityY;
    movePaddle();
    checkCollision();
    render();
}

id = setInterval(update, 1000/60);

document.body.addEventListener("keydown", setKeys);
document.body.addEventListener("keyup", setKeys);

const socket = new WebSocket(
    'wss://'
    + window.location.host
    + '/ws/pong/play2players/'
);

socket.onopen = function (event)
{
    console.log('socket baglandi')
}

socket.onmessage = function (event) {
    const data = JSON.parse(event.data);
    type = data.type
};
});