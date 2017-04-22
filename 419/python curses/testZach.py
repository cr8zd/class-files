#!/usr/bin/env python3
#AUTHOR: Zach Barnes

import curses , curses.panel  
import time 
import random
import sys
from threading import Thread
import threading
import collections

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
                if(self.panel.hidden()):
                        self.panel.show()
                try:    
                        self.panel.move(int(self.coords.getYPos()) , int(self.coords.getXPos()))
                except:
                        pass
class Animation():
        
        def __init__(self, fpa , drawOrder , panH , panW , startX, startY , gop=None):
                if(gop == None):
                        self.gop = GameObjectPanel(panH , panW , startX , startY)
                else:
                        self.gop = gop
                self.totalFrameCount = 0 
                self.fpa = fpa
                self.frRemToDraw = fpa
                self.currentDraw = 0 #--> Index into drawOrder of the current frame to draw
                self.drawOrder = drawOrder #--> List of functions , each function draws a unique sequence of characters / colors
                l = len(self.drawOrder)
                self.lastDrawIndex = l - 1
                self.singleRunFrameCount = l * fpa 
                self.setStartFrame() #get the current frame number 

        def setStartFrame(self):
                global FRAMECOUNT
                #self.startFrame = FRAMECOUNT
                self.curFrame = FRAMECOUNT
                
        def resetTotalFrameCount(self):
                self.totalFrameCount = 0
                
        def draw(self , newFrame):
                if(self.frRemToDraw > 0):
                        #if((self.currentDraw == 0) and (self.frRemToDraw == self.fpa)): 
                        #       self.gop.panel.show()
                        self.drawOrder[self.currentDraw]()
                else:
                        if(self.currentDraw < self.lastDrawIndex):
                                self.currentDraw += 1
                                #self.frRemToDraw = self.fpa
                                self.drawOrder[self.currentDraw]()
                        else:
                                self.currentDraw = 0
                        self.frRemToDraw = self.fpa
                if(self.curFrame < newFrame):
                        self.frRemToDraw -= 1
                        self.curFrame += 1
                        self.totalFrameCount += 1

class Explosion(Animation):
        panWidth = 5
        panHeight = 5
        
        def __init__(self, startX , startY , fpa):
                drawOrder = [self.draw1 , self.draw2 , self.draw2 , self.draw3]
                super(Explosion , self).__init__(fpa , drawOrder , 5 , 5 , startX , startY)

        def draw0(self):
                self.window.addch(2 , 3 , '@' , curses.color_pair(2))           

        def draw1(self):
                self.gop.window.addch(1 , 3 , '#' , curses.color_pair(2))
                self.gop.window.addch(2 , 2 , '#' , curses.color_pair(2))
                self.gop.window.addch(2 , 3 , '@' , curses.color_pair(1))
                self.gop.window.addch(2 , 4 , '#' , curses.color_pair(2))
                self.gop.window.addch(3 , 3 , '#' , curses.color_pair(2))
        
        def draw2(self):
                self.gop.window.addch(0 , 3 , '@' , curses.color_pair(2))
                self.gop.window.addch(1 , 2 , '@' , curses.color_pair(2))
                self.gop.window.addch(1 , 3 , '#' , curses.color_pair(1))
                self.gop.window.addch(1 , 4 , '@' , curses.color_pair(2))
                self.gop.window.addch(2 , 2 , '#' , curses.color_pair(1))
                self.gop.window.addch(2 , 3 , '@' , curses.color_pair(2))
                self.gop.window.addch(2 , 4 , '#' , curses.color_pair(1))
                self.gop.window.addch(3 , 2 , '@' , curses.color_pair(2))
                self.gop.window.addch(3 , 3 , '#' , curses.color_pair(1))
                self.gop.window.addch(3 , 4 , '@' , curses.color_pair(2))
                self.gop.window.addch(4 , 3 , '@' , curses.color_pair(2))
                
        def draw3(self):
                self.gop.window.addch(0 , 3 , '*' , curses.color_pair(3))
                self.gop.window.addch(1 , 2 , '*' , curses.color_pair(3))
                self.gop.window.addch(1 , 3 , '*' , curses.color_pair(4))
                self.gop.window.addch(1 , 4 , '*' , curses.color_pair(3))
                self.gop.window.addch(2 , 2 , '*' , curses.color_pair(4))
                self.gop.window.addch(2 , 3 , '*' , curses.color_pair(3))
                self.gop.window.addch(2 , 4 , '*' , curses.color_pair(4))
                self.gop.window.addch(3 , 2 , '*' , curses.color_pair(3))
                self.gop.window.addch(3 , 3 , '*' , curses.color_pair(4))
                self.gop.window.addch(3 , 4 , '*' , curses.color_pair(3))
                self.gop.window.addch(4 , 3 , '*' , curses.color_pair(3))
                
