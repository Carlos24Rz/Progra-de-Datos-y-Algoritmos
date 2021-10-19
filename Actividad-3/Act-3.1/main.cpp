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

void Insertar(struct Node * &root, int data) {
  if (root == NULL) {
    root = newNode(data);
    return;
  }
  else {
    if (data < root->data) {
      Insertar(root->left, data);
    }
    else if (data > root->data) {
      Insertar(root->right, data);
    }
  }
}

void Inorden(struct Node* root) {
  if (root == NULL) {
    return;
  }
  Inorden(root->left);

  cout << root->data << " ";

  Inorden(root->right);
}


int main(int argc, char const *argv[]) {
  struct Node * root = NULL;
  Insertar(root, 10);
  Insertar(root, 5);
  Insertar(root, 2);
  Insertar(root, 7);

  Insertar(root, 15);
  Insertar(root, 12);
  Insertar(root, 17);



  Inorden(root);
  cout << endl;
  return 0;
}
