#!/usr/bin/env python3

import curses , curses.panel  
import time 
import random

#Make class abstract so it can't be instantiated (later)
class GameObject:
	def __init__(self , panH , panW):
		self.window = curses.newwin(panH , panW , 0 , 0)
		self.panel = curses.panel.new_panel(self.window)
		self.state = {'x' : 0.0 , 'y' : 0.0 , 'vx' : 0.0 , 'vy' : 0.0}

	def setXPos(self , x):
		self.state['x'] = x
		
	def setYPos(self , y):	
		self.state['y'] = y
		
	def setXYPos(self , x , y):
		setXPos(x)
		setYPos(Y)
		
	def setXVel(self , vx):
		self.state['vx'] = vx
		
	def setYVel(self , vy):
		self.state['vy'] = vy
				
	def getXPos(self):
		return self.state['x']

	def getYPos(self):
		return self.state['y']
		
	def getXYPos(self):
		return self.state['x'] , self.state['y']

	def getXVel(self):
		return self.state['vx']
		
	def getYVel(self):
		return self.state['vy']
		
	def getXYVel(self):
		return self.state['vx'] , self.state['vy']
		
	def setState(self , x , y , vx , vy):
		self.setXPos(x)
		self.setYPos(y)
		self.setXVel(vx)
		self.setYVel(vy)

	def movePos(self):
		self.panel.move(int(self.state['y']) , int(self.state['x']))
	#return True is outside boundary, otherwise False	
	def boundaryCheck(self , max_x , max_y):  
		if(self.state['y'] < 0):
			return True
		elif(self.state['y'] + self.window.getyx()[0] >= max_y):
			return True
		elif(self.state['x'] < 0):
			return True
		elif(self.state['x'] + self.window.getmaxyx()[1] >= max_x):
			return True
		return False

#make into signleton?
class Spaceship():
	panWidth = 7
	panHeight = 5
	
	def __init__(self , x , y):
		self.x = x
		self.y = y
		self.shipWin = curses.newwin(Spaceship.panHeight , Spaceship.panWidth , y , x)
		self.shipPan = curses.panel.new_panel(self.shipWin)
		 
	def updatePos(self , q , max_x , max_y):
		if(q == ord('w') and self.y > 0):
			self.y -= 1
		elif(q == ord('s') and self.y < max_y - self.shipWin.getmaxyx()[0]):
			self.y += 1
		elif(q == ord('a') and self.x > 0):
			self.x -= 1
		elif(q == ord('d') and self.x < max_x - self.shipWin.getmaxyx()[1]):
			self.x += 1
		self.shipPan.move(self.y , self.x)
	
	def drawShip(self):	
		self.shipWin.addstr(0 , 0 , '  /^\\ ' , curses.color_pair(1));
		self.shipWin.addstr(1 , 0 , ' ||_|| ' , curses.color_pair(1));
		self.shipWin.addstr(2 , 0 , '< /_\\ >' , curses.color_pair(1));
		self.shipWin.addstr(3 , 0 , ' ^^^^^ ' , curses.color_pair(2));		


class Asteroid(GameObject):
	panWidth = 4
	panHeight = 4
	
	def __init__(self):
			super().__init__(Asteroid.panHeight , Asteroid.panWidth)
			
	def draw(self):		
		self.window.addstr(0 , 0 , '/Oo\\' , curses.color_pair(3))
		self.window.addstr(1 , 0 , 'OO0o' , curses.color_pair(3))
		self.window.addstr(2 , 0 , '\\0o/ ' , curses.color_pair(3))
		
