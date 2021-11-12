// Programa que trabaja con un grafo
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 16/10/21
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// IMPORTANTE, DEBEMOS DECLARAR LAS CLASES PARA QUE SE LLAMEN UNAS A OTRAS
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

  cout << char(indexArrAzul + 65);

  // Verificar que el NodeBlue apunte a algo que no sea NULL
  if(tmpBlue->next != NULL){
    NodeRed* tmpRed = tmpBlue->next;

    // Imprimir mientras haya NodeRed
    while(tmpRed != NULL){
      cout << " - " << char((tmpRed->data->index)+65); // char((tmpRed->data)+65)
      tmpRed = tmpRed->next;
    }
    cout << endl;
  }
}

NodeBlue* createNodeBlue(){
  NodeBlue* newNodeBlue = new NodeBlue();
  return newNodeBlue;
}

// poner ascii con alt

int main() {
  int n;
  string str, input;

  // Crear array
  // cout << "Size: ";
  cin >> n;
  int matrix[n][n];


  // Creando array de pointers
  NodeBlue* arrAzul[n];
  for(int i=0; i<n; i++){
    arrAzul[i] = createNodeBlue();
    arrAzul[i]->setIndex(i); // cada NodeBlue guarda su indice correspondiente al arrAzul
    cout << i << " - ";
  }

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin >> matrix[i][j];
      // Aqui tenemos A en i==0
      if(matrix[i][j] == 1){
        // Aqui va la magia 
        Inserta_al_final(arrAzul, i, j);
      }
    }
  }

  cout << "\n------------" << endl;


  for(int i=0; i<n; i++){
    ImprimeListaNodeBlue(arrAzul[i], i);
  }

  
  
  // for(int i=0; i<n; i++){
  //   cout << char(i+65);
  //   Imprime(arrAzul[i]);
  // }


  
  



  // // Output
  // cout << endl << "Print" << endl;
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < n; ++j) {
  //     cout << matrix[i][j] << " ";
  //   }
  //   cout << endl;
  // }



	return 0;

}
