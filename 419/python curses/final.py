#!/usr/bin/env python3

import curses , curses.panel  
import time 
import random
import sys, socket, signal, select, termios, tty, argparse
from threading import Thread
import threading

class Coords:
        
        def __init__(self , panH , panW , startX , startY):
                self.panH = panH
                self.panW = panW 
                self.state = {'x' : startX , 'y' : startY , 'dx' : 0.0 , 'dy' : 0.0}

        def setXPos(self , x):
                self.state['x'] = x
                
        def setYPos(self , y):  
                self.state['y'] = y
                
        def setXYPos(self , x , y):
                self.setXPos(x)
                self.setYPos(y)
                
        def setXDelta(self , dx):
                self.state['dx'] = dx
                
        def setYDelta(self , dy):
                self.state['dy'] = dy
                
        def setXYDelta(self , dx , dy):
                self.setXVel(dx)
                self.setYVel(dy)
                                
        def getXPos(self):
                return self.state['x']

        def getYPos(self):
                return self.state['y']
                
        def getXYPos(self):
                return self.state['x'] , self.state['y']

        def getXDelta(self):
                return self.state['dx']
                
        def getYDelta(self):
                return self.state['dy']
                
        def getXYDelta(self):
                return self.state['dx'] , self.state['dy']
                
        def setState(self , x , y , dx , dy):
                self.setXPos(x)
                self.setYPos(y)
                self.setXDelta(dx)
                self.setYDelta(dy)
                
        def moveLeft(self , dx = None):
                x = self.getXPos()
                if(dx != None):
                        x -= dx
                else:
                        x -= self.getXDelta()
                if(x <= 0):
                        x = 0
                        self.setXPos(x)
                        return False
                self.setXPos(x)
                return True
                
        def moveRight(self , dx = None):
                x = self.getXPos()
                if(dx != None):
                        x += dx
                else:
                        x += self.getXDelta()
                if(x >= MAX_X - self.panW):
                        x = MAX_X - self.panW
                        self.setXPos(x)
                        return False
                self.setXPos(x)
                return True

        def moveUp(self , dy = None):
                y = self.getYPos()
                if(dy != None):
                        y -= dy
                else:
                        y -= self.getYDelta()
                if(y <= 0):
                        y = 0
                        self.setYPos(y)
                        return False
                self.setYPos(y)
                return True
        #True if in bounds , false if out       
        def moveDown(self , dy = None):
                y = self.getYPos()
                if(dy != None):
                        y += dy
                else:
                        y += self.getYDelta()
                if(y >= MAX_Y - self.panH):
                        y = MAX_Y - self.panH
                        self.setYPos(y)
                        return False
                self.setYPos(y)
                return True
                
class GameObjectPanel():
        
        def __init__(self , panH , panW , startX , startY):
                self.panH = panH
                self.panW = panW 
                self.coords = Coords(panH , panW , startX , startY)
                self.window = curses.newwin(panH , panW , int(startY) , int(startX))
                self.panel = curses.panel.new_panel(self.window)
                
        def movePanelPos(self):
                self.panel.move(int(self.coords.getYPos()) , int(self.coords.getXPos()))

class Animation():
        
        def __init__(self, fpa , drawOrder , panH , panW , startX , startY , gop = None):
                if(gop == None):
                        self.gop = GameObjectPanel(panH , panW , startX , startY)
                else:
                        self.gop = gop
                self.frameCount = 0 
                self.fpa = fpa
                self.frRemToDraw = fpa
                self.currentDraw = 0
                self.drawOrder = drawOrder
                self.lastDrawIndex = len(self.drawOrder) - 1
                self.setStartFrame()
                
        def setStartFrame(self):
                global FRAMECOUNT
                self.startFrame = FRAMECOUNT
                self.curFrame = FRAMECOUNT
                
        def draw(self , newFrame):

                if(self.frRemToDraw > 0):
                        if((self.currentDraw == 0) and (self.frRemToDraw == self.fpa)):
                                self.gop.panel.show()
                        self.drawOrder[self.currentDraw]()
                else:
                        if(self.currentDraw < self.lastDrawIndex):
                                self.currentDraw += 1
                                self.frRemToDraw = self.fpa
                                self.drawOrder[self.currentDraw]()
                        else:
                                self.currentDraw = 0
                                
                if(self.curFrame < newFrame):
                        self.frRemToDraw -= 1
                        self.curFrame += 1
        
        
