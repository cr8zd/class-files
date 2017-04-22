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
class Background():
        panWidth = 86
        panHeight = 31

        def __init__(self , x , y):
                self.x = x
                self.y = y
                self.backWin = curses.newwin(Background.panHeight , Background.panWidth , y , x)
                self.backPan = curses.panel.new_panel(self.backWin)

        def drawStars(self, x, y):
                self.backWin.addstr(y, x, "  .       *             .   .")#36 across
                self.backWin.addstr(y+1, x, ".              +   /\\        *     .")
                self.backWin.addstr(y+2, x, "      .          <    >")
                self.backWin.addstr(y+3, x, "                 x \\/")
                self.backWin.addstr(y+4, x, "  *          .              +      *")
                self.backWin.addstr(y+5, x, "       .          .")
        
        def drawBackground(self):
                self.drawStars(0,0)
                self.drawStars(60,0)
                self.drawStars(15,9)
                self.drawStars(45,13)
                self.drawStars(7,20)       

#make into signleton?
class Spaceship():
        panWidth = 7
        panHeight = 5

        def __init__(self , x , y):
                self.x = x
                self.y = y
                self.shipWin = curses.newwin(Spaceship.panHeight , Spaceship.panWidth , y , x)
                self.shipPan = curses.panel.new_panel(self.shipWin)
                 
        def moveUp(self, max_y):
                if self.y > 0:
                        self.y -= 1
                self.shipPan.move(self.y , self.x)

        def moveDown(self, max_y):
                if(self.y < max_y - self.shipWin.getmaxyx()[0]):
                        self.y += 1
                self.shipPan.move(self.y , self.x)
                        
        def moveLeft(self, max_x):
                if(self.x > 0):
                        self.x -= 1
                self.shipPan.move(self.y , self.x)

        def moveRight(self, max_x):
                if(self.x < max_x - self.shipWin.getmaxyx()[1]):
                        self.x += 1
                self.shipPan.move(self.y , self.x)

        #def updatePos(self , q , max_x , max_y):
        #       if(q == ord('w') and self.y > 0):
        #               self.y -= 1
        #       elif(q == ord('s') and self.y < max_y - self.shipWin.getmaxyx()[0]):
        #               self.y += 1
        #       elif(q == ord('a') and self.x > 0):
        #               self.x -= 1
        #       elif(q == ord('d') and self.x < max_x - self.shipWin.getmaxyx()[1]):
        #               self.x += 1
        #       self.shipPan.move(self.y , self.x)
        
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
                
#WORKING ON THIS RIGHT NOW (10/26/2016) ------------------------------------------------------- 
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
                        if(self.checkForCollision(ss , o , func)):
                                return 0
                return 1
                                
        def checkForCollision(self , ss , obj , func):
                if(ss.shipWin.enclose(int(obj.getYPos()) + 1, int(obj.getXPos())) #check "bottom" left (hit right side of ship)
                    or ss.shipWin.enclose(int(obj.getYPos()) + 1, int(obj.getXPos()) + 3) #check "bottom" right (hit left side of ship)
                    or ss.shipWin.enclose(int(obj.getYPos()) + 2, int(obj.getXPos()) + 1)): #check "bottom" middle (hit front of ship)
                        func(obj)
                        return 1
                return 0
                        #if(obj.window.enclose(ss.y , ss.x)):
                        #   func(obj)
        
#------------------------------------------------------------------------------------------------

