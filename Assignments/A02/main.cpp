/**
 *  Course: CMPS 2143 - OOP
 *  Assignment: P02
 *  Purpose: Push and pop value onto and from List.
 *
 *  @author Logan Wheeler
 *  @version 1.1 09/04/18
 */
#include <iostream>

using namespace std;

int A[100];

/**
 *  Struct: Node
 * Creates the Node used in List
 *
 */

struct Node
{
    int x;
    Node *next;
    Node()
    {
        x = -1;
        next = NULL;
    }
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

/**
 *  Class:List
 creates the List we use with Nodes
 */

class List
{
private:
    Node *Head;
    Node *Tail;
    int Size;
    
public:
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }
    /**
     *  Push a new node and value onto the Tail of the list
     *
     *  @param {int} digit the single digit to encode.
     *  @return (void) Nothing.
     */
    
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);
        
        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
    /**
     *  Insert a new Node and  value onto the list
     *
     *  @param {int} digit the single digit to encode.
     *  @return (void) Nothing.
     */
    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);
        
        // figure out where it goes in the list
        
        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }
    /**
     *  Print out List Value.
     *
     *  @param {nothing}
     *  @return (void) Nothing.
     */
    
    void PrintTail()
    {
        cout << Tail->x << endl;
    }
    /**
     *  Print out List Strings.
     *
     *  @param {nothing}
     *  @return (String) Returns the strings.
     */
    
    string Print()
    {
        Node *Temp = Head;
        string list;
        
        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }
        
        return list;
    }
    /**
     *  pops of a value from the list.
     NOT Working.
     *
     *  @param {nothing}
     *  @return (int) Returns 0
     */
    int Pop()
    {
        Size--;
        return 0; //
    }
    /**
     *  Creates a new list that contains both First and sexond function
     *
     *  @param {const} First list and rhs list
     *  @return (void) brand new list comprised of both first list and RHS.
     */
    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;
        
        // Get a reference to beginning of local list
        Node *Temp = Head;
        
        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }
        
        // Get a reference to head of Rhs
        Temp = Rhs.Head;
        
        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }
        
        // Return new concatenated version of lists
        return NewList;
    }
    /**
     *  Implementation of [] operator
     *
     *  @param {int}index
     *  @return (void) function returns an
     // int value as if the list were an array.
     */
    int operator[](int index)
    {
        Node *Temp = Head;
        
        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {
            
            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }
    
    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};
/**
 *  calls the push function in the list class to assign values to it, prints list then creates third list.
 *
 *  @param {int, char}
 *  @return (int) returns 0.
 */
int main(int argc, char **argv)
{
    List L1;
    List L2;
    
    for (int i = 0; i < 25; i++)
    {
        L1.Push(i);
    }
    
    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);
    }
    
    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();
    
    List L3 = L1 + L2;
    cout << L3 << endl;
    
    cout << L3[5] << endl;
    return 0;
}
