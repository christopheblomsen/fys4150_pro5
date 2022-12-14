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

PDESolver:
	g++ -c -I include src/PDESolver.cpp

full:
	g++ -c -I include main.cpp

compile: utils PDESolver box full

link:
	g++ -o main main.o utils.o box.o PDESolver.o -larmadillo -O2

plot_all:
	@shell_scripts/plot_all.sh

run:
	@shell_scripts/run_all.sh

animate:
	@shell_scripts/animate.sh

clean:
	@rm -rf *.o

# end
