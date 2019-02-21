#include <iostream>
#include <string>
#include "MedianHeap.h"
#include <stdexcept>
using namespace std;

Heap::Heap(){
  m_size = 0;
  m_capacity = 50;
  m_heap = new int[50];
}

Heap::Heap(int cap){
  m_size = 0;
  m_capacity = cap;
  m_heap = new int[cap];
}

Heap::~Heap(){
  delete[] m_heap;
}

void Heap::insert(int item){
  int index = m_size + 1;
  m_heap[index] = item;
  m_size++;
  if(m_size > 1)
    bubbleUp(index);
}

void Heap::bubbleUp(int index){
  int temp;
  if (m_heap[index / 2] < m_heap[index]){
    temp = m_heap[index / 2];
    m_heap[index / 2] = m_heap[index];
    m_heap[index] = temp;
    if(index /2 > 1)
    bubbleUp(index / 2);
  }
  else{
    return;
  }

}

void Heap::trickleDown(int index){
}

int Heap::getSize(){
  return m_size;
}

int Heap::getCapacity(){
  return m_capacity;
}

void Heap::dump(){
  cout << "-------------------" << endl;
  cout << "HEAP DUMPING" << endl;
  cout << "-------------------" << endl;
  cout <<"Heap capacity: " << m_capacity << endl;
  cout <<"Heap size: " << m_size << endl;
  for(int i = 0; i <= m_size; i++){
    cout << "Index: " << i << " Value: " << m_heap[i] << endl;
  }
  
}

MedianHeap::MedianHeap(bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap=100 ) {
  minHeap = new Heap(cap/2);
  maxHeap = new Heap(cap/2);
}

MedianHeap::MedianHeap(const MedianHeap<T>& otherH){
  minHeap = otherH.minHeap;
  maxHeap = otherH.maxHeap;
}
MedianHeap::~MedianHeap(){
  delete minHeap;
  minHeap = NULL;
  delete maxHeap;
  maxHeap = NULL;
}
const MedianHeap<T>& MedianHeap::operator= (const MedianHeap<T>& rhs){
  minHeap = rhs.minHeap;
  maxHeap = rhs.maxHeap;
}
int MedianHeap::size(){
  return minHeap->getSize + maxHeap->getSize;
}
int MedianHeap::capacity(){
  return minHeap->getCapacity + maxHeap->getCapacity;
}
void MedianHeap::insert(const T& item){
  if(minHeapSize() > maxHeapSize()){
    maxHeap->insert(item);
  }
  else
    minHeap->insert(item);
}
T MedianHeap::getMedian(){
  if(size() % 2 == 0)
    return getMax();
  else{
    if(maxHeapSize() > minHeapSize())
      return getMax();
    else
      return getMin();
  }
}
T MedianHeap::getMin(){
  return minHeap[1];
}
T MedianHeap::getMax(){
  return maxHeap[1];
}
bool MedianHeap::deleteItem(T& givenitem, bool (*equalTo) (const T&, const T&)){}
void MedianHeap::dump(){
  cout << "-------------------" << endl;
  cout << "MEDIANHEAP DUMPING" << endl;
  cout << "-------------------" << endl;
  minHeap->dump();
  cout << endl;
  maxHeap->dump();
}
int MedianHeap::maxHeapSize(){
  return maxHeap->getSize();
}
int MedianHeap::minHeapSize(){
  return minHeap->getSize();
}
T MedianHeap::locateInMaxHeap(int pos){
 if(pos > maxHeapSize() + 1)
    throw out_of_range("Invalid index");
  else
    return maxHeap[pos + 1];
}
T MedianHeap::locateInMinHeap(int pos){
  if(pos > minHeapSize() + 1)
    throw out_of_range("Invalid index");
  else
    return minHeap[pos + 1];
}
