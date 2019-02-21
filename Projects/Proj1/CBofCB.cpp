#include <iostream>
#include <stdexcept>
#include "CBofCB.h"

using namespace std;

CBofCB::CBofCB(){
  m_obSize = 1; //OuterCB always has at least 1 InnerCB and starts with 1
  m_oldest = 0; 
  m_newest = 0; 

  m_buffers[0] = new InnerCB(10); //creates new dynamically allocated InnerCB with capacity 10
}

CBofCB::CBofCB(const CBofCB& other){
  m_obSize = other.m_obSize; //copy data members
  m_oldest = other.m_oldest;
  m_newest = other.m_newest;

  for(int i = 0; i < other.m_obSize; i++){ //copy all of the InnerCB's within the OuterCB of other
    m_buffers[(m_oldest + i) % m_obCapacity] = new InnerCB(*other.m_buffers[(m_oldest + i) % m_obCapacity]);
  }
  
}

CBofCB::~CBofCB(){
  for(int i = 0; i < m_obSize; i++){ //delete every InnerCB within OuterCB
    delete m_buffers[(m_oldest + i) % m_obCapacity];
  }
}

void CBofCB::enqueue(int data){
  if(m_buffers[m_newest]->isFull()){ //checks to see if newest InnerCB is full
    if(isFull()) //if it's full, check to see if the OuterCB is full too
      //throw exception here
      throw overflow_error("All InnerCB's of the circular buffer are full!");
    else{ //if InnerCB is full, but OuterCB is not, create a new InnerCB with 2*capacity of newest and enqueue data
      m_buffers[(m_newest + 1) % m_obCapacity] = new InnerCB(2*m_buffers[m_newest]->capacity());
      m_newest = (m_newest + 1) % m_obCapacity;
      m_buffers[m_newest]->enqueue(data);
      m_obSize++;
    }
  }
  else{
    m_buffers[m_newest]->enqueue(data); //if InnerCB is not full, enqueue normally
  }
}

int CBofCB::dequeue(){
  int num;
  if(isEmpty()) //checks to see if OuterCB is empty in the first place
    //throw exception
    throw underflow_error("Nothing to dequeue!");
  else{ //if there is data, dequeue the oldest int in the oldest InnerCB
    num = m_buffers[m_oldest]->dequeue();
    if(m_buffers[m_oldest]->isEmpty()){ //Checks to see if the oldest InnerCB is now empty after dequeueing
      if(m_obSize != 1){ //Unless it is our very last InnerCB, delete it
	delete m_buffers[m_oldest];
	m_obSize--; //Should never reach 0
	m_oldest = (m_oldest + 1) % m_obCapacity; //Moves the m_oldest index to the next oldest InnerCB
      }
    }
  }
  return num;
}

bool CBofCB::isFull(){
  if(m_obSize == m_obCapacity && m_buffers[m_newest]->isFull()) //Must have maximum InnerCB's and the newest InnerCB must also be full
    return true;
  else
    return false;
}

bool CBofCB::isEmpty(){
  if(size() == 0)
    return true;
  else
    return false;
}

int CBofCB::size(){
  int sum = 0;

  for(int i = 0; i < m_obSize; i++){ //Loops through every InnerCB and adds the sum of integers up
    sum = sum + m_buffers[(m_oldest + i) % m_obCapacity]->size();
  }
  return sum;
}

const CBofCB& CBofCB::operator=(const CBofCB& rhs){
  for(int i = 0; i < m_obSize; i++){ //Loop through lhs object and delete everything
    delete m_buffers[(m_oldest + i) % m_obCapacity];
  }
  
  m_obSize = rhs.m_obSize; //Copy data members
  m_oldest = rhs.m_oldest;
  m_newest = rhs.m_newest;
  
  for(int i = 0; i < m_obSize; i++){ //Loops through rhs m_buffers and copies every InnerCB and its values
    m_buffers[(m_oldest + i) % m_obCapacity] = new InnerCB(*rhs.m_buffers[(m_oldest + i) % m_obCapacity]);
  }
  return rhs;
}

void CBofCB::dump(){
  cout << "---------------------------" << endl;
  cout << "Outer Circular buffer dump(), m_obSize = " << m_obSize << ":" << endl;
  for(int i = 0; i < m_obSize; i++){
    cout << "[" << (m_oldest + i) % m_obCapacity << "] ";
    m_buffers[(m_oldest + i) % m_obCapacity]->dump();
  }
  cout << "---------------------------" << endl;
  
}
