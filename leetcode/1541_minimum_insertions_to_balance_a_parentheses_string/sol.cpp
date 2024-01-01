/*
Facebook/TikTok/JPMorgan

Given a parentheses string s containing only the characters '(' and ')'. A parentheses string is balanced if:

Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
In other words, we treat '(' as an opening parenthesis and '))' as a closing parenthesis.

For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.
You can insert the characters '(' and ')' at any position of the string to balance it if needed.

Return the minimum number of insertions needed to make s balanced.

 

Example 1:

Input: s = "(()))"
Output: 1
Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to add one more ')' at the end of the string to be "(())))" which is balanced.
Example 2:

Input: s = "())"
Output: 0
Explanation: The string is already balanced.
Example 3:

Input: s = "))())("
Output: 3
Explanation: Add '(' to match the first '))', Add '))' to match the last '('.
 

Constraints:

1 <= s.length <= 10^5
s consists of '(' and ')' only.
*/


// need to make/treat '))' as a whole by inspecting next character
class Solution {
public:
    int minInsertions(string s) {
        int ans = 0;
        int left = 0;

        for(int i=0; i<s.size(); ++i) {
            if(s[i] == '(') {
                ++left;
            }
            else {
                if(i==s.size()-1 || s[i+1]!=')')
                    ++ans;  // add ')' to make '))' first
                else
                    ++i;
                
                // now we can treat it as single parentheses matching
                if(left)
                    --left;  // matching
                else
                    ++ans;  // add '('
            }
        }
        ans += left*2;  // add '))'

        return ans;
    }
};
