#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Node
{
  int valor;
  struct Node *next;
  struct Node *prev;
};

void Imprime(struct Node *tmp)
{
  while (tmp != NULL)
  {
    cout << tmp->valor << endl;
    tmp = tmp->next;
  }
}

void ordenaBurbuja(struct Node *&pthead)
{
  struct Node *current = pthead;
  bool found = 1;

  ///Mientras se haya efectuado un swap entre elementos, la lista aun no esta completamente ordenada
  while (found == 1)
  {
    struct Node *nextNode = current->next;
    //Cuenta cuantos swaps se hicieron
    int contador = 0;

    while (nextNode != NULL) /// mientras no hemos llegado al final de la lista
    {

      if (current->valor > nextNode->valor) /// ordenado ascendiente
      {
        current->next = nextNode->next;

        //caso en el que no hemos llegado al ultimo elemento de la lista, pues el siguiente elemento sería NULL
        if (nextNode->next != NULL)
        {
          nextNode->next->prev = current;
        }

        nextNode->next = current;
        nextNode->prev = current->prev;

        //caso en el que no estamos al inicio  de la lista, pues el elemento anterior sería NULL
        if (current->prev != NULL)
        {
          current->prev->next = nextNode;
        }

        current->prev = nextNode;
        nextNode = current->next;
        ///aumenta contador porque se realizo un swap
        contador++;
      }
      else /// el numero actual no es mayor que el siguiente
      {
        /// avanza a los siguientes elementos en la lista para seguir comparando
        /// el contador de swap no aumenta
        current = current->next;
        nextNode = current->next;
      }
    }

    /// tenemos que regresar al inicio de la lista para continuar ordenando los elementos faltantes
    /// requisito para ciclo anidado
    /// esta es la parte que hace el algoritmo O(N^3) - debe haber una forma mas elegante de almacenar
    /// el apuntador inicial de la lista ya modificada
    while (current->prev != NULL)
    {
      current = current->prev;
    }

    ///si no se iniciaron swaps, la lista ya esta ordenada, termina ciclo.
    if (contador == 0)
    {
      found = 0;
    }

    ///libera espacio
    delete nextNode;
  }

  ///modifica la lista original
  pthead = current;
}

void Inserta_al_inicio(int valor, struct Node *&pthead)
{
  struct Node *newNode = new Node;
  newNode->valor = valor;

  newNode->prev = NULL;
  newNode->next = pthead;
  if (pthead != NULL)
    pthead->prev = newNode;

  pthead = newNode;
}

int main()
{
  struct Node *head = NULL;
  Inserta_al_inicio(20, head);
  Inserta_al_inicio(1, head);
  Inserta_al_inicio(15, head);
  Inserta_al_inicio(6, head);
  Inserta_al_inicio(8, head);
  Inserta_al_inicio(2, head);
  Inserta_al_inicio(4, head);
  Inserta_al_inicio(14, head);
  Inserta_al_inicio(7, head);
  Inserta_al_inicio(10, head);
  Inserta_al_inicio(12, head);
  Inserta_al_inicio(3, head);
  Inserta_al_inicio(19, head);
  Inserta_al_inicio(13, head);
  Inserta_al_inicio(18, head);
  Inserta_al_inicio(17, head);
  Inserta_al_inicio(11, head);
  Inserta_al_inicio(5, head);
  Inserta_al_inicio(9, head);

  Imprime(head);

  cout << endl;

  ordenaBurbuja(head);

  Imprime(head);
}