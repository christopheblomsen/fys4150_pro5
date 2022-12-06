##
# Project 5
#
# @file
# @version 0.1

all: compile link clean

utils:
	g++ -c -I include src/utils.cpp

full:
	g++ -c -I include main.cpp

compile: utils full

link:
	g++ -o main main.o utils.o -larmadillo

clean:
	@rm -rf *.o


# end
