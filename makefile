#makefile

make SRI:
	g++ -std=c++11 -pthread SRI.cpp -o SRI
	
make clean:
	rm SRI
