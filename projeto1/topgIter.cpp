#include <iostream>
#include <string>
#include <vector> 

using namespace std; 

vector<vector<int>> table; 

void printdp(vector<vector<int>> dp, int seqLen) {

    for(int i = 0; i < seqLen; i++) {
        for(int j = 0; j < seqLen; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
}

string findExpression(vector<int> sequence, int target, int seqLen ) {

    vector<vector<int>> dp(seqLen, vector<int>(seqLen));
    
   // initialize the diagonal of the table 
    for (int i = 0; i < seqLen; i++) {
            dp[i][i] = sequence[i];
    }
for (int k = 0; k < seqLen - 1; k++) {
    for (int i = 0; i < seqLen - 1; i++) {
        
            int j = i + k + 1;

            printf("k = %d\ni = %d\nj = %d\n", k, i, j);

            int right = dp[i][j - 1] - 1;
            int left = dp[i + 1][j] - 1;

            
            printf("right: %d (%d, %d)\nleft: %d (%d, %d)\n", right, i , j - 1, left, i + 1, j );

            dp[i][j] = table[right][left];

            printdp(dp, seqLen);

            if (j == seqLen - 1) {
                break;
                
            }

        }
    }
    
    return string();
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
        
        vector<int> sequence(seqLen); 
        
        // store the input sequence
        for (int i = 0; i < seqLen; i++) { 
            cin >> sequence[i]; 
        } 
        
        int target; 
        cin >> target; 

        findExpression(sequence, target, seqLen);
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