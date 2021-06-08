LDFLAGS=-std=c++11

all: ; g++ $(LDFLAGS) main.cpp Player.cpp Archer.cpp Fighter.cpp Priest.cpp Scout.cpp Tank.cpp Board.cpp Game.cpp InputParser.cpp -o game;
run: ; ./game
valgrind: ; valgrind --leak-check=full ./game
clean: ; rm -rf game;
