// Programa que trabaja con un grafo dirigido sin ciclos
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 20/10/21
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "node.h"
using namespace std;

// is tree?
// https://www.baeldung.com/cs/determine-graph-is-tree


// Descripcion: Funcion que permite crear un nuevo nodo azul en el heap
// Entrada: Nada
// Salida: Un apuntador a un nodo azul
// Complejidad: O(1)
NodeBlue* createNodeBlue(){
  NodeBlue* newNodeBlue = new NodeBlue();
  return newNodeBlue;
}

// Descripcion: Convertir int a char
// Entrada: int
// Salida: char
// Complejidad: O(1)
char intToChar(int index){
  return char(index+65);
}

// Descripcion: Convertir char a int
// Entrada: char
// Salida: int
// Complejidad: O(1)
int charToInt(char c){
  return ((int)c)-65;
}

// Descripcion: Funcion que permite agregar un nodo rojo a un nodo azul
// Entrada: Arreglo de pointers de nodo azul, indice del nodo azul al que se le desea insertar un nodo rojo, indice del valor que se le debe adjuntar al nodo rojo
// Salida: Nada
// Complejidad: O(n)
void Inserta_al_final(NodeBlue* arrAzul[], int indexArr, int indexValue){

  // Posicion del array al que se le debe insertar un nodo rojo
  NodeBlue* temp = arrAzul[indexArr];

  // Posicion que debe ser insertada en el nodo rojo
  NodeBlue* tempToInsert = arrAzul[indexValue];
  NodeRed* newNodeRed = new NodeRed(tempToInsert);

  // Si mi NodeBlue en la posicion en su posicion no apunta a nada:
  if(temp->next == NULL){
    temp->next = newNodeRed;
    return;
  }

  // En caso de que el NodeBlue en su posicion ya apunte a un NodeRed
  // Obtenemos el primer NodeRed al que apunta NodeBlue
  NodeRed* lastRed = temp->next;

  // Se recorre lastRed hasta el final de la lista ligada para insertar el nodo
  while(lastRed->next != NULL)
    lastRed = lastRed->next;

  lastRed->next = newNodeRed;
  return;
}


// Descripcion: Crear lista de adyacencias
// Entrada: Double pointer al inicio del array azul, vertices, arcos
// Salida: nada
// Complejidad: O(n2)
void loadGraph(NodeBlue** arrAzul, int n, int m){
  char input1, input2;
  int blueValue, redValue;
  for(int i=0; i<n; i++){
    arrAzul[i] = createNodeBlue();
    arrAzul[i]->setIndex(i); // cada NodeBlue guarda su indice correspondiente al arrAzul
  }

  // Creacion de nodos
  for(int i=0; i<m; i++){
    cin >> input1 >> input2;
    blueValue = charToInt(input1);
    redValue = charToInt(input2);
    Inserta_al_final(arrAzul, blueValue, redValue);
  }
}


// Descripcion: Llenar array de restricciones de entrada
// Entrada: Pointer a nodo azul, pointer al inicio del array status
// Salida: Nada
// Complejidad: O(n)
void loadStatus(NodeBlue* arrAzul, int* status) {
  NodeBlue* tmpBlue = arrAzul;
  if(tmpBlue->next != NULL){
    NodeRed* tmpRed = tmpBlue->next;
    while(tmpRed != NULL){
      status[tmpRed->data->index] += 1;
      tmpRed = tmpRed->next;
    }
  }
}


// Descripcion: Actualizar grado de entrada de cada nodo al restarle 1
// Entrada: Pointer a nodo azul, pointer al inicio del array status
// Salida: Nada
// Complejidad: O(n)
void changeStatus(NodeBlue* arrAzul, int* status) {
  NodeBlue* tmpBlue = arrAzul;
  if(tmpBlue->next != NULL){
    NodeRed* tmpRed = tmpBlue->next;
    while(tmpRed != NULL){
      status[tmpRed->data->index] -= 1;
      tmpRed = tmpRed->next;
    }
  }
}


// Descripcion: Verificar si un elemento esta en un vector
// Entrada: Vector de int, valor a buscar
// Salida: Bool de si el valor esta o no
// Complejidad: O(n)
bool isInVector(vector<int> vecValues, int val){
  int size = vecValues.size();

  for(int i=0; i<size; i++)
    if(vecValues[i] == val)
      return true;
  return false;
}



// Descripcion: Imprimir los nodos del DAG usando el algoritmo de Kahn
// Entrada: Double pointer al inicio del array azul, vertices, arcos
// Salida: Nada
// Complejidad: O(n2)
void topologicalSort(NodeBlue** arrAzul, int n, int m) {
  arrQueue myQueue;
  int index;

  // Array de restricciones
  int status[n] = {0};

  vector<int> myVector;

  // Recorrer lista y asignar restricciones
  // Recorrido de nodos azules
  for (int i = 0; i < n; i++) {
    loadStatus(arrAzul[i], status);
  }

  // for (int i = 0; i < n; i++) {
  //   cout << "Nodo " << intToChar(i) << " - " << status[i] << endl;
  // }
 
  // Iniciando agregando los nodos con entradas de cero
  for (int i = 0; i < n; i++) {
    if(status[i] == 0) {
      myQueue.enQueue(i);
      myVector.push_back(i);
    }
  }

  char ar1[n];
  int ar2[n];
  
  // Pop y updates
  while(!myQueue.isEmpty())
  {
    // myQueue.print();
    // cout << endl;
    index = myQueue.top();
    cout << intToChar(index) << " ";
    myQueue.deQueue();
    changeStatus(arrAzul[index], status);

    // for (int i = 0; i < n; i++) {
    //   cout << "Status: " << intToChar(i) << " - " << status[i];
    // }

    for (int i = 0; i < n; i++) {
      if(status[i] == 0 && !isInVector(myVector,i)){
        myQueue.enQueue(i);
        myVector.push_back(i);
      }
    }
  }
  cout << endl;
}


// Descripcion: Funcion que verifica si el Grafo Dirigido (DAG) es un árbol o no
// Entrada: Pointer a array azul, nodos, arcos
// Salida: Bool
// Complejidad: O(n2)
bool isTree(NodeBlue* arrAzul[], int n, int m){

  int status[n] = {0};
  
  // Recorrer lista y asignar restricciones
  // Recorrido de nodos azules
  for (int i = 0; i < n; i++) {
    loadStatus(arrAzul[i], status);
  }

  int raiz = 0; 
  for(int i=0; i<n; i++){
    
    if(status[i] != 1 && raiz == 0)
      raiz = 1;
      
    else if(status[i] == 0 && raiz == 1)
      return false;

    else if(status[i] != 1 && raiz == 1)
      return false;
  }
  return true;
}




int main() {
  int n; // Vertices
  int m; // Arcos

  cin >> n;
  cin >> m;

  // Crear array de nodos azules
  NodeBlue* arrAzul[n];

  // Cargar arcos en lista de adyacencia
  loadGraph(arrAzul, n, m);

  // Checar si el grafo es un arbol
  cout << boolalpha << isTree(arrAzul, n, m) << endl;

  // Topological sort con algoritmo de Kahn
  topologicalSort(arrAzul, n, m);

  return 0;
}
