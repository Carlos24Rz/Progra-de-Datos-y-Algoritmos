// Programa que trabaja con un binary search tree
// Carlos Daniel Diaz Arrazate  - A01734902
// Jose Angel Gonzalez Carrera  - A01552274
// Carlos Eduardo Ruiz Lira     - A01735706
// 16/10/21
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
  int n;
  string str, input;

  // Crear array
  cout << "Size: ";
  cin >> n;
  int array[n][n];

  // Input
  int j = 0;
  cout << "Fill array: " << endl;
  for (int i = -1; i < n; i++) {
    getline(cin, input);
    istringstream ss(input);
    while (ss >> str) {
      cout << "[" << i << "]" << "[" << j << "]" << " = " << str << endl;
      array[i][j] = stoi(str);
      j++;
    }
    j = 0;
  }




  // Output
  cout << endl << "Print" << endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << array[i][j] << " ";
    }
    cout << endl;
  }


	return 0;

}
