#include <iostream>
#include <stdexcept>
using namespace std;

class HashTable{
  static char * const DELETED;
 public:
  HashTable(int n = 101);
  ~HashTable();
  HashTable(HashTable& other);
  const HashTable& operator = (HashTable& rhs);
  void insert(const char *str);
  bool find(const char *str);
  char * remove(const char *str);
  bool isRehashing();
  int tableSize(int table = 0);
  int size(int table = 0);
  const char * at(int index, int table = 0);
  void dump();
  unsigned int hashCode(const char *str);
 private:
  char ** hTable;
  int m_size;
  int m_capacity;
  bool m_rehashing;
};
