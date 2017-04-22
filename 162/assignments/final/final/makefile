#########################################################
# File: Makefile
# Description: A more robust makefile for CS162.
# You need to edit the variables under "USER SECTION"
#########################################################

# #'s are line-comments 

# CXX is a standard variable name used for the compiler. 
CXX = g++

# CXXFLAGS is a standard variable name for compile flags.
# -std=c++0x specifies to use a certain language version.
CXX += -std=c++0x

# -Wall turns on all warnings
CXXFLAGS += -Wall

# -pedantic-errors strictly enforces the standard
CXXFLAGS += -pedantic-errors

# -g turns on debug information 
CXXFLAGS += -g

####################
### USER SECTION ###
####################

# SRCS is a standard name for the source files. 
# Edit as needed.
SRC1 = main.cpp
SRC2 = Bedroom.cpp
SRC3 = Food.cpp
SRC4 = Kitchen.cpp
SRC5 = response_check.cpp
SRC6 = Pack.cpp
SRCS = ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6}

# HEADERS is a standard name for the header files. 
# Edit these as needed.
HD1 = response_check.h
HD2 = Bedroom.h
HD3 = Elevator.h
HD4 = Food.h
HD5 = Guarded.h
HD6 = Hall.h
HD7 = Kitchen.h
HD8 = Pack.h
HD9 = Portal.h
HD10 = Room.h
HEADERS = ${HD1} ${HD2} ${HD3} ${HD4} ${HD5} ${HD6}
HEADERS += ${HD7} ${HD8} ${HD9} ${HD10}
# These will be your executable names. 
# Edit as needed.
PROG1 = escape
PROG2 = 
#PROG3 = 
PROGS = ${PROG1} ${PROG2} ${PROG3}

# This is the name of your document(s). 
# Edit as needed.
DOC1 = final_report.pdf
DOC2 = tests.pdf
DOCS = ${DOC1} ${DOC2}

# This is the name of your compressed file. 
# Edit name as needed. Keep the format.
TAR = cs162_final_frasej.tar.bz2

#####################
### BUILD SECTION ###
#####################

# Typing 'make' in terminal calls the first build availible.
# In this case, default.
default:
	${CXX} ${SRCS} ${HEADERS} -o ${PROG1}

# Typing 'make all' in terminal calls this build.
all:
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o ${PROG1}
 
# Typing 'make tar' in terminal calls this build.
# This creates a compressed file for submission.
tar:
	tar cvjf ${TAR} ${SRCS} ${HEADERS} ${DOCS}  makefile

# Typing 'make clean' calls this build.
# It's designed to clean up the folder.
# Be careful with this, edit as needed.
clean: 
	rm -f ${PROGS} *.o *~

${PROG1}:
	${CXX} ${SRCS} ${HEADERS} -o ${PROG1}
