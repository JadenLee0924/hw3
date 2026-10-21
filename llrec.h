#ifndef LLREC_H
#define LLREC_H
#ifndef NULL
#define NULL 0
#endif


struct Node
{
    int val;
    Node *next;

    Node(int v, Node* n) : val(v), next(n) {}
};


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot);


template <typename Comp>
Node* llfilter(Node* head, Comp pred);






template <typename Comp>
Node* llfilter(Node* head, Comp pred)
{
    
    
    
    if (head == NULL) {
        return NULL;
    }
 
    if (pred(head->val)) {
        
        
        Node* rest = head->next;
        delete head;
        return llfilter(rest, pred);
    }
 
    
    head->next = llfilter(head->next, pred);
    return head;

}

#endif
