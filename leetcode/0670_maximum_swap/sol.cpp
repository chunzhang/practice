/*
You are given an integer num. You can swap two digits at most once to get the maximum valued number.

Return the maximum valued number you can get.

 

Example 1:

Input: num = 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:

Input: num = 9973
Output: 9973
Explanation: No swap.
 

Constraints:

0 <= num <= 108
*/


// greedy: starting from MSB, swap it with the largest digit on it's right
// if there're multiple such digits, swap with the LSB one
class Solution {
public:
    int maximumSwap(int num) {
        vector<int> digits;  // digits[0] is LSB
        while(num) {
            digits.push_back(num%10);
            num /= 10;
        }

        // index to largest digit from LSB to current digit
        vector<int> idx(digits.size(), 0);
        for(int i=1; i<digits.size(); ++i) {
            idx[i] = digits[i]>digits[idx[i-1]] ? i : idx[i-1];
        }

        // do one greedy swap
        for(int i=digits.size()-1; i>0; --i) {
            if(digits[i] < digits[idx[i-1]]) {
                swap(digits[i], digits[idx[i-1]]);
                break;
            }
        }

        // rebuild result
        int ans = 0;
        for(int i=digits.size()-1; i>=0; --i)
            ans = ans*10 + digits[i];

        return ans;
    }
};
