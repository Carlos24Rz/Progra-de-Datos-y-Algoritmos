// Programa que trabaja con un grafo
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 16/10/21
#include <iostream>
#include <string>
#include <sstream>
using namespace std;



void Inserta_al_final(struct Node* &pthead, int node_data) {
  struct Node* newNode = new Node;
  struct Node* last = pthead;
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


class Node{

  private:
    int data;
    bool status = false;
    Node* next;

  public:

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
    }
  }
  
    

  // // Output
  // cout << endl << "Print" << endl;
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < n; ++j) {
  //     cout << matrix[i][j] << " ";
  //   }
  //   cout << endl;
  // }


  cout << char(65) << endl;


	return 0;

}
