#include <cstdio>
#include <iostream>
#include <string> 
#include <vector> 

using namespace std; 

vector<vector<int>> table; 

string constructExpression(vector<vector<vector<int>>>& dp, int i, int j, int result) {
    if (i == j) {
        return to_string(dp[i][i][0]); 
    } 
    for (int k = j - 1; k >= i; k--) {
        for (int left : dp[i][k]) {
            for (int right : dp[k + 1][j]) {

                if (table[left - 1][right - 1] == result) {
                    string leftExpr = constructExpression(dp, i, k, left); 
                    string rightExpr = constructExpression(dp, k + 1, j, right); 
                    
                    return "(" + leftExpr + " " + rightExpr + ")"; 
                    } 
                }
            } 
        } 
        return "";
    } 
                    
    string findExpressionWithTarget(vector<int>& numbers, int target, int n) {

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n)); 
        for (int i = 0; i < n; i++) { 
            dp[i][i].push_back(numbers[i]); 
            } 
                    
        for (int cl = 2; cl <= n; cl++) {
             for (int i = 0; i <= n - cl; i++) {
                int j = i + cl - 1; 
                for (int k = j - 1; k >= i; k--) {
                    for (int p = 0; p < (int) dp[i][k].size(); p++) {
                        for (int q = 0; q < (int) dp[k + 1][j].size(); q++) {
                            int left = dp[i][k][p]; 
                            int right = dp[k + 1][j][q];
                            int result = table[left - 1][right - 1];
                            dp[i][j].push_back(result); }
                        } 
                    }
                } 
        } 

for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) { cout << "dp[" << i << "][" << j << "]: "; for (int k = 0; k < (int) dp[i][j].size(); k++) { cout << dp[i][j][k] << " "; } cout << endl; } }

        for (int i = 0; i < (int) dp[0][n - 1].size(); i++) {
            if (dp[0][n - 1][i] == target) {
                 string expression = constructExpression(dp, 0, n - 1, target); 
                 return expression; 
            } 
        } 
        return ""; 
    } 
    
    int main() { 
        int maxInt, seqLength; 
        
        cin >> maxInt >> seqLength; 
        
        table.resize(maxInt, vector<int>(maxInt));
         
        for (int i = 0; i < maxInt; i++) { 
            for (int j = 0; j < maxInt; j++) { 
                cin >> table[i][j]; 
            } 
        } 
        
        vector<int> numbers(seqLength); 
        
        for (int i = 0; i < seqLength; i++) { 
            cin >> numbers[i]; 
        } 
        
        int target; 
        cin >> target; 

        string result = findExpressionWithTarget(numbers, target, seqLength); 
        
        if (result != "") { 
            cout << 1 << endl << result << endl;
        } else { 
            cout << 0 << endl; 
        } 
        return 0; 
    }