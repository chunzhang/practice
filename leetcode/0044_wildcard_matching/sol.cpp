/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input: s = "adceb", p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input: s = "acdcb", p = "a*c?b"
Output: false
 

Constraints:

0 <= s.length, p.length <= 2000
s contains only lowercase English letters.
p contains only lowercase English letters, '?' or '*'.
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        // dp(m,n): whether s[0:m) and p[0:n) matches
        const int M = s.size();
        const int N = p.size();
        vector<vector<int>> dp(M+1, vector<int>(N+1,0));
        dp[0][0] = 1;  // empty string matches empty pattern
        // first column, i.e., dp[m][0]=0 for m>=1, as empty pattern cannot match non-empty string
        // first row, i.e., dp[0][n] for n>=1, only "***" matches empty string
        for(int n=0; n<N; ++n)
            if(p[n] == '*')
                dp[0][n+1] = 1;
            else
                break;  // as soon as the first non-'*' char is met, everything stops matching afterwards
        
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                char sc = s[m-1];
                char pc = p[n-1];
                if(pc == '*') {
                    dp[m][n] = dp[m-1][n]/*one or more instantion*/ | dp[m][n-1]/*zero instantion*/;
                }
                else {
                    bool match = (sc==pc || pc=='?');
                    dp[m][n] = (match?dp[m-1][n-1]:0);
                }
            }
        }
        
        return dp[M][N];
    }
};


// A better linear solution (in Java)
/*
Complexity O(S⋅P) is much better than O(S⋅P⋅(S+P)), but still could be improved. There is no need to compute the entire matrix, i.e., to check all the possibilities for each star:

Star matches zero characters.
Star matches one character.
Star matches two characters.
...

Star matches all remaining characters.
Let's just pick up the first opportunity "matches zero characters" and proceed further. If this assumption would lead in "no match" situation, then backtrack: come back to the previous star, assume now that it matches one more character (one) and proceed again. Again "no match" situation? Backtrack again: come back to the previous star, and assume now that it matches one more character (two), etc.

pic

Algorithm

Here is the algorithm.

Let's use two pointers here: s_idx to iterate over the string, and p_idx to iterate over the pattern. While s_idx < s_len:

If there are still characters in the pattern (p_idx < p_len) and the characters under the pointers match (p[p_idx] == s[s_idx] or p[p_idx] == '?'), then move forward by increasing both pointers.

Otherwise, if there are still characters in the pattern (p_idx < p_len), and p[p_idx] == '*', then first check "match zero characters" situation, i.e., increase only pattern pointer p_idx++. Write down for a possible backtrack the star position in star_idx variable, and the current string pointer in s_tmp_idx variable.

Else if there is "no match" situation: the pattern is used up p_idx < p_len or the characters under the pointers doesn't match.

If there was no stars in the pattern, i.e., no star_idx, return False.

If there was a star, then backtrack: set pattern pointer just after the last star p_idx = star_idx + 1, and string pointer s_idx = s_tmp_idx + 1, i.e., assume that this time the star matches one more character. Save the current string pointer for the possible backtrack s_tmp_idx = s_idx.

Return True if all remaining characters in the pattern are stars.
*/

/*
Time complexity: O(\min(S, P))O(min(S,P)) for the best case and better than O(S \log P)O(SlogP) for the average case, where SS and PP are lengths of the input string and the pattern correspondingly. Please refer to this article https://arxiv.org/pdf/1407.0950.pdf for detailed proof. However, in the worst-case scenario, this algorithm requires O(S \cdot P)O(S⋅P) time.
Space complexity: O(1)O(1) since it's a constant space solution.
*/
class Solution {
    public boolean isMatch(String s, String p) {
        int sLen = s.length(), pLen = p.length();
        int sIdx = 0, pIdx = 0;
        int starIdx = -1, sTmpIdx = -1;

        while (sIdx < sLen) {
            // If the pattern caracter = string character
            // or pattern character = '?'
            if (pIdx < pLen && (p.charAt(pIdx) == '?' || p.charAt(pIdx) == s.charAt(sIdx))) {
                ++sIdx;
                ++pIdx;
    
            // If pattern character = '*'
            } else if (pIdx < pLen && p.charAt(pIdx) == '*') {
                // Check the situation
                // when '*' matches no characters
                starIdx = pIdx;
                sTmpIdx = sIdx;
                ++pIdx;
                          
            // If pattern character != string character
            // or pattern is used up
            // and there was no '*' character in pattern 
            } else if (starIdx == -1) {
                return false;
                          
            // If pattern character != string character
            // or pattern is used up
            // and there was '*' character in pattern before
            } else {
                // Backtrack: check the situation
                // when '*' matches one more character
                pIdx = starIdx + 1;
                sIdx = sTmpIdx + 1;
                sTmpIdx = sIdx;
            }
        }

        // The remaining characters in the pattern should all be '*' characters
        for (int i = pIdx; i < pLen; i++) {
            if (p.charAt(i) != '*') {
                return false;
            }
   
        }
        return true;
    }
};
