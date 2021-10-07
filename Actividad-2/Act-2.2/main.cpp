#include <iostream>
using namespace std;


struct Node {
   int data;
   struct Node *next;
};


// Descripcion: Inserta un nodo al final de la lista ligada
// Entrada: Referencia de estructura de datos y entero del nodo a insertar
// Salida: Lista con el nuevo nodo
// Complejidad: O(n)
void Inserta_al_final(struct Node* &pthead, int node_data) {
  struct Node* newNode = new Node;
  struct Node* last = pthead;
  newNode->data = node_data;
  newNode->next = NULL;
  if (pthead == NULL) {
    pthead = newNode;
    return;
  }
  while (last->next != NULL)
    last = last->next;
  last->next = newNode;
  return;
}


// Descripcion: Invierte el orden de la lista ligada
// Entrada: Referencia de estructura de datos y entero del nodo a insertar
// Salida: Lista invertida
// Complejidad: O(n)
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


// Descripcion: Compara si dos listas ligadas son iguales
// Entrada: 2 Pointers a las listas
// Salida: Bool
// Complejidad: O(n)
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


// Descripcion: Concatena el cotenido de una lista a otra
// Entrada: Referencia del pointer a 2 listas
// Salida: Lista concatenada
// Complejidad: O(n)
void concat(struct Node* &pthead_m, struct Node* &pthead_n) {
  struct Node* last = pthead_m;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = pthead_n;
}


// Descripcion: Imprime los datos de la lista ligada
// Entrada: Pointer a estructura de datos
// Salida: Impresión de la lista
// Complejidad: O(n)
void Imprime(struct Node *tmp) {
   //traverse the list to display each node
   while (tmp != NULL)
   {
      cout << tmp->data << endl;
      tmp = tmp->next;
   }
}






int main() {
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
