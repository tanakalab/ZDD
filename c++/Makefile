VPATH = src include
CPPFLAGS = -I include

CXX = g++ -O3 -Wall -Wextra -pedantic -std=c++0x -lm  # O は最適化用 
#CXX = g++ -g3 -Wall -Wextra -pedantic -std=c++0x -lm 

zdd: main.o hash.o zdd.o
	g++ -O3 -Wall -Wextra -pedantic -std=c++0x -lm main.o hash.o zdd.o -o zdd
#	g++ -g3 -Wall -Wextra -pedantic -std=c++0x -lm main.o hash.o zdd.o -o zdd

clean:
	rm -rf *.o *.dSYM
