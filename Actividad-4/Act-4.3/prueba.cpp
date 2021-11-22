#include <bits/stdc++.h>
#include "class.h"
using namespace std;


// RegistroNode(string date, string time, string port, string log)
void Insertar(RedNode* &pthead, string redData, string hostData, string regDate, string regTime, string regPort, string regLog){
  RedNode* newRedNode = new RedNode(redData);
  HostNode* newHostNode = new HostNode(hostData);
  RegistroNode* newRegistroNode = new RegistroNode(regDate, regTime, regPort, regLog);
    
  //cout << newRedNode->m_data << "." << newHostNode->m_data << ":" << newRegistroNode->getRegistro() << endl;

 
  // Lista vacia
  if (pthead == NULL) {
    
    pthead = newRedNode;
    pthead->next = newHostNode;
    pthead->next->next = newRegistroNode;
    return;
  }
  
  // Recorrer lista RedNode
  RedNode* tempRed = pthead;

  while (tempRed->down != NULL){

    // Red duplicada
    if (tempRed->m_data == newRedNode->m_data){
        delete newRedNode;
        
        // Recorrer lista HostNode
        HostNode* tempHost = tempRed->next;
        while (tempHost->down != NULL) {
          
          // Host duplicado
          if (tempHost->m_data == newHostNode->m_data){
            delete newHostNode;

            // Recorrer lista RegistroNode
            RegistroNode* tempRegistro = tempHost->next;
            while (tempRegistro->down != NULL) {
                
              // Registro duplicado ¡??¡?¡?¡??¡
              if(tempRegistro->getRegistro() == newRegistroNode->getRegistro()){
                delete newRegistroNode;
                return;
              }
              tempRegistro = tempRegistro->down; // Recorrer ciclo
            }
            
            // Insertar registro
            tempRegistro->down = newRegistroNode;
            tempHost->addToCounter(); // Sumar counter
            return;
          }            

          tempHost = tempHost->down;  // Recorrer ciclo
        }
        // Insertar host
        tempHost->down = newHostNode;
        
        newHostNode->next = newRegistroNode;
        tempRed->addToCounter(); // Sumar counter
        return;
    }
    tempRed = tempRed->down;
  }

  // Insertar red
  tempRed->down = newRedNode;
  newRedNode->addToCounter();
  newRedNode->next = newHostNode;
  newHostNode->addToCounter();
  newHostNode->next = newRegistroNode;



  return;
}




void InsertarRegistro(HostNode* &tmpHost, RegistroNode* &newRegistroNode) {
  
  RegistroNode* tmpRegistro = tmpHost->next;
  
  while(tmpRegistro != NULL)
  {
    if (tmpRegistro->getRegistro() == newRegistroNode->getRegistro()){
      delete newRegistroNode;
      return;
    }
    
    if(tmpRegistro->down != NULL) tmpRegistro = tmpRegistro->down; 
  }
  tmpRegistro->down = newRegistroNode;

}


void InsertarHost(RedNode* &tmpRed, HostNode* &newHostNode, RegistroNode* & newRegistroNode) {
  HostNode* tmpHost = tmpRed->next;

  while (tmpHost != NULL) {
    if (tmpHost->m_data == newHostNode->m_data) {
      delete newHostNode;
      // void InsertarRegistro(HostNode* &tmpHost, RegistroNode* &newRegistroNode)
      InsertarRegistro(tmpHost, newRegistroNode);
      return;
    }
    if(tmpHost->down != NULL) tmpHost = tmpHost->down;
  }
  tmpHost->down = newHostNode;
  InsertarRegistro(tmpHost->down, newRegistroNode);
}

void InsertarRed(RedNode* &pthead, string redData, string hostData, string regDate, string regTime, string regPort, string regLog){
  RedNode* newRedNode = new RedNode(redData);
  HostNode* newHostNode = new HostNode(hostData);
  RegistroNode* newRegistroNode = new RegistroNode(regDate, regTime, regPort, regLog);

 
  // Lista vacia
  if (pthead == NULL) {
    pthead = newRedNode;
    pthead->next = newHostNode;
    pthead->next->next = newRegistroNode;
    return;
  }

  // Recorrer lista
  RedNode* tmpRed = pthead;
  while (tmpRed != NULL) {
    //Si la red coincide
    if (tmpRed->m_data == newRedNode->m_data) {
      // Ya no necesitamos el nodo de Red
      delete newRedNode;
      // (RedNode* &tmpRed, HostNode* &newHostNode, RegistroNode* & newRegistroNode) {
      InsertarHost(tmpRed, newHostNode, newRegistroNode);
      return;
    }
    //De lo contrario, mientras el siguiente nodo de Red no sea NULL:
    if(tmpRed->down != NULL) tmpRed = tmpRed->down; // avanza en el ciclo
  }
  
  // Crear una nueva red
  tmpRed->down = newRedNode;
  // InsertarHost()
  InsertarHost(tmpRed->down, newHostNode, newRegistroNode);
}







void leerArchivo(RedNode* &pthead) 
{
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
       string log = redes_host[4];

       //cout << red << "." << host << ":" << port << endl;
        
       InsertarRed(pthead, red,host,fecha,hora,port,log);
    }
  }
}


    



    


int main(){
  RedNode* pthead = NULL;

  cout << "Bucle";
  leerArchivo(pthead);

  cout << "-----" << endl;
  cout << "pthead" << endl;
  cout << "↓" << endl;

  cout << pthead->m_data << "→" << pthead->next->m_data
   << "→" << pthead->next->down->m_data << "→" 
   << pthead->next->down->down->m_data << endl;

  cout << "↓" << endl;  
  cout << pthead->down->m_data << endl;
  cout << "↓" << endl;  
  
  
  return 0;
}


