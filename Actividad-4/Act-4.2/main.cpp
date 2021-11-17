// Programa que trabaja con un grafo dirigido sin ciclos
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 20/10/21
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class NodeRed;
class NodeBlue;

class NodeRed{
  public:
    NodeBlue* data = NULL;
    NodeRed* next = NULL;
    NodeRed(){};
    NodeRed(NodeBlue* m_data){
      data = m_data;
    };

};

class NodeBlue{
  public:
    int index;
    bool status = false;
    NodeRed* next = NULL;

    NodeBlue(){
      status = false;
      next = NULL;
    }

    int getData(){
      return index;
    }

    bool getStatus(){
      return status;
    }

    void process(){
      status = true;
    }

    void setIndex(int m_index){
      index = m_index;
    }

};

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


void ImprimeListaNodeBlue(NodeBlue* tmpBlue, int indexArrAzul){
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


// n = vertices m = arcos
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


int main() {
  int n; // Vertices
  int m; // Arcos

//   cout << "Vertices: ";
  cin >> n;
// //   cout << "Arcos: ";
  cin >> m;
    
    // n = 13;
    // m = 18;
    
  // Crear array de nodos azules
  NodeBlue* arrAzul[n];

  loadGraph(arrAzul, n, m);



    // TODO REVISAR N-2, POR QUE???????

//   Lista de adyacencias
  for(int i=0; i<n; i++){
    ImprimeListaNodeBlue(arrAzul[i], i);
  }

  return 0;
}
