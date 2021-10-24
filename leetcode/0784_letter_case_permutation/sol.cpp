/*
  Given a string s, we can transform every letter individually to be lowercase or uppercase to create another string.

  Return a list of all possible strings we could create. You can return the output in any order.

 

  Example 1:

  Input: s = "a1b2"
  Output: ["a1b2","a1B2","A1b2","A1B2"]
  Example 2:

  Input: s = "3z4"
  Output: ["3z4","3Z4"]
  Example 3:

  Input: s = "12345"
  Output: ["12345"]
  Example 4:

  Input: s = "0"
  Output: ["0"]
 

  Constraints:

  s will be a string with length between 1 and 12.
  s will consist only of letters or digits.
*/


// DFS
// time complexity: O(N*2^N)
// space complexity: O(N)
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        string cur;
        dfs(s, 0, cur, ans);
        return ans;
    }
    
private:
    void dfs(const string &s, int idx, string &cur, vector<string> &ans) {
        if(cur.size() == s.size()) {
            ans.emplace_back(cur);
            return;
        }
        
        if(isdigit(s[idx])) {
            cur.push_back(s[idx]);
            dfs(s, idx+1, cur, ans);
            cur.pop_back();
        }
        else {
            cur.push_back(tolower(s[idx]));
            dfs(s, idx+1, cur, ans);
            cur.pop_back();
            
            cur.push_back(toupper(s[idx]));
            dfs(s, idx+1, cur, ans);
            cur.pop_back();
        }
    }
};


// ref DFS impl from HuaHua
class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        vector<string> ans;
        dfs(S, 0, ans);
        return ans;
    }
private:
    void dfs(string& S, int s, vector<string>& ans) {
        if (s == S.length()) {
            ans.push_back(S);
            return;      
        }
        dfs(S, s + 1, ans);    
        if (!isalpha(S[s])) return;          
        S[s] ^= (1 << 5);
        dfs(S, s + 1, ans);
        S[s] ^= (1 << 5);
    }
};


// binary bitmask (in Java)
class Solution {
    public List<String> letterCasePermutation(String S) {
        int B = 0;
        for (char c: S.toCharArray())
            if (Character.isLetter(c))
                B++;

        List<String> ans = new ArrayList();

        for (int bits = 0; bits < 1<<B; bits++) {
            int b = 0;
            StringBuilder word = new StringBuilder();
            for (char letter: S.toCharArray()) {
                if (Character.isLetter(letter)) {
                    if (((bits >> b++) & 1) == 1)
                        word.append(Character.toLowerCase(letter));
                    else
                        word.append(Character.toUpperCase(letter));
                } else {
                    word.append(letter);
                }
            }

            ans.add(word.toString());
        }

        return ans;

    }
};
