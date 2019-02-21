#include <iostream>
#include <stdexcept>
#include "primes.cpp"
#include "HashTable.h"
#include "words.h"
#include <cstring>

using namespace std;
char * const HashTable::DELETED  = (char *) &DELETED;

HashTable::HashTable(int n){
  hTable = new char*[roundUpPrime(n)];
  m_size = 0;
  m_capacity = roundUpPrime(n);
  m_rehashing = true;
  
}

HashTable::~HashTable(){
  for(int i = 0; i < m_capacity; i++){
    delete hTable[i];
  }
  delete hTable;
}
HashTable::HashTable(HashTable& other){
  for(int i = 0; i < other.m_capacity; i++){ //copies other's data into hTable
    strcpy(hTable[i], other.hTable[i]);
  }
  m_size = other.m_size; //copy private members
  m_capacity = other.m_capacity;
  m_rehashing = other.m_rehashing;
}
const HashTable& HashTable::operator=(HashTable& rhs){
  HashTable *ptr;

  HashTable newhTable(rhs.m_capacity); //create new hTable to be returned
  ptr = &newhTable;
  for(int i = 0; i < rhs.m_capacity; i++){ //populate hTable with copied values
    strcpy(newhTable.hTable[i], rhs.hTable[i]);
  }
  newhTable.m_size = rhs.m_size; //copy private members
  newhTable.m_capacity = rhs.m_capacity;
  newhTable.m_rehashing = rhs.m_rehashing;
  return *ptr;
}
void HashTable::insert(const char *str){
  if(find(str)) //checks to see  if the value already exists
    cout << "Value already exists" << endl;
  else{ //if it doesnt exist, begin to insert new str
    int probeCounter = 1; 
    int index = hashCode(str) % m_capacity;
    while(hTable[index] != NULL){ //linear probe until open slot is found
      probeCounter++;
      index++;
      index = index % m_capacity;
    }
    if(probeCounter >= 10 || m_size / m_capacity >= 0.5){ //rehashing enabled if >= 10 or load factor > 0.5
      m_rehashing = true;
      //rehash
    }
    
    hTable[index] = new char[20]; //create new cstring
    strcpy(hTable[index], str); //str is copied into cstring slot
    m_size++;
    
  }
}
bool HashTable::find(const char *str){
  int probeCounter = 1;
  int index = hashCode(str) % m_capacity;
  while(hTable[index] != NULL and !strcmp(hTable[index], str)){ //parses through hTable until a NULL is hit or if found
    index++;
    index = index % m_capacity;
    probeCounter++;
  }
  cout << "inserting " << str << " into index: " << index << endl;
  if(probeCounter >= 10){ //enabling rehashing mode if >= 10
    m_rehashing = true;
  }
  if(hTable[index] != NULL){
    strcmp(hTable[index], str); //if it exists, return true
    return true;
  }
  else{ //otherwise, return false
    return false;
  }
}
char * HashTable::remove(const char *str){
  char *returnValue; //create variable to hold returned value
  int probeCounter = 1;
  int index = hashCode(str) % m_capacity;
  if(!find(str)){ //checks to see if the value exists in the first place
    returnValue = NULL;
    return returnValue;
  }
  else{ //if it exists, get to the exact index it is stored in
    while(!strcmp(hTable[index], str)){
      index++;
      index = index % m_capacity;
      probeCounter++;
    }
    strcpy(returnValue, hTable[index]); //once found, store the value into returnValue
    strcpy(hTable[index], "DELETED"); //dummy delete
    m_size--;
  }
  if(probeCounter >= 10){
    m_rehashing = true; //enabling rehashing mode if >= 10
  }
  return returnValue;
}
bool HashTable::isRehashing(){
  return m_rehashing;
}
int HashTable::tableSize(int table){
  return m_capacity;
}
int HashTable::size(int table){
  return m_size;
}
const char * HashTable::at(int index, int table){
  if(index < 0 || index > m_capacity){ //checks to see if index is invalid
    throw out_of_range("Out of range"); //if so, throw exception
  }
  return hTable[index]; //otherwise, return the desired cstring
}
void HashTable::dump(){
  char const *value;
  for(int i = 0; i < m_capacity; i++){ //parse through hTable and print out values
    cout << "hTable [" << i << "] = ";   
    if(hTable[i] != NULL){
      value = at(i,0);      
      cout << value << endl;
    }
    else
      cout << endl;
  }
}
unsigned int HashTable::hashCode(const char *str) {

   unsigned int val = 0 ;
   const unsigned int thirtyThree = 33 ;  // magic number from textbook

   int i = 0 ;
   while (str[i] != '\0') {
      val = val * thirtyThree + str[i] ;
      i++ ;
   }
   return val ;
}