class Laser(Animation):
        panWidth = 1
        panHeight = 1
        fpa = 8
        deltaPerFrame = 1
        
        def __init__(self , startX , startY , container = None):
                if(container != None):
                        self.container = container
                drawOrder = [self.draw0 , self.draw1 , self.draw2]
                super(Laser , self).__init__(Laser.fpa , drawOrder , Laser.panHeight , Laser.panWidth , startX , startY)
                self.gop.coords.setYDelta(Laser.deltaPerFrame)
                
                
        def setContainer(self , container):
                self.container = container
        
        def setFireLocation(self , startX , startY):
                self.gop.coords.setXYPos(startX , startY)
                self.gop.movePanelPos()
                self.isInBounds = True
                
        def remove(self):
                        self.container.append(self)
                        self.gop.window.erase()
                                        
        def move(self):
                self.isInBounds = self.gop.coords.moveUp()
                self.gop.movePanelPos()
                return self.isInBounds  
        
        def draw0(self):
                try:
                        self.gop.window.erase()
                        self.gop.window.addstr(0 , 0 , '^' , curses.color_pair(4)|curses.A_BOLD|curses.A_UNDERLINE)             
                except curses.error:
                        pass
                        
        def draw1(self):
                try:    
                        self.gop.window.erase()
                        self.gop.window.addstr(0 , 0 , '^' , curses.color_pair(5)|curses.A_BOLD)        
                except curses.error:
                        pass
                
        def draw2(self):
                try:
                        self.gop.window.erase()
                        self.gop.window.addstr(0 , 0 , '^' , curses.color_pair(4)|curses.A_BOLD|curses.A_UNDERLINE)     
                except curses.error:
                        pass
                        
class AfterBurner(Animation):
        fpa = 5
        deltaPerFrame = 1
        
        def __init__(self , gop):
                self.flag = False
                self.burnerCount = 0
                drawOrder = [self.draw0 , self.draw1 , self.draw2 , self.draw3, self.draw4, self.draw5]
                super(AfterBurner , self).__init__(AfterBurner.fpa , drawOrder , gop.panH , gop.panW , gop.coords.getXPos() , gop.coords.getYPos , gop)

        def move(self):
                pass
                
        def draw(self , FRAMECOUNT):
                if(self.flag == True):
                        super(AfterBurner , self).draw(FRAMECOUNT)
                else:
                        self.draw3()
                        self.draw4()
                        self.draw5()

        def draw0(self):
                try:
                        self.gop.window.addstr(3 , 0 , '  \\^^^/' , curses.color_pair(1)|curses.A_BOLD)         
                except curses.error:
                        pass
                        
        def draw1(self):
                try:    
                        self.gop.window.addstr(4 , 0 , '  \\^/' , curses.color_pair(2)|curses.A_BOLD)   
                except curses.error:
                        pass
                
        def draw2(self):
                try:
                        self.gop.window.addstr(5 , 0 , '   ^' , curses.color_pair(4)|curses.A_BOLD)     
                except curses.error:
                        pass
                        
        def draw3(self):
                try:
                        self.gop.window.addstr(3 , 0 , '       ' , curses.color_pair(1)|curses.A_BOLD)  
                except curses.error:
                        pass
                        
        def draw4(self):
                try:
                        self.gop.window.addstr(4  , 0 , '       ' , curses.color_pair(1)|curses.A_BOLD) 
                except curses.error:
                        pass
                        
        def draw5(self):
                try:
                        #self.gop.window.erase()
                        self.gop.window.addstr(5 , 0 , '       ' , curses.color_pair(1)|curses.A_BOLD)  
                except curses.error:
                        pass


class Gun():
        
        def __init__(self , ma = None):
                if(ma != None):
                        self.MAXAMMO = ma
                else:
                        self.MAXAMMO = 10       
                self.ammo = []
                #self.MAXAMMO is multiplied by two to ensure that 
                #       there will always be enough ammo objects 
                #       available to shoot
                for laz in range(self.MAXAMMO*2):
                        self.ammo.append(Laser(0 , 0 , self.ammo))              
                self.availAmmo = self.MAXAMMO
                self.ammoReload = Thread(target=self.loadAmmo , args=(1,) , daemon=True)
                self.ammoReload.start()
                
        def getAvailAmmo(self):
                return self.availAmmo

        def shoot(self , fireX , fireY):
                global ACTIVELIST
                if(self.availAmmo > 0):
                        try:
                                l = self.ammo.pop()
                        except IndexError:
                                #lazy instantiation, should never happen but here just in case
                                self.ammo.append(Laser(0 , 0 , self.ammo))
                        else:
                                l.setFireLocation(fireX , fireY)
                                ACTIVELIST[id(l)] = l
                                self.availAmmo -= 1
        
        def loadAmmo(self , delay):
                while(True):
                        time.sleep(delay)
                        if(self.availAmmo < self.MAXAMMO):
                                self.availAmmo += 1
                
                        