class ShipExplosion(Animation):
        panWidth = 9
        panHeight = 9
        
        def __init__(self, startX , startY , fpa):
                drawOrder = [self.draw0 , self.draw1 , self.draw2 , 
                                         self.draw3 , self.draw4 , self.draw3 , 
                                         self.draw2 , self.draw1 , self.draw0]
                super(ShipExplosion , self).__init__(fpa , drawOrder , 9 , 9 , startX , startY)

        def draw0(self):
                self.gop.window.addch(4 , 4 , '@' , curses.color_pair(2))               

        def draw1(self):
                self.gop.window.addch(3 , 4 , '#' , curses.color_pair(2))
                self.gop.window.addch(4 , 3 , '#' , curses.color_pair(2))
                self.gop.window.addch(4 , 4 , '@' , curses.color_pair(1))
                self.gop.window.addch(4 , 5 , '#' , curses.color_pair(2))
                self.gop.window.addch(5 , 4 , '#' , curses.color_pair(2))
        
        def draw2(self):
                self.gop.window.addch(2 , 4 , '@' , curses.color_pair(2))
                self.gop.window.addch(3 , 3 , '@' , curses.color_pair(2))
                self.gop.window.addch(3 , 4 , '#' , curses.color_pair(1))
                self.gop.window.addch(3 , 5 , '@' , curses.color_pair(2))
                self.gop.window.addch(4 , 2 , '@' , curses.color_pair(2))
                self.gop.window.addch(4 , 3 , '#' , curses.color_pair(1))
                self.gop.window.addch(4 , 4 , '@' , curses.color_pair(2))
                self.gop.window.addch(4 , 5 , '#' , curses.color_pair(1))
                self.gop.window.addch(4 , 6 , '@' , curses.color_pair(2))
                self.gop.window.addch(5 , 3 , '@' , curses.color_pair(2))
                self.gop.window.addch(5 , 4 , '#' , curses.color_pair(1))
                self.gop.window.addch(5 , 5 , '@' , curses.color_pair(2))
                self.gop.window.addch(6 , 4 , '@' , curses.color_pair(2))

        def draw3(self):
                self.gop.window.addch(2 , 3 , '#' , curses.color_pair(1))
                self.gop.window.addch(2 , 4 , '@' , curses.color_pair(2))
                self.gop.window.addch(2 , 5 , '#' , curses.color_pair(1))
                self.gop.window.addch(3 , 2 , '#' , curses.color_pair(1))
                self.gop.window.addch(3 , 3 , '@' , curses.color_pair(2))
                self.gop.window.addch(3 , 4 , '#' , curses.color_pair(1))
                self.gop.window.addch(3 , 5 , '@' , curses.color_pair(2))
                self.gop.window.addch(3 , 6 , '#' , curses.color_pair(1))
                self.gop.window.addch(7 , 4 , '#' , curses.color_pair(1))
                self.gop.window.addch(1 , 4 , '#' , curses.color_pair(1))
                self.gop.window.addch(4 , 1 , '#' , curses.color_pair(1))
                self.gop.window.addch(4 , 2 , '@' , curses.color_pair(2))
                self.gop.window.addch(4 , 3 , '#' , curses.color_pair(1))
                self.gop.window.addch(4 , 4 , '@' , curses.color_pair(2))
                self.gop.window.addch(4 , 5 , '#' , curses.color_pair(1))
                self.gop.window.addch(4 , 6 , '@' , curses.color_pair(2))
                self.gop.window.addch(4 , 7 , '#' , curses.color_pair(1))
                self.gop.window.addch(5 , 2 , '#' , curses.color_pair(1))
                self.gop.window.addch(5 , 3 , '@' , curses.color_pair(2))
                self.gop.window.addch(5 , 4 , '#' , curses.color_pair(1))
                self.gop.window.addch(5 , 5 , '@' , curses.color_pair(2))
                self.gop.window.addch(5 , 6 , '#' , curses.color_pair(1))
                self.gop.window.addch(6 , 3 , '#' , curses.color_pair(1))
                self.gop.window.addch(6 , 4 , '@' , curses.color_pair(2))
                self.gop.window.addch(6 , 5 , '#' , curses.color_pair(1))
                
        def draw4(self):
                self.gop.window.addstr(2 , 0 , ' * *  * *' , curses.color_pair(4))
                self.gop.window.addstr(3 , 0 , ' *      *' , curses.color_pair(4))
                self.gop.window.addstr(4 , 0 , '    *' , curses.color_pair(4))
                self.gop.window.addstr(5 , 0 , ' *      *' , curses.color_pair(4))
                self.gop.window.addstr(6 , 0 , ' * *  * *' , curses.color_pair(4))

