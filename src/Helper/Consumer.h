// A class that represents waiting for and retrieving the evaluated value
class Consumer
{
 private:
   BoundedBuffer <bool> * boundedBuffer;// The bounded buffer object to be used
 public:
   // Constructor: initializing all data members using attribute list. Notice that we have passed the BoundedBuffer Object.
   Consumer(BoundedBuffer <bool> * p_boundedBuffer);
   void consume(); // Consume function
   ~Consumer();// Destructor
};
