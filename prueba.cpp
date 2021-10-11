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
  

  while(found == 1)
  {
    struct Node *nextNode = current->next;
    int contador = 0;

    while(nextNode !=NULL)
    {

      if(current->valor > nextNode->valor)
      {
        current -> next = nextNode -> next;

        if(nextNode-> next != NULL)
        {
          nextNode->next->prev = current;
        }

        nextNode -> next = current;
        nextNode -> prev = current -> prev;

        if(current->prev != NULL)
        {
          current->prev->next = nextNode;
        }

        current -> prev = nextNode;
        nextNode = current->next;
        contador++;
      }
      else
      {
        current = current->next;
        nextNode = current->next;
      }
      

    }

    while(current->prev != NULL)
    {
      current = current -> prev;
    }

    if(contador == 0)
    {
      found = 0;
    }

    delete nextNode;

  }

  pthead = current;
  
}

void Inserta_al_inicio(int valor, struct Node *&pthead)
{
  struct Node *newNode = new Node;
  newNode->valor = valor;

  

  newNode->prev = NULL;
  newNode->next = pthead;
  if(pthead != NULL) pthead->prev = newNode;
  
  pthead = newNode;
}



int main()
{
  struct Node *head = NULL;
  Inserta_al_inicio(1,head);
  Inserta_al_inicio(2,head);
  Inserta_al_inicio(6,head);
  Inserta_al_inicio(4,head);
  Inserta_al_inicio(8,head);
  Inserta_al_inicio(0,head);


  Imprime(head);

  cout << endl;

  ordenaBurbuja(head);

  Imprime(head);
}