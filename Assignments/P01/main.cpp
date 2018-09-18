/**
 *  Course: CMPS 2143 - OOP
 *  Assignment: A01
 *  Purpose: C++ class implements functionality of a c++ vector using an array
 *           as a storage container. the vector will grow and shrink when neccessary
 *           elements will be pushed on and poped off when told to.
 *
 *  @author Logan Wheeler
 *  @version 1.1 09/04/18
 */




#include <iostream>
#include "myVector.h"

using namespace std;

int main() {
    
    myVector V(10);
    V.pop_back();
    V.push_back(4);
    V.push_back(13);
    V.push_back(73);
    V.print();
    // Creating new array to fill
    myVector B(10);
    for(int i = 0;i < 1000;i++){
        B.push_back(i);
    }
    
    cout << "Vector size is " << B.vSize << endl;
       for(int i = 0;i < 997;i++){
           B.pop_back();
       }
    B.print();
}
