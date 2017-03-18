template <typename T>
void BoundedBuffer<T>::produce(T p_item) // Produce: add item to buffer
{
  std::unique_lock<std::mutex> l(mutex); // Define a new unique lock and pass mutex to it.
  for ( ;count == size ; ) // While buffer is full
  {
    cout << "Waiting on producer condition variable\n";
    // Wait on the producer condition variable with unique_lock "l". Notice the lambda function that indicates that will wake up the waiting thread when consumption occurs.
    produce_cond.wait(l, [this](){return count != size; });
    // Upon return from wait via a signal mutex will be re-acquired
  }
  // If we are here and producer index reached the end of the buffer, and buffer is not full then there is definitely empty space in the front.
  // Set producer current index to 0
  if ( producer_current == size -1 ) producer_current =0;
  else producer_current ++; // Else increment producer current index
  buffer[producer_current] = p_item; // Assign Item to producer current index
  count ++; // increment the number of elements in the buffer
  consume_cond.notify_one(); // Notify one of the consumers waiting threads.
}

template <typename T>
T BoundedBuffer<T>::consume( // Consume: return item to caller
{
  std::unique_lock<std::mutex> l(mutex);
  for ( ;count == 0 ; ) // while buffer is empty
  {
    cout << "Waiting on consumer condition variable\n";
    // Wait on the consumer condition variable with unique_lock "l". Notice the lambda function that will wake up the waiting thread when production occurs.
    consume_cond.wait(l, [this](){return count != 0; });
    // Upon return from wait via a signal mutex will be re-acquired
  }
  // If we are here and consumer index reached the end of the buffer, and buffer is not empty then there is definitely occupied items in the front.
  // Set consumer current index to 0
  if ( consumer_current == size -1 ) consumer_current =0;
  else consumer_current++; // Else increment consumer current index
  bool item = buffer[consumer_current]; // extract item at consumer current index
  count --; // Decrement the number of elements in the buffer
  produce_cond.notify_one(); // Notify one of the producers waiting threads
  return item; // return the item
}