#WORKING ON THIS RIGHT NOW (10/26/2016)	-------------------------------------------------------	
class GameObjectLogic():
	
	def __init__(self , max_x , max_y):
		self.max_x = max_x
		self.max_y = max_y 
		self.count = 0.0
		self.spawnLineCoord = max_y
		self.minSpawnLine = int(max_y * 0.15)
		self.gameObjsDict = {}
		self.gameObjClassNames = [c.__name__ for c in GameObject.__subclasses__()]
	
	def createGameObjs(self):
		for cNameStr in self.gameObjClassNames:
			self.gameObjsDict[cNameStr] = {"active" : [] , "inactive" : []}
			clazz = globals()[cNameStr]
			numObjsToFillScr = (self.max_x // clazz.panWidth)
			self.gameObjsDict[cNameStr]['numActiveObjs'] = 0 
			self.gameObjsDict[cNameStr]['numInactiveObjs'] = numObjsToFillScr
			for i in range(0 , numObjsToFillScr*2): #prob change this calc
				self.gameObjsDict[cNameStr]["inactive"].append(clazz())
		
	
	def spawn(self , className , start_x):
		spawnStack = self.gameObjsDict[className.__name__]['inactive']
		newSpawn = spawnStack.pop()
		newSpawn.panel.show()
		self.gameObjsDict[className.__name__]['numInactiveObjs'] -= 1
		self.gameObjsDict[className.__name__]['numActiveObjs'] += 1
		self.gameObjsDict[className.__name__]['active'].append(newSpawn)
		newSpawn.panel.move(0 , start_x)
		newSpawn.setXPos(start_x)
		newSpawn.setYVel(12)
		
	def kill(self , obj):
		className = obj.__class__.__name__
		obj.setState(0 , 0 , 0 , 0)
		obj.panel.hide()
		deadObjIndex = self.gameObjsDict[className]['active'].index(obj)
		deadObj = self.gameObjsDict[className]['active'].pop(deadObjIndex)
		self.gameObjsDict[className]['inactive'].append(deadObj)
		self.gameObjsDict[className]['numInactiveObjs'] += 1
		self.gameObjsDict[className]['numActiveObjs'] -= 1
		
	def chooseSpawnVector(self , className , spawnVectToUse):
		maxVSP = self.max_x - className.panWidth 
		if((spawnVectToUse % 4) == 0):
			return [maxVSP // 3 , 2 * (maxVSP // 3)]
		elif((spawnVectToUse % 4) == 1):
			return [maxVSP // 4 , maxVSP // 2 , 3 * (maxVSP // 4)]
		elif((spawnVectToUse % 4) == 2):
			r = int(maxVSP / 5)
			return [r , 2 * r , 3 * r , 4 * r]
		elif((spawnVectToUse % 4) == 3):
			return [random.randrange(maxVSP)]
		
	def runVectSpawn(self , t , dt , className , gt):
		#self.spawn(className , int(self.max_x / 2))
		if((0 <= t) and (t <= 0.25 * gt)):
			tbs = 4
		elif((0.25 * gt < t) and (t <= 0.5 * gt)):
			tbs = 3
		elif((0.5 * gt < t) and (t <= 0.75 * gt)):
			tbs = 2
		elif((0.75 * gt < t) and (t <= gt)):
			tbs = 1
		elif(t > gt):
			tbs = 0.5
		
		self.count += dt	
		if(tbs <= self.count):
			self.count = 0 
			spVec = self.chooseSpawnVector(className , random.randrange(0 , 4))
			for i in spVec:
				self.spawn(className , i)
#-----------------------------------------------------------------------------------------------
class PhysicsEngine():
	
	def __init__(self , max_x , max_y):
		self.max_x = max_x
		self.max_y = max_y
	
	def applyKinematics(self , gameObj , updateTimeDelta):
		gameObj.state['x'] += (gameObj.state['vx'] * updateTimeDelta)
		gameObj.state['y'] += (gameObj.state['vy'] * updateTimeDelta)	
			
	def runPhysics(self , activeObjects , ss , dt , func):
		for o in activeObjects:
			self.applyKinematics(o , dt)
			self.checkForCollision(ss , o , func)
				
	def checkForCollision(self , ss , obj , func):
		if(ss.shipWin.enclose(int(obj.getYPos()) , int(obj.getXPos()))):
			func(obj)
		#if(obj.window.enclose(ss.y , ss.x)):
		#	func(obj)
	
#------------------------------------------------------------------------------------------------

#make into singleton?
class GameLoop:
	
	def __init__(self):
		self.userInput = -1
		#Elapsed Game time
		self.t = 0.0 
		#Time in milliseconds between frame render 
		#Frame renders every 20ms (50 FPS)
		self.dt = 0.03
		self.FPS = (1 / self.dt)
		
	def startGame(self , stdscr):
		self.stdscr = stdscr
		self.stdscr.nodelay(1)
		self.max_y , self.max_x = stdscr.getmaxyx()
		self.configureCursesSettings()
		self.createPlayer()
		self.pe = PhysicsEngine(self.max_x , self.max_y)
		self.runGameLoop()
	
	def configureCursesSettings(self):
		curses.init_pair(1 , curses.COLOR_RED , curses.COLOR_BLACK)
		curses.init_pair(2 , curses.COLOR_YELLOW , curses.COLOR_BLACK)
		curses.init_pair(3 , curses.COLOR_CYAN , curses.COLOR_BLACK)
		curses.curs_set(0)
		
	def createPlayer(self):
		self.spaceShip = Spaceship(int(self.max_x/2) , int(self.max_y/2))
		
	def processInput(self):
		self.userInput = self.stdscr.getch()
		self.spaceShip.updatePos(self.userInput , self.max_x , self.max_y)

	def render(self , gol):
		self.stdscr.erase()
		self.spaceShip.drawShip()
		
		for o in gol.gameObjsDict['Asteroid']['active']:
			if(o.boundaryCheck(self.max_x , self.max_y)):
				gol.kill(o)
			else:
				o.movePos()
				o.draw()
			
		curses.panel.update_panels()
		self.stdscr.refresh()	
	
	def runGameLoop(self):
		currentTime = time.perf_counter()
		lag = 0.0
		
		
		gol = GameObjectLogic(self.max_x , self.max_y)
		gol.createGameObjs()
		
		while(self.userInput != ord('q')):
		#process input--------------------------------------
			self.processInput()
		#Update loop----------------------------------------
			newTime = time.perf_counter()
			elapsedTime = newTime - currentTime
			currentTime = newTime
			lag += elapsedTime
			
			while(lag >= self.dt):			 
				#update()
				self.t += self.dt
				lag -= self.dt
				gol.runVectSpawn(self.t , self.dt , Asteroid , 60)
				self.pe.runPhysics(gol.gameObjsDict['Asteroid']['active'] , self.spaceShip , self.dt , gol.kill)


		#render()-------------------------------------------
			
			self.render(gol)
			
		curses.endwin()

gl = GameLoop()
curses.wrapper(gl.startGame)  