class Spaceship():
        panWidth = 7
        panHeight = 7
        XMOVE = 1.5
        YMOVE = 1
        XBOOST = 3
        YBOOST = 2
        
        def __init__(self , startX , startY):
                self.gop = GameObjectPanel(Spaceship.panHeight , Spaceship.panWidth , startX , startY)
                self.burner = AfterBurner(self.gop)
                self.ssMaxX = MAX_X - Spaceship.panWidth
                self.ssMaxY = MAX_Y + Spaceship.panHeight
                self.gun = Gun()
                if self.gop.panel.hidden(): self.gop.panel.show()
                
        def shootLaser(self):
                #Add 3 to correctly align laser with ship
                self.gun.shoot(self.gop.coords.getXPos() + 3 , self.gop.coords.getYPos())
                
        def moveLeft(self):
                self.gop.coords.moveLeft(Spaceship.XMOVE)
                self.burner.flag = False
                
        def moveRight(self):
                self.gop.coords.moveRight(Spaceship.XMOVE)
                self.burner.flag = False
                
        def moveForward(self):
                self.gop.coords.moveUp(Spaceship.YMOVE)
                self.burner.flag = False
                
        def moveBack(self):
                self.gop.coords.moveDown(Spaceship.YMOVE)
                self.burner.flag = False
                
        def boostLeft(self):
                self.gop.coords.moveLeft(Spaceship.XBOOST)
                self.burner.flag = True
                
        def boostRight(self):
                self.gop.coords.moveRight(Spaceship.XBOOST)
                self.burner.flag = True
                
        def boostForward(self):
                self.gop.coords.moveUp(Spaceship.YBOOST)
                self.burner.flag = True

        def boostBack(self):
                self.gop.coords.moveDown(Spaceship.YBOOST)
                self.burner.flag = True

        def drawShip(self):
                global FRAMECOUNT 
                self.gop.movePanelPos()
                self.gop.window.addstr(0 , 2 , '/^\\ ' , curses.color_pair(5)|curses.A_BOLD)
                self.gop.window.addch(1 , 1 , '|' , curses.color_pair(5)|curses.A_BOLD)
                self.gop.window.addch(1 , 2 , '|' , curses.color_pair(4)|curses.A_BOLD)
                self.gop.window.addch(1 , 3 , '+' , curses.color_pair(4)|curses.A_BOLD)
                self.gop.window.addch(1 , 4 , '|' , curses.color_pair(4)|curses.A_BOLD)
                self.gop.window.addch(1 , 5 , '|' , curses.color_pair(5)|curses.A_BOLD)
                self.gop.window.addch(2 , 0 , '<' , curses.color_pair(5)|curses.A_BOLD)
                self.gop.window.addstr(2 , 2 , '/_\\ >' , curses.color_pair(3)|curses.A_BOLD)
                self.gop.window.addch(2 , 6 , '>' , curses.color_pair(5)|curses.A_BOLD)
                if self.burner.flag == True:
                        self.gop.window.addstr(3 , 1 , '\\^^^/' , curses.color_pair(1)|curses.A_BOLD)
                        self.burner.draw(FRAMECOUNT)
                else:
                        self.gop.window.addstr(3 , 1 , ' ^^^' , curses.color_pair(1)|curses.A_BOLD)
                        self.gop.window.addstr(4 , 0 , '     ' , curses.color_pair(1)|curses.A_BOLD)
                        self.gop.window.addstr(5 , 0 , '     ' , curses.color_pair(1)|curses.A_BOLD)
                
