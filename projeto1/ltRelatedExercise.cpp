#include <cstdio>
#include <vector>
#include <string>

using namespace std;


class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> asw;

        for (int i = 0; i < expression.length(); i++) {
            char current = expression[i];
            
            // if current char is an operation
            if (current == 'x' | current == '-' | current == '+') {
                string leftExpression = expression.substr(0,i);
                string rightExpression = expression.substr(i + 1, expression.length());

                printf("(%s) %c (%s)\n ", leftExpression.c_str(), current, rightExpression.c_str());

                vector<int> aswLeft = diffWaysToCompute(leftExpression);
                vector<int> aswRight = diffWaysToCompute(rightExpression);

                for(int leftNum : aswLeft) {
                    for(int rightNum: aswRight) {
                        if(current == '+') {
                            asw.push_back(leftNum + rightNum);
                        }
                        else if (current == '-') {
                            asw.push_back(leftNum - rightNum);
                        } 
                        else if (current == 'x') {
                            asw.push_back(leftNum * rightNum);
                        }

                    }
                }

            }
        }

        if(asw.empty()) {
            asw.push_back(stoi(expression));
        }
        
        return asw;
    }
};

int main() {
    Solution* test = new Solution();
    vector<int> sol = test->diffWaysToCompute("2x3-1-2");
    
    for(int i : sol) {
        printf("%d\n", i);
    }
}