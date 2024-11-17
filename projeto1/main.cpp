#include <iostream>
#include <list>

using namespace std;

void printMatrix(list<int>* matrix, int numInt) {

    cout << "Matriz resultante:\n"; for (int i = 0; i < numInt; i++) { for (int val : matrix[i+1]) { cout << val << " "; } cout << endl; }
}

void printList(const list<int>& lst) { 
    printf("Sequence Given:\n");
    for (int val : lst) { cout << val << " "; } cout << endl; 
}

list<int> parseIntLine(string line) {
    int i = 0;

    list<int> output;

    while (line[i] != '\0') {

        if (line[i] != ' ') {
            int num = 0;
            int mult = 1;

            while(line[i] - '0' <= 9 && line[i] - '0' >= 0) {
                num *=  mult;
                num += line[i] - '0';
                i++;
                mult *= 10;
            }

            output.push_back(num); 
        } else {
            i++;
        }

    }

    return output;
}

list<int>* addBuferToMatrix(string buffer, list<int>* matrix, int line) {

    list<int> nums = parseIntLine(buffer);
    
    for(int i : nums) {
        matrix[line + 1].push_back(i);
    }

    return matrix;
}

list<int>* getTable(int numInt) {
    list<int>* matrix = new list<int>[numInt + 1];

    // each line
    for (int i = 0; i < numInt; i++) {

        string buf;

        getline(cin, buf);    

        addBuferToMatrix(buf, matrix, i);
        
    }

    return matrix;
}

list<int> getSequence() {
    string seq;

    getline(cin, seq);

   return parseIntLine(seq); 
}

int main() {

    int numInt, sqLen, result;

    cin >> numInt >> sqLen;
    cin.ignore(); 

    list<int>* table = getTable(numInt);

    list<int> seq = getSequence();

    cin >> result;
    cin.ignore();

    // debugging prints
    printMatrix(table, numInt);
    printList(seq);
    printf("Resultado Esperado:\n%d\n", result);
}