#include <iostream>
#include <list>

using namespace std;

void printMatrix(list<int>* matrix, int numInt) {

    cout << "Matriz resultante:\n"; for (int i = 0; i < numInt; i++) { for (int val : matrix[i+1]) { cout << val << " "; } cout << endl; }
}

list<int>* addBuferToMatrix(string buffer, int numInt, list<int>* matrix, int line) {

    int i = 0;
    int addedNumbers = 0;

    while (buffer[i] != '\0' && addedNumbers != numInt) {

        if (buffer[i] != ' ') {
            int num = 0;
            int mult = 1;

            while(buffer[i] - '0' <= 9 && buffer[i] - '0' >= 0) {
                num *=  mult;
                num += buffer[i] - '0';
                i++;
                mult *= 10;
            }

            matrix[line + 1].push_back(num); 
            addedNumbers++;
        }
        i++;
    }
    return matrix;
}

int main() {

    int numInt, sqLen;

    cin >> numInt >> sqLen;
    cin.ignore(); 

    list<int>* matrix = new list<int>[numInt + 1];

    // each line
    for (int i = 0; i < numInt; i++) {

        string buf;

        getline(cin, buf);    

        addBuferToMatrix(buf, numInt, matrix, i);
        
    }

    printMatrix(matrix, numInt);
}