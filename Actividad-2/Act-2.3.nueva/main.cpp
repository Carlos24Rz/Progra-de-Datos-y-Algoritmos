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

void splitIp(string *ptstring, string ip) {
  stringstream ss(ip);
  for (int i = 0; i < 5; i++)
  {
    if(i >= 3)
    {
      getline(ss,ptstring[i], ':');
    }
    else
    {
      getline(ss,ptstring[i], '.');
    }
  }
}



void busqueda(struct Node *head, string ip1, string ip2)
{
  struct Node* ptini = NULL, *ptfin = NULL;
  struct Node* temp = head;

  string ip_1[5];
  string* pt_1 = ip_1;
  splitIp(pt_1, ip1);

  int ip_split[5];

  for (int i = 0; i < 5; i++) {
    ip_split[i] = stoi(ip_1[i]);
  }

  string ip_list[5];
  string* pt_list = ip_list;
  int ip_split_list[5];

  while (temp != NULL) {
    string iplist = temp->registro.getIP();
    splitIp(pt_list, iplist);


    for (int i = 0; i < 5; i++) {
      ip_split_list[i] = stoi(ip_list[i]);
    }

      if(ip_split_list[0] > ip_split[0]) {
        ptini = temp;
        break;
      }
      else if(ip_split_list[0] == ip_split[0]) {
        if(ip_split_list[1] > ip_split[1]) {
          ptini = temp;
          break;
        }
        else if(ip_split_list[1] == ip_split[1]) {
          if(ip_split_list[2] > ip_split[2]) {
            ptini = temp;
            break;
          }
          else if(ip_split_list[2] == ip_split[2]) {
            if(ip_split_list[3] > ip_split[3]) {
              ptini = temp;
              break;
            }
            else if(ip_split_list[3] == ip_split[3]) {
              if(ip_split_list[4] > ip_split[4]) {
                ptini = temp;
                break;
              }
              else if(ip_split_list[4] == ip_split[4]) {
                ptini = temp;
                break;
              }
            }
          }
        }
      }
    temp = temp->next;
  }


  string ip_2[5];
  string* pt_2 = ip_2;
  splitIp(pt_2, ip2);

  temp = ptini;

  if (ptini != NULL) {
    cout << "Ini: " << ptini->registro.getRegistro() << endl;
  }
  else {
    cout << "Error" << endl;
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
  busqueda(head, "999.94.195.38:4160", "960.96.3.29:5267");
}
