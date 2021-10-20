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

void Preorder(struct Node* root){
  if(root == NULL)
    return;
  
  cout << root->data << " ";

  Preorder(root->left);

  Preorder(root->right);
}

void Postorder(struct Node* root){
  if(root == NULL)
    return;
  
  Postorder(root->left);

  Postorder(root->right);

  cout << root->data << " ";
}



int height(struct Node* root){

  if(root == NULL)
    return 0;
  
  int leftHeight = height(root->left);
  int rightHeight = height(root->right);

  if(leftHeight > rightHeight)
    return leftHeight+1;
  else
    return rightHeight+1;
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
  Insertar(root, 18);


  Inorden(root);
  cout << endl;
  Preorder(root);
  cout << endl;
  Postorder(root);
  cout << endl;

  cout << "Height: " << height(root) << endl;


  return 0;
}
