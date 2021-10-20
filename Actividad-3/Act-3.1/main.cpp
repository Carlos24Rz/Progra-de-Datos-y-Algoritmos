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

int countNodeChildren(struct Node *&root)
{
  struct Node *temp = root;
  int children = 0;

  while (temp != NULL)
  {
    if (temp->left != NULL && temp->right != NULL)
      children = 2;
    else if ((temp->left != NULL && temp->right == NULL) || (temp->left == NULL && temp->right != NULL))
      children = 1;
    break;
  }

  return children;
}

void Eliminar(struct Node *&root, int valor)
{
  struct Node *tmp = root;
  struct Node *padre = NULL; //se necesita tener localizado al nodo Padre del actual elemento

  while (tmp != NULL)
  {
    if (valor == tmp->data) //el elemento se ha encontrado en el arbol
    {
      int children = countNodeChildren(tmp);

      switch (children)
      {
      case 0: // 0 hijos
        if (padre == NULL)
          root = NULL; // si el elemento al eliminar es el unico elemento en la lista
        else
        {
          // se corta el enlace del elemento a lista
          if (valor > padre->data)
            padre->right = NULL;
          else if (valor < padre->data)
            padre->left = NULL;
        }
        break;

      case 1: // 1 hijo
        if (valor > padre->data)
        {
          // conectar hijo del elemento al padre
          if (tmp->left == NULL)
            padre->right = tmp->right;
          else
            padre->right = tmp->left;
        }
        else if (valor < padre->data)
        {
          // conectar hijo del elemento al padre
          if (tmp->left == NULL)
            padre->left = tmp->right;
          else
            padre->left = tmp->left;
        }
        break;

      case 2: // 2 hijos
        padre = tmp->right;

        struct Node *pt = tmp->right;

        int contador = 0;

        //localizar el elemnto menor de los mayores (sucesor)
        while (pt != NULL)
        {
          if (contador > 1)
            padre = padre->left;

          contador++;
          pt = pt->left;
        }

        // mover sucesor a posicion a eliminar
        if (padre->left == NULL)
        {
          tmp->data = padre->data;
          tmp->right = NULL;
        }
        else
        {
          tmp->data = padre->left->data;
          padre->left = NULL;
        }
        break;
      }

      break;
    }
    else // el elemento a eliminar no se ha encontrado en la actual posicion del arbol
    {
      padre = tmp;

      // moverse al siguiente elemento en el arbol
      if (valor > tmp->data)
        tmp = tmp->right;
      else
        tmp = tmp->left;
    }
  }

  /// si el elemento ha eliminar no esta en la lista, la lista queda intacta
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

  // else if (n == 4)
  //   LevelByLevel(root);
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

  Eliminar(root, 1);

  return 0;
}
