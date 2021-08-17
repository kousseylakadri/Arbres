OPTIONS=-O2
#OPTIONS = -std=c++11 -g -O0 -Wall
all : exam

exam : exam.cpp arbreavl.h pile.h tableau.h liste.h graphe.h arbreavl.h arbremap.h
	g++ ${OPTIONS} -o exam exam.cpp 
	
# date.o : date.cpp date.h
# 	g++ ${OPTIONS} -c -o date.o date.cpp

# journal.o : journal.cpp journal.h date.h arbreavl.h
# 	g++ ${OPTIONS} -c -o journal.o journal.cpp

# testdate : testdate.cpp date.o
# 	g++ $(OPTIONS) -o testdate testdate.cpp date.o

run:
	./exam
clean:
	rm -rf exam *~ *.o 