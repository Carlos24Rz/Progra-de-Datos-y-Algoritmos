#include <iostream>
using namespace std;

class NodeRed;
class NodeBlue;

class NodeRed{
  public:
    NodeBlue* data = NULL;
    NodeRed* next = NULL;
    NodeRed(){};
    NodeRed(NodeBlue* m_data){
      data = m_data;
    };

};

class NodeBlue{
  public:
    int index;
    bool status = false;
    NodeRed* next = NULL;

    NodeBlue(){
      status = false;
      next = NULL;
    }

    int getData(){
      return index;
    }

    bool getStatus(){
      return status;
    }

    void process(){
      status = true;
    }

    void setIndex(int m_index){
      index = m_index;
    }

};

class arrQueue{
  int front = -1;
  int rear = -1;
  int queue[1024]; // Preguntar por hacer esto

  public:

    arrQueue(){}

    void enQueue(int node){

      if(isFull()){
        cout << "Queue is full" << endl;
        return;
      }
      else if(isEmpty()){
        front = rear = 0;
      }
      else{
        rear++;
      }
      queue[rear] = node;
    }

    void deQueue(){

      if(isEmpty()){
        cout << "Queue already empty" << endl;
        return;
      }
      // when the queue has only one element
      else if(front == rear){
        front = rear = -1;
      }
      else{
        queue[front] = -1;
        front++;
      }
    }

    int top(){
      return queue[front];
    }

    bool isEmpty(){
      return front == -1 && rear == -1 ? true : false;
    }

    bool isFull(){
      return rear == 1023 ? true : false;
    }

    void print(){
      for(int i=0; i<=rear; i++)
        cout << queue[i] << " - ";
    }



};
