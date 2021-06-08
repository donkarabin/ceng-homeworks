LDFLAGS=-std=c++11

all: ; g++ $(LDFLAGS) main.cpp Laptime.cpp Car.cpp Race.cpp Championship.cpp -o F1;
run: ; ./F1
valgrind: ; valgrind --leak-check=full ./F1
clean: ; rm -rf F1;