class Background():
        panWidth = 86
        panHeight = 31

        def __init__(self , x , y):
                self.x = x
                self.y = y
                self.backWin = curses.newwin(Background.panHeight , Background.panWidth , y , x)
                self.backPan = curses.panel.new_panel(self.backWin)

        def drawStars(self, x, y):
                self.backWin.addstr(y, x, "  .       *             .   .")
                self.backWin.addstr(y, x, "*" )
                self.backWin.addstr(y+1, x, ".              +   /\\        *     .")
                self.backWin.addstr(y+2, x, "      .          <    >")
                self.backWin.addstr(y+3, x, "                 x \\/")
                self.backWin.addstr(y+4, x, "  *          .              +      *")
                self.backWin.addstr(y+5, x, "       .          .")

        def drawAsteroidS(self, x, y):
                self.backWin.addstr(y, x,   "   ___" , curses.color_pair(7))
                self.backWin.addstr(y+1, x, "__/ O \\__ " , curses.color_pair(7))
                self.backWin.addstr(y+2, x, "\\  o     \\" , curses.color_pair(7))
                self.backWin.addstr(y+3, x, " |__   o _/" , curses.color_pair(7))
                self.backWin.addstr(y+4, x, "   \\___/" , curses.color_pair(7))


        def drawAsteroidM(self, x, y):
                self.backWin.addstr(y, x,   "        ___________", curses.color_pair(8))
                self.backWin.addstr(y+1, x, "     __/ O       | \\__ ", curses.color_pair(8))
                self.backWin.addstr(y+2, x, "    /   o        \\_/  \\", curses.color_pair(8))
                self.backWin.addstr(y+3, x, "   |         /\\        |", curses.color_pair(8))
                self.backWin.addstr(y+4, x, "    \___     \\/____O__/", curses.color_pair(8))
                self.backWin.addstr(y+5, x, "        \\o___/", curses.color_pair(8))

        def drawAsteroidL(self, x, y):
                self.backWin.addstr(y+1, x,  "             __________", curses.color_pair(9))
                self.backWin.addstr(y+2, x,  "          __/ O        \\___ ", curses.color_pair(9))
                self.backWin.addstr(y+3, x,  "         / o               \\_", curses.color_pair(9))
                self.backWin.addstr(y+4, x,  "         |       /\          \\", curses.color_pair(9))
                self.backWin.addstr(y+5, x,  "        /        \/       ___/", curses.color_pair(9))
                self.backWin.addstr(y+6, x,  "       /                 /", curses.color_pair(9))
                self.backWin.addstr(y+7, x,  "      |     __          /", curses.color_pair(9))
                self.backWin.addstr(y+8, x,  "      |    /  \\_    O   \\____ ", curses.color_pair(9))
                self.backWin.addstr(y+9, x,  "      |   /     |            \\", curses.color_pair(9))
                self.backWin.addstr(y+10, x, "       \\__\\___  |             |", curses.color_pair(9))
                self.backWin.addstr(y+11, x, "          \___\\/       ___O__/", curses.color_pair(9))
                self.backWin.addstr(y+12, x, "              \\_______/", curses.color_pair(9))
        

        def drawCloudS(self, x, y):
                self.backWin.addstr(y, x,   "     ~~~~~")
                self.backWin.addstr(y+1, x, "  ~~~    ~~~~")
                self.backWin.addstr(y+2, x, "~~         ~~")
                self.backWin.addstr(y+3, x, "~~~   ~~~~~~")
                self.backWin.addstr(y+4, x, "  ~~~~")

        def drawCloudM(self, x, y):
                self.backWin.addstr(y, x,   "            ~~~~~~~~")
                self.backWin.addstr(y+1, x, "        ~~~~~      ~~")
                self.backWin.addstr(y+2, x, "   ~~~~~~~          ~~~~")
                self.backWin.addstr(y+3, x, "~~                    ~~~")
                self.backWin.addstr(y+4, x, "  ~~~~        ~~~~~~~~~")
                self.backWin.addstr(y+5, x, "     ~~~~~~~~~~")

        def drawCloudL(self, x, y):
                self.backWin.addstr(y, x,   "  ~~~~~~             ~~~~~~~")
                self.backWin.addstr(y+1, x, "~~~    ~~~~~~      ~~~      ~~")
                self.backWin.addstr(y+2, x, "~~           ~~~~~~~     ~~~~")
                self.backWin.addstr(y+3, x, "~~                 ~~~~~~~")
                self.backWin.addstr(y+4, x, "  ~~~~        ~~~~~~~~~")
                self.backWin.addstr(y+5, x, "     ~~~~~~~~~~")
        
        def drawClouds(self):
                self.drawCloudL(1,0)
                self.drawCloudS(60,0)
                self.drawCloudM(15,9)
                self.drawCloudS(7,18)

        def drawBackground(self):
                self.drawStars(0,0)
                self.drawStars(60,0)
                self.drawStars(15,9)
                self.drawStars(45,13)
                self.drawStars(7,18)

        def drawAsteroids(self):
                self.drawBackground()
                self.drawAsteroidL(0,0)
                self.drawAsteroidS(19,9)
                self.drawAsteroidM(45,13)
                self.drawAsteroidS(60,0) 


