#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
    //Base case: nothing left, so both output lists end here
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }
 
    //Detach the first node and let 'head' move on to the rest of the list
    Node* current = head;
    head = head->next;
 
    //Split the rest first (head ends up NULL when the recursion bottoms out)
    llpivot(head, smaller, larger, pivot);
 
    //Put the detached node at the FRONT of the correct list
    if (current->val <= pivot) {
        current->next = smaller;
        smaller = current;
    } else {
        current->next = larger;
        larger = current;
    }
}
 

