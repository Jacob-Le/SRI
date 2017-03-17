#include "Consumer.h"
// Constructor
Consumer::Consumer(BoundedBuffer <int> * p_boundedBuffer){ boundedBuffer = p_boundedBuffer; }

void Consumer::consume() // Consume function
{
    //Debug statement


    bool truth = boundedBuffer->consume(); // Extract item from buffer
}

Consumer::~Consumer() // Destructor
{

}
