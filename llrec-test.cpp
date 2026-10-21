#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------

// Removes odd numbers
struct IsOdd {
    bool operator()(int v) { return v % 2 != 0; }
};
 
// Removes numbers greater than a limit chosen at construction
struct GreaterThan {
    int limit;
    GreaterThan(int l) : limit(l) {}
    bool operator()(int v) { return v > limit; }
};
 
// Removes everything
struct RemoveAll {
    bool operator()(int) { return true; }
};
 
// Removes nothing
struct RemoveNone {
    bool operator()(int) { return false; }
};



int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out your linked list code
    Node* smaller = NULL;
    Node* larger = NULL;
    llpivot(head, smaller, larger, 9);
    cout << "Pivot 9 -> smaller: ";
    print(smaller);
    cout << "Pivot 9 -> larger:  ";
    print(larger);
    cout << "head after llpivot is " << (head == NULL ? "NULL" : "NOT NULL (bug!)") << endl;
    dealloc(smaller);
    dealloc(larger);
 
    // llpivot with garbage in smaller/larger, and with pivot at the extremes
    head = readList(argv[1]);
    smaller = (Node*)0x1;       // garbage on purpose
    larger = (Node*)0x2;
    llpivot(head, smaller, larger, 1000);   // everything <= pivot
    cout << "Pivot 1000 -> smaller: ";
    print(smaller);
    cout << "Pivot 1000 -> larger is " << (larger == NULL ? "empty" : "NOT empty (bug!)") << endl;
    dealloc(smaller);
 
    head = readList(argv[1]);
    llpivot(head, smaller, larger, -1000);  // everything > pivot
    cout << "Pivot -1000 -> smaller is " << (smaller == NULL ? "empty" : "NOT empty (bug!)") << endl;
    cout << "Pivot -1000 -> larger: ";
    print(larger);
    dealloc(larger);
 
    // empty list
    head = NULL;
    llpivot(head, smaller, larger, 9);
    cout << "Empty list -> smaller/larger/head all NULL? "
         << ((smaller == NULL && larger == NULL && head == NULL) ? "yes" : "NO (bug!)") << endl;
 
    // ---- llfilter ----
    head = readList(argv[1]);
    head = llfilter(head, IsOdd());
    cout << "Remove odds: ";
    print(head);
    dealloc(head);
 
    head = readList(argv[1]);
    head = llfilter(head, GreaterThan(9));
    cout << "Remove values > 9: ";
    print(head);
    dealloc(head);
 
    head = readList(argv[1]);
    head = llfilter(head, RemoveAll());
    cout << "Remove all -> list is " << (head == NULL ? "empty" : "NOT empty (bug!)") << endl;
    dealloc(head);
 
    head = readList(argv[1]);
    head = llfilter(head, RemoveNone());
    cout << "Remove none: ";
    print(head);
    dealloc(head);
 
    head = llfilter((Node*)NULL, IsOdd());
    cout << "Filter on empty list -> " << (head == NULL ? "NULL" : "NOT NULL (bug!)") << endl;


    
    return 0;

}
