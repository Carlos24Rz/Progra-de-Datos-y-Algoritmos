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
#include <vector>
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

void splitIp(vector<int> &arr, string ip) {
  string arrIp[5];
  stringstream ss(ip);

  for (int i = 0; i < 5; i++)
  {
    if(i >= 3)
    {
      getline(ss,arrIp[i], ':');
    }
    else
    {
      getline(ss,arrIp[i], '.');
    }

    arr.push_back(stoi(arrIp[i]));
    }
}

bool compararMenor(string ipUsuario, string ipLista)
{
  string ipU = ipUsuario;
  string ipL = ipLista;

  vector<int> usuario, lista;
  splitIp(usuario, ipU);
  splitIp(lista, ipL);

  for (int i = 0; i < 5; i++)
  {
    if(usuario[i] < lista[i]) return 1;
    else if(usuario[i] > lista[i]) return 0;
  }

  return 0;
}

void Imprime(struct Node *pthead)
{
  struct Node *tmp = pthead;
  while (tmp != NULL)
  {
    cout << tmp->registro.getRegistro() << endl;
    tmp = tmp->next;
  }
  delete tmp;
}

void Imprime(struct Node *inicio,struct Node *final)
{
  struct Node *tmp = final;

  if( inicio == NULL && final == NULL)
  {
    cout << " " << endl;
  }
  else if(tmp == inicio)
  {
    cout << tmp->registro.getRegistro() << endl;
  }
  else
  {
    while(tmp != NULL && tmp != inicio)
    {
      cout << tmp->registro.getRegistro() << endl;
      tmp = tmp->prev;
      if(tmp == inicio && tmp != NULL) cout << tmp->registro.getRegistro() << endl;
    }
  }
  
}

void guardarBusqueda(struct Node *inicio,struct Node *final)
{
  ofstream Myfile1("sortedSearched.txt");
  struct Node* tmp = inicio;

  if( inicio == NULL && final == NULL)
  {
    Myfile1 << " " << endl;
  }
  else if(inicio == final)
  {
    Myfile1 << tmp->registro.getRegistro() << endl;
  }
  else
  {
    while(tmp != NULL && tmp != final)
    {
      Myfile1 << tmp->registro.getRegistro() << endl;
      tmp = tmp->next;
      if(tmp == final && tmp != NULL) Myfile1 << tmp->registro.getRegistro() << endl;
    }
  }

  Myfile1.close();

}

void busqueda(struct Node *head, string ipInicio, string ipFinal)
{
  struct Node* ptini = NULL, *ptfin = NULL;
  struct Node* temp = head;

  //obtener el limite inferior
  while (temp != NULL) 
  {
    if(ipInicio == temp->registro.getIP())
    {
      ptini = temp;
      break;
    }
    else
    {
      if(compararMenor(ipInicio,temp->registro.getIP()))
      {
        ptini = temp;
        break;
      }

      ptini = temp;
    }

    temp = temp->next;
  }

  if(temp == NULL) ptini = NULL;
  
  temp = head;

  //obtener el limite superior
  while (temp != NULL)
  {
    if (ipFinal == temp->registro.getIP())
    {
      ptfin = temp;
      break;
    }
    else
    {
      if(compararMenor(ipFinal,temp->registro.getIP()))
      {
        ptfin = temp->prev;
        break;
      }

      ptfin = temp;
    }

    temp = temp->next;
  }

  if(ptfin != NULL)
  {
    while(ptfin->next != NULL)
    {
      if(ptfin->registro.getIP() == ptfin->next->registro.getIP())
      {
        ptfin = ptfin -> next;
      }
      else break;
    }
  }
  
  if(compararMenor(ipFinal,head->registro.getIP()) || ptini == NULL) 
  {
    ptini = NULL;
    if(temp == NULL) ptfin = NULL;
  }

  Imprime(ptini,ptfin);
  guardarBusqueda(ptini,ptfin);

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

  string ipInicio;
  string ipFinal;
  struct Node *final;

  cin >> ipInicio;
  cin >> ipFinal;

  if (ipInicio > ipFinal)
  {
    head = NULL;
    final = NULL;
    Imprime(head, final);
    guardarBusqueda(head,final);
  }
  else
  {
    busqueda(head, ipInicio, ipFinal);
  }
  
}