class Input():
        
        def __init__(self , stdscr , spaceShip, player):
                self.stdscr = stdscr
                self.spaceShip = spaceShip
                self.cmd = -1
                self.player = player

        def pause(self):
                choice = 1
                #continue getting input until the appropriate input is recieved
                while True:
                        s1.sendInput(NO_DEC) #send no decision signal

                        #check for other input
                        otherChoice = s1.otherInput() #check if other player made a decision
                        otherChoice = int(otherChoice)
                        if otherChoice == -1:
                                message(self, "Network Error")
                                sys.exit(1)
                        elif otherChoice == 1:
                                option = choose(self, "Other player is ready, do you want to continue?")
                                s1.sendInput(str(option))
                                if(option == 8):
                                        return True
                        elif otherChoice == 2:
                                option = choose(self, "Other player wants to swap, do you want to be player " +
                                                str((self.player + 1) % 2 + 1) + "?")
                                s1.sendInput(str(option))
                                if(option == 8):
                                        self.player = (self.player + 1) % 2
                        elif otherChoice == 3: 
                                message(self, "Other player chose to exit.")
                                return False


                        #display options
                        self.stdscr.erase()
                        self.stdscr.border(0)
                        self.stdscr.addstr(3, 5, "Player " + str(self.player + 1) + ", what do you want to do?")
                        self.stdscr.addstr(choice * 2 + 3, 9, ">", curses.A_BLINK)
                        self.stdscr.addstr(5, 10, "Continue")
                        self.stdscr.addstr(7, 10, "Swap Controls")
                        self.stdscr.addstr(9, 10, "End Game")
                        self.stdscr.refresh()
         
                        key = self.stdscr.getch()
                        if(key == curses.KEY_UP):
                                if(choice > 1):
                                        choice -= 1
                        if(key == curses.KEY_DOWN):
                                if(choice < 3):
                                        choice += 1

                        #made a decision so check other player
                        if(key == curses.KEY_ENTER or key == 10 or key == 13):
                                otherChoice = 0
                                s1.sendInput(str(choice))

                                if choice == 1 or choice == 2:
                                        while(otherChoice == 0):
                                                otherChoice = int(s1.otherInput())
                                                if otherChoice == -1:
                                                        message(self, "Network Error")
                                                        sys.exit(1)
                                                
                                                elif otherChoice == 8:
                                                        if choice == 1:
                                                                return True
                                                        if choice == 2:
                                                                self.player = (self.player + 1) % 2
                                                elif otherChoice == 9:
                                                        if choice == 1:
                                                                message(self, "Other player doesn't want to play yet")
                                                        if choice == 2:
                                                                message(self, "Other player doesn't want to swap")
                                                elif otherChoice == 10:
                                                        message(self, "Other player did not respond")
                                                elif otherChoice != 0: #concurrent input so make the guest wait 1 seconds and exit the loop
                                                                       # and make the host resend the confirmation request
                                                                if s1.status == "guest":
                                                                        time.sleep(1)
                                                                        otherChoice = 1
                                                                else:
                                                                        s1.sendInput(str(choice))
                                                                        otherChoice = 0 
                                elif choice == 3:
                                        return False
        
                                

        def processInput(self):
                cmd = self.stdscr.getch()
                if self.player == 0:
                        if (cmd != curses.KEY_RIGHT and cmd != curses.KEY_LEFT and cmd != ord('p') and
                           cmd != ord('a') and cmd != ord('d') and cmd != 32):
                                cmd = -1
                elif self.player == 1:
                        if (cmd != curses.KEY_UP and cmd != curses.KEY_DOWN and cmd != ord('p') and
                           cmd != ord('s') and cmd != ord('w') and cmd != 32):
                                cmd = -1

                s1.sendInput(str(cmd))
                otherCMD = int(s1.otherInput())

                if (cmd != -1 or otherCMD != -1):
                        #"a"
                        if(cmd == ord('a') or otherCMD == ord('a')):
                                self.spaceShip.boostLeft()
                        #"d"
                        elif(cmd == ord('d') or otherCMD == ord('d')):
                                self.spaceShip.boostRight()
                        #left
                        elif(cmd == curses.KEY_LEFT or otherCMD == curses.KEY_LEFT):
                                self.spaceShip.moveLeft()
                        #right
                        elif(cmd == curses.KEY_RIGHT or otherCMD == curses.KEY_RIGHT):
                                self.spaceShip.moveRight()
                        #"s"
                        elif(cmd == ord('s') or otherCMD == ord('s')):
                                self.spaceShip.boostBack()
                        #"w"
                        elif(cmd == ord('w') or otherCMD == ord('w')):
                                self.spaceShip.boostForward()
                        #up
                        elif(cmd == curses.KEY_UP or otherCMD == curses.KEY_UP):
                                self.spaceShip.moveForward()
                        #down
                        elif(cmd == curses.KEY_DOWN or otherCMD == curses.KEY_DOWN):
                                self.spaceShip.moveBack()
                        #laser
                        elif(cmd == 32 or otherCMD == 32):
                                self.spaceShip.shootLaser()
                        #pause
                        elif (cmd == ord('p') or otherCMD == ord('p')):
                                return self.pause()
                                
                return True
                
class Score():
        
        def __init__(self):
                global MAX_X
                self.score = 0
                self.panHeight = 3
                self.panWidth = 12
                self.window = curses.newwin(self.panHeight , self.panWidth , 0 , MAX_X - self.panWidth)
                self.panel = curses.panel.new_panel(self.window)

        def getPoints(self):
                return self.score
                
        def addPoint(self , points):
                self.score =+ points
                
        def printScore(self):
                self.window.box()
                self.score = FRAMECOUNT
                scoreStr = str(self.score)
                self.window.addstr(1 , 1 , scoreStr.zfill(10) , curses.color_pair(1)|curses.A_BOLD)
                self.panel.top()
                
class AmmoDisplay():
        
        def __init__(self , maxAmmo):
                global MAX_X
                self.maxAmmo = maxAmmo
                self.availAmmo = 0
                #constants chosen soley for aesthetics
                self.panHeight = 3
                self.panWidth = 20
                self.barLength = 18
                #--------------------------------------
                self.window = curses.newwin(self.panHeight , self.panWidth , 0 , 0)
                self.panel = curses.panel.new_panel(self.window)
        
        def printAmmoCount(self , newAmmoCount):
                self.window.erase()
                self.window.box()
                numCellsToPrint = int((newAmmoCount / self.maxAmmo) * self.barLength)
                ammoPrint = ' '  * numCellsToPrint
                self.window.addstr(1 , 1 , ammoPrint , curses.color_pair(6)|curses.A_BOLD)
                self.panel.top()



def choose(self, msg):
        choice = 1
        startTime = time.time()
        wait = 60 #wait in seconds
        while True:
                self.stdscr.erase()
                self.stdscr.addstr(3, 5, msg)
                self.stdscr.addstr(choice * 2 + 3, 9, ">", curses.A_BLINK)
                self.stdscr.addstr(5, 10, "Yes")
                self.stdscr.addstr(7, 10, "No")
                self.stdscr.refresh()
                key = self.stdscr.getch()
                if(key == curses.KEY_UP):
                        if(choice == 2):
                                choice -= 1
                if(key == curses.KEY_DOWN):
                        if(choice == 1):
                                choice += 1

                if(key == curses.KEY_ENTER or key == 10 or key == 13):
                        return choice + 7
                if(startTime + wait < time.time()):
                        return 10

