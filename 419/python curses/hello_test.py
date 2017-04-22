#!/usr/bin/python3

#start up curses
import curses
stdscr = curses.initscr()

curses.noecho() #don't echo keys
stdscr.border(0)
stdscr.addstr(3, 5, "Paused. What do you want to do?")
stdscr.addstr(5, 10, "Continue - Press c")
stdscr.addstr(7, 10, "Swap Controls - Press s")
stdscr.addstr(9, 10, "End Game - Press e")
stdscr.refresh()
choice = stdscr.getch()

stdscr.clear()
stdscr.border(0)
if chr(choice) == 'c':
    stdscr.addstr(12, 25, "Conintued")
elif chr(choice) == 's':
    stdscr.addstr(12, 25, "Swapped Controls")
elif chr(choice) == 'e':
    stdscr.addstr(12, 25, "End Game")
else:
    stdscr.addstr(12, 25, "You pressed " + chr(choice))
stdscr.refresh()
stdscr.getch() #wait for input so user can see message
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
