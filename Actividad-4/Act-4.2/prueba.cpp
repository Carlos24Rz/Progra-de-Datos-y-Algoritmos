#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace  std;

char intToChar(int index){
  return char(index+65);
}


int charToInt(char c){
  return ((int)c)-65;
}

class Graph{
  int n;
  list<int> *l;
public:
  Graph(int n){
    this->n = n;
    l = new list<int>[n];
  }

  void insertarArista(int x, int y)
  {
    l[x].push_back(y);
  }
  void printAdjList()
  {
    for (int i = 0; i < n; i++)
     {
        cout << i << "->";
        for (int& x : l[i]) {
            cout << x << " ";
        }
        cout << endl;
     }
  }
  
  void printQueue(queue<int> q)
  {
	 //printing content of queue 
	 while (!q.empty()){
		 cout<<" "<<q.front();
		 q.pop();
	 }
	 cout<<endl;
  }

  void topologicalOrder()
  {

    vector<int> inDegree;
    inDegree.resize(n);
    
    for(int i = 0; i < n; i++)
    {
      for(int x : l[i])
      {
        inDegree[x] = inDegree[x] + 1;
      }
    }

    queue<int> q;
    for (int i = 0;i<n;i++)
    {
      if(inDegree[i] == 0) q.push(i);
    }

    int index = 0;
    vector<int> order;
    order.resize(n);
    while(!q.empty())
    {
      int at = q.front();
      q.pop();
      order[index++] = at;
      for(int x : l[at])
      {
        inDegree[x]--;
        if(inDegree[x] == 0)
        {
          q.push(x);
        }
      }
    }

    for(int i : order)
    {
      cout << intToChar(i) << " ";
    }
    cout << endl;
  
  }

};


int main() 
{
  int n,m;

  cin >> n;
  cin >> m;

  Graph g(n);

  for(int i=0;i<m;i++)
  {
    char input1,input2;
    cin >> input1 >> input2;

    int x = charToInt(input1);
    int y = charToInt(input2);
    g.insertarArista(x,y);
  }

  g.printAdjList();
  cout << endl;
  g.topologicalOrder();

  return 0;
} 