def message(self, msg):
        self.stdscr.erase()
        self.stdscr.addstr(3, 5, msg)
        self.stdscr.refresh()
        time.sleep(3) #sleep for 3 seconds so user can read message
        
                
class GameLoop:
        
        def __init__(self, s1):
                self.t = 0.0
                self.dt = 0.02
                self.player = -1
                #self.frameCount = 0
                self.highscores = [0, 0, 0, 0, 0]
                #count = 0
                #if os.path.exists('highscores.txt'):
                #        scores = open('highscores.txt', 'r')
                #        for score in scores:
                #                self.highscores[count] = int(score)
                #                count += 1
                #        scores.close()
                
        def startGame(self , stdscr):
                global MAX_X , MAX_Y , ACTIVELIST , FRAMECOUNT
                self.stdscr = stdscr
                self.stdscr.nodelay(1)
                self.stdscr.keypad(1)
                curses.init_pair(1 , curses.COLOR_RED , curses.COLOR_BLACK)
                curses.init_pair(2 , curses.COLOR_YELLOW , curses.COLOR_BLACK)
                curses.init_pair(3 , curses.COLOR_CYAN , curses.COLOR_BLACK)
                curses.init_pair(4 , curses.COLOR_WHITE , curses.COLOR_BLACK)
                curses.init_pair(5 , curses.COLOR_GREEN , curses.COLOR_BLACK)
                curses.init_pair(6 , curses.COLOR_GREEN , curses.COLOR_GREEN)
                if(curses.COLORS == 256):
                        curses.init_pair(7, 245, curses.COLOR_BLACK)
                        curses.init_pair(8, 240, curses.COLOR_BLACK)
                        curses.init_pair(9, 247, curses.COLOR_BLACK)
                else:
                        curses.init_pair(7, curses.COLOR_GREEN, curses.COLOR_BLACK)
                        curses.init_pair(8, curses.COLOR_GREEN, curses.COLOR_BLACK)
                        curses.init_pair(9, curses.COLOR_GREEN, curses.COLOR_BLACK)
                curses.curs_set(0)
                self.createBackground()
                #----------------------------------------------------------------------

                play = self.menu()
                while(play):
                        FRAMECOUNT = 0
                        ACTIVELIST = {}
                        MAX_Y , MAX_X = stdscr.getmaxyx()
                        self.spaceShip = Spaceship(int(MAX_X/2) , int(MAX_Y/2))
                        self.shGun = self.spaceShip.gun
                        self.userInput = Input(stdscr , self.spaceShip, self.player)
                        self.score = Score()
                        self.ammoDisp = AmmoDisplay(self.shGun.MAXAMMO)
                        self.runGameLoop()
                        play = self.menu()
                #scores = open('highscore.txt', 'w')
                #for score in self.highscores:
                #        scores.write(str(score) + "\n")
                        
        def createBackground(self):
                self.background = []
                self.background.append(Background(80, 0))
                self.background.append(Background(0, 0))
                self.background.append(Background(0, 30))
                self.background.append(Background(70, 20))
                self.background.append(Background(100, 40))
                self.background.append(Background(110, 10))

        def instructions(self):
                
                self.stdscr.erase()
                self.stdscr.border(0)
                self.stdscr.addstr(3, 5, "Controls")
                self.stdscr.addstr(5, 10, "Use the arrow keys to move")
                self.stdscr.addstr(7, 10, "Press p to pause the game")
                self.stdscr.addstr(9, 10, "TIP: Pausing the game allows the user to switch")
                self.stdscr.addstr(10, 15, "between moving vertically or horizontally")
                self.stdscr.addstr(12, 10, "TIP: You can exit the game prematurely through")
                self.stdscr.addstr(13, 15, "the pause menu")
                self.stdscr.addstr(20, 10, "Press Any Key To Continue")
                self.stdscr.refresh()
                while(True):
                        choice = self.stdscr.getch()
                        s1.sendInput("3")
                        otherChoice = s1.otherInput() #check if other player exited
                        otherChoice = int(otherChoice)
                        if otherChoice == -1:
                                message(self, "Network Error")
                                sys.exit(1)
                        elif otherChoice == 5:
                                message(self, "Other player chose to exit.")
                                return False
                        if(choice != -1):
                                return True

        def highscore(self):
                line = 1
                self.stdscr.erase()
                self.stdscr.border(0)
                self.stdscr.addstr(3, 5, "Highscores")
                for score in self.highscores: 
                        self.stdscr.addstr(line * 2 + 3, 10, str(score))
                        line += 1

                self.stdscr.addstr(20, 10, "Press Any Key To Continue")
                self.stdscr.refresh()
                while True:
                        choice = self.stdscr.getch()
                        s1.sendInput("4")
                        otherChoice = s1.otherInput() #check if other player exited
                        otherChoice = int(otherChoice)
                        if otherChoice == -1:
                                message(self, "Network Error")
                                sys.exit(1)
                        elif otherChoice == 5:
                                message(self, "Other player chose to exit.")
                                return False
                        if(choice != -1):
                                return True
                        
             
        def menu(self):
                global NO_DEC
                NO_DEC = "0"
                choice = 1
                otherplayer = 0 #status of other player (0 means in this menu other numbers mean their corresponding menu)
                #continue playing until the player chooses to exit
                while(True):
                        s1.sendInput(NO_DEC) #send no decision signal
                        otherChoice = s1.otherInput() #check if other player made a decision
                        otherChoice = int(otherChoice)
                        if otherChoice == -1:
                                message(self, "Network Error")
                                sys.exit(1)
                        elif otherChoice == 1:
                                option = choose(self, "Other player want's to be player 1, do you want to be player 2?")
                                s1.sendInput(str(option))
                                if(option == 8):
                                        self.player = 1
                                        return True
                        elif otherChoice == 2:
                                option = choose(self, "Other player want's to be player 2, do you want to be player 1?")
                                s1.sendInput(str(option))
                                if(option == 8):
                                        self.player = 0
                                        return True
                        elif otherChoice == 3: #set status to menu 3
                                otherplayer = 3
                        elif otherChoice == 4: #set status to menu 4
                                otherplayer = 4
                        elif otherChoice == 5:
                                message(self, "Other player chose to exit.")
                                return False
                        elif otherChoice == 0: #set status back to this menu
                                otherplayer = 0
                        
                        self.stdscr.erase()
                        self.stdscr.border(0)
                        self.stdscr.addstr(3, 5, "What do you want to do?")
                        self.stdscr.addstr(choice * 2 + 3, 9, ">", curses.A_BLINK)
                        self.stdscr.addstr(5, 10, "Play as Player 1")
                        self.stdscr.addstr(7, 10, "Play as Player 2")
                        self.stdscr.addstr(9, 10, "Instructions")
                        self.stdscr.addstr(11, 10, "Highscores")
                        self.stdscr.addstr(13, 10, "Exit")
                        self.stdscr.refresh()

                        key = self.stdscr.getch()
                        if(key == curses.KEY_UP):
                                if(choice > 1):
                                        choice -= 1
                        if(key == curses.KEY_DOWN):
                                if(choice < 5):
                                        choice += 1
            
                        #made a decision so check other player
                        if(key == curses.KEY_ENTER or key == 10 or key == 13):
                                otherChoice = 0 #equil to int(NO_DEC) so that if other player is in a seperate
                                                #menu, when they return and send a NO_DEC signal the while
                                                #and if statements wont get tripped up in choice 1 and 2

                                s1.sendInput(str(choice))
                                if choice == 1 or choice == 2:
                                        if otherplayer == 3:
                                                message(self, "Other player is looking at the instructions, please wait")
                                        elif otherplayer == 4:
                                                message(self, "Other player is looking at the highscores, please wait")
                                                
                                        #wait for input
                                        while(otherChoice == 0):
                                                otherChoice = int(s1.otherInput())
                                                if otherChoice == -1:
                                                        message(self, "Network Error")
                                                        sys.exit(1)
                                                elif otherChoice == 8:
                                                        if choice == 1:
                                                                self.player = 0
                                                        else:
                                                                self.player = 1
                                                        return True
                                                elif otherChoice == 9:
                                                        message(self, "Other player doesn't want to play yet")
                                                elif otherChoice == 10:
                                                        message(self, "Other player did not respond")
                                                elif otherChoice == 0:
                                                        #if other player was in a different menu and returned then reset there status
                                                        otherplayer = 0
                                                elif otherChoice != 3 and otherChoice != 4: #concurrent input so make the guest wait 1 seconds and exit the loop
                                                      #and make the host resend the confirmation request
                                                        if s1.status == "guest":
                                                                time.sleep(1)
                                                                otherChoice = 1
                                                        else:
                                                                s1.sendInput(str(choice))
                                                                otherChoice = 0

                                elif choice == 3:
                                        if self.instructions() == False:
                                                return False
                                elif choice == 4:
                                        if self.highscore() == False:
                                                return False
                                elif choice == 5:
                                        return False
    
        def render(self):
                self.stdscr.erase()
                for b in self.background:
                        #needs to be b.drawClouds for one level and b.drawBackground for another level
                        b.drawAsteroids() 
                self.score.printScore()
                self.ammoDisp.printAmmoCount(self.shGun.getAvailAmmo())
                self.spaceShip.drawShip()
                for oid , obj in ACTIVELIST.items():
                        if(obj != None):
                                obj.draw(FRAMECOUNT)
                curses.panel.update_panels()
                self.stdscr.refresh()   
                
        def update(self):
                for oid , obj in ACTIVELIST.items():
                        if(obj != None):
                                if(not obj.move()):
                                        obj.remove()
                                        ACTIVELIST[oid] = None
                                
        def runGameLoop(self):
                currentTime = time.perf_counter()
                lag = 0.0
                global FRAMECOUNT
                
                while(self.userInput.processInput()):#get user input
                #Update loop----------------------------------------
                        newTime = time.perf_counter()
                        elapsedTime = newTime - currentTime
                        currentTime = newTime
                        lag += elapsedTime
                        
                        while(lag >= self.dt):
                                #update()
                                self.update()
                                self.t += self.dt
                                lag -= self.dt
                                FRAMECOUNT = FRAMECOUNT + 1
                #render()-------------------------------------------
                        self.render()
                #---------------------------------------------------
                lowScore = self.score.getPoints()
                for score in range(len(self.highscores)):
                        if self.highscores[score] < lowScore:
                                temp = self.highscores[score]
                                self.highscores[score] = lowScore
                                lowScore = temp
 
                curses.endwin()



