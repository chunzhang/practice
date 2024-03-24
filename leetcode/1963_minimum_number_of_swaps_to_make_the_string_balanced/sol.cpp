/*
Facebook/Expedia/Twillio

You are given a 0-indexed string s of even length n. The string consists of exactly n / 2 opening brackets '[' and n / 2 closing brackets ']'.

A string is called balanced if and only if:

It is the empty string, or
It can be written as AB, where both A and B are balanced strings, or
It can be written as [C], where C is a balanced string.
You may swap the brackets at any two indices any number of times.

Return the minimum number of swaps to make s balanced.

Example 1:

Input: s = "][]["
Output: 1
Explanation: You can make the string balanced by swapping index 0 with index 3.
The resulting string is "[[]]".

Example 2:

Input: s = "]]][[["
Output: 2
Explanation: You can do the following to make the string balanced:
- Swap index 0 with index 4. s = "[]][][".
- Swap index 1 with index 5. s = "[[][]]".
The resulting string is "[[][]]".

Example 3:

Input: s = "[]"
Output: 0
Explanation: The string is already balanced.
 

Constraints:

n == s.length
2 <= n <= 10^6
n is even.
s[i] is either '[' or ']'.
The number of opening brackets '[' equals n / 2, and the number of closing brackets ']' equals n / 2.
*/


// greedy: count the balance of '['
// -- when negative balance is detected, always swap it with the right most '['
// -- this is becuase we want the ']' to appear as late in the string as possible
// -- NOTE: there is no need to do the actual swap, unless we want to return the valid string
// time: O(N), space: O(1)
class Solution {
public:
    int minSwaps(string s) {
        int ans = 0;
        int balance = 0;
        for(int i=0; i<s.size(); ++i) {
            if(s[i] == '[') {
                ++balance;
            }
            else {
                --balance;
                if(balance < 0) {
                    // assume swapped with the right most '['
                    // -- no need to do any actual swap as the "hypertically swapped" ']' must have been balanced with the swapped '['
                    balance = 1;  
                    ++ans;
                }
            }
        }

        return ans;
    }
};
