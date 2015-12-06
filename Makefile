
CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD -O2  -DPAD
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = main.o groupoff.o watCard.o watCardOffice.o student.o bank.o parent.o nameServer.o vendingMachine.o bottlingPlant.o truck.o
EXECS = 1soda				# all executables

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

${EXECS} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $< -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC01} ${EXECS} ImplType
