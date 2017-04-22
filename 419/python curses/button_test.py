#!/usr/bin/python3

#start up curses
import curses

HEIGHT = 24
WIDTH = 80
TESTING = True

curses.initscr()
stdscr = curses.newwin(HEIGHT, WIDTH, 0, 0)
curses.noecho() #don't echo keys
stdscr.keypad(1)

#function for displaying other players decision
#statement is the number of the other player's death funciton returned
#player is the other player's name
#returns 0 if other player choose to play again and this player doesn't
#want to, if player does want to then returns 1
#returns -1 if other player choose to quit to main menu
def decision(statement, player):
    stdscr.clear()
    stdscr.border(0)
    stdscr.timeout(-1)
    decision = "play again" if statement == 1 else "return to main menu"
    stdscr.addstr(3, 5, "Your Partner has decided to " + decision)
    if statement == 1:
        stdscr.addstr(5, 10, "Do you want to play again?")
        stdscr.addstr(7, 10, "Press y for yes and n for no")
        stdscr.refresh()
        while True:
            choice = stdscr.getch()
            if choice == 110: #choice is n
                return 0
            elif choice == 121: #choice is y
                return 1
    elif statement == 0:
        stdscr.addstr(5, 5, "You will be taken back to the main menu.")
        return -1

#funciton for waiting screen for starting a game as player 1
#takes other player's name
#returns 0 if player wants to return to main menu
#returns 1 if player wants to play again
#returns -1 if while loop is exited (which shouldn't happen)
def death(player):
    stdscr.clear()
    stdscr.border(0)
    stdscr.timeout(100)
    stdscr.addstr(3, 5, "You have died. What do you want to do?")
    stdscr.addstr(5, 10, "Play Again - Press p")
    stdscr.addstr(7, 10, "Return to Main Menu - Press r")
    stdscr.refresh()
    while True:
        #if other player already made a decision
        #   statement = other player's decision
        #   choice = decision(statement, player)
        #   if statement == 1:
        #       send choice to other player
        #   if choice == 0 or choice == -1:
        #       return 0
        #   elif choice == 1:
        #       return 1
        choice = stdscr.getch()
        #send choice to other player
        if choice == 114: #choice is r
            return 0
        elif choice == 112: #choice is p
            #choice = get decision back from other player
            #if choice == 1:
                #print message saying other player agrees to play again
                return 1
            #elif choice == 0
                #print message saying other player quit to main menu
                #return 0

    return -1

#funciton for waiting screen for starting a game as player 1
#returns 0 if player wants to return to main menu
#returns 1 if a 1st player is chosen
#returns -1 if while loop is exited (which shouldn't happen)
def join():
    stdscr.clear()
    stdscr.border(0)
    stdscr.timeout(-1)
    stdscr.addstr(3, 5, "Pick a player to join")
    #get list of available players from the server
    #loop through them all and display them (maybe only the first 10)
    #make a counter for the addstr y value and increment by 2 each loop
    stdscr.addstr(5, 10, "Return to Main Menu - Press r")
    stdscr.refresh()
    while True:
        choice = stdscr.getch()

        if choice == 114: #choice is r
            return 0
        #elif check if a first player has been chosen
        #   send this player's name to first player
        #   get back first player's name
        #   return 1

    return -1

#funciton for waiting screen for starting a game as player 1
#returns 0 if player wants to return to main menu
#returns 1 if a second player is chosen
#returns -1 if while loop is exited (which shouldn't happen)
def start():
    stdscr.clear()
    stdscr.border(0)
    stdscr.timeout(100)
    stdscr.addstr(3, 5, "Waiting for 2nd player")
    stdscr.addstr(5, 10, "Return to Main Menu - Press r")
    stdscr.refresh()
    while True:
        choice = stdscr.getch()

        if choice == 114: #choice is r
            return 0
        #elif check if a second player has been chosen
        #   get second player's name
        #   send this player's name
        #   return 1

    return -1

def pause():
    stdscr.clear()
    stdscr.border(0)
    stdscr.timeout(-1)
    stdscr.addstr(3, 5, "Paused. What do you want to do?")
    stdscr.addstr(5, 10, "Continue - Press c")
    stdscr.addstr(7, 10, "Swap Controls - Press s")
    stdscr.addstr(9, 10, "End Game - Press e")
    stdscr.refresh()
    while True:
        choice = stdscr.getch()
        if choice == 99: #choice is c
            return 1
        elif choice == 115: #choice is s
            return 0
        elif choice == 101: #choice is e
            return -1
    
    return 1

def menu(name):
    stdscr.clear()
    stdscr.border(0)
    stdscr.timeout(-1)
    stdscr.addstr(3, 5, name + ", what do you want to do?")
    stdscr.addstr(5, 10, "Play new game - Press 1")
    stdscr.addstr(7, 10, "Exit - Press 4")
    stdscr.refresh()
    choice = stdscr.getch()

    stdscr.clear()
    stdscr.border(0)
    if choice == 49: #choice is 1
        return 1
    elif choice == 52: #choice is 4
        return 0
    
    return 1

play = menu("HOPPY")
c = 1
x = 25
y = 12
player = 0
while play:
    if TESTING:
        stdscr.clear()
        stdscr.border(0)
        stdscr.addstr(y, x, str(c))

    stdscr.timeout(100)
    button = stdscr.getch()
    if button != -1:
        if button == curses.KEY_RIGHT and player == 0:
            x += 1
            if x >= WIDTH - 1:
                x -= 1
        elif button == curses.KEY_LEFT and player == 0:
            x -= 1
            if x <= 0:
                x += 1
        elif button == curses.KEY_UP and player == 1:
            y -= 1
            if y <= 0:
                y += 1
        elif button == curses.KEY_DOWN and player == 1:
            y += 1
            if y >= HEIGHT - 1:
                y -= 1
        if button == 112: #button is p
            cont = pause()
            if cont == -1:
                c = 1
                player = 0
                play = menu("HOPPY")
            elif cont == 0:
                player = (player + 1) % 2
    if TESTING:
        c += 1
stdscr.keypad(0)
curses.echo()
curses.endwin()






#curse.wrapper([funciton]) sets up and exits curses for you, function is the
                          #code the runs in curses

#initialize curses
#curses.noecho() #don't echo keys
#curses.cbreak() or curses.raw() #react instantly to keys, raw doesn't ignore
                                 #CTRL-Z(suspend) and CTRL-C(exit)
#stdscr.keypad(1) #read navigation key sequences for me


#deinitialize curses
#curses.nocbreak(); stdscr.keypad(0); curses.echo()

#exit curses
#curses.endwin()
