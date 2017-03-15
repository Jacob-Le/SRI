//Server.h

#include "TCPServerSocket.h"
#include "SRI.cpp"

class Server{
	public:
	TCPServer server;
	
	map<int,SRI> SRIMap;
};