#make into singleton?
class GameLoop:
        
        def __init__(self):
                self.player = -1
                self.userInput = -1
                #Elapsed Game time
                self.t = 0.0 
                #Time in milliseconds between frame render 
                #Frame renders every 20ms (50 FPS)
                self.dt = 0.03
                self.FPS = (1 / self.dt)

        def startGame(self , stdscr):
                self.stdscr = stdscr
                play = self.menu("Hoppy")
                while(play):
                        self.t = 0.0 
                        self.dt = 0.03
                        self.FPS = (1 / self.dt)
                        self.stdscr.nodelay(1)
                        self.max_y , self.max_x = stdscr.getmaxyx()
                        self.configureCursesSettings()
                        self.createBackground()
                        self.createPlayer()
                        self.pe = PhysicsEngine(self.max_x , self.max_y)
                        self.runGameLoop()
                        play = self.menu("Hoppy")
        
        def configureCursesSettings(self):
                curses.init_pair(1 , curses.COLOR_RED , curses.COLOR_BLACK)
                curses.init_pair(2 , curses.COLOR_YELLOW , curses.COLOR_BLACK)
                curses.init_pair(3 , curses.COLOR_CYAN , curses.COLOR_BLACK)
                curses.curs_set(0)
                
        def createPlayer(self):
                self.spaceShip = Spaceship(int(self.max_x/2) , int(self.max_y/2))

        def createBackground(self):
                self.background = []
                self.background.append(Background(80, 0))
                self.background.append(Background(0, 0))
                self.background.append(Background(0, 30))
                self.background.append(Background(70, 20))
                self.background.append(Background(100, 40))
                self.background.append(Background(110, 10))
                
        def swapPlayer(self):
                self.player = (self.player + 1) % 2

        def processInput(self):
                #check if other player has input
                #if so call appropriate move function or pause the game
                self.userInput = self.stdscr.getch()
                if self.userInput != -1:
                        if self.userInput == curses.KEY_RIGHT and self.player == 0:
                                self.spaceShip.moveRight(self.max_x)
                                #send move to player 1
                        elif self.userInput == curses.KEY_LEFT and self.player == 0:
                                self.spaceShip.moveLeft(self.max_x)
                                #send move to player 1
                        elif self.userInput == curses.KEY_UP and self.player == 1:
                                self.spaceShip.moveUp(self.max_y)
                                #send move to player 0
                        elif self.userInput == curses.KEY_DOWN and self.player == 1:
                                self.spaceShip.moveDown(self.max_y)
                                #send move to player 0
                        elif self.userInput == 112: #button is p
                                #send pause signal to other player
                                cont = self.pause()
                                if cont == -1:
                                        return False
                                        #return to main menu
                                
                        #self.spaceShip.updatePos(self.userInput , self.max_x , self.max_y)
                return True
                        
        def pause(self):
                cont = False
                otherCont = False
                #continue getting input until the appropriate input is recieved
                while True:
                        #check if other player has input
                        #if input is to swap
                        #       ask if player wants to swap
                        #       send response to other player
                        #       if yes then swap player
                        #elif input is to exit
                        #       return -1
                        #elif input is continue
                        #       set otherCont to True
                        #       if otherCont and cont are both True
                        #               return 1
                        self.stdscr.erase()
                        self.stdscr.border(0)
                        self.stdscr.addstr(3, 5, "Player " + str(self.player + 1) + ", what do you want to do?")
                        self.stdscr.addstr(5, 10, "Continue - Press c")
                        self.stdscr.addstr(7, 10, "Swap Controls - Press s")
                        self.stdscr.addstr(9, 10, "End Game - Press e")
                        self.stdscr.refresh()
                        

                        choice = self.stdscr.getch()
                        if choice == 99: #choice is c
                                #send decision to other player
                                cont = True
                                #if cont and otherCont  ****(makes sure both are ready to continue)
                                return 1
                        elif choice == 115: #choice is s
                                #send choice to other player
                                #if other player confirmed switching controls
                                self.swapPlayer()
                                #if other player did not confirm then say so and continue pausing
                        elif choice == 101: #choice is e
                                #send decision to other player
                                return -1

        def instructions(self):
                while(True):
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
                        choice = self.stdscr.getch()
                        if(choice != -1):
                                return
                        



        def menu(self, name):
                #continue playing until the player chooses to exit
                while(True):
                        self.stdscr.erase()
                        self.stdscr.border(0)
                        self.stdscr.addstr(3, 5, name + ", what do you want to do?")
                        self.stdscr.addstr(5, 10, "Play new game - Press 1")
                        #self.stdscr.addstr(7, 10, "Join a player 1 - Press 2")
                        #self.stdscr.addstr(9, 10, "Highscores - Press 3")
                        #self.stdscr.addstr(11, 10, "Instructions - Press 4")
                        #self.stdscr.addstr(13, 10, "Exit - Press 5")
                        self.stdscr.addstr(7, 10, "Instructions - Press 4")
                        self.stdscr.addstr(9, 10, "Exit - Press 5")
                        self.stdscr.refresh()
                        choice = self.stdscr.getch()
                        if choice == 49: #choice is 1
                                self.player = 0
                                #if calling waiting for player menu returns 1
                                #       return True
                                #otherwise do nothing
                                return 1
                        #elif choice == 50:
                        #       self.player = 1
                        #       if calling pick a player menu returns 1
                        #               return True
                        #elif choice == 51:
                        #       call highscores menu
                        elif choice == 52: #choice is 4
                                self.instructions()
                        elif choice == 53: #choice is 5
                                return False
                

        def render(self , gol):
                self.stdscr.erase()
                for b in self.background:
                        b.drawBackground()
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

                play = True
                        
                gol = GameObjectLogic(self.max_x , self.max_y)
                gol.createGameObjs()
                        
                while(play):
                #process input--------------------------------------
                        play = self.processInput()
                        if(self.userInput == 112):
                                currentTime = time.perf_counter()
                                
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
                                if(self.pe.runPhysics(gol.gameObjsDict['Asteroid']['active'] , self.spaceShip , self.dt , gol.kill) == 0):
                                        play = False


                #render()-------------------------------------------
                        
                        self.render(gol)
                        
                curses.endwin()

gl = GameLoop()
curses.wrapper(gl.startGame)
