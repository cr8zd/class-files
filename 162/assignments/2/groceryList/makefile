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
CXXFLAGS = -std=c++0x

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
SRC1 = gameOfLife.cpp
SRC2 =
SRC3 =
SRC4 =
SRCS = ${SRC1} ${SRC2} ${SRC3}

# HEADERS is a standard name for the header files. 
# Edit these as needed.
HEADER1 = response_check.h
HEADER2 = int_check.h
#HEADER3 = 
HEADERS = ${HEADER1} ${HEADER2} ${HEADER3}

# These will be your executable names. 
# Edit as needed.
PROG1 = gameOfLife
PROG2 = 
#PROG3 = 
PROGS = ${PROG1} ${PROG2} ${PROG3}

# This is the name of your document(s). 
# Edit as needed.
DOC1 = Initial_thoughts.pdf
DOC2 = Game_of_Life_prereflextions.pdf
DOC3 = Game_of_Life.pdf
DOCS = ${DOC1} ${DOC2} ${DOC3}

# This is the name of your compressed file. 
# Edit name as needed. Keep the format.
TAR = cs162_assignment1_frasej.tar.bz2

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
