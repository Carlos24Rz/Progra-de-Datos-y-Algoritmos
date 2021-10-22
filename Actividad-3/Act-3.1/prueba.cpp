// Programa que trabaja con un arbol binario de busqueda
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
// 8/10/21

#include <iostream>
using namespace std;

struct Node
{
  int data;
  struct Node *left;
  struct Node *right;
};

struct Node *newNode(int data)
{
  struct Node *temp = new Node;
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

void Insertar(struct Node *&root, int data)
{
  if (root == NULL)
  {
    root = newNode(data);
    return;
  }
  else
  {
    if (data < root->data)
    {
      Insertar(root->left, data);
    }
    else if (data > root->data)
    {
      Insertar(root->right, data);
    }
  }
}

int countChildrens(Node* &root){

    Node* temp = root;

    if(temp != NULL)
        
        if( temp->left != NULL && temp->right != NULL )
            return 2;
    
        else if ((temp->left != NULL && temp->right == NULL) || (temp->left == NULL && temp->right != NULL))
            return 1;

    return 0;
}


void eliminar(Node* &root, int valor){

    Node* temp = root;
    Node* father = NULL;

    while(temp != NULL){

        if(temp->data == valor){

            int children = countChildrens(temp);

            // No tiene hijos y es un nodo hoja
            if(children == 0){

                if(father == NULL)   // Solo habia un elemento en el arbol
                    root = NULL;
                else{
                    if(valor < father->data)
                        father->left = NULL;    // Lo desconectamos
                    else if(valor > father->data)
                        father->right = NULL;   // Lo desconectamos
                }
                // delete temp;
                break;

            }



        }


    }




}



void Inorder(struct Node *root)
{
  if (root == NULL)
  {
    return;
  }
  Inorder(root->left);

  cout << root->data << " ";

  Inorder(root->right);
}

void Preorder(struct Node *root)
{
  if (root == NULL)
    return;

  cout << root->data << " ";

  Preorder(root->left);

  Preorder(root->right);
}

void Postorder(struct Node *root)
{
  if (root == NULL)
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


void printCurrentLevel(struct Node* root, int level){

  if(root != NULL)

    if(level == 1)
      cout << root->data << " ";
    else if(level > 1){
      printCurrentLevel(root->left, level-1);
      printCurrentLevel(root->right, level-1);
    }
}


void LevelByLevel(struct Node* root){

  int hgt = height(root);
  
  if(root!=NULL)

    for(int i=1; i<=hgt; i++)
      printCurrentLevel(root, i);
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

int getLevel(struct Node *root, int data, int i)
{
  if (root == NULL)
  {
    return -1;
  }

  if (root->data == data)
  {
    return i;
  }

  int downlevel = getLevel(root->left, data, i + 1);

  if (downlevel != -1)
  {
    return downlevel;
  }

  downlevel = getLevel(root->right, data, i + 1);
  return downlevel;
}

int whatlevelamI(struct Node *root, int data)
{
  return getLevel(root, data, 0);
}



int main(int argc, char const *argv[])
{
  struct Node *root = NULL;
  Insertar(root, 10);
  Insertar(root, 5);
  Insertar(root, 2);
  // Insertar(root, 1);
  Insertar(root, 7);
  Insertar(root, 15);
  Insertar(root, 12);
  Insertar(root, 17);

  cout << whatlevelamI(root, 1) << endl;

  Inorder(root);
  cout << endl;
  // Preorder(root);
  // cout << endl;
  // Postorder(root);
  // cout << endl;

  cout << "height: " << height(root) << endl;
  LevelByLevel(root);
  cout << endl;


  return 0;
}
