#include <iostream>
#include "myVector.h"

using namespace std;

/**
 *  Creates the array with the size given in main
 *
 *  param (int) an int to create size of array
 *  return (void) Nothing.
 */

myVector::myVector(int size){
    vSize = size;
    origsize = size;
    theVector = new int[vSize];
    for(int i= 0;i<vSize;i++){
        theVector[i] = i;
    }
}

/**
 *  Prints out what is currently in the array
 *
 *  param () nothing
 *  return (void) Nothing.
 */

void myVector::print(){
    for(int i=0;i<index;i++){
        cout<< theVector[i]<<" ";
    }
    cout << endl;
}

/**
 *  Shrinks the array when called, cannot shrink an array past
 *   original size
 *
 *  param () nothing
 *  return (void) Nothing.
 */

void myVector::shrink(){
    if(vSize == origsize){
        
    }
    else{
        vSize = vSize/2;
        int *newarray = new int[vSize/2];
        for(int i = 0; i < vSize; i++){
            newarray[i] = theVector[i];
        }
        index = vSize;
        delete[] theVector;
        theVector = newarray;

    }
}
/**
 *  Pops an element off the back of an array, will test to see
 *   if the array is empty if so will return 0
 *
 *  param () nothing
 *  return (int) return the element.
 */

int myVector::pop_back(){
    if(index == 0){
        cout << "Cannot remove from empty Vector" << endl;
        return 0;
    }
    else if(percentfull() <= vSize*.4){
        cout <<"shrinking" << endl;
        resize(.5);
        return theVector[index--];
    }
    else{
        return theVector[index--];
    }
}

/**
 * Function will grow the array to a size of 1.5
 *
 *  param () nothing
 *  return (int) return the element.
 */

void myVector::push_back(int item){
    if (index >= vSize){
        resize(1.5);
    }
    
    theVector[index++] = item;
}

/**
 *  tests how full the array is in order to shrink or not shrink the array
 *
 *  param () nothing
 *  return (float) decimal/percentage of how full the array is.
 */


float myVector::percentfull(){
    float pfull = (float)index/vSize;
    return pfull;
}

/**
 *  resizes the array to a set decimal grows or shrinks array
 *
 *  param () double ratio
 *  return (int*) dynamic new array full of int.
 */


int* myVector::resize(double ratio){
    if(vSize == origsize){
        return 0;
    }
    else{
        vSize = vSize * ratio;
        int* newarray = new int[vSize/2];
        for(int i = 0; i < vSize; i++){
            newarray[i] = theVector[i];
        }
        index = vSize;
        delete[] theVector;
        return newarray;

    
    }
}
