#include <iostream>
#include <string>
#include <vector> 

using namespace std; 

vector<vector<int>> table; 

vector<int> sequence;

vector<vector<vector<pair<pair<int, int>, pair<int, int>>>>> pl;

// now i have to make it span all the values combining all the current with all the previous from each side.
// but we only store one case per result, the most to the left one, so i eventually can place a second brake conditon
// that is when n reaches seqLen - 1, cause that means that we already have all the possible values and don't need
// to lose time calculating the remaining and save a lot of cicles depending on the case.

/*
void printdp(vector<vector<int>> dp, int seqLen) {

    for(int i = 0; i < seqLen; i++) {
        for(int j = 0; j < seqLen; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
}

void printp(vector<vector<pair<pair<int, int>, pair<int, int>>>> pl, int seqLen) {
        for(int i = 0; i < seqLen; i++) {
        for(int j = 0; j < seqLen; j++) {
            printf("[(%d, %d), (%d, %d)] ", pl[i][j].first.first, pl[i][j].first.second, pl[i][j].second.first, pl[i][j].second.second);
        }
        printf("\n");
    }
}
*/

string generateExp(pair<int, int> p) {
    pair<pair<int, int>, pair<int, int>> c; 

    if (p.first == p.second) {
        return to_string(sequence[p.first]);
    } else if (p.first + 1 == p.second) {
        return "(" + to_string(sequence[p.first]) + " " + to_string(sequence[p.second]) + ")";
    } else {
        c = pl[p.first][p.second];
        return "(" + generateExp(c.first) + " " + generateExp(c.second) + ")";
    }
}

string findExpression(vector<int> sequence, int target, int seqLen ) {

    vector<vector<vector<int>>> dp(seqLen, vector<vector<int>>(seqLen));

    pl.resize(seqLen, vector<vector<pair<pair<int, int>, pair<int, int>>>>(seqLen));
    
   // initialize the diagonal of the tables
    for (int i = 0; i < seqLen; i++) {
            pair<pair<int, int>, pair<int, int>> p;
            p.first.first = i;
            p.first.second = i;
            p.second.first = i;
            p.second.second = i;
            dp[i][i][0] = sequence[i];
            pl[i][i][0] = p;
    }
    for (int k = 0; k < seqLen - 1; k++) {
        for (int i = 0; i < seqLen - 1; i++) {
        
            int j = i + k + 1;

            int u = j;
            int v = u - 1;


            while (v != i - 1) {

                // n represents the number of values. it allows to store the values by how much to the left they are
                int n = 0;

                // l and m represents the span of all the value combinations between two positions
                for (int l = 0; l < seqLen - 1; l++) {
                    for (int m = 0; m < seqLen - 1; m++ ) {
                        int right = dp[i][v][l] - 1;
                        int left = dp[u][j][m] - 1;

                        if (left >= 0 && right >= 0) {
                            int result = table[right][left];

                            //case when we are calculating the final options and find one that fits in the result
                            if (k == seqLen - 2 && result == target) {
                                pair<pair<int, int>, pair<int, int>> p;
                                p.first.first = i;
                                p.first.second = v;
                                p.second.first = u;
                                p.second.second =j;
                                dp[i][j][n] = target;
                                pl[i][j][n] = p;
                                break;
                            } else if (k != seqLen - 2) {
                                dp[i][j][n] = result;

                                // eventually we have to store in wich index the previous value was stored
                                // so we won't have a pair but 3 numbers instead, i, j represent the place in
                                // the sequence and l/m represent the index in the previous value we got it
                                // since it can have multiple values now, from 1 to seqLen values
                                pair<pair<int, int>, pair<int, int>> p;
                                p.first.first = i;
                                p.first.second = v;
                                p.second.first = u;
                                p.second.second =j;
                                pl[i][j][n] = p;
                                n++;
                            } else {
                            u--;
                            v--; 
                            }
                        
                        } else {
                        u--;
                        v--;
                        }
                    }
                }
            }

            if (j == seqLen - 1) {
                break;
                
            }
        }
    }
    pair<int, int> p;

    p.first = 0; 
    p.second = seqLen - 1;

    return generateExp(p);
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

    string resp = findExpression(sequence, target, seqLen);
    
    if (resp != "") { 
        cout << 1 << endl << resp << endl;
    } else { 
        cout << 0 << endl; 
    } 
    return 0; 
}