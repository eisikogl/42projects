# match.py
from random import choice
class Game():
    def __init__(self):
        self.canvasWidth = 1280
        self.canvasHeight = 720

        self.player = {
        'height': self.canvasHeight/3.6,
        'width': 15,
        'offset': 50,
        'speed' : 10,
        }

        self.player1 = {
            'x': self.player['offset'],
            'y': self.canvasHeight/2 - self.player['height']/2,

            'velocity' : 0,

            'right': self.player['offset'] + self.player['width'],

            'canHit': True,

            'score': 0,
        }

        self.player2 = {
            'x': self.canvasWidth - self.player['offset'] - self.player['width'],
            'y': self.canvasHeight/2 - self.player['height']/2,

            'velocity' : 0,

            'canHit': True,

            'score': 0,
        }

        self.ball = {
            'radius': 10,

            'x': self.canvasWidth/2,
            'y': self.canvasHeight/2,

            'velocityX': 10,
            'velocityY': 3,
        }
        self.end = False


    def getPlayer1(self):
        return self.player1
    
    def getPlayer2(self):
        return self.player2
    
    def getEnd(self):
        return self.end

    def resetBall(self):
        self.ball['x'] = self.canvasWidth/2
        self.ball['y'] = self.canvasHeight/2
        self.ball['velocityX'] = self.ball['velocityX'] * -1

    def updatePaddle(self, player, move):
        if player == 'player1':
            if move == 'down':
                self.player1['velocity'] = self.player['speed']
            elif move == 'up':
                self.player1['velocity'] = -self.player['speed']
            else:
                self.player1['velocity'] = 0  # Reset velocity if no key is pressed
        elif player == 'player2':
            if move == 'down':
                self.player2['velocity'] = self.player['speed']
                print(self.player2['velocity'])
            elif move == 'up':
                self.player2['velocity'] = -self.player['speed']
            else:
                self.player2['velocity'] = 0  # Reset velocity if no key is pressed

    def updateBall(self):
        # Update paddle positions based on velocity
        self.player1['y'] += self.player1['velocity']
        self.player2['y'] += self.player2['velocity']

        # Clamp paddle positions to stay within canvas bounds
        self.player1['y'] = max(0, min(self.canvasHeight - self.player['height'], self.player1['y']))
        self.player2['y'] = max(0, min(self.canvasHeight - self.player['height'], self.player2['y']))

        self.ball['x'] += self.ball['velocityX']
        self.ball['y'] += self.ball['velocityY']
        self.checkWallCollision()
        self.checkPaddleCollision()
        self.checkGoal()
        return {'x': self.ball['x'], 'y': self.ball['y']}

    def checkWallCollision(self):
        if self.ball['velocityY'] > 0:
            if self.ball['y'] + self.ball['radius'] >= self.canvasHeight:
                self.ball['velocityY'] = self.ball['velocityY'] * -1
        else:
            if self.ball['y'] - self.ball['radius'] <= 0:
                self.ball['velocityY'] = self.ball['velocityY'] * -1
    def checkPaddleCollision(self):
        if self.ball['velocityX'] > 0:
            if self.ball['x'] >= self.player2['x']:
                if self.ball['y'] >= self.player2['y'] and self.ball['y'] <= self.player2['y'] + self.player['height']:
                    self.ball['velocityX'] = self.ball['velocityX'] * -1
        else:
            if self.ball['x'] <= self.player1['x'] + self.player['width']:
                if self.ball['y'] >= self.player1['y'] and self.ball['y'] <= self.player1['y'] + self.player['height']:
                    self.ball['velocityX'] = self.ball['velocityX'] * -1
    def checkGoal(self):
        if self.ball['x'] >= self.canvasWidth:
            self.player1['score'] += 1
            self.resetBall()
        elif self.ball['x'] <= 0:
            self.player2['score'] += 1
            self.resetBall()
        
        if self.player1['score'] == 5 or self.player2['score'] == 5:
            self.end = True
