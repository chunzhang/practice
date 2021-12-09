/*
Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...
 

Example 1:

Input: columnNumber = 1
Output: "A"
Example 2:

Input: columnNumber = 28
Output: "AB"
Example 3:

Input: columnNumber = 701
Output: "ZY"
Example 4:

Input: columnNumber = 2147483647
Output: "FXSHRXW"
 

Constraints:

1 <= columnNumber <= 2^31 - 1
*/


class Solution {
public:
    string convertToTitle(int num) {
        string ans;
        while(num) {
            int m = num % 26;
            if(m) {
                ans.push_back('A' + m - 1);
                num /= 26;
            }
            else {
                ans.push_back('Z');
                num /= 26;
                --num;  // digit 0 becomes digit Z, so needs to borrow one from higher bit
            }
        }
        
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
