//client.h
#include "TCPSocket.cpp"

class Client{
	public:
	TCPSocket client;
	
	void UploadFile(string fileName);

};