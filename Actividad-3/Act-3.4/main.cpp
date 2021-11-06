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


Node* insert(Node* root, Registro data)
{
    // Crear el nuevo nodo a agregar
    Node* newnode = newNode(data);
 
    // Pointer que recorre el arbol
    Node* temp = root;
 
    // Pointer father mantiene el nodo al que se le debe insertar un hijo
    Node* father = NULL;
 
    while (temp != NULL) {
        father = temp;
        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
 
    // Si la raiz es NULL, el arbol esta vacio
    // El newnode es la raiz
    if (father == NULL)
        father = newnode;
 
    // Es un hijo menor
    else if (data < father->data)
        father->left = newnode;
 
    // Es un hijo mayor
    else
        father->right = newnode;
 
    // Retorna el pointer en donde se inserto el newnode
    return father;
}


// Descripcion: Lectura del archivo para la creacion del arbol
// Entrada: Apuntador a root de lista ligada
// Salida: Nada
// Complejidad: O(n)
int n = 0;

void leerArchivo(struct Node *&root)
{
  string line;
  ifstream file("bitacora7MB.txt");
  if (file.is_open())
  {
    while (getline(file, line))
    {
      stringstream ss(line); // Renglon individual
      string fechas[3];
      string fecha;
      string myString[5];

      for (int i = 0; i < 5; i++)
      {
        if (i == 4)
          getline(ss, myString[i]);
        else
          getline(ss, myString[i], ' ');
      }

      fecha = myString[2];
      stringstream sss(fecha);
      sss << fecha;

      for (int i = 0; i < 3; i++)
      {
        getline(sss, fechas[i], ':');
      }

      Registro r(
          myString[0],
          stoi(myString[1]),
          stoi(fechas[0]),
          stoi(fechas[1]),
          stoi(fechas[2]),
          myString[3],
          myString[4]);

    //   Insertar(root, r);      
    if(n==0)
        root = insert(root, r);
    else 
        insert(root, r);

      cout << "Insertando nodo: " << n << endl;
      n++;
    }
  }
}

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


int main()
{
  struct Node *root = NULL;
  leerArchivo(root);

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
