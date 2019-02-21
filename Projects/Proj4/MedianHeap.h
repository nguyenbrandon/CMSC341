#ifndef _MEDIANHEAP_H_
#define _MEDIANHEAP_H_

#include <iostream>
#include <string>
using namespace std;



class Heap{
public:
  Heap();
  Heap(int cap);
  ~Heap();
  void insert(int item);
  void bubbleUp(int index);
  void trickleDown(int index);
  int getSize();
  int getCapacity();
  void dump();
private:
  int m_size;
  int m_capacity;
  int *m_heap;
};



template <typename T>
class MedianHeap{
  
public:
  MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap=100 ) ;
  MedianHeap(const MedianHeap<T>& otherH);
  ~MedianHeap();
  const MedianHeap<T>& operator=(const MedianHeap<T>& rhs);
  int size();
  int capacity();
  void insert(const T& item);
  T getMedian();
  T getMin();
  T getMax();
  bool deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&));
  void dump();
  int maxHeapSize();
  int minHeapSize();
  T locateInMaxHeap(int pos);
  T locateInMinHeap(int pos);

private:

  Heap *minHeap;
  Heap *maxHeap;
  
};

#endif
