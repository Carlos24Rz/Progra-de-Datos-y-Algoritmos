#include <iostream>
using namespace std;


// TODO
// Trabajando con un heap max

// Modificar el metodo pop:
    // al eliminar el elemento front, el ultimo elemento (rear) pasa a la posicion del front
    // despues de esto, se debe hacer el heapify para ver que se cumpla el heap

// Modificar el metodo push:
    // al agregar un elemento, se hace en el rear
    // posteriormente, se debe verificar con heapify que sus padres sean mayores que el nuevo elemento


class priority_queue{

    private:
        int front;
        int rear;
        int queue[1024];
        
    public:
        priority_queue(){
            front = -1;
            rear = -1;
        }

        void push(int data){

            if(isFull()){               // Cuando la fila esta llena, no se puede agregar nada
                cout << "Queue is full" << endl;
                return;
            }

            else if(empty()){           // Si la fila esta vacio, ahora empezamos en indice 0
                front = rear = 0;
            }
            
            else{                       // En otro caso, movemos el rear un lugar
                rear++;
            }

            queue[rear] = data;         // Agreamos el valor en la posicion del rear

            // Ahora debemos verificar que se cumpla el heap
            heapifyUp(rear);
        }


        void pop(){

            if(empty()){                // No podemos eliminar algo de una queue vacia
                cout << "Queue is already empty" << endl;
                return;
            }

            else if(front==rear){       // front y rear estan en 0, ahora la fila debe quedarse vacia
                front = rear = -1;
            }

            else{                       // En otro caso, solo movemos el front un lugar
                // front++;

                queue[front] = queue[rear];
                cout << "My value in front is: " << front << " " << queue[front] << endl;
                rear--;
                cout << "My rear is: " << rear << " " << queue[rear] << endl;
                heapifyDown(front);

            }

        }


        int top(){
            if(front!=-1)
                return queue[front];
            else
                return -1;
        }

        bool empty(){
            return ((front==-1 && rear==-1) ? true : false);
        }
        
        int size(){
            return rear+1;
        }


        // Extra functions -------------------------------------------------
        bool isFull(){
            return ((rear == 1024-1) ? true : false);
        }

        void print(){
            if(!empty()){
                cout << "\nPrinting queue: " << endl;
                for(int i=front; i<=rear; i++)
                    cout << queue[i] << " " ;
            }   
        }

        void swap(int indexChild, int indexParent){
            int temp = queue[indexChild];
            queue[indexChild] = queue[indexParent];
            queue[indexParent] = temp;
        }

        void heapifyUp(int indexChild){

            int indexParent = (indexChild-1) / 2;

            if(queue[indexChild] > queue[indexParent]){
                swap(indexChild, indexParent);
                heapifyUp(indexParent);
            }
        }

        void heapifyDown(int indexParent){

            int indexChildHigher = 0;
            int indexLeftChild = (2*indexParent) + 1;
            int indexRigthChild = (2*indexParent) + 2;

            cout << "IndLeftChild: " << indexLeftChild << endl;
            cout << "IndexRightChild: " << indexRigthChild << endl;

            if(indexRigthChild > rear && indexLeftChild > rear)
                return;

            if(indexRigthChild > rear)
                indexChildHigher = indexLeftChild;
            else
                indexChildHigher = (queue[indexLeftChild] > queue[indexRigthChild]) ? indexLeftChild : indexRigthChild;

            cout << "The childHiger is: " << queue[indexChildHigher] << endl;
            cout << endl;
            if(queue[indexChildHigher] > queue[indexParent]){
                swap(indexChildHigher, indexParent);
                heapifyDown(indexChildHigher);
            }
        }
    
};



int main(){

    priority_queue myQueue;

    cout << myQueue.empty() << endl;

    myQueue.push(40);
    myQueue.push(31);
    myQueue.push(25);
    myQueue.push(17);
    myQueue.push(23);
    myQueue.push(22);
    myQueue.push(12);

    myQueue.push(39);
    myQueue.push(44);

    myQueue.pop();

    cout << "\n\nBorrando el 40\n " << endl;
    myQueue.pop();

    cout << "\n\nBorrando el 39\n " << endl;
    myQueue.pop();
   

    myQueue.print();


    cout << "\n\n----------------------" << endl;
    cout << myQueue.top() << endl;


    cout << endl;
    return 0;
}

