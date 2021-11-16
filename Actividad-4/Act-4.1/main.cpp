// Descripcion: 
// Entrada: 
// Salida: 
// Complejidad: O(n)


// Programa que trabaja con un grafo
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 16/10/21
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
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


// Descripcion: Funcion que permite crear un nuevo nodo azul en el heap
// Entrada: Nada
// Salida: Un apuntador a un nodo azul
// Complejidad: O(1)
NodeBlue* createNodeBlue(){
  NodeBlue* newNodeBlue = new NodeBlue();
  return newNodeBlue;
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

// Descripcion: Funcion que permite convertir un indice en una letra
// Entrada: Indice a imprimir
// Salida: Nada
// Complejidad: O(1)
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

// Descripcion: Funcion que permite imprimir los nodos rojos de un nodo azul
// Entrada: Pointer a un nodo azul del que se imprimira la lista de nodos rojos, posicion del nodo azul
// Salida: Nada
// Complejidad: O(n)
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

// Descripcion: Imprimir recorrido de BFS
// Entrada: Lista de adyacencia, nodo inicial
// Salida: Nada
// Complejidad: O(n2)
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


// Descripcion: Imprimir recorrido de DFS
// Entrada: Matriz de adyacencia, nodo inicial
// Salida: Nada
// Complejidad: O(n2)
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


  // OUTPUT
  cout << endl;

  // Matriz de adyacencias
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  // Lista de adyacencias
  for(int i=0; i<n; i++){
    ImprimeListaNodeBlue(arrAzul[i], i);
  }

  cout << endl;

  // Recorridos
  // BFS
  BFS(arrAzul, 0);
  cout << endl;

  // DFS
  DFS((int *)matrix, n, 0);

	return 0;
}
