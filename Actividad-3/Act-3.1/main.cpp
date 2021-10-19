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

void Inorder(struct Node* root) {
  if (root == NULL) {
    return;
  }
  Inorder(root->left);

  cout << root->data << " ";

  Inorder(root->right);
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

void LevelByLevel(struct Node* root){

}

void traversal(struct Node* root, int n) {
  if (n == 1)
    Preorder(root);

  else if (n == 2)
    Inorder(root);

  else if (n == 3)
    Postorder(root);

  else if (n == 4)
    LevelByLevel(root);
}


int getLevel(struct Node* root, int data, int i) {
  if (root == NULL) {
    return -1;
  }

  if (root->data == data) {
    return i;
  }

  int downlevel = getLevel(root->left, data, i+1);

  if (downlevel != -1) {
    return downlevel;
  }

  downlevel = getLevel(root->right, data, i+1);
  return downlevel;
}

int whatlevelamI(struct Node* root, int data) {
  return getLevel(root, data, 0);
}



int main(int argc, char const *argv[]) {
  struct Node * root = NULL;
  Insertar(root, 10);
  Insertar(root, 5);
  Insertar(root, 2);
  Insertar(root, 1);
  Insertar(root, 7);

  Insertar(root, 15);
  Insertar(root, 12);
  Insertar(root, 17);

  cout << whatlevelamI(root, 1) << endl;

  // Inorden(root);
  // cout << endl;
  // Preorder(root);
  // cout << endl;
  // Postorder(root);
  // cout << endl;



  return 0;
}
