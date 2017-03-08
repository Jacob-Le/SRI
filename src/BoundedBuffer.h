#define BUFFER_SIZE 10
#define TRANSACTION_COUNT 20
#define PRODUCER_MAX_ITEM 100
#define PRODUCER_MAX_SLEEP 3
#define CONSUMER_MAX_SLEEP 6

template <typename T> // A template definition for handling any type
class BoundedBuffer {
private:
  T * buffer; // A pointer to the buffer
  size_t size; // Maximum size of the buffer
  std::mutex mutex; // A mutex for managing critical section
  std::condition_variable consume_cond; // A condition for the consumer to wait when buffer is empty
 std::condition_variable produce_cond; // A condition for the producer to wiat when buffer is full
 int producer_current; // The index pointer of the producer within the buffer
 int consumer_current; // The index pointer of the consumer within the buffer
 int count; // The current number of item in the buffer
public:
  BoundedBuffer (size_t p_size); // Constructor
  void produce (T p_item,string p_debug_string); // Produce an item and add it to the buffer
  T consume (string p_debug_string); // Consume an item and return it to the caller.
  virtual ~BoundedBuffer (); // Destructor
};

#include "BoundedBuffer.cpp"
