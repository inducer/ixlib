// ----------------------------------------------------------------------------
//  Description      : Ring queue container
// ----------------------------------------------------------------------------
//  (c) Copyright 1999 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_RING_QUEUE
#define IXLIB_RING_QUEUE




#include <ixlib_numeric.hpp>
#include <ixlib_array.hpp>




namespace ixion {
  /** A class implementing a ring queue, often also known as a
  ring buffer or in-place FIFO. This data structure does not do
  any reallocation once it is created.
  
  The "Pointer" variants of the push and pop operations are guaranteed
  not to throw exceptions, making them the perfect choice for operations
  in other threads and other critical environments where standard
  library functionality is only available in a restricted way.
  */
  template<class T,class Allocator = std::allocator<T> >
  class ring_queue {
    private:
      auto_array<T,Allocator>		Data;
      TIndex				Head;
      TIndex				Tail;
    
    public:
      ring_queue(TIndex capacity = 0)
        : Data(capacity),Head(0),Tail(0) {
	}
      
      /// Query the maximal capacity of the ring queue.
      TSize capacity() const {
        return Data.capacity();
	}
      
      /// Query the number of entries in the ring_queue.
      TSize size() const {
        return NUM_CIRCLEDIST(Head,Tail,Data.capacity());
	}
      
      /// Retrieve maximally maxcount entries from the ring queue.
      /**
      @param data The retrieved entries are copied to the area starting at data.
      @return how many entries actually have been retrieved.
      */
      inline TSize pop(T *data,TSize maxcount = 1);
      
      /// Place count entries starting at data in the ring queue.
      inline void push(T *data,TSize count = 1);
      
      /// Get a pointer where data may be read directly out of the ring_queue buffer.
      /**
      @param maxcount is set to the number of T's that may maximally be read.
      */
      inline T *popPointer(TSize &maxcount);
      
      /// Inform the ring_queue that count entries have actually been read.
      inline void popPointerCommit(TSize count);

      /// Get a pointer where data may be written directly into the ring_queue buffer.
      /**
      @param maxcount is set to the number of T's that may maximally be written.
      @return the pointer.
      */
      inline T *pushPointer(TSize &maxcount);
      
      /// Inform the ring_queue that count entries have actually been written.
      inline void pushPointerCommit(TSize count);
      
      /// Reallocate the buffer, invalidate all current contents.
      inline void allocate(TSize capacity) {
        Data.allocate(capacity);
	Head = 0;
	Tail = 0;
	}
    };
  }




template<class T,class Allocator>
ixion::TSize ixion::ring_queue<T,Allocator>::pop(T *data,TSize maxcount) {
  while (count) {
    TSize loopmax;
    T *buffer = popPointer(loopmax);
    if (loopmax == 0)
      EXGEN_THROW(EC_BUFFERUNDERFLOW)
    
    TSize countdown = loopmax;
    while (countdown--)
      *data++ = *buffer++;

    popPointerCommit(loopmax);
    count -= loopmax;
    }
  }




template<class T,class Allocator>
void ixion::ring_queue<T,Allocator>::push(T *data,TSize count) {
  TSize result = 0;
  while (count) {
    TSize loopmax;
    T *buffer = pushPointer(loopmax);
    if (loopmax == 0) break;
    
    TSize countdown = loopmax;
    while (countdown--)
      *buffer++ = *data++;

    pushPointerCommit(loopmax);
    count -= loopmax;
    result += loopmax;
    }
  return result;
  }




template<class T,class Allocator>
T *ixion::ring_queue<T,Allocator>::popPointer(TSize &maxcount) {
  if (Tail <= Head)
    maxcount = Head-Tail;
  else
    maxcount = Data.capacity() - Tail;
  return Data+Tail;
  }




template<class T,class Allocator>
void ixion::ring_queue<T,Allocator>::popPointerCommit(TSize count) {
  Tail = (Tail+count) % Data.capacity();
  }




template<class T,class Allocator>
T *ixion::ring_queue<T,Allocator>::pushPointer(TSize &maxcount) {
  if (Tail <= Head) {
    maxcount = Data.capacity() - Head;
    if (Tail == 0 && maxcount > 0) maxcount--;
    }
  else
    // we may not fill the buffer entirely, as head == tail means "empty"!
    maxcount = Tail - Head - 1;
  return Data+Head;
  }




template<class T,class Allocator>
void ixion::ring_queue<T,Allocator>::pushPointerCommit(TSize count) {
  Head = (Head+count) % Data.capacity();
  }




#endif
