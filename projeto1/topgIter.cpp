#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector> 

using namespace std; 

vector<vector<int>> table; 

set<int> valid_values;

vector<int> sequence;

vector<vector<pair<pair<int, int>, pair<int, int>>>> pl;

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

string generateExp(pair<int, int> p) {
    pair<pair<int, int>, pair<int, int>> c; 

    if (p.first == p.second) {
        return to_string(sequence[p.first - 1]);
    } else if (p.first + 1 == p.second) {
        //string asw = string("(%d %d)", sequence[p.first - 1], sequence[p.second - 1]);
        
        return "(%d %d)";
    } else {

        c = pl[p.first][p.second];
        
        return "(" + generateExp(c.first) + generateExp(c.second) + ")";

    }
}

string findExpression(vector<int> sequence, int target, int seqLen ) {

    vector<vector<int>> dp(seqLen, vector<int>(seqLen));

    pl.resize(seqLen, vector<pair<pair<int, int>, pair<int, int>>>(seqLen));
    
   // initialize the diagonal of the tables
    for (int i = 0; i < seqLen; i++) {
            pair<pair<int, int>, pair<int, int>> p;
            p.first.first = i;
            p.first.second = i;
            p.second.first = i;
            p.second.second = i;
            dp[i][i] = sequence[i];
            pl[i][i] = p;
    }
    for (int k = 0; k < seqLen - 1; k++) {
        for (int i = 0; i < seqLen - 1; i++) {
        
            int j = i + k + 1;

            printf("\nk = %d\nm[%d, %d]\n", k, i, j);

            int u = j;
            int v = u - 1;


            while (v != i - 1) {

                int right = dp[i][v] - 1;
                int left = dp[u][j] - 1;

                if (left >= 0 && right >= 0) {
                    int result = table[right][left];

                    //case when we are calculating the final options and find one that fits in the result
                    if (k == seqLen - 2 && result == target) {
                        pair<pair<int, int>, pair<int, int>> p;
                        p.first.first = i;
                        p.first.second = v;
                        p.second.first = u;
                        p.second.second =j;
                        dp[i][j] = target;
                        pl[i][j] = p;
                        printdp(dp,  seqLen);
                        printp(pl, seqLen);
                        break;
                    } else if (k != seqLen - 2 && valid_values.find(result) != valid_values.end()) {
                        dp[i][j] = result;
                        pair<pair<int, int>, pair<int, int>> p;
                        p.first.first = i;
                        p.first.second = v;
                        p.second.first = u;
                        p.second.second =j;
                        pl[i][j] = p;
                        printdp(dp,  seqLen);printf("\nm[%d, %d] op m[%d, %d]\n", i, v, u, j);
                        printp(pl, seqLen);
                        break; 
                    } else {
                    u--;
                    v--; 
                    }
                
                } else {
                u--;
                v--;
                }

            }

            /*
            int right = dp[i][j - 1] - 1;
            int left = dp[i + 1 + k][j] - 1;

            

            dp[i][j] = table[right][left];

            printdp(dp, seqLen);
            */
            if (j == seqLen - 1) {
                break;
                
            }
            //desenvolver o traceback e o escolhedor de possibilidades

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

    for (int i = 0; i < maxInt; i++) { 
        for (int j = 0; j < maxInt ; j++) { 
            int value = table[i][j];
            if (value == target) {
                valid_values.insert(i + 1);
                valid_values.insert(j + 1);
            }
        } 
    } 

    printf("%s\n", findExpression(sequence, target, seqLen).c_str());
    
    // now that we know the target and the operator descriptor table we can know
    // what to expect for the left and the right expressions and with that we can
    // filter by a lot the number of stored values what causes a minor necessity
    // of merging value as we progress in the table

    /*string result = findExpressionWithTarget(numbers, target, seqLength); 
    
    if (result != "") { 
        cout << 1 << endl << result << endl;
    } else { 
        cout << 0 << endl; 
    } 
    */
    return 0; 
}