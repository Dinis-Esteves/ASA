#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// global variables
vector<vector<int>> matrix;
int sqLen, target;

vector<int> parseIntLine(string line) {
    int i = 0;

    vector<int> output;

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

vector<int> getSequence() {
    string seq;

    getline(cin, seq);

   return parseIntLine(seq); 
}

vector<vector<int>> getMatrix(int numInt) {
    vector<vector<int>> matrix;

    for (int i = 0; i < numInt; i++) {
        string buf;
        getline(cin, buf);

        vector<int> line = parseIntLine(buf);

        matrix.push_back(line);
    }

    return matrix;
}

pair<vector<int>, vector<string>> getAllResults(vector<int> seq, int len) {
    pair<vector<int>, vector<string>> rt;

    if (len == 1) {
        rt.first.push_back(seq[0]);
        rt.second.push_back((to_string(seq[0])));
        return rt;
    }

    if (len == 2) {
        rt.first.push_back(matrix[seq[0] - 1][seq[1] - 1]); 
        rt.second.push_back("(" + to_string(seq[0]) + " " +  to_string(seq[1]) + ")");
        return rt;
    }

    for (int i = len - 1; i > 0; i--) {
        vector<int> right(seq.begin() + i, seq.end());
        vector<int> left(seq.begin(), seq.begin() + i);

        pair<vector<int>, vector<string>> leftResult = getAllResults(left, i);
        pair<vector<int>, vector<string>> rightResult = getAllResults(right, len - i);

        for (int l = 0; l < static_cast<int>(leftResult.first.size()); l++) {
            for (int r = 0; r < static_cast<int>(rightResult.first.size()); r++) {
                int result = matrix[leftResult.first[l] - 1][rightResult.first[r] - 1];
                string exp = "(" + leftResult.second[l] + " " + rightResult.second[r] + ")";

                if (len == sqLen && result == target) {
                    pair<vector<int>, vector<string>> found;
                    found.first = {1};
                    found.second = {exp};
                    return found;
                }

                rt.first.push_back(result);
                rt.second.push_back(exp);
            }
        }
    }

    return rt;
}

int main() {

    int numInt;

    cin >> numInt >> sqLen;
    cin.ignore(); 

    matrix = getMatrix(numInt);

    vector<int> seq = getSequence();

    cin >> target;

    pair<vector<int>, vector<string>> asw = getAllResults(seq, sqLen);

    if (asw.first.size() != 1) {
        cout << 0 << endl;
    } else {
        cout << asw.first[0] << endl;
        cout << asw.second[0] << endl;
    }

    return 0;
}