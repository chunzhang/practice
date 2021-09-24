/*
Given a string s, reverse the string according to the following rules:

All the characters that are not English letters remain in the same position.
All the English letters (lowercase or uppercase) should be reversed.
Return s after reversing it.

 

Example 1:

Input: s = "ab-cd"
Output: "dc-ba"
Example 2:

Input: s = "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"
Example 3:

Input: s = "Test1ng-Leet=code-Q!"
Output: "Qedo1ct-eeLg=ntse-T!"
 

Constraints:

1 <= s.length <= 100
s consists of characters with ASCII values in the range [33, 122].
s does not contain '\"' or '\\'.
*/

// use two pointers -- concise impl
class Solution {
public:
    string reverseOnlyLetters(string s) {
        for(int i=0,j=s.size()-1; i<j; ) {
            if(!isalpha(s[i]))
                ++i;
            else if(!isalpha(s[j]))
                --j;
            else
                swap(s[i++],s[j--]);
        }
        
        return s;
    }
};


// use two pointers -- less concise impl
class Solution {
public:
    string reverseOnlyLetters(string s) {
        for(int i=0,j=s.size()-1; i<j; ++i,--j) {
            while(i<s.size() && !isLetter(s[i]))
                ++i;
            while(j>=0 && !isLetter(s[j]))
                --j;
            if(i >= j)
                break;
            swap(s[i],s[j]);
        }
        
        return s;
    }
    
private:
    bool isLetter(char c) {
        return c>='a'&&c<='z' || c>='A'&&c<='Z';
    }
};