class Asteroid(Animation):
        panWidth = 4
        panHeight = 4
        deltaPerFrame = .2
        fpa = 19
        
        def __init__(self , startX , startY , container = None):
                self.container = container
                drawOrder = [self.draw0 , self.draw1]
                super(Asteroid , self).__init__(Asteroid.fpa , drawOrder , Asteroid.panHeight , Asteroid.panWidth , startX , startY)
                self.gop.coords.setYDelta(Laser.deltaPerFrame)
                        
        def setContainer(self , container):
                self.container = container
        
        def setFireLocation(self , startX , startY):
                self.gop.coords.setXYPos(startX , startY)
                self.gop.movePanelPos()
                self.isInBounds = True
                
        def remove(self):
                if(self.container != None):
                        self.container.append(self)
                        self.isInBounds = False
                        self.gop.window.erase()
                        self.gop.coords.setXYPos(0 , 0)
                        self.gop.movePanelPos()
                                        
        def move(self):
                self.isInBounds = self.gop.coords.moveDown(Asteroid.deltaPerFrame)
                self.gop.movePanelPos()
                return self.isInBounds  
                
        def collisionCheck(self , obj):
                #maybe check both sides of cell
                oX , oY = obj.gop.coords.getXYPos()
                return self.gop.window.enclose(int(oY) ,int(oX))
                        
        def draw0(self):
                self.gop.window.addch(0 , 0 , '/' , curses.color_pair(2))
                self.gop.window.addch(1 , 0 , '0' , curses.color_pair(2))
                self.gop.window.addch(2 , 0 , 'o' , curses.color_pair(3))
                self.gop.window.addch(3 , 0 , '\\' , curses.color_pair(2))
                self.gop.window.addch(0 , 1 , 'O' , curses.color_pair(3))
                self.gop.window.addch(1 , 1 , 'O' , curses.color_pair(3))
                self.gop.window.addch(2 , 1 , '0' , curses.color_pair(2))
                self.gop.window.addch(3 , 1 , 'o' , curses.color_pair(3))
                self.gop.window.addch(0 , 2 , '\\' , curses.color_pair(2))
                self.gop.window.addch(1 , 2 , '0' , curses.color_pair(2))
                self.gop.window.addch(2 , 2 , 'o' , curses.color_pair(3))
                self.gop.window.addch(3 , 2 , '/' , curses.color_pair(2))

        def draw1(self):
                self.gop.window.addch(0 , 0 , '/' , curses.color_pair(2))
                self.gop.window.addch(1 , 0 , '0' , curses.color_pair(2))
                self.gop.window.addch(2 , 0 , 'o' , curses.color_pair(3))
                self.gop.window.addch(3 , 0 , '\\' , curses.color_pair(2))
                
                self.gop.window.addch(0 , 1 , 'O' , curses.color_pair(3))
                self.gop.window.addch(1 , 1 , 'O' , curses.color_pair(3))
                self.gop.window.addch(2 , 1 , '0' , curses.color_pair(2))
                self.gop.window.addch(3 , 1 , 'o' , curses.color_pair(3))
                
                self.gop.window.addch(0 , 2 , '\\' , curses.color_pair(2))
                self.gop.window.addch(1 , 2 , '0' , curses.color_pair(2))
                self.gop.window.addch(2 , 2 , 'o' , curses.color_pair(3))
                self.gop.window.addch(3 , 2 , '/' , curses.color_pair(2))
                
                
