#!/usr/bin/env python3

import curses , curses.panel  
import time 
import random
import sys
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
		#	there will always be enough ammo objects 
		# 	available to shoot
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
		self.gop.window.addch(2 , 1 , '|' , curses.color_pair(4)|curses.A_BOLD)
		self.gop.window.addch(3 , 1 , '+' , curses.color_pair(4)|curses.A_BOLD)
		self.gop.window.addch(4 , 1 , '|' , curses.color_pair(4)|curses.A_BOLD)
		self.gop.window.addch(5 , 1 , '|' , curses.color_pair(5)|curses.A_BOLD)
		self.gop.window.addch(0 , 2 , '<' , curses.color_pair(5)|curses.A_BOLD)
		self.gop.window.addstr(2 , 2 , '/_\\ >' , curses.color_pair(3)|curses.A_BOLD)
		self.gop.window.addch(6 , 2 , '>' , curses.color_pair(5)|curses.A_BOLD)
		self.gop.window.addstr(3 , 0 , ' \\^^^/' , curses.color_pair(1)|curses.A_BOLD)
		self.burner.draw(FRAMECOUNT)	
		
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
		
	def addPoint(self , points):
		score =+ points
		
	def printScore(self):
		self.window.box()
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
		
		
class GameLoop:
	
	def __init__(self):
		self.t = 0.0
		self.dt = 0.02
		#self.frameCount = 0
		
	def startGame(self , stdscr):
		global MAX_X , MAX_Y , ACTIVELIST , FRAMECOUNT
		FRAMECOUNT = 0
		ACTIVELIST = {}
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
		self.spaceShip = Spaceship(int(MAX_X/2) , int(MAX_Y/2))
		self.shGun = self.spaceShip.gun
		self.userInput = Input(stdscr , self.spaceShip)
		self.score = Score()
		self.ammoDisp = AmmoDisplay(self.shGun.MAXAMMO)
		self.runGameLoop()

	def render(self):
		self.stdscr.erase()
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
		
		while(self.userInput.getCmd()):
		#process input--------------------------------------
			#self.userInput.processInput()
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
	
		curses.endwin()

gl = GameLoop()
curses.wrapper(gl.startGame)

