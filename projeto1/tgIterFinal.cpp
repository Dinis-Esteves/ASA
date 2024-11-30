#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector> 

using namespace std; 

vector<vector<int>> table; 

vector<int> sequence;

vector<vector<vector<pair<tuple<int, int, int>, tuple<int, int, int>>>>> pl;

// now i have to make it span all the values combining all the current with all the previous from each side.
// but we only store one case per result, the most to the left one, so i eventually can place a second brake conditon
// that is when n reaches maxInt, cause that means that we already have all the possible values and don't need
// to lose time calculating the remaining and save a lot of cicles depending on the case.

// Function to print a tuple of three integers
void printTuple(const std::tuple<int, int, int>& t) {
    std::cout << "(" 
              << std::get<0>(t) << ", " 
              << std::get<1>(t) << ", " 
              << std::get<2>(t) << ")";
}

// Function to print a pair of tuples
void printPairOfTuples(const std::pair<std::tuple<int, int, int>, std::tuple<int, int, int>>& p) {
    std::cout << "First tuple: ";
    printTuple(p.first);
    std::cout << "\nSecond tuple: ";
    printTuple(p.second);
    std::cout << std::endl;
}

void printdp(vector<vector<vector<int>>> dp, int seqLen, int maxInt) {

    for(int i = 0; i < seqLen; i++) {
        for(int j = 0; j < seqLen; j++) {
            printf("{");
            for(int k = 0; k < maxInt; k++) {
                printf("%d ", dp[i][j][k]);
            }
            printf("}");
        }
        printf("\n");
    }
    printf("\n");
}

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

    vector<vector<vector<int>>> dp(seqLen, vector<vector<int>>(seqLen, vector<int>(maxInt)));

    pl.resize(seqLen); for (int i = 0; i < seqLen; ++i) { pl[i].resize(seqLen, vector<pair<tuple<int, int, int>, tuple<int, int, int>>>(maxInt)); }    

   // initialize the diagonal of the table
    for (int i = 0; i < seqLen; i++) {
            dp[i][i][0] = sequence[i];
    }

    //printdp(dp, seqLen, maxInt);
    for (int k = 0; k < seqLen - 1; k++) {
        for (int i = 0; i < seqLen - 1; i++) {
        
            int j = i + k + 1;

            int u = j;
            int v = u - 1;

            int n = 0;
            set<int> stored_results;
            while (v != i - 1) {

                if (n == maxInt) {break;}

                // l and m represents the span of all the value combinations between two positions
                for (int l = 0; l < maxInt - 1; l++) {
                        if (n == maxInt) {break;}
                    for (int m = 0; m < maxInt - 1; m++ ) {

                        if (n == maxInt) {break;}

                        int left = dp[i][v][l] - 1;
                        int right = dp[u][j][m] - 1;

                        if (right < 0 || left < 0) {break;}

                        //printf("i: %d, j: %d, k: %d\n", i, j, k);
                        //printf("r: %d, l: %d\n", right, left);

                        if (left >= 0 && right >= 0) {
                          int result = table[left][right];
                          //printf("Processing: i=%d, j=%d, n=%d, result=%d\n", i, j, n, result);
                          // printf("result: %d\n", result);
                          // printf("bool: %d\n", stored_results.find(result)
                          // == stored_results.end()); case when we are
                          // calculating the final options and find one that
                          // fits in the result
                          if (k == seqLen - 2 && result == target) {
                            pair<tuple<int, int, int>, tuple<int, int, int>> p;

                            get<0>(p.first) = i;
                            get<1>(p.first) = v;
                            get<2>(p.first) = l;

                            get<0>(p.second) = u;
                            get<1>(p.second) = j;
                            get<2>(p.second) = m;

                            dp[i][j][0] = target;
                            pl[i][j][0] = p;

                              //pair<tuple<int,int, int>, tuple<int, int, int>> c = pl[i][j][n];
                              //printf("(%d, %d, %d)\n", i, j, n);
                              //printPairOfTuples(c);
                              //printf("\n");

                            //printdp(dp, seqLen, maxInt);
                            tuple<int, int, int> p2;
                            get<0>(p2) = 0;
                            get<1>(p2) = seqLen - 1;
                            //get<2>(p2) = 0;
                            //printf("Target reached: %d at dp[%d][%d][%d]\n", result, i, j, n);
                            return generateExp(p2);
                            } else if (k != seqLen - 2 && stored_results.find(result) == stored_results.end()) {
                              dp[i][j][n] = result;
                              // printdp(dp, seqLen, maxInt);

                              pair<tuple<int, int, int>, tuple<int, int, int>> p;

                              get<0>(p.first) = i;
                              get<1>(p.first) = v;
                              get<2>(p.first) = l;

                              get<0>(p.second) = u;
                              get<1>(p.second) = j;
                              get<2>(p.second) = m;

                              pl[i][j][n] = p;

                              //pair<tuple<int,int, int>, tuple<int, int, int>> c = pl[i][j][n];

                              //printf("(%d, %d, %d)\n", i, j, n);
                              //printPairOfTuples(c);
                              //printf("\n");
                              /*
                              if (i == 0 && j == 3) {
                              tuple<int, int, int> d;
                              get<0>(d) = i;
                              get<1>(d) = j;
                              get<2>(d) = n;


                              printPairOfTuples(p);

                              printf("Stored result: %d at dp[%d][%d][%d]\n", result, i, j, n);
                              printf("%s\n\n", generateExp(d).c_str());
                              }
                            */

                              stored_results.insert(result);
                              
                              n++;
                            }
                        } 
                    }
                }
                u--;
                v--;
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