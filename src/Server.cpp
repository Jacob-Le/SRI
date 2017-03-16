//Server.cpp
#include "Server.h"
#include <iostream>
using namespace std;

Sever::Sever(const char * _address, int _port, int _backlog){
	server = TCPServerSocket(_address,_port,_backlog);
}

void Sever::Daemon(){
	server = TCPServerSocket("0.0.0.0",9999,100);
	server.initializeSocket();
	for( ;; ){
		TCPSocket* tcpSocket = server.getConnection();
		if(tcpSocket == NULL) break;
		int maxBytes = 1024;
		char buffer[maxBytes];
		memset(buffer,0,maxBytes);
		int bytes_read =  tcpSocket->readFromSocket(buffer, maxBytes);
		cout << buffer;
		
		if(buffer[0] == 'a') buffer[0] = 'b';
		int bytes_sent = tcpSocket->writeToSocket(buffer, maxBytes);
		cout << buffer;
		tcpSocket->shutDown();
	  //check if Socket in map
	    //if not add new (ID,Socket) to map
	  //access Socket from map
	  //do thing and send string back if needed
	}
}

int main(){
	Sever* serve = new Sever("0.0.0.0",9999,100);
	//Server* serve = new Server();
	serve->Daemon();
}

