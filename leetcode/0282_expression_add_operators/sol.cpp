/*
Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.

Note that operands in the returned expressions should not contain leading zeros.

 

Example 1:

Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.
Example 3:

Input: num = "105", target = 5
Output: ["1*0+5","10-5"]
Explanation: Both "1*0+5" and "10-5" evaluate to 5.
Note that "1-05" is not a valid expression because the 5 has a leading zero.
Example 4:

Input: num = "00", target = 0
Output: ["0*0","0+0","0-0"]
Explanation: "0*0", "0+0", and "0-0" all evaluate to 0.
Note that "00" is not a valid expression because the 0 has a leading zero.
Example 5:

Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.
 

Constraints:

1 <= num.length <= 10
num consists of only digits.
-2^31 <= target <= 2^31 - 1
*/


// DFS
// time complexity: O(4^N), i.e., each digit can be inserted with '+', '-', '*', or no operator
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        _f.resize(128);
        _f['+'] = [](long n1, long n2) {return n1+n2;};
        _f['-'] = [](long n1, long n2) {return n1-n2;};
        _f['*'] = [](long n1, long n2) {return n1*n2;};
        
        vector<string> ans;
        string exp;
        dfs(num, target, 0, 0, '+', 0, '+', exp, ans);
        return ans;
    }
    
private:
    vector<function<long(long,long)>> _f;
    char _ops[3] = {'+', '-', '*'};

    // prevNum2--prevOp2--prevNum1--prevOp1--curIdx
    void dfs(const string &num, const int target, int curIdx, long prevNum2, char prevOp2, long prevNum1, char prevOp1, string &exp, vector<string> &ans) {
        if(curIdx == num.size()) {
            if(_f[prevOp2](prevNum2,prevNum1) == target)
                ans.push_back(exp);
            return;
        }
        
        for(int i=curIdx; i<num.size(); ++i) {  // insert op after i-th digit
            if(num[curIdx]=='0' && i>curIdx)  // avoid leading zero
                break;
            
            string curNumStr = num.substr(curIdx,i-curIdx+1);
            long curNum = stol(curNumStr);
            for(char op : _ops) {
                string exp2 = exp + curNumStr;
                if(i != num.size()-1)
                    exp2.push_back(op);
                
                if(prevOp1 == '*') {
                    dfs(num, target, i+1, prevNum2, prevOp2, prevNum1*curNum, op, exp2, ans);
                }
                else {
                    dfs(num, target, i+1, _f[prevOp2](prevNum2,prevNum1), prevOp1, curNum, op, exp2, ans);
                }
                
                if(i == num.size()-1)
                    break;
            }
        }
    }
};


// Better DFS impl
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> ans;
        dfs(num, target, 0, 0, 0, "", ans);
        return ans;
    }
    
private:
    void dfs(const string &num, int target, int curIdx, long prevNum/*operand 1*/, long val/*calculated val of current expression*/, const string &exp/*must be const so as to pass in temp string*/, vector<string> &ans) {
        if(curIdx == num.size()) {
            if(val == target)
                ans.push_back(exp);
            return;
        }
        
        for(int i=curIdx; i<num.size(); ++i) {  // try to find the second operand
            if(num[curIdx]=='0' && i>curIdx)  // avoid leading zero
                break;
            
            string curNumStr = num.substr(curIdx, i-curIdx+1);
            long curNum = stol(curNumStr);
            if(curIdx == 0) {  // this is the first operand
                dfs(num, target, i+1, curNum, curNum, curNumStr, ans);
            }
            else {  // this is the second operand
                dfs(num, target, i+1, curNum, val+curNum, exp+"+"+curNumStr, ans);
                dfs(num, target, i+1, -curNum/*minus ==> add an negative number*/, val-curNum, exp+"-"+curNumStr, ans);
                dfs(num, target, i+1, prevNum*curNum, val-prevNum+prevNum*curNum, exp+"*"+curNumStr, ans);
            }
        }
    }
};
