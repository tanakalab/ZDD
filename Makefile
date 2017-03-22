VPATH = src include
CPPFLAGS = -I include

CXX = g++ -O3 -Wall -Wextra -pedantic -std=c++0x -lm  # O は最適化用 
#CXX = g++ -g3 -Wall -Wextra -pedantic -std=c++0x -lm 

#zdd: main.o tools.o run.o rule.o rulelist.o classbench_rule.o classbench_rulelist.o header.o rbt.o mrt.o dtree.o
zdd: main.o node.o
	g++ -O3 -Wall -Wextra -pedantic -std=c++0x -lm main.o node.o -o zdd
#	g++ -g3 -Wall -Wextra -pedantic -std=c++0x -lm main.o tools.o run.o rule.o rulelist.o classbench_rule.o classbench_rulelist.o header.o rbt.o mrt.o dtree.o -o dtree

clean:
	rm -rf *.o *.dSYM
