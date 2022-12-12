##
# Project 5
#
# @file
# @version 0.1

all: compile link clean run

utils:
	g++ -c -I include src/utils.cpp

box:
	g++ -c -I include src/box.cpp

full:
	g++ -c -I include main.cpp

compile: utils full box

link:
	g++ -o main main.o utils.o box.o -larmadillo

run:
	./main

clean:
	@rm -rf *.o


# end
