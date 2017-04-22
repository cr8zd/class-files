 #!/usr/bin/env python3

import curses , curses.panel  
import time 
import random
import sys, socket, signal, select, termios, tty, argparse, errno

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
        
    def __init__(self, s1):
        self.player = -1
        self.myInput = -1
        #Elapsed Game time
        self.t = 0.0 
        #Time in milliseconds between frame render 
        #Frame renders every 20ms (50 FPS)
        self.dt = 0.03
        self.FPS = (1 / self.dt)

    def startGame(self , stdscr):
        self.stdscr = stdscr
        play = self.menu()
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
            play = self.menu()
    
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
        self.myInput = self.stdscr.getch()
        if self.player == 0:
            if self.myInput != curses.KEY_RIGHT and self.myInput != curses.KEY_LEFT and self.myInput != 112:
                self.myInput = -1
        elif self.player == 1:
            if self.myInput != curses.KEY_UP and self.myInput != curses.KEY_DOWN and self.myInput != 112:
                self.myInput = -1

        self.otherInput = s1.otherInput()
        self.otherInput = int(self.otherInput)
        s1.sendInput(self.myInput)

        if (self.myInput != -1 or self.otherInput != -1):
            if (self.myInput == curses.KEY_RIGHT or self.otherInput == curses.KEY_RIGHT):
                self.spaceShip.moveRight(self.max_x)
                #send move to player 1
            if (self.myInput == curses.KEY_LEFT or self.otherInput == curses.KEY_LEFT):
                self.spaceShip.moveLeft(self.max_x)
                #send move to player 1
            if (self.myInput == curses.KEY_UP or self.otherInput == curses.KEY_UP):
                self.spaceShip.moveUp(self.max_y)
                #send move to player 0
            if (self.myInput == curses.KEY_DOWN or self.otherInput == curses.KEY_DOWN):
                self.spaceShip.moveDown(self.max_y)
                #send move to player 0
            if self.myInput == 112 or self.otherInput == 112: #button is p
                cont = self.pause()

                ####### Send return to main menu signal ######
                if cont == -1:
                    return False
                    #return to main menu
                    
            #self.spaceShip.updatePos(self.myInput, self.otherInput , self.max_x , self.max_y)
        return True
                    
    def pause(self):
        cont = False
        otherCont = False
        choice = 1
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
                    
            self.choice = str(choice)

            if choice == 1:
                s1.sendInput(self.choice)
                self.cont = True
                self.otherCont = s1.otherInput()
                if self.otherCont == "True":
                    self.otherCont = True
                if self.cont and self.otherCont:
                    return 1
            elif choice == 2:
                s1.sendInput(self.choice)
                #if other player confirmed switching controls
                self.swapPlayer()
                #if other player did not confirm then say so and continue pausing
            elif choice == 3:
                s1.sendInput(self.choice)
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

    def choose(self, msg):
        choice = 1
        while(1):
            self.stdscr.erase()
            self.stdscr.addstr(3, 5, msg)
            self.stdscr.addstr(choice * 2 + 3, 9, ">", curses.A_BLINK)
            self.stdscr.addstr(5, 10, "Yes")
            self.stdscr.addstr(7, 10, "No")
            self.stdscr.addstr(9, 10, str(choice))
            self.stdscr.refresh()
            key = self.stdscr.getch()
            if(key == curses.KEY_UP):
                if(choice == 2):
                    choice -= 1
            if(key == curses.KEY_DOWN):
                if(choice == 1):
                    choice += 1
            
            if(key == curses.KEY_ENTER or key == 10 or key == 13):
                return choice

    def message(self, msg):
        self.stdscr.erase()
        self.stdscr.addstr(3, 5, msg)
        self.stdscr.refresh()
        key = self.stdscr.getch()        

    def menu(self):
        choice = 1
        player = 0
        otherPlayer = 0

        #continue playing until the player chooses to exit
        while(True):
            #get input
            self.stdscr.erase()
            self.stdscr.border(0)
            self.stdscr.addstr(3, 5, "What do you want to do?")
            self.stdscr.addstr(choice * 2 + 3, 9, ">", curses.A_BLINK)
            self.stdscr.addstr(5, 10, "Play as Player 1")
            self.stdscr.addstr(7, 10, "Play as Player 2")
            #self.stdscr.addstr(9, 10, "Highscores - Press 3")
            #self.stdscr.addstr(11, 10, "Instructions - Press 4")
            #self.stdscr.addstr(13, 10, "Exit - Press 5")
            self.stdscr.addstr(9, 10, "Instructions")
            self.stdscr.addstr(11, 10, "Exit")
            self.stdscr.refresh()
            
            key = self.stdscr.getch()
            #check if other player has input 
            #if otherChoice is 0, there is no input
            #ignore if otherChoice is 3
            otherChoice = s1.otherInput()
            otherChoice = int(otherChoice)
            if otherChoice == -1:
                self.message("Network Error")
                return False
            if otherChoice == 1:
                option = self.choose("Other player want's to be player 1, do you agree?")
                strOption = str(option)
                s1.sendInput(strOption)
                if(option == 1):
                    self.player = 1
                    return True                   
            elif otherChoice == 2:
                option = self.choose("Other player want's to be player 2, do you agree?")
                if(option == 1):
                    s1.sendInput("1")
                    self.player = 0
                    return True
                else:
                    s1.sendInput("0")
            elif otherChoice == 4:
                self.message("Other player choose to exit.")
                return False
            
            if(key == curses.KEY_UP):
                if(choice > 1):
                    choice -= 1
            if(key == curses.KEY_DOWN):
                if(choice < 4):
                    choice += 1
            
            if(key == curses.KEY_ENTER or key == 10 or key == 13):
                self.choice = str(choice)
                s1.sendInput(self.choice)

                if choice == 1:
                    otherChoice = 0
                    #wait for input
                    while(otherChoice == 0):
                        otherChoice = s1.otherInput()
                        otherChoice = int(otherChoice)
                        if otherChoice == -1:
                            self.message("Network Error")
                            return False
                        elif otherChoice == 1:
                            self.player = 0
                            return True
                elif choice == 2:
                    otherChoice = 0
                    #wait for input
                    while(otherChoice == 0):
                        otherChoice = s1.otherInput()
                        otherChoice = int(otherChoice)
                        if otherChoice == -1:
                            self.message("Network Error")
                            return False
                        elif otherChoice == 1:
                            self.player = 1
                            return True
                #elif choice == 51:
                #       call highscores menu
                elif choice == 3:
                    self.instructions()
                elif choice == 4:
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
                    if(self.myInput == 112 or self.otherInput == 112):
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

        self.guestsocket, self.address = self.hostsocket.accept()
        self.guestsocket.setblocking(False)

        random.seed(seed)
        self.seed = str(seed)
        self.guestsocket.send(self.seed.encode("ascii"))

    def otherInput(self):
        try:
            msg = self.guestsocket.recv(4096)
        except socket.timeout:
            return "0"
        except socket.error as e:
            err = e.args[0]
            if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
                return "0"
            return msg.decode("utf-8")
        else:
            if len(msg) == 0:
                return -1
            return msg.decode("utf-8")

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
        self.guestsocket.setblocking(False)
        
    def otherInput(self):
        try:
            msg = self.guestsocket.recv(4096)
        except socket.timeout:
            return "0"
        except socket.error as e:
            err = e.args[0]
            if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
                return "0"
            return msg.decode("utf-8")
        else:
            if len(msg) == 0:
                return -1
            return msg.decode("utf-8")

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
