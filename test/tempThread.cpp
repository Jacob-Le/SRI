#pragma once

#include <stdlib>
#include <thread>

#include "Connection.h"
//#include "TCPServerSocket.h"

using namespace std;

void threadFunction(int x){
  cout<< "thread" << x <<endl;
}

//Attempts to manage threads via a bounded buffer class. Use in SRI.cpp
int main () {
  BoundedBuffer <int> * boundedBuffer; // Declare an integer Bound Buffer
  //GarbageCollector * garbageCollector = new GarbageCollector();

  // Instantiate a new TCPSocketServer Object that listens on all insterfaces on port 9999
  // NOTE: the address and port number is irrelevant, as long as the client and server side have the same
  //TCPServerSocket * tcpServerSocket = new TCPServerSocket("0.0.0.0",9999,100);

  try{ // try just in case we cannot allocate buffer
    boundedBuffer = new BoundedBuffer <int>(BUFFER_SIZE); // instantiate buffer with
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
    std::thread t1(threadFunction, 21);

    // Wait for the threads to finish
    t1.join();
    // Delete objects and release all of their resources

  }
  catch (int) { // If exception caught
    cout << "Exception caught here\n"; // Print message
    boundedBuffer = NULL; // set boundedBuffer to NULL to avoid destruction
  }
  if (boundedBuffer != NULL) delete (boundedBuffer); // Destruct boundedBuffer if instantiated
  //delete(garbageCollector);
  //delete(tcpServerSocket);
}