#####################################################################################
### Start up the host server 
#####################################################################################
class HostSocket:
        status = "host"

        def __init__(self, seed):
                ### Retrieve the server socket information from text file
                self.serverFile = open("serverinfo.txt", "r")
                self.server = self.serverFile.readline().strip()
                self.port = self.serverFile.readline().strip()
                self.port = int(self.port)
                self.serverFile.close()

                self.hostsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.hostsocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                self.hostsocket.connect((self.server, self.port))

                ### Store this port to use to connect to the guest later
                self.hostPort = self.hostsocket.getsockname()[1]
                self.hostName = socket.gethostname()

                ### This will be modified later to use a menu system
                self.testName = input("What is your host name? ")
                self.hostIdentifier = '!host'
                self.hostsocket.send(self.hostIdentifier.encode("ascii"))
                self.serverMsg = self.hostsocket.recv(3).decode("utf-8").strip()
                if self.serverMsg == '!':
                        self.hostsocket.send(self.testName.encode("ascii"))

                self.hostsocket.shutdown(socket.SHUT_RDWR)
                self.hostsocket.close()

                ### Start waiting for a guest to connect
                self.hostsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

                ### Allow the socket to reuse the port without waiting for natural timeout
                self.hostsocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                self.hostsocket.bind((self.hostName, self.hostPort))
                self.hostsocket.listen(1)

                (self.guestsocket, self.address) = self.hostsocket.accept()

                random.seed(seed)
                self.seed = str(seed)
                self.guestsocket.send(self.seed.encode("ascii"))

        def otherInput(self):
                return self.guestsocket.recv(4096).decode("utf-8")

        def sendInput(self, myInput):
                self.myInput = str(myInput)
                self.guestsocket.send(self.myInput.encode("ascii"))

