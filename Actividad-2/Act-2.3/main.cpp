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

  bool operator>(const Node& b)
  {

    string ip_1[5];
    string ip_2[5];

    stringstream ss_1(ip);
    stringstream ss_2((b.ip));

    for (int i = 0; i < 5; i++)
    {
      if(i >= 3)
      {
        getline(ss_1,ip_1[i], ':');
        getline(ss_2,ip_2[i], ':');
      }
      else
      {
        getline(ss_1, ip_1[i], '.');
        getline(ss_2, ip_2[i], '.');
      }
    }

    cout << (stoi(ip_1[0]) > stoi(ip_2[0])) << endl;
    if(stoi(ip_1[0]) > stoi(ip_2[0]))
    {
      return 1;
    }
    else if(stoi(ip_1[0]) == stoi(ip_2[0]))
    {
      if (stoi(ip_1[1]) > stoi(ip_2[1]))
      {
        return 1;
      }
      else if(stoi(ip_1[1]) == stoi(ip_2[1]))
      {
        if (stoi(ip_1[2]) > stoi(ip_2[2]))
        {
         return 1;
        }
        else if(stoi(ip_1[2]) == stoi(ip_2[2]))
        {
          if (stoi(ip_1[3]) > stoi(ip_2[3]))
          {
            return 1;
          }
          else if(stoi(ip_1[3]) == stoi(ip_2[3]))
          {
            if (stoi(ip_1[4]) > stoi(ip_2[4]))
            {
              return 1;
            }
            else if(stoi(ip_1[4]) == stoi(ip_2[4]))
            {
              if(mes > b.mes)
              {
                return 1;
              }
              else if(mes == b.mes)
              {
                if (dia > b.dia)
                {
                  return 1;
                }
                else if(dia == b.dia)
                {
                  if (hora > b.hora)
                  {
                    return 1;
                  }
                  else if(hora == b.hora)
                  {
                    if(minuto > b.minuto)
                    {
                      return 1;
                    }
                    else if(minuto == b.minuto)
                    {
                      if(segundo > b.segundo)
                      {
                        return 1;
                      }
                      else if( segundo == b.segundo)
                      {
                        if(log > b.log)
                        {
                          return 1;
                        }
                        else
                        {
                          return 0;
                        }
                      }
                      else
                      {
                        return 0;
                      }
                    }
                    else
                    {
                      return 0;
                    }
                  }
                  else
                  {
                    return 0;
                  }
                  
                }
                else
                {
                  return 0;
                }
                
              }
              else
              {
                return 0;
              }
            }
            else
            {
              return 0;
            } 
          }
          else
          {
            return 0;
          }
          
        }
        else
        {
          return 0;
        }
        
      }
      else
      {
        return 0;
      }
      
    }
    else
    {
      return 0;
    }
  }

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

      if (current->operator>(*nextNode)) /// ordenado ascendiente
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

int main()
{
  struct Node *head = NULL;
  leerArchivo(head);

  ordenaBurbuja(head);

  cout << head->ip << endl;
  cout << head->next->ip << endl;
  cout << head->next->next->ip << endl;
  cout << head->next->next->next->ip << endl;
}
