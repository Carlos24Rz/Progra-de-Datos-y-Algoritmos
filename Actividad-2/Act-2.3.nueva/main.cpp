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



// https://www.py4u.net/discuss/114256
// verificar funcionamiento
void burbuja(Node* &pthead){

  Node* temp = pthead;
  bool swapped = true;
  int var = 0;
  while(swapped){

    swapped = false;
    temp = pthead;

    while(temp->next != NULL){

      if(temp->registro.getMes() > temp->next->registro.getMes()){
        swapped = true;

        if(temp == pthead){
          temp->next->prev = NULL;
          pthead = temp->next;
        }
        else{
          temp->prev->next = temp->next;
          temp->next->prev = temp->prev;
        }
        temp->prev = temp->next;
        if(temp->next == NULL){
          temp->next = NULL;
        }
        else{
          temp->next = temp->next->next;
          temp->next->prev = temp;
        }
        temp->prev->next = temp;
        temp = temp->prev;
      }
      temp = temp->next;
    }
  }
}




// void burbujaPorValor(Node* &pthead){

//   bool swapped = true;
//   Node* ltptr = NULL;

//   while(swapped){
    
//     Node* head = pthead;
//     swapped = false;

//     while(head->next != ltptr){

//       if(head->next->registro <= head->registro){

//         Node* current = head;
//         Node* nextNode = head->next;
//         Node* temp;
//         temp = (Node*)malloc(sizeof(Node));

//         temp->registro = current->registro;
//         current->registro = nextNode->registro;
//         nextNode->registro = temp->registro;

//         swapped = true;
//         head = head->next;
//       }
//       else
//         head = head->next;
//     }
//     ltptr = head;
//   }
// }



int main()
{
  struct Node *head = NULL;
  leerArchivo(head);
  // burbuja(head);
  
  Imprime(head);
}



