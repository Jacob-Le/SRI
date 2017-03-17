// A class that represents starting a AND evaluate thread
#include "Rule.h"

class Producer
{
private:
  Rule * rule; //Rule to evaluate
  BoundedBuffer <bool> * boundedBuffer; // The bounded buffer object to be used
public:
  // Constructor: initializing all data members using attribute list. Notice that we have passed the BoundedBuffer Object.
  Producer(int p_number, Rule * r, BoundedBuffer <bool> * p_boundedBuffer);
  void produce(); // Produce function
  ~Producer(); // Destructor
};
