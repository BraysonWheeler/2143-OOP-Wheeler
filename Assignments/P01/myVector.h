#include <iostream>

using namespace std;

class myVector{
private:
    int *theVector;
    int max;
    int origsize;
    
public:
    myVector(int size);
    int vSize;
    int  pop_back();
    int index = 0;
    int var;
    float percentfull();
    void print();
    void add(int item);
    void push_back(int item);
    void shrink();
};
