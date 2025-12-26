cacheSim: cacheSim.cpp
	g++ -g -Wall -o cacheSim cacheSim.cpp cache.cpp

.PHONY: clean
clean:
	rm -f *.o
	rm -f cacheSim
