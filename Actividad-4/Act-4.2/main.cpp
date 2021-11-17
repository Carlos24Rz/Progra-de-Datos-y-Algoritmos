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


void loadStatus(NodeBlue* arrAzul, int* status, int n) {
  NodeBlue* tmpBlue = arrAzul;
  if(tmpBlue->next != NULL){
    NodeRed* tmpRed = tmpBlue->next;
    while(tmpRed != NULL){

      status[tmpRed->data->index] += 1;
      // cout << tmpRed->data->index << endl;
      tmpRed = tmpRed->next;
    }
  }
}

void topologicalSort(NodeBlue** arrAzul, int n, int m) {

  // Array de restricciones
  int status[n] = {0};

  // Recorrer lista y asignar restricciones
  // Recorrido de nodos azules
  for (int i = 0; i < n; i++) {
    loadStatus(arrAzul[i], status, i);
  }

  for (int i = 0; i < n; i++) {
    cout << "Nodo " << intToChar(i) << " - " << status[i] << endl;
  }
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

//   Lista de adyacencias
  // for(int i=0; i<n; i++){
  //   printList(arrAzul[i], i);
  // }

  topologicalSort(arrAzul, n, m);

  return 0;
}
