/*
  Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.

  Return all the possible results. You may return the answer in any order.

 

  Example 1:

  Input: s = "()())()"
  Output: ["(())()","()()()"]
  Example 2:

  Input: s = "(a)())()"
  Output: ["(a())()","(a)()()"]
  Example 3:

  Input: s = ")("
  Output: [""]
 

  Constraints:

  1 <= s.length <= 25
  s consists of lowercase English letters and parentheses '(' and ')'.
  There will be at most 20 parentheses in s.
*/


// DFS: first compute min number of left/right parentheses that need to be removed, then DFS to search the solution
// time complexity: O(2^N)
// space complexity: O(N)
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        // count number of left and right parenthesis to be removed -- this is greedy
        int left = 0;
        int right = 0;
        for(const char c : s) {
            if(c == '(') {
                ++left;
            }
            else if(c == ')') {
                if(left)
                    --left;
                else
                    ++right;
            }
        }
        
        vector<string> ans;
        dfs(s, 0, left, right, ans);
        
        return ans;
    }
    
private:
    bool isValid(const string &s) {
        int count = 0;
        for(const char c : s) {
            if(c == '(')
                ++count;
            else if (c == ')')
                --count;
            
            if(count < 0)  // more right parenthesis ==> invalid
                return false;
        }
        
        return count==0;
    }
    
    void dfs(const string &s, int idx, int left, int right, vector<string> &ans) {
        if(left==0 && right==0) {
            if(isValid(s))
                ans.emplace_back(s);
            return;
        }
        
        for(int i=idx; i<s.size(); ++i) {
            if(s[i]!='(' && s[i]!=')')
                continue;
            if(i!=idx && s[i]==s[i-1])  // avoid duplicates
                continue;

            string ss = s;
            ss.erase(i, 1);
            if(s[i]==')' && right)  // pruning: try remove ')' first, as otherwise it will always be illegal
                dfs(ss, i/*no need to increment, since i-th char is erased*/, left, right-1, ans);
            if(s[i]=='(' && left)
                dfs(ss, i, left-1, right, ans);
        }
    }
};


// BFS: current level ==> try remove one parenthesis ==> next level
// -- first level that becomes valid ==> this is the answer as we've removed min number of parentheses
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        set<string> curLv;
        curLv.insert(s);
        while(!curLv.empty()) {
            bool found = false;
            set<string> nextLv;
            for(const string& ns : curLv) {
                if(isValid(ns)) {
                    found = true;
                    res.push_back(ns);
                }

                if(!found) {
                    for(int i=0; i<ns.size(); ++i) {
                        if(ns[i]=='(' || ns[i]==')')
                            nextLv.insert(ns.substr(0, i)+ns.substr(i+1));
                    }
                }
            }
            if(found)
                break;
            curLv.swap(nextLv);
        }

        return res;
    }

    bool isValid(const string &s) {  // note empty string is also valid
        int count = 0;
        for(char c : s) {
            if(c == '(')
                ++count;
            else if(c == ')')
                --count;
            if(count < 0)
                break;
        }
        return count==0;
    }
};


// DFS: a different search idea and impl
// https://leetcode.com/problems/remove-invalid-parentheses/discuss/75027/
class Solution2 {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> results;
        search(results, s, 0, 0, 0, '(', ')');
        return results;
    }

    void search(vector<string> &results, const string &s, int count, int cur, int start, char left, char right) {
        for( ; cur<s.size(); ++cur) {
            if(s[cur] == left)
                ++count;
            else if(s[cur] == right)
                --count;

            if(count < 0) {  // found invalid matching
                /*	while(s[start] != right)
                    ++start;
                */
                for(int j=start; j<=cur; ++j) {
                    if(s[j]==right && (j==start || s[j-1]!=s[j])) {  // use same technique as "combination sum II" to remove duplicates!!!
                        string ns = s.substr(0,j) + s.substr(j+1);
                        search(results, ns, count+1, cur, j, left, right);
                    }
                }
                return;  // current s is not valid, so simply exit
            }
        }

        if(count > 0) {  // only possible after first round (i.e., left to right scan)
            string ns = s;
            reverse(ns.begin(), ns.end());
            search(results, ns, 0, 0, 0, ')', '(');
        }
        else if(count == 0) {  // found valid solution
            string ns = s;
            if(left == ')')  // becomes valid after second round (i.e., right to left scan)
                reverse(ns.begin(), ns.end());
            results.push_back(ns);
        }
    }
};
