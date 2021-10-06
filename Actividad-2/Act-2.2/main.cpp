#include <iostream>
using namespace std;


struct Node {
   int data;
   struct Node *next;
};

void Inserta_al_final(struct Node* &pthead, int node_data) {
  /* 1. create and allocate node */
  struct Node* newNode = new Node;
  struct Node* last = pthead; /* used in step 5*/
  /* 2. assign data to the node */
  newNode->data = node_data;
  /* 3. set next pointer of new node to null as its the last node*/
  newNode->next = NULL;
  /* 4. if list is empty, new node becomes first node */
  if (pthead == NULL) {
    pthead = newNode;
    return;
  }
  /* 5. Else traverse till the last node */
  while (last->next != NULL)
    last = last->next;
  /* 6. Change the next of last node */
  last->next = newNode;
  return;
}


bool equals(struct Node* pthead_m, struct Node* pthead_n) {
  while (pthead_m != NULL && pthead_n != NULL) {
    if (pthead_m->data != pthead_n->data) {
      return false;
    }
    pthead_m = pthead_m->next;
    pthead_n = pthead_n->next;

  }
  return (pthead_m == NULL && pthead_n == NULL);
}

void concat(struct Node* &pthead_m, struct Node* &pthead_n) {
  struct Node* last = pthead_m;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = pthead_n;
}


void Imprime(struct Node *tmp) {
   //traverse the list to display each node
   while (tmp != NULL)
   {
      cout << tmp->data << endl;
      tmp = tmp->next;
   }
}


void reverse(struct Node* &pthead) {
  struct Node* prev, *curr, *next;
  curr = pthead;
  prev = NULL;
  next = NULL;

  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  pthead = prev;
}



int main() {
  /* empty list */
  struct Node* head_m = NULL;
  struct Node* head_n = NULL;
  int m, n, input;

  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> input;
    Inserta_al_final(head_m,input);
  }
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> input;
    Inserta_al_final(head_n,input);
  }

  reverse(head_m);
  reverse(head_n);
  Imprime(head_m);
  Imprime(head_n);
  concat(head_n,head_m);
  Imprime(head_n);
  //Como se comparan las listas si a la n se le concatena la lista m
  if(equals(head_m,head_n)){
    cout << "true" << endl;
  }
  else cout << "false" << endl;






  return 0;
}



// checando mi git
