CFLAGS = -Wall -Wextra -DDEBUG -g -std=c++14

nadeem_p1: nadeem_p1.o
	g++ $(CFLAGS) nadeem_p1.o -o nadeem_p1

nadeem_p1.o: nadeem_p1.cpp
	g++ $(CFLAGS)  -c nadeem_p1.cpp -o nadeem_p1.o
	
clean: 
	rm -rf ./nadeem_p1 *.o
