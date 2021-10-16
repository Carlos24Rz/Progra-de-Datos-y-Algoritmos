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


Node* limitInferior(Node* head, string ip){

  Node* temp = head;

  // Creating our arrya of int's of the ip
  string ip_1[5];
  string* pt_1 = ip_1;
  splitIp(pt_1, ip);

  int ip_split[5];
  for (int i = 0; i < 5; i++) {
    ip_split[i] = stoi(ip_1[i]);
  }

  // Base of ip .txt, this changes in the loop
  string ip_list[5];
  string* pt_list = ip_list;
  int ip_split_list[5];


  while (temp != NULL) {

    string iplist = temp->registro.getIP();
    splitIp(pt_list, iplist);
    
    for (int i = 0; i < 5; i++) {
      ip_split_list[i] = stoi(ip_list[i]);
    }

    if(ip_split[0] < ip_split_list[0]){
      break;
    }
    else if(ip_split[0] == ip_split_list[0]){

      if(ip_split[1] < ip_split_list[1])
        break;

      else if(ip_split[1] == ip_split_list[1]){

        if(ip_split[2] < ip_split_list[2])
          break;
        
        else if(ip_split[2] == ip_split_list[2]){

          if(ip_split[3] < ip_split_list[3])
            break;
          
          else if(ip_split[3] == ip_split_list[3]){

            if(ip_split[4] < ip_split_list[4])
              break;
            
            else if(ip_split[4] == ip_split_list[4])
              if(ip_split[5] < ip_split_list[5])
                break; 
          }
        }
      }
    }
    temp = temp->next;
  }
  return temp->prev;
}



Node* limitSuperior(Node* ini, string ip){

  Node* temp = ini;

  // Creating our arrya of int's of the ip
  string ip_1[5];
  string* pt_1 = ip_1;
  splitIp(pt_1, ip);

  int ip_split[5];
  for (int i = 0; i < 5; i++) {
    ip_split[i] = stoi(ip_1[i]);
  }

  // Base of ip .txt, this changes in the loop
  string ip_list[5];
  string* pt_list = ip_list;
  int ip_split_list[5];

  string ip_listNext[5];
  string* pt_listNext = ip_listNext;
  int ip_split_list_next[5];


  while(temp->next != NULL){

    string iplist = temp->registro.getIP();
    splitIp(pt_list, iplist);

    string iplistNext = temp->next->registro.getIP();
    splitIp(pt_listNext, iplistNext);

    for (int i = 0; i < 5; i++) {
      ip_split_list[i] = stoi(ip_list[i]);
      ip_split_list_next[i] = stoi(ip_listNext[i]);
    }

    // cout << "---------------" << endl;
    // cout << "ip_list: " << temp->registro.getIP() << endl;
    // cout << "user_ip: " << ip << endl;
    // cout << "ip_list_next: " << temp->next->registro.getIP() << endl;

    cout << "ip[0]" << ip_split_list[0] << " < " << ip_split[0] << " < " << ip_split_list_next[0] << endl;

    if((ip_split_list[0] <= ip_split[0]) && (ip_split[0] < ip_split_list_next[0])){
      break;
    }
    else if((ip_split_list[0] == ip_split[0]) && (ip_split[0] == ip_split_list_next[0])){

      cout << "ip[1]" << ip_split_list[1] << " < " << ip_split[1] << " < " << ip_split_list_next[1] << endl;

      if((ip_split_list[1] <= ip_split[1]) && (ip_split[1] <= ip_split_list_next[1])){
        break;
      }
      else if((ip_split_list[1] == ip_split[1]) && (ip_split[1] == ip_split_list_next[1])){

        cout << "ip[2]" << ip_split_list[2] << " < " << ip_split[2] << " < " << ip_split_list_next[2] << endl;

        if((ip_split_list[2] <= ip_split[2]) && (ip_split[2] <= ip_split_list_next[2])){
          break;
        }
        else if((ip_split_list[2] == ip_split[2]) && (ip_split[2] == ip_split_list_next[2])){

          cout << "ip[3]" << ip_split_list[3] << " < " << ip_split[3] << " < " << ip_split_list_next[3] << endl;

          if((ip_split_list[3] <= ip_split[3]) && (ip_split[3] <= ip_split_list_next[3])){
            break;
          }
          else if((ip_split_list[3] == ip_split[3]) && (ip_split[3] == ip_split_list_next[3])){

            cout << "ip[4]" << ip_split_list[4] << " < " << ip_split[4] << " < " << ip_split_list_next[4] << endl;

            if((ip_split_list[4] <= ip_split[4]) && (ip_split[4] <= ip_split_list_next[4])){
              break;
            }
            else if((ip_split_list[4] == ip_split[4]) && (ip_split[4] == ip_split_list_next[4])){
              break;
            }
          }
        }
      }
    }
    temp = temp->next;
  }
  return temp;
}


// upperLimit
// recorrer la ip a la derecha hasta que sea diferente



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

  cout << "PRUEBAS:::: " << endl;
  
  Node* ini = limitInferior(head, "118.15.416.57:4486");
  cout << "ini: " << ini->registro.getRegistro() << endl;

  Node* fin = limitSuperior(head, "107.96.3.29:5268");
  cout << "fin: " << fin->registro.getRegistro() << endl;


}



