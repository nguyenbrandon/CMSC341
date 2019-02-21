// File: drivercpp
//
// CMSC 341 Fall 2018 Project 2


#include <iostream>
#include <fstream>
using namespace std ;

#include "Sally.h"

int main() {
   string fname ;

   //cout << "Enter file name: " ;
   //cin >> fname ;
   fname = "test.sally";
   ifstream ifile(fname.c_str()) ;

   Sally S(ifile) ;

   S.mainLoop() ;

   ifile.close() ;
   return 0 ;
}