class GuestSocket:
        status = "guest"

        def __init__(self):
                self.serverFile = open("serverinfo.txt", "r")
                self.server = self.serverFile.readline().strip()
                self.port = self.serverFile.readline().strip()
                self.port = int(self.port)
                self.serverFile.close()

                self.guestsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.guestsocket.connect((self.server, self.port))

                #send guest identifier
                self.guestIdentifier = "guest"
                self.guestsocket.send(self.guestIdentifier.encode("ascii"))

                #get the list of host names from the server
                self.hostNames = self.guestsocket.recv(4096).decode("utf-8").strip()
                print("guest: list of hostnames: " + self.hostNames)

                self.hostChoice = input("Enter host name to join: ")

                self.guestsocket.send(self.hostChoice.encode("ascii"))
                self.rawHostAddress = self.guestsocket.recv(4096).decode("utf-8").strip()
                print("guest: received host address " + self.rawHostAddress + " from server.")

                self.guestsocket.close()
                self.portFlag = True
                self.hostAddress = ""
                self.hostPort = ""
                for x in self.rawHostAddress:
                        if x in "() '\n\t":
                                continue
                        elif x == ',':
                                self.portFlag = False
                        else:
                                if self.portFlag:
                                        self.hostAddress += x
                                else:
                                        self.hostPort += x

                self.guestsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.guestsocket.connect((self.hostAddress, int(self.hostPort)))
                self.seed = self.guestsocket.recv(4096).decode("utf-8")
                self.seed = float(self.seed)
                random.seed(self.seed)

        def otherInput(self):
                return self.guestsocket.recv(4096).decode("utf-8")

        def sendInput(self, myInput):
                self.myInput = str(myInput)
                self.guestsocket.send(self.myInput.encode("ascii"))

### Temporary argument parser will be used until the network and menu system is integrated
parser = argparse.ArgumentParser(description="Enter 'host' or 'join'")
parser.add_argument('action', metavar='P', type=str, help='Host or join a game.')
args = parser.parse_args()

if args.action == "host":
        seed = time.clock()
        s1 = HostSocket(seed)
        gl = GameLoop(s1)
        curses.wrapper(gl.startGame)
elif args.action == "join":
        s1 = GuestSocket()
        gl = GameLoop(s1)
        curses.wrapper(gl.startGame)
else:
        print("Invalid argument. Use argument 'host' or 'join'.")

