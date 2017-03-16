#include <stdlib.h>
#include <iostream>
#include <thread>

//#include "Connection.h"
//#include "TCPServerSocket.h"

using namespace std;

void threadFunction(std::mutex * mtx, int x){
  mtx->lock()
  std::cout<< "thread" << x << std::endl;
}

//Attempts to manage threads via a bounded buffer class. Use in SRI.cpp
int main () {
  std::mutex mtx;
  //GarbageCollector * garbageCollector = new GarbageCollector();

  // Instantiate a new TCPSocketServer Object that listens on all insterfaces on port 9999
  // NOTE: the port number is irrelevant, as long as the client and server side have the same.  IP address should be 192.168.1.1
  //TCPServerSocket * tcpServerSocket = new TCPServerSocket("0.0.0.0",9999,100);

  try{
    // CREATE OBJECTS HERE

    //tcpServerSocket->initializeSocket();
    //for(;;){
      // Wait for connection and return a TCPSocket object upon one
      //TCPSocket * tcpSocket = tcpServerSocket->getConnection();
      //if (tcpSocket == NULL) break; // if tcpSocket is NULL then error occured and we break the loop
      //garbageCollector->cleanup();
      //Connection * c = new Connection (tcpSocket);
      //c->start();
      //garbageCollector->addConnection(c);
    //}
    //Create threads here.  Most likely have to use loops for each rule or something
    //NOTE: each time evaluate is executed, EITHER rule or fact, then must use unique_lock.

    //A lock requires a mutex, and a condition variable.  Use unique_lock

    std::thread t1(threadFunction, 21);

    // Wait for the threads to finish
    t1.join();
    // Delete objects and release all of their resources

  }
  catch (int) { // If exception caught
    std::cout << "Exception caught here\n"; // Print message
  }
  //delete(garbageCollector);
  //delete(tcpServerSocket);
}
