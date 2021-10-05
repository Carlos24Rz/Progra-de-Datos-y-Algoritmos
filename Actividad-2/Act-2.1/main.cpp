#include <iostream>
using namespace std;


struct Node {
   int data;
   struct Node *next;
};


void Inserta_al_inicio(struct Node* &pthead, int node_data) {
  struct Node* newNode = new Node;

  newNode->data = node_data;

  newNode->next = pthead;

  pthead = newNode;
}



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

void Elimina_al_inicio(struct Node* &pthead) {
  //Si la lista esta vacia, imprimir "ERROR"
  if(pthead == NULL) {
    cout << "ERROR" << endl;
  }
  else {
  //Placeholder del nodo a borrar
  Node* temp = pthead;
  //Set head al siguiente nodo
  pthead = pthead->next;
  //Delete node
  delete temp;
  }
}

void Elimina_al_final(struct Node* &pthead) {
  //Si la lista esta vacia, mantenerla igual
  if(pthead == NULL) {
    cout << "ERROR" << endl;
  }
  else{
    Node* temp = pthead;
    while (temp->next->next != NULL) {
      temp = temp->next;
    }

    Node* last = temp->next;
    temp->next = NULL;
    delete last;
  }
}



void Imprime(struct Node *tmp) {
   //traverse the list to display each node
   while (tmp != NULL)
   {
      cout << tmp->data << endl;
      tmp = tmp->next;
   }
}



int main() {
  /* empty list */
  struct Node* head = NULL;
  int user = 1;
  int input;
  while(user != 0){
    cin >> user;
    if (user == 1) {
      cin >> input;
      Inserta_al_inicio(head,input);
    }
    else if (user == 2) {
      cin >> input;
      Inserta_al_final(head,input);
    }
    else if (user == 3) {
      Elimina_al_inicio(head);
    }
    else if (user == 4) {
      Elimina_al_final(head);
    }
    else if (user == 5) {
      Imprime(head);
    }
  }
  return 0;
}
