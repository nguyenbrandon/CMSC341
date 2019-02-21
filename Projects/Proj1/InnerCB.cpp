#include <iostream>
#include <stdexcept>
#include "InnerCB.h"

using namespace std;
InnerCB::InnerCB(int n){
  m_capacity = n;
  m_size = 0;
  m_start = 0;
  m_end = 0;
  m_buffer = new int[n]; //Creates dynamically allocated array of size n
}

InnerCB::InnerCB(const InnerCB& other){
  m_capacity = other.m_capacity; //Copy all of the data members
  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;
  m_buffer = new int[other.m_capacity]; //Creates a new dynamically allocated array of the same size
  
  for(int i = 0; i < other.m_capacity; i++){ //Fills the new array with the contents of the other InnerCB
    m_buffer[i] = other.m_buffer[i];
  }
}

InnerCB::~InnerCB(){
  delete[] m_buffer; //Simply delete the whole array
  m_buffer = NULL;
}

void InnerCB::enqueue(int data){
  if(isEmpty()){ //If the InnerCB is empty, create the first data member without changing m_end afterwards
    m_buffer[m_start] = data;
    m_end = m_start;
    m_size++;
  }
  
  else if (isFull()) //If the InnerCB is full, throw an exception
    //throwexception
    throw overflow_error("Cannot enqueue, InnerCB is full!");

  else{ //If the InnerCB is not empty, and is not full, enqueue normally
    m_buffer[(m_end + 1) % m_capacity] = data;
    m_end = (m_end + 1) % m_capacity;
    m_size++;
  }
}

int InnerCB::dequeue(){
  int num;
  if(isEmpty()){ //If the InnerCB is empty, throw an exception
    //throwexception
    throw underflow_error("Cannot dequeue, InnerCB is empty!");
  }
  else{ //Otherwise, dequeue normally
    num = m_buffer[m_start];
    m_buffer[m_start] = 0;;
    m_start = (m_start + 1) % m_capacity;
    m_size--;
  }
  return num;
}

bool InnerCB::isFull(){
  if(m_size == m_capacity)
    return true;
  else
    return false;
}

bool InnerCB::isEmpty(){
  if(m_size == 0)
    return true;
  else
    return false;
}

int InnerCB::capacity(){
  return m_capacity;
}

int InnerCB::size(){
  return m_size;
}

const InnerCB& InnerCB::operator=(const InnerCB& rhs){
  delete[] m_buffer; //Delete any pre-existing data
  m_buffer = NULL; //Set to null just to avoid any problems

  m_capacity = rhs.m_capacity; //Copy data members
  m_size = rhs.m_size;
  m_start = rhs.m_start;
  m_end = rhs.m_end;
  m_buffer = new int[rhs.m_capacity]; //Create new array of ints with the same capacity of the rhs InnerCB

  for(int i = 0; i < rhs.m_capacity; i++){ //Fill the new array
    m_buffer[i] = rhs.m_buffer[i];
  }

  return rhs;
}

void InnerCB::dump(){
  cout << "InnerCB dump(): m_size = " << m_size << endl;
  for(int i = 0; i < m_size; i ++){
    cout << "[" << (m_start + i) % m_capacity << "] " << m_buffer[(m_start + i) % m_capacity] << ", ";
  }
  cout << endl;
}
