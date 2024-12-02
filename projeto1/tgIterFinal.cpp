#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector> 

using namespace std; 
// O(m²/2 * n²) probably mine is like this
vector<vector<int>> table; 

vector<int> sequence;

vector<vector<vector<pair<tuple<int, int, int>, tuple<int, int, int>>>>> pl;

string generateExp(tuple<int, int, int> p) {
    pair<tuple<int, int, int>, tuple<int, int, int>> c; 

    if (get<0>(p) == get<1>(p)) {
        return to_string(sequence[get<0>(p)]);
    } else if (get<0>(p) + 1 == get<1>(p)) {
        return "(" + to_string(sequence[get<0>(p)]) + " " + to_string(sequence[get<1>(p)]) + ")";
    } else {
        c = pl[get<0>(p)][get<1>(p)][get<2>(p)];
        return "(" + generateExp(c.first) + " " + generateExp(c.second) + ")";
    }
}

string findExpression(vector<int> sequence, int target, int seqLen, int maxInt) {
    // handle the caise when seqlen is 1
    if (seqLen == 1 && target == sequence[0]) {
        return to_string(sequence[0]);
    }

    vector<vector<vector<int>>> dp(seqLen, vector<vector<int>>(seqLen, vector<int>(maxInt)));

    pl.resize(seqLen); for (int i = 0; i < seqLen; ++i) { pl[i].resize(seqLen, vector<pair<tuple<int, int, int>, tuple<int, int, int>>>(maxInt, make_pair(make_tuple(0, 0, 0), make_tuple(0, 0, 0)))); }    

   // initialize the diagonal of the table
    for (int i = 0; i < seqLen; i++) {
            dp[i][i][0] = sequence[i];
    }

    for (int k = 0; k < seqLen - 1; k++) {
        for (int i = 0; i < seqLen - 1; i++) {
        
            int j = i + k + 1;

            int u = j;

            int n = 0;
            set<int> stored_results;
            while (u - 1 != i - 1) {

                if (n == maxInt) {break;}

                // l and m represents the span of all the value combinations between two positions
                for (int l = 0; l < maxInt; l++) {
                    if (n == maxInt) {break;}
                    for (int m = 0; m < maxInt; m++) {

                        if (n == maxInt) {break;}

                        int left = dp[i][u - 1][l] - 1;
                        int right = dp[u][j][m] - 1;

                        if (right < 0 || left < 0) {break;}

                        if (left >= 0 && right >= 0) {
                          int result = table[left][right];
                          // case when we are
                          // calculating the final options and find one that
                          // fits in the result
                          if (k == seqLen - 2 && result == target) {
                            pair<tuple<int, int, int>, tuple<int, int, int>> p;

                            get<0>(p.first) = i;
                            get<1>(p.first) = u - 1;
                            get<2>(p.first) = l;

                            get<0>(p.second) = u;
                            get<1>(p.second) = j;
                            get<2>(p.second) = m;

                            dp[i][j][0] = target;
                            pl[i][j][0] = p;

                            tuple<int, int, int> p2;
                            get<0>(p2) = 0;
                            get<1>(p2) = seqLen - 1;
                            get<2>(p2) = 0;

                            return generateExp(p2);
                            } else if (k != seqLen - 2 && stored_results.find(result) == stored_results.end()) {
                              dp[i][j][n] = result;

                              pair<tuple<int, int, int>, tuple<int, int, int>> p;

                              get<0>(p.first) = i;
                              get<1>(p.first) = u - 1;
                              get<2>(p.first) = l;

                              get<0>(p.second) = u;
                              get<1>(p.second) = j;
                              get<2>(p.second) = m;

                              pl[i][j][n] = p;

                              stored_results.insert(result);
                              n++;
                            }
                        } 
                    }
                }
                u--;
            }
            if (j == seqLen - 1) {
                break;
                
            }
        }
    }
    return "";
}

int main() { 
    int maxInt, seqLen; 
    
    cin >> maxInt >> seqLen; 
    
    table.resize(maxInt, vector<int>(maxInt));
        
    // store the input table
    for (int i = 0; i < maxInt; i++) { 
        for (int j = 0; j < maxInt; j++) { 
            cin >> table[i][j]; 
        } 
    } 
    
    sequence.resize(seqLen);
    
    // store the input sequence
    for (int i = 0; i < seqLen; i++) { 
        cin >> sequence[i]; 
    } 
    
    int target; 
    cin >> target; 

    string resp = findExpression(sequence, target, seqLen, maxInt);
    
    if (resp != "") { 
        cout << 1 << endl << resp << endl;
    } else { 
        cout << 0 << endl; 
    } 
    return 0; 
}