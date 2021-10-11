// Programa que trabaja con una lista ligada de nodos
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
// 8/10/21

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Node
{
  int mes;
  int dia;
  int hora;
  int minuto;
  int segundo;
  string ip;
  string log;
  struct Node *next;
  struct Node *prev;
};

// Conversion de mes a número
int mesNumero(string mes)
{
  int m_mes;
  if (mes == "Jan")
    return m_mes = 1;
  else if (mes == "Feb")
    return m_mes = 2;
  else if (mes == "Mar")
    return m_mes = 3;
  else if (mes == "Apr")
    return m_mes = 4;
  else if (mes == "May")
    return m_mes = 5;
  else if (mes == "Jun")
    return m_mes = 6;
  else if (mes == "Jul")
    return m_mes = 7;
  else if (mes == "Aug")
    return m_mes = 8;
  else if (mes == "Sep")
    return m_mes = 9;
  else if (mes == "Oct")
    return m_mes = 10;
  else if (mes == "Nov")
    return m_mes = 11;
  else
    return m_mes = 12;
}

// Descripcion: Inserta un nodo al inicio de la lista ligada
// Entrada: Referencia de estructura de datos y entero del nodo a insertar
// Salida: Lista con el nuevo nodo
// Complejidad: O(1)
void Inserta_al_inicio(int node_mes, int node_dia, int node_hora, int node_minuto, int node_segundo, string node_ip, string node_log, struct Node *&pthead)
{
  struct Node *newNode = new Node;
  newNode->mes = node_mes;
  newNode->dia = node_dia;
  newNode->hora = node_hora;
  newNode->minuto = node_minuto;
  newNode->segundo = node_segundo;
  newNode->ip = node_ip;
  newNode->log = node_log;
  newNode->next = pthead;
  newNode->prev = NULL;
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

      Inserta_al_inicio(
          mesNumero(string[0]),
          stoi(string[1]),
          stoi(fechas[0]),
          stoi(fechas[1]),
          stoi(fechas[2]),
          string[3],
          string[4],
          head);
    }
  }
}

void Imprime(struct Node *tmp)
{
  while (tmp != NULL)
  {
    cout << tmp->ip << endl;
    tmp = tmp->next;
  }
}

void ordenaBurbuja(struct Node *pthead)
{
  Node *newNode = pthead;
  Node *temp = new Node;

  while (newNode != NULL)
  {
    temp = newNode->next;
    
    if (newNode >= temp)
    {
      if (newNode->prev != NULL)
      {
        newNode->prev->next = temp;
      }

      temp->next->prev = newNode;
      newNode -> next = temp -> next;
      temp->prev = newNode->prev;
      temp-> next = newNode;
      newNode->prev = temp;
    }

    newNode = newNode->next;

  }
}

int main()
{
  struct Node *head = NULL;
  leerArchivo(head);
  Imprime(head);

  ordenaBurbuja(head);
}
