// Programa que trabaja con un arbol binario de busqueda
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
// 8/10/21

#include <iostream>
using namespace std;


struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

struct Node* newNode(int data) {
  struct Node *temp = new Node;
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

struct Node* Insertar(struct Node * &root, int data) {
  if (root == NULL) {
    newNode(data);
  }
  else {
    if (data < root->data) {
      root->left = Insertar(root->left, data);
    }
    else if (data > root->data) {
      root->right = Insertar(root->left, data);
    }
  }
  return root;
}


int main(int argc, char const *argv[]) {
  struct Node * root = NULL;
  Insertar(root, 10);
  Insertar(root, 5);
  Insertar(root, 8);
  Insertar(root, 13);
  Insertar(root, 3);
  Insertar(root, 7);
  Insertar(root, 16);
  Insertar(root, 14);
  Insertar(root, 12);
  Insertar(root, 15);



  return 0;
}
