/*
You are given a string of digits num, such as "123456579". We can split it into a Fibonacci-like sequence [123, 456, 579].

Formally, a Fibonacci-like sequence is a list f of non-negative integers such that:

0 <= f[i] < 231, (that is, each integer fits in a 32-bit signed integer type),
f.length >= 3, and
f[i] + f[i + 1] == f[i + 2] for all 0 <= i < f.length - 2.
Note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.

Return any Fibonacci-like sequence split from num, or return [] if it cannot be done.

 

Example 1:

Input: num = "123456579"
Output: [123,456,579]
Example 2:

Input: num = "11235813"
Output: [1,1,2,3,5,8,13]
Example 3:

Input: num = "112358130"
Output: []
Explanation: The task is impossible.
Example 4:

Input: num = "0123"
Output: []
Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
Example 5:

Input: num = "1101111"
Output: [11,0,11,11]
Explanation: The output [11, 0, 11, 11] would also be accepted.
 

Constraints:

1 <= num.length <= 200
num contains only digits.
*/


// DFS
// time complexity: O(2^N), i.e., each character can be a breaking of the number or not
// but practically due to the pruning, the complexity is same as iterative approach: O(10*10*N)
class Solution {
public:
    vector<int> splitIntoFibonacci(string num) {
        vector<int> ans;
        dfs(num, 0, ans);
        return ans;
    }
    
private:
    bool dfs(const string &num, int cur, vector<int> &ans) {
        if(cur == num.size())
            return ans.size()>=3;
        
        for(int i=cur; i<num.size(); ++i) {
            if(num[cur]=='0' && i>cur)  // number can not have leading zero
                break;
              
            long val = stol(num.substr(cur,i-cur+1));  // use long to avoid integer overflow
            if(val > INT_MAX)    // from problem definition
                break;
            int sz = ans.size();
            if(sz<2 || val==(long)ans[sz-1]+ans[sz-2]) {
                ans.push_back(val);
                if(dfs(num, i+1, ans))
                    return true;
                ans.pop_back();
            }
            else if(val > (long)ans[sz-1]+ans[sz-2])
                break;
        }
        
        return false;
    }
};


// Iterative: enumerate all possible first two numbers, and then linear search rest of the string and check if that forms one Fibonacci sequence
// time complexity: O(10*10*N)
class Solution {
public:
    vector<int> splitIntoFibonacci(string num) {
        for(int i=0; i<num.size(); ++i) {
            if(num[0]=='0' && i>=1)  // number shall not start with leading zero
                break;
            const long num1 = stol(num.substr(0,i+1));
            if(num1 > INT_MAX)
                break;
            for(int j=i+1; j<num.size(); ++j) {
                if(num[i+1]=='0' && j-i>=2)
                    break;
                const long num2 = stol(num.substr(i+1, j-i));
                if(num2 > INT_MAX)
                    break;
                
                int n1 = num1;
                int n2 = num2;
                vector<int> fib = {n1, n2};
                int k = j+1;
                while(k < num.size()) {
                    long n3 = (long)n1 + n2;
                    if(n3 > INT_MAX)
                        break;
                    string s3 = to_string(n3);
                    if(num.substr(k,s3.size()) == s3) {
                        fib.push_back(n3);
                        n1 = n2;
                        n2 = n3;
                        k += s3.size();
                    }
                    else {
                        break;
                    }
                }
                
                if(k==num.size() && fib.size()>=3)
                    return fib;
            }
        }
        
        return {};
    }
};
