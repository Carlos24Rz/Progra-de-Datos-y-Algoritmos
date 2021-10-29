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
                front++;
            }

        }


        int top(){
            return queue[front];
        }

        bool empty(){
            return ((front==-1 && rear==-1) ? true : false);
        }
        
        int size(){
            return rear+1;
        }


        // Extra functions -------------------------------------------
        bool isFull(){
            return ((rear == 1024-1) ? true : false);
        }

        void print(){
            if(!empty())
                for(int i=front; i<=rear; i++)
                    cout << queue[i] << " " ;
        }



    
};



int main(){

    priority_queue myQueue;

    cout << myQueue.empty() << endl;

    myQueue.push(2);
    myQueue.push(5);
    myQueue.push(7);
    myQueue.pop();


    cout << "\nPrinting queue: " << endl;
    myQueue.print();


    cout << endl;
    return 0;
}

