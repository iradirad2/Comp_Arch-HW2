cacheSim: cacheSim.cpp
	g++ -std=c++11 -g -Wall -o cacheSim cacheSim.cpp

.PHONY: clean
clean:
	rm -f *.o
	rm -f cacheSim
