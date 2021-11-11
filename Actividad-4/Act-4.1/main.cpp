// Programa que trabaja con un grafo
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 16/10/21
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Node{

  public:
    int data;
    bool status = false;
    Node* next;

    Node(){}

    Node(int m_data){
      data = m_data;
    }

    int getData(){
      return data;
    }

    bool getStatus(){
      return status;
    }

    void process(){
      status = true;
    }

    void setData(int m_data){
      data = m_data;
    }

};

void Inserta_al_final(Node* &pthead, int node_data) {
  Node* newNode = new Node;
  Node* last = pthead;
  newNode->data = node_data;
  newNode->next = NULL;

  if (pthead == NULL) {
    pthead = newNode;
    return;
  }

  while (last->next != NULL)
    last = last->next;
  last->next = newNode;
  return;
}





void Imprime(Node *tmp) {
   //traverse the list to display each node
   cout << "A->";
   while (tmp != NULL)
   {
      cout << tmp->data << "->" ;
      tmp = tmp->next;
   }
   cout << endl;
}




// poner ascii con alt

int main() {
  int n;
  string str, input;

  // Crear array
  cout << "Size: ";
  cin >> n;
  int matrix[n][n];


  // Creando array de pointers
  Node* arrAzul[n];

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin >> matrix[i][j];
      // Aqui tenemos A en i==0
      if(matrix[i][j] == 1){
        Node* newNode = new Node(j);
        if(arrAzul[i] != NULL){
          arrAzul[i] = newNode;
        }
        else{
          cout << "Entrando a funcion inse" << endl;
          Inserta_al_final(arrAzul[i], j);
        }
      }
    }
  }

  cout << "\n------------" << endl;
  Imprime(arrAzul[0]);



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
