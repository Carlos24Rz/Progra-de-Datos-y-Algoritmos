// Programa que trabaja con una lista ligada de nodos
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
// 8/10/21

#include <iostream>
using namespace std;


struct Node {
   int data;
   struct Node *next;
};

// Descripcion: Inserta un nodo al inicio de la lista ligada
// Entrada: Referencia de estructura de datos y entero del nodo a insertar
// Salida: Lista con el nuevo nodo
// Complejidad: O(1)
void Inserta_al_inicio(struct Node* &pthead, int node_data) {
  struct Node* newNode = new Node;
  newNode->data = node_data;
  newNode->next = pthead;
  pthead = newNode;
}

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

// Descripcion: Elimina un nodo al inicio de la lista ligada
// Entrada: Referencia de estructura de datos
// Salida: Lista con el nodo eliminado
// Complejidad: O(1)
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

// Descripcion: Elimina un nodo al final de la lista ligada
// Entrada: Referencia de estructura de datos
// Salida: Lista con el nodo eliminado
// Complejidad: O(n)
void Elimina_al_final(struct Node* &pthead) {
  //Si la lista esta vacia, mantenerla igual
  if(pthead == NULL) {
    cout << "ERROR" << endl;
  }

  //Cuando se quiere eliminar al final cuando hay un elemento
  else if(pthead->next == NULL){
    Node* temp = pthead;
    pthead = NULL;
    delete temp;
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
  struct Node* head = NULL;
  int user = 1;
  int input;

  while(user != 0) {
    cin >> user;
    if (user == 1) {
      cin >> input;
      Inserta_al_inicio(head,input);
    }
    else if (user == 2) {
      cin >> input;
      Inserta_al_final(head,input);
    }
    else if (user == 3)
      Elimina_al_inicio(head);

    else if (user == 4)
      Elimina_al_final(head);

    else if (user == 5)
      Imprime(head);
  }
  return 0;
}
