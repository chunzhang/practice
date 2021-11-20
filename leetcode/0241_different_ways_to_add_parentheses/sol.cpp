/*
  Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.

 

  Example 1:

  Input: expression = "2-1-1"
  Output: [0,2]
  Explanation:
  ((2-1)-1) = 0 
  (2-(1-1)) = 2
  Example 2:

  Input: expression = "2*3-4*5"
  Output: [-34,-14,-10,-10,10]
  Explanation:
  (2*(3-(4*5))) = -34 
  ((2*3)-(4*5)) = -14 
  ((2*(3-4))*5) = -10 
  (2*((3-4)*5)) = -10 
  (((2*3)-4)*5) = 10
 

  Constraints:

  1 <= expression.length <= 20
  expression consists of digits and the operator '+', '-', and '*'.
  All the integer values in the input expression are in the range [0, 99].
*/


// DFS by parsing input expression into numbers and operators first
// time complexity: O(2^N), where N is the number of operators, i.e., each operator can be a breaking point or not
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        // parse expression into numbers and operators
        vector<int> nums;
        vector<char> ops;
        int num = 0;
        for(char c : expression) {
            if(c>='0' && c<='9') {
                num = num*10 + (c-'0');
            }
            else {
                nums.push_back(num);
                num = 0;
                ops.push_back(c);
            }
        }
        nums.push_back(num);
        
        return dfs(nums, ops, 0, nums.size()-1);
    }
    
private:
    vector<int> dfs(const vector<int> &nums, const vector<char> &ops, int start, int end) {
        vector<int> ans;
        
        if(start == end) {
            ans.push_back(nums[start]);
            return ans;
        }
                
        // try all different groupings
        for(int i=start; i<end; ++i) {
            auto ans1 = dfs(nums, ops, start, i);
            auto ans2 = dfs(nums, ops, i+1, end);
            for(int n1 : ans1) {
                for(int n2 : ans2) {
                    if(ops[i] == '+')
                        ans.push_back(n1+n2);
                    else if(ops[i] == '-')
                        ans.push_back(n1-n2);
                    else
                        ans.push_back(n1*n2);
                }
            }
        }
        
        return ans;
    }
};


// DFS with memoization
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        return dfs(expression);        
    }
    
private:
    unordered_map<string,vector<int>> _mem;  // for memoization
    
    vector<int> dfs(const string &exp) {
        if(_mem.count(exp))
            return _mem[exp];
        
        vector<int> ans;
        for(int i=0; i<exp.size(); ++i) {
            if(exp[i]=='+' || exp[i]=='-' || exp[i]=='*') {
                for(int left : dfs(exp.substr(0,i))) {
                    for(int right : dfs(exp.substr(i+1))) {
                        if(exp[i] == '+')
                            ans.push_back(left+right);
                        else if(exp[i] == '-')
                            ans.push_back(left-right);
                        else
                            ans.push_back(left*right);
                    }
                }
            }
        }
        
        if(ans.empty())
            ans.push_back(stoi(exp));  // important: current expression is a single number
        
        _mem[exp] = ans;
        return ans;        
    }
};


// DFS with memlization, simplified code using lambda and std::function
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        _op.resize(128);
        _op['+'] = [](int n1, int n2) {return n1+n2;};
        _op['-'] = [](int n1, int n2) {return n1-n2;};
        _op['*'] = [](int n1, int n2) {return n1*n2;};
        
        return dfs(expression);        
    }
    
private:
    unordered_map<string,vector<int>> _mem;  // for memoization
    vector<function<int(int,int)>> _op;
    
    vector<int> dfs(const string &exp) {
        if(_mem.count(exp))
            return _mem[exp];
        
        vector<int> ans;
        for(int i=0; i<exp.size(); ++i) {
            if(exp[i]=='+' || exp[i]=='-' || exp[i]=='*') {
                for(int left : dfs(exp.substr(0,i))) {
                    for(int right : dfs(exp.substr(i+1))) {
                        ans.push_back(_op[exp[i]](left,right));
                    }
                }
            }
        }
        
        if(ans.empty())
            ans.push_back(stoi(exp));  // important: current expression is a single number
        
        _mem[exp] = ans;
        return ans;        
    }
};
