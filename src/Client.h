//client.h
#include "TCPSocket.cpp"

class Client{
	public:
	TCPSocket client;
	
	Client();
	
	void ListenForInput();
	void UploadFile(string fileName);

};