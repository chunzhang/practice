/*
Facebook/BitGo

An original string, consisting of lowercase English letters, can be encoded by the following steps:

Arbitrarily split it into a sequence of some number of non-empty substrings.
Arbitrarily choose some elements (possibly none) of the sequence, and replace each with its length (as a numeric string).
Concatenate the sequence as the encoded string.
For example, one way to encode an original string "abcdefghijklmnop" might be:

Split it as a sequence: ["ab", "cdefghijklmn", "o", "p"].
Choose the second and third elements to be replaced by their lengths, respectively. The sequence becomes ["ab", "12", "1", "p"].
Concatenate the elements of the sequence to get the encoded string: "ab121p".
Given two encoded strings s1 and s2, consisting of lowercase English letters and digits 1-9 (inclusive), return true if there exists an original string that could be encoded as both s1 and s2. Otherwise, return false.

Note: The test cases are generated such that the number of consecutive digits in s1 and s2 does not exceed 3.

 

Example 1:

Input: s1 = "internationalization", s2 = "i18n"
Output: true
Explanation: It is possible that "internationalization" was the original string.
- "internationalization" 
  -> Split:       ["internationalization"]
  -> Do not replace any element
  -> Concatenate:  "internationalization", which is s1.
- "internationalization"
  -> Split:       ["i", "nternationalizatio", "n"]
  -> Replace:     ["i", "18",                 "n"]
  -> Concatenate:  "i18n", which is s2
Example 2:

Input: s1 = "l123e", s2 = "44"
Output: true
Explanation: It is possible that "leetcode" was the original string.
- "leetcode" 
  -> Split:      ["l", "e", "et", "cod", "e"]
  -> Replace:    ["l", "1", "2",  "3",   "e"]
  -> Concatenate: "l123e", which is s1.
- "leetcode" 
  -> Split:      ["leet", "code"]
  -> Replace:    ["4",    "4"]
  -> Concatenate: "44", which is s2.
Example 3:

Input: s1 = "a5b", s2 = "c5b"
Output: false
Explanation: It is impossible.
- The original string encoded as s1 must start with the letter 'a'.
- The original string encoded as s2 must start with the letter 'c'.
 

Constraints:

1 <= s1.length, s2.length <= 40
s1 and s2 consist of digits 1-9 (inclusive), and lowercase English letters only.
The number of consecutive digits in s1 and s2 does not exceed 3.
*/


// search with memoization
class Solution {
public:
    bool possiblyEquals(string s1, string s2) {
        return search(s1,s2,0,0,0,0);
    }

private:
    bool searchNum1(const string &s1, const string &s2, unsigned num1, unsigned num2, unsigned i, unsigned j) {
        for(unsigned ii=i; ii<s1.size()&&isdigit(s1[ii]); ++ii)
            if(search(s1, s2, stoi(s1.substr(i,ii-i+1)), num2, ii+1, j))
                return true;
        return false;
    }

    bool searchNum2(const string &s1, const string &s2, unsigned num1, unsigned num2, unsigned i, unsigned j) {
        for(unsigned jj=j; jj<s2.size()&&isdigit(s2[jj]); ++jj)
            if(search(s1, s2, num1, stoi(s2.substr(j,jj-j+1)), i, jj+1))
                return true;
        return false;
    }

    bool search(const string &s1, const string &s2, unsigned num1, unsigned num2, unsigned i, unsigned j) {
        // the encoding works because 0<=num1,num2<=999, 0<=i,j<=40
        unsigned encoding = (unsigned)(num1<<22) + (unsigned)(num2<<12) + (unsigned)(i<<6) + (unsigned)j;
        auto it = m_mem.find(encoding);
        if(it != m_mem.end())
            return it->second;

        if(i==s1.size() && !num1)  // s1 is consumed
            return j==s2.size() && !num2;
        if(j==s2.size() && !num2)  // s2 is consumed
            return i==s1.size() && !num1;

        bool status = false;

        // both string are not consumed
        if(num1 && num2) {
            int delta = min(num1,num2);
            status = search(s1,s2,num1-delta,num2-delta,i,j);
        }
        else if(num1)  // num2==0
            status = isalpha(s2[j]) ? search(s1,s2,num1-1,num2,i,j+1) : searchNum2(s1,s2,num1,num2,i,j);
        else if(num2)  // num1==0
            status = isalpha(s1[i]) ? search(s1,s2,num1,num2-1,i+1,j) : searchNum1(s1,s2,num1,num2,i,j);
        else {  // num1==num2==0
            if(isdigit(s1[i]))
                status = searchNum1(s1,s2,num1,num2,i,j);
            else if(isdigit(s2[j]))
                status = searchNum2(s1,s2,num1,num2,i,j);
            else
                status = s1[i]==s2[j] ? search(s1,s2,num1,num2,i+1,j+1) : false;
        }

        m_mem[encoding] = status;
        return status;  // should not reach here
    }

private:
    unordered_map<unsigned,int> m_mem;
};


