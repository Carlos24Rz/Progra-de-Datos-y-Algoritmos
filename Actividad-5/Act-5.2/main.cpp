// Programa que trabaja con un binary search tree y un hash table
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 16/10/21
#include <iostream>
#include <fstream>
#include <sstream>
#include "resumen.h"
#include <vector>
#include <string>
using namespace std;

struct Node
{
  Resumen data;
  struct Node *left;
  struct Node *right;
};

struct Node *newNode(float red, float host)
{
  struct Node *temp;
  // temp = (Node *)malloc(sizeof(Node));
  temp = new Node;
  temp->data.m_red = red;
  // cout << red << " - " << host << endl;
  temp->data.m_vecHost.push_back(host);
  // temp->data.m_vecHost[0] = host;
//  cout << "--Prueba--" << endl;

  temp->left = NULL;
  temp->right = NULL;
  return temp;
}




// Descripcion: Insertar 
Node* Insertar(Node* root, float red, float host)
{
    // cout << "Insertando" << endl;
    // Crear el nuevo nodo resumen a agregar
    Node* newnode = newNode(red, host);
    // Resumen* nuevoResumen = newResumen(red, host);
 
    // Pointer que recorre el arbol
    Node* temp = root;

    // Pointer father mantiene el nodo al que se le debe insertar un hijo
    Node* father = NULL;

    
 
    while (temp != NULL) {
        father = temp;

        // Misma red (no hay que inserta otro nuevo nodo Resumen)
        if(temp->data.m_red == red){
          temp->data.m_countReg += 1; // Agregamos un registro
          // Comparar el nuevo host con el vector de host 
          for(int i=0; i<temp->data.m_vecHost.size(); i++ ){
            // Mismo host
            if(temp->data.m_vecHost[i] == host){
              // temp->m_countReg += 1;
              return father; // Para salirse de la funcion
            }
          }
          // Distinto host
          temp->data.m_countHost += 1; // Agregamos un nuevo host
          temp->data.m_vecHost.push_back(host);
          return father;
        }

        if(red < temp->data.m_red){
          temp = temp->left;
        }

        else{ // red > temp->data.m_red
          temp = temp->right;
        }
    }
    
 
    // Si la raiz es NULL, el arbol esta vacio
    // El newnode es la raiz
    if (father == NULL)
        father = newnode;
 
    // Es un hijo menor
    else if (red < father->data.m_red){
      father->left = newnode;
      // cout << "Father-left: " << newnode->data.m_red << endl;
    }
 
    // Es un hijo mayor
    else{
      father->right = newnode;
      // cout << "Father-right: " << newnode->data.m_red << endl;
    }
 
    // Retorna el pointer en donde se inserto el newnode
    return father;
}


void leerArchivo(struct Node *&root)
{
  string line;
  ifstream file("bitacoraModificado.txt");
  int n = 0;
  
  float redF;
  float hostF;

  // vector<char> ip;
  string ip;

  if (file.is_open())
  {
    while (getline(file, line))
    {
      stringstream ss(line); // Renglon individual
      string fecha;
      string ip;
      string red_host;
      string myString[5];
      string ips[2];
      string redes_host[4];

      for (int i = 0; i < 5; i++)
      {
        if (i == 4)
          getline(ss, myString[i]);
        else
          getline(ss, myString[i], ' ');
      }
      
      ip = myString[3];
      stringstream sss(ip);
      sss << ip;

      for (int i = 0; i < 2; i++)
      {
        getline(sss,ips[i],':');
      }

      red_host = ips[0];
      stringstream ssss(red_host);
      ssss << red_host;

       for (int i = 0; i < 4; i++)
       {
        getline(ssss,redes_host[i],'.');
       }

       
       string red = redes_host[0] + "." + redes_host[1];
       string host = redes_host[2] + "." + redes_host[3];
       string port = ips[1];
       fecha = myString[0] + " " + myString[1];
       string hora = myString[2];
       string log = myString[4];

      redF = stof(red);
      hostF = stof(host);

      // cout << "Red:  " << redF << endl;
      // cout << "Host: " << hostF << endl;
      // cout << "IP: " << ip << endl;

      if(n==0){
        root = Insertar(root, redF, hostF);
        n++;
      }
      else{
          Insertar(root, redF, hostF);      
      }

    }
  }
}


void Inorder(Node *root)
{
  if (root == NULL)
    return;

  Inorder(root->left);
  cout << root->data.m_red << endl;
  Inorder(root->right);
}


void Preorder(Node *root)
{
  if (root == NULL)
    return;
  cout << root->data.m_red << endl;
  Preorder(root->left);
  Preorder(root->right);
}


int main()
{
  


  cout << "Hello world" << endl;
  struct Node *root = NULL;
  leerArchivo(root);
  Inorder(root);

  cout << "\nTesting" << endl;

  // NOTA: Cambie los contadores de 0 a 1
  // NOTA: Revisar cuando se repiten, en bitacora2: 10.03, este valor se repite varias veces

  cout << "Red:           " << root->left->left->data.m_red << endl;
  cout << "Num registros: " << root->left->left->data.m_countReg << endl;
  cout << "Num hosts:     " << root->left->left->data.m_countHost << endl;
  cout << "Imprimiendo registros: " << endl;

  for(auto h : root->left->left->data.m_vecHost)
    cout << h << endl;
  // cout << root->data.m_vecHost[0] << endl;

  return 0;
}
