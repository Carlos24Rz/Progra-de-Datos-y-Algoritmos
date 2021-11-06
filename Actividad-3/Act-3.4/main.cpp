// Programa que trabaja con una lista doblemente ligada de nodos
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
// 16/10/21
#include <iostream>
#include <fstream>
#include <sstream>
#include "registro.h"
#include <vector>
using namespace std;

struct Node
{
  Registro data;
  struct Node *left;
  struct Node *right;
};

struct Node *newNode(Registro data)
{
  struct Node *temp;
  temp = (Node *)malloc(sizeof(Node));

  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

// Descripcion: Insertar de nodo
// Entrada: Referencia del apuntador a la raiz del arbol, dato a insertar
// Salida: Nada
// Complejidad: O(n)
void Insertar(struct Node *&root, Registro data)
{
  if (root == NULL)
  {
    root = newNode(data);
    return;
  }

  else
  {
    if (data < root->data)

      if (root->left == NULL)
        root->left = newNode(data);
      else
        Insertar(root->left, data);

    else if (root->data < data)
      if (root->right == NULL)
        root->right = newNode(data);
      else
        Insertar(root->right, data);
  }
}

// Descripcion: Lectura del archivo para la creacion del arbol
// Entrada: Apuntador a root de lista ligada
// Salida: Nada
// Complejidad: O(n)
int n = 0;
stringstream ss;
stringstream sss;
string line;
string fechas[3];
string fecha;
string myString[5];

void leerArchivo(struct Node *&root)
{
  // string line;
  ifstream file("bitacora2MB.txt");
  if (file.is_open())
  {
    while (getline(file, line))
    {
      // stringstream ss(line); // Renglon individual
      ss << line;
      // cout << line << endl;

      // string fechas[3];
      // string fecha;
      // string myString[5];

      for (int i = 0; i < 5; i++)
      {
        if (i == 4)
          getline(ss, myString[i]);
        else
          getline(ss, myString[i], ' ');
      }

      fecha = myString[2];
      // stringstream sss(fecha);
      sss << fecha;


      for (int i = 0; i < 3; i++)
      {
        getline(sss, fechas[i], ':');
      }

      //  Registro(string mes, int dia, int hora, int minuto, int segundo, string ip, string log)

      Registro* myRegister = new Registro(
          myString[0],
          stoi(myString[1]),
          stoi(fechas[0]),
          stoi(fechas[1]),
          stoi(fechas[2]),
          myString[3],
          myString[4]);
      // Registro r(
      //     myString[0],
      //     stoi(myString[1]),
      //     stoi(fechas[0]),
      //     stoi(fechas[1]),
      //     stoi(fechas[2]),
      //     myString[3],
      //     myString[4]);

      // cout << myRegister->getRegistro() << endl;
      cout << "Insertando nodo: " << n << endl;
      n++;
      Insertar(root, *myRegister);

      delete  myRegister;
      ss.str("");
      ss.clear(); // Clear state flags.
      sss.str("");
      sss.clear(); // Clear state flags.
      
    }
  }
}


// LLega al 41,526


// Descripcion: Almacenar nodos en inorden convexo en un vector
// Entrada: Apuntador a la raiz del arbol
// Salida: Nada
// Complejidad: O(n)
void InorderConvexo(struct Node *root, vector<Registro> &registro)
{
  if (root == NULL)
    return;

  InorderConvexo(root->right, registro);
  registro.push_back(root->data);
  InorderConvexo(root->left, registro);
}

// Lineas que matan el codigo de la bitacora: estas lineas son al ir eliminando las de arriba
// 9666: Apr 02 04:58:48 119.7.10.137:2045 Illegal user
// 19081: Oct 07 21:51:45 260.558.961.482:5850 Illegal user
// 19081: Feb 13 13:53:45 188.644.613.104:2026 Illegal user
// 61074: Oct 07 21:51:09 128.560.636.362:9760 Illegal user
// 61074: Jun 06 06:16:11 937.937.964.25:8073 Failed password for root
// 82078: Jan 15 01:05:26 139.176.217.262:1512 Failed password for root
// 82078: Mar 06 14:52:04 888.709.256.537:5105 Failed password for illegal user test


int main()
{
  struct Node *root = NULL;
  leerArchivo(root);

  //   cout << root->data.getIP() << endl;
  //   cout << root->left->data.getIP() << endl;
  //   cout << root->right->data.getIP() << endl;
  //   cout << root->right->left->left << endl;

  cout << "--------------------" << endl;
  vector<Registro> registros;
  InorderConvexo(root, registros);

  for (int i = 0; i < registros.size(); i++)
  {
    cout << registros[i].getRegistro() << endl;
    if (i == 4) {
      break;
    }
  }


  return 0;
}
