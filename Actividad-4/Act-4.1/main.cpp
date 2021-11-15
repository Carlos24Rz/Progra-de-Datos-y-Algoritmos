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
// FALTA ARREGLAR PARA CUANDO SE TENGAN MAS DE 27 ENTRADAS

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


NodeBlue* createNodeBlue(){
  NodeBlue* newNodeBlue = new NodeBlue();
  return newNodeBlue;
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


void imprimeLetra(int index){
  // Si es de A - Z
  if(index <= 25){
    cout << char(index+65);
  }
  // Si requiere de mas de 1 letra
  else if (index >=26){
    imprimeLetra(index/26-1);
    imprimeLetra(index%26);
  }
}


void ImprimeListaNodeBlue(NodeBlue* tmpBlue, int indexArrAzul){
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


// BFS
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

void BFS(NodeBlue* arrAzul[], int inicio) {

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


// DFS
class arrStack{

  int stack[1024];
  int top = -1;

  public:

    arrStack(){};

    void push(int data){
      if(!isFull()){
        top++;
        stack[top] = data;
      }
      else{
        cout << "The stack is full" << endl;
      }
    }

    void pop(){
      if(!isEmpty()){
        stack[top] = -1;
        top--;
      }
      else{
        cout << "Stack already empty. Nothing to pop" << endl;
      }
    }

    int theTop(){
      return stack[top];
    }

    bool isEmpty(){
      return top == -1 ? true : false;
    }

    bool isFull(){
      return top == 1024-1 ? true : false;
    }

    void print(){
      for(int i=0; i<=top; i++){
        imprimeLetra(stack[i]); cout << "  ";
      }
      cout << endl;
    }

};

bool isInVector(vector<int> vecValues, int val){

  int size = vecValues.size();

  for(int i=0; i<size; i++)
    if(vecValues[i] == val)
      return true;
  return false;
}

void DFS(int* matrixAdj, int altura, int inicio){

  // Creando vector de los valores ya procesados
  vector<int> vecValues;

  // Creando el stack
  arrStack myStack;
  myStack.push(inicio);
  vecValues.push_back(inicio);

  while(!myStack.isEmpty()){

    int topStack = myStack.theTop();

    imprimeLetra(topStack); cout << " ";
    myStack.pop();

    int i=altura-1;

    while(i >= 0){
      if(*((matrixAdj+topStack*altura) + i)==1 && !isInVector(vecValues, i)){
        vecValues.push_back(i);
        myStack.push(i);
      }
      i--;
    }
  }
  cout << endl;
}




int main() {
  // Crear array
  int n;
  string str, input;
  cin >> n;
  int matrix[n][n];


  // Creando array de pointers
  NodeBlue* arrAzul[n];
  for(int i=0; i<n; i++){
    arrAzul[i] = createNodeBlue();
    arrAzul[i]->setIndex(i); // cada NodeBlue guarda su indice correspondiente al arrAzul
    // cout << i << " - ";
  }

  // INPUT
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin >> matrix[i][j];
      // Creacion de lista de adyacencias
      if(matrix[i][j] == 1){
        Inserta_al_final(arrAzul, i, j);
      }
    }
  }

  cout << "\n------------" << endl;


  // OUTPUT
  // Matriz de adyacencias
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << "\n------------" << endl;

  // Lista de adyacencias
  for(int i=0; i<n; i++){
    ImprimeListaNodeBlue(arrAzul[i], i);
  }

  cout << "\n------------" << endl;

  // Recorridos
  // BFS
  cout << "BFS" << endl;
  BFS(arrAzul, 0);

  cout << "\n------------" << endl;

  // DFS
  cout << "DFS" << endl;
  DFS((int *)matrix, n, 0);

  // Test case ImprimirLetra
  // for (int i = 0; i < 200; i++) {
  //   imprimeLetra(i);
  //   cout << " ";
  //   if (i%11 == 0)
  //     cout << endl;
  // }



  cout << endl;
	return 0;
}
