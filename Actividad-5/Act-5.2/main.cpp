// Programa que trabaja con un binary search tree y un hash table
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 16/10/21
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "hash.h"
using namespace std;

struct Node
{
  Resumen data;
  struct Node *left;
  struct Node *right;
};


// Descripcion: Crear un nuevo nodo
// Entrada: red y host
// Salida: Nuevo nodo
// Complejidad: O(1)
struct Node *newNode(string red, string host)
{
  struct Node *temp;
  // temp = (Node *)malloc(sizeof(Node));
  temp = new Node;
  temp->data.m_red = red;
  temp->data.m_vecHost.push_back(host);
  // temp->data.m_vecHost[0] = host;
  //  cout << "--Prueba--" << endl;

  temp->left = NULL;
  temp->right = NULL;
  return temp;
}


// Descripcion: Insertar de nodo
// Entrada: Referencia del apuntador a la raiz del arbol, dato a insertar
// Salida: Nada
// Complejidad: O(n)
Node* Insertar(Node* root, string red, string host)
{
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
              return father; // Para salirse de la funcion
            }
          }
          // Distinto host
          temp->data.m_countHost += 1; // Agregamos un nuevo host
          temp->data.m_vecHost.push_back(host);
          return father;
        }

        if(temp->data.isLess(red)){
          temp = temp->right;
        }

        else{ // red > temp->data.m_red
          temp = temp->left;
        }
    }
     
    // Si la raiz es NULL, el arbol esta vacio
    // El newnode es la raiz
    if (father == NULL)
        father = newnode;
 
    // Es un hijo menor
    else if (father->data.isGreater(red)){
      father->left = newnode;
    }
 
    // Es un hijo mayor
    else{
      father->right = newnode;
    }
 
    // Retorna el pointer en donde se inserto el newnode
    return father;
}


// Descripcion: Lectura del archivo para la creacion del arbol
// Entrada: Apuntador a root de lista ligada
// Salida: Nada
// Complejidad: O(n)
void leerArchivo(struct Node *&root)
{
  string line;
  ifstream file("bitacora2.txt");
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

      // to_string(stoi())
       
       string red = to_string(stoi(redes_host[0])) + "." + to_string(stoi(redes_host[1]));
       string host = to_string(stoi(redes_host[2])) + "." + to_string(stoi(redes_host[3]));
       string port = ips[1];
       fecha = myString[0] + " " + myString[1];
       string hora = myString[2];
       string log = myString[4];

      // redF = stof(red);
      // hostF = stof(host);

      if(n==0){
        root = Insertar(root, red, host);
        n++;
      }
      else{
          Insertar(root, red, host);      
      }

    }
  }
}
 

// Descricion: Insercion inorder para el hash table
// Entrada: Root del arbol, Referencia del hash table
// Salida: Nada
// Complejidad: O(n)
void InsertInorder(Node *root, HashTable &myHashTable)
{
  if (root == NULL)
    return;

  InsertInorder(root->left, myHashTable);

  myHashTable.ins(root->data);
  InsertInorder(root->right, myHashTable);
}


// Descricion: Merge sort
// Entrada: Inicio, mitad, fin, vector desordenado
// Salida: Nada
// Complejidad: O(n) 
void merge(int inicio, int mitad, int fin, vector<float> &vHost)
{

    int i = inicio;
    int j = mitad+1;
    int k = inicio;
    vector<float> temp;
    
    while(i<=mitad && j<=fin){
        if(vHost[i] < vHost[j]){
            temp.push_back(vHost[i]);
            i++;
        }
        else{
            temp.push_back(vHost[j]);
            j++;
        }
        k++;
    }

    if(i>mitad){            // Se acabaron los elementos del vHosteglo de i
        while(k<=fin){
            temp.push_back(vHost[j]);
            k++;
            j++;
        }
    }
    else{                // Se acabaron los elementos del arreglo j
        while(k<=fin){
            temp.push_back(vHost[i]);
            k++;
            i++;
        }
    }

    // Copiando los elementos del temporal al original
    for(auto element : temp){
        vHost[inicio] = element;
        inicio++;
    }
    
}


// Descricion: Merge sort
// Entrada: Inicio, fin, vector
// Salida: Nada
// Complejidad: O(log n)
void mergeSort(int inicio, int fin, vector<float> &vHost){

    if(inicio < fin){

        int mitad = (inicio+fin)/2;

        mergeSort(inicio, mitad, vHost);
        
        mergeSort(mitad+1, fin, vHost);
        
        merge(inicio, mitad, fin, vHost);
    }
}



int main()
{

  // Creando hashTable
  HashTable myHashTable;

  struct Node *root = NULL;
  leerArchivo(root);
  InsertInorder(root, myHashTable);
    
  
  // Consultas
  int n = 0;
  string q;
  Resumen* temp;
  vector<float> vFHost;

  cin >> n;
  for(int i=0; i<n; i++) {
    // Buscar red en hashTable
    cin >> q;
    temp = myHashTable.search(q);

    // Si existe el objeto
    if (temp){
      // Imprimir datos de red
      temp->printResumen();

      // Guardar redes de m_vecHost
      for(int i=0; i<temp->m_vecHost.size(); i++){
        vFHost.push_back(stof(temp->m_vecHost[i]));
      }
      
      // Ordernar vector de redes
      mergeSort(0, vFHost.size()-1, vFHost);

      // Imprimir redes
      for(auto h : vFHost)
        cout << h << endl;
      vFHost.clear();
    }

    cout << endl;
  }

  return 0;
}
