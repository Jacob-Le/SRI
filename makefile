#makefile

make SRI:
	g++ -std=c++11 -g -pthread SRI.cpp -o SRI

make clean:
	rm SRI
