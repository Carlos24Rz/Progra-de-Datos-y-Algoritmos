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

// NOTAS:
// para saber si un nodo solo tiene una raiz, se checa una vez el array status
// HINT:
// SE PUEDE RESOLVER CON: EL ARRAY STATUS DEBE TENER SOLO 1 Y UN CERO

// Tree definition
// The tree contains a single node called the root of the tree
// Each node, except the root, must have a single parent
// The tree should always be connected.
// https://www.baeldung.com/cs/determine-graph-is-tree




NodeBlue* createNodeBlue(){
  NodeBlue* newNodeBlue = new NodeBlue();
  return newNodeBlue;
}

char intToChar(int index){
  return char(index+65);
}


int charToInt(char c){
  return ((int)c)-65;
}


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


void printList(NodeBlue* tmpBlue, int indexArrAzul){
  cout << intToChar(indexArrAzul);

  // Verificar que el NodeBlue apunte a algo que no sea NULL
  if(tmpBlue->next != NULL){
    NodeRed* tmpRed = tmpBlue->next;

    // Imprimir mientras haya NodeRed
    while(tmpRed != NULL){
      cout << " - " << intToChar(tmpRed->data->index); // char((tmpRed->data)+65)
      tmpRed = tmpRed->next;
    }
  }
  cout << endl;
}



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

bool isInVector(vector<int> vecValues, int val){

  int size = vecValues.size();

  for(int i=0; i<size; i++)
    if(vecValues[i] == val)
      return true;
  return false;
}

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

int main() {
  int n; // Vertices
  int m; // Arcos

  // "Vertices: ";
  cin >> n;
  // "Arcos: ";
  cin >> m;

  // n = 13;
  // m = 18;

  // Crear array de nodos azules
  NodeBlue* arrAzul[n];

  loadGraph(arrAzul, n, m);

  // Lista de adyacencias
  for(int i=0; i<n; i++){
    printList(arrAzul[i], i);
  }

  topologicalSort(arrAzul, n, m);

  return 0;
}
