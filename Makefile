VPATH = src include
CPPFLAGS = -I include

#CXX = g++ -O3 -Wall -Wextra -pedantic -std=c++0x -lm  # O は最適化用 
CXX = g++ -g3 -Wall -Wextra -pedantic -std=c++0x -lm 

zdd: main.o nhash.o zdd.o
	g++ -g3 -Wall -Wextra -pedantic -std=c++0x -lm main.o nhash.o zdd.o -o zdd

clean:
	rm -rf *.o *.dSYM
