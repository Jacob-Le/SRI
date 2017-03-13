//TCPSocket * tcpSocket = new TCPServerSocket(//Address, port and buffer size here//)

#include "../sockets/TCPSocket.h"
// A class representing a single connection form a client
class Connection : public thread //Inherit from Thread
{
  private:
    TCPSocket * tcpSocket; // TCP Socket for communication with client
    Connection * next_connection; // A way to build a linked list of connections for the garbage collector to be able to track them
  public:
    Connection(TCPSocket * p_tcpSocket); // Constructor: Set client connected TCP socket
    void * threadMainBody (void * arg); // Main thread body that serves the connection
    void setNextConnection(Connection * connection); // Set the next pointer: used by the

    Connection * getNextConnection (); // Get a pointer to the next connection
    ~Connection(); // Destructor
};
