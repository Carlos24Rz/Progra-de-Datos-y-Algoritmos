// Programa que trabaja con un grafo
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 16/10/21
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include <vector>

// NOTAS:
// PROBAR EL CODIGO CON UNA MATRIZ DE TO_DO 0

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



void imprimeLetra(int index){

  index +=65;
  if(index <= 90){
    cout << char(index);
  }
  // Agregar para que añada las demas AA- AB- AC

}


void ImprimeListaNodeBlue(NodeBlue* tmpBlue, int indexArrAzul){
  // cout << char(indexArrAzul + 65);
  imprimeLetra(indexArrAzul);
  
  // Verificar que el NodeBlue apunte a algo que no sea NULL
  if(tmpBlue->next != NULL){
    NodeRed* tmpRed = tmpBlue->next;

    // Imprimir mientras haya NodeRed
    while(tmpRed != NULL){
      cout << " - "; imprimeLetra(tmpRed->data->index); // char((tmpRed->data)+65)
      tmpRed = tmpRed->next;
    }
    cout << endl;
  }
}



NodeBlue* createNodeBlue(){
  NodeBlue* newNodeBlue = new NodeBlue();
  return newNodeBlue;
}



class arrQueue{

  int front = -1;
  int rear = -1;
  NodeBlue* queue[1024]; // Preguntar por hacer esto


  public:

    arrQueue(){}

    void enQueue(NodeBlue* node){

      if(isFull()){
        cout << "Queue is full" << endl;
        return;
      }
      else if(isEmpty()){
        front = rear = 0;
      }
      else{
        rear++;
      }
      queue[rear] = node; 
    }

    void deQueue(){
      
      if(isEmpty()){
        cout << "Queue already empty" << endl;
        return;
      }
      // when the queue has only one element
      else if(front == rear){
        front = rear = -1;
      }
      else{
        queue[front] = NULL;
        front++;
      }
    }

    NodeBlue* top(){
      return queue[front];
    }

    bool isEmpty(){
      return front == -1 && rear == -1 ? true : false;
    }

    bool isFull(){
      return rear == 1023 ? true : false;
    }



};



void BSF(NodeBlue* arrAzul[], int inicio) {
  
  // Crear queue
  arrQueue myQueue;

  // Insertar nodo inicial al queue
  myQueue.enQueue(arrAzul[inicio]);
  arrAzul[inicio]->process();
  
  while(!myQueue.isEmpty())
  {
    NodeBlue* topQueue = myQueue.top();

    if(topQueue->next != NULL){
      NodeRed* tempRed = topQueue->next;

      // Agregar los nodos rojos del Top al queue:
      while(tempRed != NULL){
        if(tempRed->data->getStatus() == false){
          // cout << "Valor que se guardara en la queue: "; imprimeLetra(tempRed->data->index); cout  << endl;
          myQueue.enQueue(tempRed->data);
          tempRed->data->process();
        }
        tempRed = tempRed->next;
      }
    
      imprimeLetra(topQueue->index); cout << " ";
      myQueue.deQueue();

    }

    // Acceder al nodo azul inicial
    // Procesar el nodo (Actualizar status y enviarlo al queue)
    // Imprimir y sacar del queue

    // Funcion de ImprimirRojos
    // Acceder a los nodos rojos apuntados por el nodo azul
    // if status == 0 
    // Procesar los nodos
    // Imprimir y sacar del queue

    // Acceder al primer nodo rojo al que el nodo azul apunta y encontrar su equivalente en nodo azul
    // El nuevo nodo azul sera el temporal -> ImprimirRojos
  }
  cout << endl;
}






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

  cout << "\n------------" << endl;
  

  // int x = 70;
  // int mod = x % 90;
  // cout << "Mod es: " << mod << endl;
  
  // for(int i=0; i<n; i++){
  //   cout << char(i+65);
  //   Imprime(arrAzul[i]);
  // }

  BSF(arrAzul, 0);


  
  



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
