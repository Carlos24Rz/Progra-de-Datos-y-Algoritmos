// registro.h                       listo
// el registro este en el nodo      listo
// lectura del archivo              listo
// hacer la sobrecarga              
// burbuja                          
// hacer la busqueda




// Programa que trabaja con una lista ligada de nodos
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
// 8/10/21

#include <iostream>
#include <fstream>
#include <sstream>
#include "registro.h"
using namespace std;



class Node{
    
    public:
        Registro registro;
        struct Node* next;
        struct Node* prev;
};

Node *split(Node *head);

Node *merge(Node *first, Node *second)
{
    // If first linked list is empty
    if (!first)
        return second;
 
    // If second linked list is empty
    if (!second)
        return first;
 
    // Pick the smaller value
    if (first->registro < second->registro)
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

Node *mergeSort(Node *head)
{
    if (!head || !head->next)
        return head;
    Node *second = split(head);
 
    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);
 
    // Merge the two sorted halves
    return merge(head,second);
}

Node *split(Node *head)
{
    Node *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *temp = slow->next;
    slow->next = NULL;
    return temp;
}

// Descripcion: Inserta un nodo al inicio de la lista ligada
// Entrada: Referencia de estructura de datos y entero del nodo a insertar
// Salida: Lista con el nuevo nodo
// Complejidad: O(1)
void Inserta_al_inicio(Registro registro, struct Node* &pthead)
{
  // Node* newNode = new Node; // This doesn't work
  Node* newNode;
  newNode = (Node*)malloc(sizeof(Node));

  newNode->registro = registro;

  newNode->prev = NULL;
  newNode->next = pthead;
  if(pthead != NULL)
    pthead->prev = newNode;
  
  pthead = newNode;
}


//Funcion que guarda contenido de archivo txt en un vector de registros
void leerArchivo(struct Node *&head)
{
  string line;
  ifstream file("bitacora.txt");
  if (file.is_open())
  {
    while (getline(file, line))
    {
      stringstream ss(line); // Renglon individual
      string fechas[3];
      string fecha;
      string string[5];
      for (int i = 0; i < 5; i++)
      {
        if (i == 4)
          getline(ss, string[i]);
        else
          getline(ss, string[i], ' ');
      }
      fecha = string[2];
      stringstream sss(fecha);
      for (int i = 0; i < 3; i++)
      {
        getline(sss, fechas[i], ':');
      }

      Registro r(
                string[0],
                stoi(string[1]),
                stoi(fechas[0]),
                stoi(fechas[1]),
                stoi(fechas[2]),
                string[3],
                string[4]
            );

      Inserta_al_inicio(r, head);
    }
  }
}


void Imprime(struct Node *tmp)
{
  while (tmp != NULL)
  {
    cout << tmp->registro.getRegistro() << endl;
    tmp = tmp->next;
  }
}

int main()
{
  struct Node *head = NULL;
  leerArchivo(head);
  head = mergeSort(head);
  
  ofstream Myfile("sorted.txt");

  struct Node *temp = head;
  while(temp!=NULL)
  {
    Myfile << temp->registro.getRegistro() << endl;
    temp = temp->next;
  }
  Myfile.close();

}


