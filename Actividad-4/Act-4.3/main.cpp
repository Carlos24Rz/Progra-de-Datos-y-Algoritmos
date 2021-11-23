#include <bits/stdc++.h>
#include "class.h"
using namespace std;



void InsertarNuevo(RedNode* &pthead, string redData, string hostData, string regDate, string regTime, string regPort, string regLog){

  RedNode* newRedNode = new RedNode(redData);
  HostNode* newHostNode = new HostNode(hostData);
  RegistroNode* newRegistroNode = new RegistroNode(regDate, regTime, regPort, regLog);

  // Si la lista de red nodes esta vacia, se apunta a ella
  if(pthead==NULL){
    pthead = newRedNode;
    pthead->next = newHostNode;
    pthead->next->next = newRegistroNode;
    return;
  }

  // En caso de que no, se busca el ultimo nodo de red
  RedNode* tmpRed = pthead;
  RedNode* lastRed = NULL; // A este nodo, a su down se le agrega el nuevo valor

  // Se recorre la lista de red nodes
  while(tmpRed != NULL){
    lastRed = tmpRed;

    // El red node esta en la lista
    if(tmpRed->m_data == newRedNode->m_data){
      // Eliminar un nodo
      delete newRedNode;

      // Se recorre la lista de hosts de la red encontrada
      HostNode* tmpHost = tmpRed->next;
      HostNode* lastHost = NULL; // A este nodo, a su down se le agrega el nuevo valor
      while(tmpHost != NULL){
        lastHost = tmpHost;

        // El host esta en la lista
        if(tmpHost->m_data == newHostNode->m_data){
          // Eliminamos un nodo
          delete newHostNode;

          // Se recorre la lista de registros
          RegistroNode* tmpRegistro = tmpHost->next;
          RegistroNode* lastRegistro = NULL; // A este nodo, a su down se le agrega el nuevo valor
          while(tmpRegistro != NULL){
            lastRegistro = tmpRegistro;
            // El registro esta en la lista
            if(tmpRegistro->getRegistro() == newRegistroNode->getRegistro()){
              // Eliminar un nodo
              delete newRegistroNode;
              return;
            }
            tmpRegistro = tmpRegistro->down;
          }
          // El registro no esta en la lista
          lastRegistro->down = newRegistroNode;
          // Agregar el addCounter al host
          tmpHost->addToCounter();
          return;
        }
        tmpHost = tmpHost->down;
      }
      // El host no esta en la lista
      lastHost->down = newHostNode;
      lastHost->down->next = newRegistroNode;
      // Agregar el addCounter al red
      tmpRed->addToCounter();
      return;
    }
    tmpRed = tmpRed->down;
  }
  // El red node no esta en la lista
  lastRed->down = newRedNode;
  lastRed->down->next = newHostNode;
  lastRed->down->next->next = newRegistroNode;
  //
  return;
}

void leerArchivo(RedNode* &pthead) {
  string line;
  ifstream file("bitacoraModificado.txt");
  int n = 0;
  if (file.is_open())
  {
    while (getline(file, line))
    {
      stringstream ss(line); // Renglon individual
      string fecha;
      string ip;
      string red_host;
      string myString[5];
      string ips[2];
      string redes_host[4];

      for (int i = 0; i < 5; i++)
      {
        if (i == 4)
          getline(ss, myString[i]);
        else
          getline(ss, myString[i], ' ');
      }
      
      ip = myString[3];
      stringstream sss(ip);
      sss << ip;

      for (int i = 0; i < 2; i++)
      {
        getline(sss,ips[i],':');
      }

      red_host = ips[0];
      stringstream ssss(red_host);
      ssss << red_host;

       for (int i = 0; i < 4; i++)
       {
        getline(ssss,redes_host[i],'.');
       }

       
       string red = redes_host[0] + "." + redes_host[1];
       string host = redes_host[2] + "." + redes_host[3];
       string port = ips[1];
       fecha = myString[0] + " " + myString[1];
       string hora = myString[2];
       string log = myString[4];

      //  cout << red << "." << host << ":" << port << endl;
        
       InsertarNuevo(pthead, red,host,fecha,hora,port,log);
    }
  }
}


int main(){

  RedNode* pthead = NULL;

  leerArchivo(pthead);

  // Vector de redes
  vector<RedNode*> vecRedes;


  cout << "\n Imprimiendo todo " << endl << endl;
  RedNode* tmpRed = pthead;
  while(tmpRed != NULL){

    cout << tmpRed->m_data << " → ";

    HostNode* tmpHost = tmpRed->next;
    while(tmpHost != NULL){
      cout << tmpHost->m_data << " → ";

      tmpHost = tmpHost->down;
    }
    tmpRed = tmpRed->down;
    cout << endl;
  }




  
  return 0;
}


