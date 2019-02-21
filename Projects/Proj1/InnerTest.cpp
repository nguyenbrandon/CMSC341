#include <iostream>
#include <stdexcept>
#include "InnerCB.h"

using namespace std;

int main(){

  InnerCB cb1(5);

  cb1.enqueue(2);
  cb1.enqueue(3);
  cb1.enqueue(4);
  cb1.enqueue(5);
  cb1.enqueue(6);
  cb1.dump();

  int removed = cb1.dequeue();
  cout << "Successfully removed: " << removed << endl;
  cb1.dump();
  removed = cb1.dequeue();
  cout << "Successfully removed: " << removed << endl;
  cb1.dump();
  removed = cb1.dequeue();
  cout << "Successfully removed: " << removed << endl;
  cb1.dump();
  removed = cb1.dequeue();
  cout << "Successfully removed: " << removed << endl;
  cb1.dump();

  cb1.enqueue(7);
  cb1.enqueue(8);
  cb1.enqueue(9);
  cb1.enqueue(10);
  cb1.dump();

  InnerCB cb2(10);
  cb2.enqueue(20);
  cb2.enqueue(21);
  cb2.enqueue(22);
  cb2.enqueue(23);
  cb2.enqueue(24);
  cb2.enqueue(25);
  cb2.enqueue(26);
  cb2.enqueue(27);
  cb2.enqueue(28);
  cb2.enqueue(29);
  cb2.dump();

  cb2 = cb1;
  cb2.dump();
  //COPY CONSTRUCTOR TEST
  /*InnerCB cb2 = cb1;
  cb2.dump();
  */
  return 0;
}
