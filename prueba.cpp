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

void ordenaBurbuja(struct Node *pthead)
{
  Node *newNode = pthead;
  Node *temp = newNode->next;

  while (newNode != NULL && temp != NULL)
  {
    if (newNode->valor > temp->valor)
    {
      if (newNode->prev != NULL)
      {
        newNode->prev->next = temp;
        pthead = temp;
      }

      temp->next->prev = newNode;
      newNode -> next = temp -> next;
      temp->prev = newNode->prev;
      temp-> next = newNode;
      newNode->prev = temp;
      
    }

    Imprime(pthead);
    cout << endl;

    newNode = newNode->next;
    temp = newNode -> next;

  }
}

void Inserta_al_inicio(int valor, struct Node *&pthead)
{
  struct Node *newNode = new Node;
  newNode->valor = valor;

  

  newNode->prev = NULL;
  newNode->next = pthead;
  if(pthead != NULL)
    pthead->prev = newNode;
  
  pthead = newNode;
}



int main()
{
  struct Node *head = NULL;
  Inserta_al_inicio(1,head);
  Inserta_al_inicio(2,head);
  Inserta_al_inicio(3,head);
  Inserta_al_inicio(4,head);
  Inserta_al_inicio(5,head);
  Inserta_al_inicio(6,head);


  Imprime(head);

  cout << endl;

  ordenaBurbuja(head);
}