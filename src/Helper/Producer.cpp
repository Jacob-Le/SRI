#include "Producer.h"
// Constructor: initializing all data members using attribute list. Notice that we have passed the BoundedBuffer Object.
Producer::Producer(Rule * r, BoundedBuffer <bool> * p_boundedBuffer){
  rule = r;
  boundedBuffer = p_boundedBuffer;
}

void Producer::produce() { // Produce function
    //Call Evaluate here

    //Debug statement

    boundedBuffer->produce(truth); // Inject item into Bounded Buffer
}

Producer::~Producer() // Destructor
{
}
