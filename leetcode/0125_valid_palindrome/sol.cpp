/*
Given a string s, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

 

Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
 

Constraints:

1 <= s.length <= 2 * 10^5
s consists only of printable ASCII characters.
*/


// two pointers
class Solution {
public:
    bool isPalindrome(string s) {
        for(int i=0,j=s.size()-1; i<j;) {
            if(!isalnum(s[i]))
                ++i;
            else if(!isalnum(s[j]))
                --j;
            else {
                if(tolower(s[i++]) != tolower(s[j--]))
                    return false;
            }
        }
        
        return true;
    }
};
