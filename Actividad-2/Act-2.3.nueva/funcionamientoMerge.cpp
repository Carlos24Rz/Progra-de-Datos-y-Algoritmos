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
    cout << "\n***Entrando a merge()" << endl;

    if(first != NULL)
      cout << "first: " <<  first->registro.getIP()[0] << endl;
    else
      cout << "first: " << first << endl;

    if(second != NULL)
      cout << "second: " <<  second->registro.getIP()[0] << endl;
    else
      cout << "second: " << second << endl;
  

    // If first linked list is empty
    // if (!first)
    if(first == NULL)
        return second;
 
    // If second linked list is empty
    // if (!second)
    if(second == NULL)
        return first;
 
    // Pick the smaller value
    if (first->registro < second->registro)
    {
        cout << "first->registro < second->registro" << endl;
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        cout << "New first: " << first->registro.getIP()[0] << endl;
        return first;
    }
    else
    {
        cout << "first->registro > second->registro" << endl;
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        cout << "New second: " << second->registro.getIP()[0] << endl;
        return second;
    }
}

Node *mergeSort(Node *head)
{
    cout << "\n---Iniciando un mergeSort()" << endl;
    
    // if (!head || !head->next)
    cout << "head before: " << head->registro.getIP()[0] << endl;
    if(head == NULL || head->next == NULL){
        cout << "entrando al condicional" << endl;
        return head;
    }
    
    Node *second = split(head);

    cout << "second before: " << second->registro.getIP()[0] << endl;
 
    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);

    cout << "head after: " << head->registro.getIP()[0] << endl;
    cout << "second after: " << second->registro.getIP()[0] << endl;
    
    return merge(head,second);
    // Merge the two sorted halves
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
    slow->next = NULL;                // por que es necesaria esta linea???????????????????
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
  ifstream file("bitacora2.txt");
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
    cout << tmp->registro.getIP() << endl;
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

  cout << "\n-------------------------" << endl;
  Imprime(head);




  // cout << "\nRecorriendo el final del arreglo: " << endl;
  // string ip = "998.94.195.38:4160";

  // Node* temp2 = head;
  // int count = 0;
  // while(temp2!=NULL){
  //   if(temp2->registro.getIP() == ip)
  //     cout << "We found it" << endl;
  //   count++;
  //   temp2 = temp2->next;
  // }
  // cout << "\nEl count es: " << count << endl;


}