// brute-force search: TLE
class Solution {
public:
    bool possiblyEquals(string s1, string s2) {
        return search(s1,s2,0,0,0,0);
    }

private:
    bool searchNum1(const string &s1, const string &s2, int num1, int num2, int i, int j) {
        for(int ii=i; ii<s1.size()&&isdigit(s1[ii]); ++ii)
            if(search(s1, s2, stoi(s1.substr(i,ii-i+1)), num2, ii+1, j))
                return true;
        return false;
    }

    bool searchNum2(const string &s1, const string &s2, int num1, int num2, int i, int j) {
        for(int jj=j; jj<s2.size()&&isdigit(s2[jj]); ++jj)
            if(search(s1, s2, num1, stoi(s2.substr(j,jj-j+1)), i, jj+1))
                return true;
        return false;
    }

    bool search(const string &s1, const string &s2, int num1, int num2, int i, int j) {
        //cout << "num1=" << num1 << ", num2=" << num2 << ", i=" << i << ", j=" << j << endl;
        if(i==s1.size() && !num1)  // s1 is consumed
            return j==s2.size() && !num2;
        if(j==s2.size() && !num2)  // s2 is consumed
            return i==s1.size() && !num1;

        // both string are not consumed
        if(num1 && num2) {
            int delta = min(num1,num2);
            return search(s1,s2,num1-delta,num2-delta,i,j);
        }
        else if(num1)
            return isalpha(s2[j]) ? search(s1,s2,num1-1,num2,i,j+1) : searchNum2(s1,s2,num1,num2,i,j);
        else if(num2)
            return isalpha(s1[i]) ? search(s1,s2,num1,num2-1,i+1,j) : searchNum1(s1,s2,num1,num2,i,j);
        else {
            if(isdigit(s1[i]))
                return searchNum1(s1,s2,num1,num2,i,j);
            else if(isdigit(s2[j]))
                return searchNum2(s1,s2,num1,num2,i,j);
            else
                return s1[i]==s2[j] ? search(s1,s2,num1,num2,i+1,j+1) : false;
        }

        return false;  // should not reach here
    }
};


// ref solution (in Java) -- very smart!!!
// diff: how many characters s1 "owes to" s2
class Solution {
    //112ms
    public boolean possiblyEquals(String s1, String s2) {
        int l1 = s1.length();
        int l2 = s2.length();
        
        // dp[i][j][diff] means if s1[i:] truncated by <diff> characters if diff > 0 
        // and s2[j:] truncated by <-diff> characters if diff < 0 are equal
        Boolean[][][] dp = new Boolean[l1 + 1][l2 + 1][2000]; 
        return dfs(0, 0, 0, s1.toCharArray(), s2.toCharArray(), dp);
    }
    
    private boolean dfs(int i, int j, int diff, char[] s1, char[] s2, Boolean[][][] dp) {
        if (i == s1.length && j == s2.length) {
            return diff == 0;
        }
        
        if (dp[i][j][diff + 1000] != null) return dp[i][j][diff + 1000];
        
        // Literal matching on s1[i] and s2[j]
        if (i < s1.length && j < s2.length && diff == 0 && s1[i] == s2[j]) {
            if (dfs(i + 1, j + 1, 0, s1, s2, dp)) {
                return dp[i][j][1000] = true;
            }
        }
        
        // Literal matching on s1[i]
        if (i < s1.length && !isDigit(s1[i]) && diff > 0 && dfs(i + 1, j, diff - 1, s1, s2, dp)) {
            return dp[i][j][diff + 1000] = true;
        }
        
        // Literal matching on s2[j]
        if (j < s2.length && !isDigit(s2[j]) && diff < 0 && dfs(i, j + 1, diff + 1, s1, s2, dp)) {
            return dp[i][j][diff + 1000] = true;
        }
        
        // Wildcard matching on s1[i]
        for (int k = i, val = 0; k < s1.length && isDigit(s1[k]); ++k) {
            val = val * 10 + (s1[k] - '0');
            if (dfs(k + 1, j, diff - val, s1, s2, dp)) {
                return dp[i][j][diff + 1000] = true;
            }
        }
        
        // Wildcard matching on s2[j]
        for (int k = j, val = 0; k < s2.length && isDigit(s2[k]); ++k) {
            val = val * 10 + (s2[k] - '0');
            if (dfs(i, k + 1, diff + val, s1, s2, dp)) {
                return dp[i][j][diff + 1000] = true;
            }
        }
        
        return dp[i][j][diff + 1000] = false;
    }
    
    private boolean isDigit(char c) {
        return c >= '0' && c <= '9';
    }
}