class Spawner():

        def spawnFunc(self, t , minTbs):
                tbs = 3*((self.gt - t) / self.gt)
                if(tbs <= minTbs):
                        tbs = minTbs
                return tbs 
        
        def __init__(self , gametime , className):
                global MAX_X
                self.count = 0
                self.numVecs = 5
                self.className = className
                self.maxSpawnPoint = MAX_X - self.className.panWidth 
                self.gt = gametime
                self.objsToSpawnList = []
                for a in range((MAX_X // self.className.panWidth) * (MAX_Y // self.className.panHeight)):
                        self.objsToSpawnList.append(self.className(0 , 0 , self.objsToSpawnList))
                
                def initializeSpawnVectors(self):
                        spawnVectToUse = random.randrange(0 , 5)
                        maxVSP = self.maxSpawnPoint
                        w = self.className.panWidth 
                        self.spawnVec0 = [x for x in range(0 , maxVSP - w) if x % (w * 7) == 0]
                        self.spawnVec1 = [x for x in range(0 , maxVSP - w) if x % (w * 6) == 0]
                        self.spawnVec2 = [x for x in range(0 , maxVSP - w) if x % (w * 4) == 0]
                        self.spawnVec3 = [x for x in range(0 , maxVSP - w) if x % (w * 3) == 0]
                        self.spawnVec4 = [1 , random.randrange(w * 2 , maxVSP - w * 2) , maxVSP - 1]
                initializeSpawnVectors(self)

        def chooseSpawnVector(self):
                global MAX_X
                spawnVectToUse = random.randrange(0 , 5)
                maxVSP = self.maxSpawnPoint
                
                def shiftVector(vect):
                        randStart = random.randrange(maxVSP)
                        i = 0
                        for x in vect:
                                vect[i] = ((x + randStart) % maxVSP)
                                i += 1
                        return vect
                
                if((spawnVectToUse % self.numVecs) == 0):
                        return shiftVector(self.spawnVec0)
                elif((spawnVectToUse % self.numVecs) == 1):
                        return shiftVector(self.spawnVec1)
                elif((spawnVectToUse % self.numVecs) == 2):
                        return shiftVector(self.spawnVec2)
                elif((spawnVectToUse % self.numVecs) == 3):
                        return shiftVector(self.spawnVec3)
                elif((spawnVectToUse % self.numVecs) == 4):
                        return self.spawnVec4
        
        #check to see if it is time to spawn vector of objects , return True , else False
        def isTimeToSpawn(self , dt , t):
                self.count += dt        
                if(self.spawnFunc(t , .5) <= self.count):
                        self.count = 0
                        return True
                return False
        
        def spawnSingleObject(self):
                try:
                        o = self.objsToSpawnList.pop()
                except IndexError:
                        #lazy instantiation, should never happen but here just in case
                        o = self.className(0 , 0 , self.objsToSpawnList)
                return o
                
        def spawnObjects(self):
                global ACTIVEOBJECTSET , GAMEOBJECTDICT
                for startX in self.chooseSpawnVector():
                        obj = self.spawnSingleObject()
                        obj.setFireLocation(startX , 0)
                        ACTIVEOBJECTSET.add(id(obj))
                        GAMEOBJECTDICT[id(obj)] = obj
                        
class Laser(Animation):
        panWidth = 1
        panHeight = 1
        fpa = 4
        deltaPerFrame = 1
        
        def __init__(self , startX , startY , container = None):
                self.container = container
                drawOrder = [self.draw0 , self.draw1]
                super(Laser , self).__init__(Laser.fpa , drawOrder , Laser.panHeight , Laser.panWidth , startX , startY)
                self.gop.coords.setYDelta(Laser.deltaPerFrame)
                
        def setContainer(self , container):
                self.container = container
        
        def setFireLocation(self , startX , startY):
                self.gop.coords.setXYPos(startX , startY)
                self.gop.movePanelPos()
                self.isInBounds = True
                
        def remove(self):
                if(self.container != None):
                        self.container.append(self)
                        self.isInBounds = False
                        self.gop.window.erase()
                        self.gop.coords.setXYPos(0 , 0)
                        self.gop.movePanelPos()
                                        
        def move(self):
                self.isInBounds = self.gop.coords.moveUp()
                self.gop.movePanelPos()
                return self.isInBounds  
        
        def draw0(self):
                try:
                        #self.gop.window.erase()
                        self.gop.window.addstr(0 , 0 , '^' , curses.color_pair(4)|curses.A_BOLD|curses.A_UNDERLINE)             
                except curses.error:
                        pass
                        
        def draw1(self):
                try:    
                        #self.gop.window.erase()
                        self.gop.window.addstr(0 , 0 , '^' , curses.color_pair(5)|curses.A_BOLD)        
                except curses.error:
                        pass

#afterburner is a little fucked , need to fix animation class
class AfterBurner(Animation):
        fpa = 5
        deltaPerFrame = 1
                
        def __init__(self, gop):
                drawOrder = [self.draw0 , self.draw1 , self.draw2 , self.draw3 , self.draw4 , self.draw5]
                super(AfterBurner , self).__init__(AfterBurner.fpa, drawOrder , 0 , 0 , Spaceship.panHeight , Spaceship.panWidth , gop) 
                
        def draw0(self):
                try:
                        self.gop.window.addstr(3 , 0 , ' \\^^^/' , curses.color_pair(1)|curses.A_BOLD)          
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
                self.activeLaserSet = set()
                self.activeLaserCount = len(self.activeLaserSet)
                for laz in range(self.MAXAMMO*2):
                        self.ammo.append(Laser(0 , 0 , self.ammo))
                self.availAmmo = self.MAXAMMO
                self.ammoReload = Thread(target=self.loadAmmo , args=(1,) , daemon=True)
                self.ammoReload.start()
        
        def removeLaser(self , l):
                self.activeLaserSet.discard(id(l))
                self.activeLaserCount -= 1
                
        def addLaser(self , l):
                self.activeLaserSet.add(id(l))
                self.activeLaserCount += 1
                
        def getAvailAmmo(self):
                return self.availAmmo

        def shoot(self , fireX , fireY):
                global ACTIVEOBJECTSET , GAMEOBJECTDICT
                if(self.availAmmo > 0):
                        try:
                                l = self.ammo.pop()
                        except IndexError:
                                #lazy instantiation, should never happen but here just in case
                                l = Laser(0 , 0 , self.ammo)
                        l.setFireLocation(fireX , fireY)
                        ACTIVEOBJECTSET.add(id(l))
                        GAMEOBJECTDICT[id(l)] = l
                        self.addLaser(l)
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
                self.burnerFlag = False
                self.ssMaxX = MAX_X - Spaceship.panWidth
                self.ssMaxY = MAX_Y + Spaceship.panHeight
                self.gun = Gun()
                if self.gop.panel.hidden(): self.gop.panel.show()
                
        def shootLaser(self):
                #Add 3 to correctly align laser with ship
                self.gun.shoot(self.gop.coords.getXPos() + 3 , self.gop.coords.getYPos())
                
        def moveLeft(self):
                self.gop.coords.moveLeft(Spaceship.XMOVE)
                self.burnerFlag = False
                
        def moveRight(self):
                self.gop.coords.moveRight(Spaceship.XMOVE)
                self.burnerFlag = False
                
        def moveForward(self):
                self.gop.coords.moveUp(Spaceship.YMOVE)
                self.burnerFlag = False
                
        def moveBack(self):
                self.gop.coords.moveDown(Spaceship.YMOVE)
                self.burnerFlag = False
                
        def boostLeft(self):
                self.gop.coords.moveLeft(Spaceship.XBOOST)
                self.burnerFlag = True
                
        def boostRight(self):
                self.gop.coords.moveRight(Spaceship.XBOOST)
                self.burnerFlag = True
                
        def boostForward(self):
                self.gop.coords.moveUp(Spaceship.YBOOST)
                self.burnerFlag = True

        def boostBack(self):
                self.gop.coords.moveDown(Spaceship.YBOOST)
                self.burnerFlag = True
                
        def collisionCheck(self , obj):
                oX , oY = obj.gop.coords.getXYPos()
                x_1 = oX 
                y_1 = oY + 1
                x_2 = oX + obj.gop.panW
                y_2 = oY + 1

                if(self.gop.window.enclose(int(y_1) ,int(x_1))):
                        return True
                else:
                        return self.gop.window.enclose(int(y_2) ,int(x_2))
                
        def drawShip(self):
                global FRAMECOUNT 
                self.gop.movePanelPos()
                self.gop.window.addstr(0 , 2 , '/^\\ ' , curses.color_pair(5)|curses.A_BOLD)
                self.gop.window.addch(1 , 1 , '|' , curses.color_pair(5)|curses.A_BOLD)
                self.gop.window.addch(2 , 1 , '|' , curses.color_pair(4)|curses.A_BOLD)
                self.gop.window.addch(3 , 1 , '+' , curses.color_pair(4)|curses.A_BOLD)
                self.gop.window.addch(4 , 1 , '|' , curses.color_pair(4)|curses.A_BOLD)
                self.gop.window.addch(5 , 1 , '|' , curses.color_pair(5)|curses.A_BOLD)
                self.gop.window.addch(0 , 2 , '<' , curses.color_pair(5)|curses.A_BOLD)
                self.gop.window.addstr(2 , 2 , '/_\\' , curses.color_pair(3)|curses.A_BOLD)
                self.gop.window.addch(6 , 2 , '>' , curses.color_pair(5)|curses.A_BOLD)
                self.burner.draw(FRAMECOUNT)
                if(not self.burnerFlag):
                        self.gop.window.addstr(3 , 0 , '      ' , curses.color_pair(3)|curses.A_BOLD)
                        self.gop.window.addstr(4 , 0 , '      ' , curses.color_pair(3)|curses.A_BOLD)
                        self.gop.window.addstr(5 , 0 , '      ' , curses.color_pair(3)|curses.A_BOLD)
                
class Input():
        
        def __init__(self , stdscr , spaceShip):
                self.stdscr = stdscr
                self.spaceShip = spaceShip
                self.cmd = -1
        
        def getCmd(self):
                cmd = self.stdscr.getch()
                if(cmd != -1):
                        if(cmd == ord('q') or cmd == ord('Q')):
                                return False
                        self.processInput(cmd)
                return True
                                
        def processInput(self , cmd):
                if(cmd >= ord('A') and cmd <= ord('Z')):
                        if(cmd == ord('A')):
                                self.spaceShip.boostLeft()
                        elif(cmd == ord('D')):
                                self.spaceShip.boostRight()
                        elif(cmd == ord('S')):
                                self.spaceShip.boostBack()
                        elif(cmd == ord('W')):
                                self.spaceShip.boostForward()
                elif(cmd >= ord('a') and cmd <= ord('z')):
                        if(cmd == ord('a')):
                                self.spaceShip.moveLeft()
                        elif(cmd == ord('d')):
                                self.spaceShip.moveRight()
                        elif(cmd == ord('s')):
                                self.spaceShip.moveBack()
                        elif(cmd == ord('w')):
                                self.spaceShip.moveForward()
                else:
                        if(cmd == 32):
                                self.spaceShip.shootLaser()
                
class Score():
        
        def __init__(self):
                global MAX_X
                self.score = 0
                self.panHeight = 3
                self.panWidth = 12
                self.window = curses.newwin(self.panHeight , self.panWidth , 0 , MAX_X - self.panWidth)
                self.panel = curses.panel.new_panel(self.window)
                
        def addPoints(self , points):
                self.score = self.score + points
                
        def printScore(self):
                self.window.box()
                scoreStr = str(FRAMECOUNT)
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

                
class GameLoop:
        
        def __init__(self):
                self.t = 0.0
                self.dt = 0.02
                #self.frameCount = 0
                
        def startGame(self , stdscr):
                global MAX_X , MAX_Y , GAMEOBJECTDICT , ACTIVEOBJECTSET , FRAMECOUNT
                FRAMECOUNT = 0
                GAMEOBJECTDICT = {}
                ACTIVEOBJECTSET = set()
                self.stdscr = stdscr
                self.stdscr.nodelay(1)
                self.stdscr.keypad(1)
                curses.init_pair(1 , curses.COLOR_RED , curses.COLOR_BLACK)
                curses.init_pair(2 , curses.COLOR_YELLOW , curses.COLOR_BLACK)
                curses.init_pair(3 , curses.COLOR_CYAN , curses.COLOR_BLACK)
                curses.init_pair(4 , curses.COLOR_WHITE , curses.COLOR_BLACK)
                curses.init_pair(5 , curses.COLOR_GREEN , curses.COLOR_BLACK)
                curses.init_pair(6 , curses.COLOR_GREEN , curses.COLOR_GREEN)
                curses.curs_set(0)
                #----------------------------------------------------------------------
                MAX_Y , MAX_X = stdscr.getmaxyx()

                self.asteroidSpawner = Spawner(60 , Asteroid) #60 is desired gametime
                self.spaceShip = Spaceship(int(MAX_X/2) , int(MAX_Y/2))
                self.shGun = self.spaceShip.gun
                self.userInput = Input(stdscr , self.spaceShip)
                self.score = Score()
                self.ammoDisp = AmmoDisplay(self.shGun.MAXAMMO)
                #---------------
                self.renderSet = set()
                self.explosions  = [Explosion(0 , 0 , 16) for i in range(20)]
                #---------------

                self.runGameLoop()

        def render(self , rd):
                global FRAMECOUNT
                #self.stdscr.erase()
                self.score.printScore()
                self.ammoDisp.printAmmoCount(self.shGun.getAvailAmmo())
                self.spaceShip.drawShip()
                for oid in ACTIVEOBJECTSET:
                        GAMEOBJECTDICT[oid].draw(FRAMECOUNT)
                removeAnimationList = []
                for anim in rd:
                        if(anim.totalFrameCount > anim.singleRunFrameCount):
                                removeAnimationList.append(anim)
                        else:
                                try:
                                        anim.draw(FRAMECOUNT)
                                except:
                                        pass
                for a in removeAnimationList:
                        if(isinstance(a , ShipExplosion)):
                                a.gop.panel.hide()
                                del(a)
                        else:   
                                a.gop.window.erase()
                                a.gop.coords.setXYPos(0 , 0)
                                a.gop.movePanelPos()
                                a.gop.panel.hide()
                                a.resetTotalFrameCount()
                                rd.discard(a)
                                self.explosions.append(a)
                curses.panel.update_panels()
                self.stdscr.refresh()   
                
        #"active" = object is currently on the screen (coordinates have not been attempted to be moved outside of the max screen dimensions)
        def update(self):
                global FRAMECOUNT
                if(self.asteroidSpawner.isTimeToSpawn(self.dt , self.t)):
                        self.asteroidSpawner.spawnObjects() #--> Spawn Asteroids
                asteroidIDsToRemove = set()
                laserIDsToRemove = set()
                for oid in ACTIVEOBJECTSET: #--> ACTIVEOBJECTSET contains all active objects (asteroids & lasers , not spaceship) 
                        obj = GAMEOBJECTDICT[oid] #--> Use instance ID to get object
                        ioob = obj.move() # --> move return status of obj: True = obj is in bounds , False = obj out of bounds
                        if(not ioob): # --> obj just moved out of bounds
                                if(isinstance(obj , Laser)):
                                        laserIDsToRemove.add(oid)
                                elif(isinstance(obj , Asteroid)):
                                        asteroidIDsToRemove.add(oid)
                                        self.score.addPoints(5)
                        else: # --> obj still in bounds
                                if(isinstance(obj , Asteroid)):
                                        if(self.spaceShip.collisionCheck(obj)): #--> first check for obj collision with ship
                                                asteroidIDsToRemove.add(oid)
                                                x , y = self.spaceShip.gop.coords.getXYPos()
                                                se = ShipExplosion(x , y , 4)
                                                self.renderSet.add(se)
                                                return False
                                                #-----------------SPACESHIP DEAD HERE--------------------------------------------
                                        if(self.spaceShip.gun.activeLaserCount > 0): #--> Check if lasers are active 
                                                for lid in self.spaceShip.gun.activeLaserSet:
                                                        laz = GAMEOBJECTDICT[lid]
                                                        if(obj.collisionCheck(laz)):
                                                                x , y = obj.gop.coords.getXYPos()
                                                                asteroidIDsToRemove.add(oid)
                                                                laserIDsToRemove.add(lid)
                                                                e = self.explosions.pop()
                                                                e.gop.coords.setXYPos(x , y)
                                                                e.gop.movePanelPos()
                                                                if(e.gop.panel.hidden()): e.gop.panel.show()
                                                                self.renderSet.add(e)
                                                                self.score.addPoints(25) #--> add 25 points for destroying asteroid with laser

                for lazrID in laserIDsToRemove:
                        lazr = GAMEOBJECTDICT[lazrID]
                        self.spaceShip.gun.removeLaser(lazr)
                        lazr.remove()
                        ACTIVEOBJECTSET.discard(lazrID)
                for astID in asteroidIDsToRemove:
                        ast = GAMEOBJECTDICT[astID]
                        ast.remove()
                        ACTIVEOBJECTSET.discard(astID)
                return True
                        
        def runGameLoop(self):
                currentTime = time.perf_counter()
                lag = 0.0
                global FRAMECOUNT
                play = True
                died = False
                dieCount = 0
                while(play):
                        play = self.userInput.getCmd()
                #Update loop----------------------------------------
                        newTime = time.perf_counter()
                        elapsedTime = newTime - currentTime
                        currentTime = newTime
                        lag += elapsedTime
                        
                        while(lag >= self.dt):          
                                #update-------------------------------------
                                self.update()
                                self.t += self.dt
                                lag -= self.dt
                                FRAMECOUNT = FRAMECOUNT + 1
                #render()-------------------------------------------
                        self.render(self.renderSet)
                #---------------------------------------------------
                curses.endwin()

gl = GameLoop()
curses.wrapper(gl.startGame)
