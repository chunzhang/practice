/*
Pinterest/Facebook/Akuna Capital

The count-and-say sequence is a sequence of digit strings defined by the recursive formula:

countAndSay(1) = "1"
countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1), which is then converted into a different digit string.
To determine how you "say" a digit string, split it into the minimal number of substrings such that each substring contains exactly one unique digit. Then for each substring, say the number of digits, then say the digit. Finally, concatenate every said digit.

For example, the saying and conversion for digit string "3322251":


Given a positive integer n, return the nth term of the count-and-say sequence.

 

Example 1:

Input: n = 1
Output: "1"
Explanation: This is the base case.
Example 2:

Input: n = 4
Output: "1211"
Explanation:
countAndSay(1) = "1"
countAndSay(2) = say "1" = one 1 = "11"
countAndSay(3) = say "11" = two 1's = "21"
countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"
 

Constraints:

1 <= n <= 30
*/

// iterative approach
class Solution {
public:
    string countAndSay(int n) {
        string ans = "1";
        for(int i=2; i<=n; ++i) {
            ostringstream oss;
            int count = 1;
            char c = ans[0];
            for(int j=1; j<ans.size(); ++j) {
                if(ans[j]!=ans[j-1]) {
                    oss << count << c;  // can also use to_string() API to avoid the use of ostringstream
                    count = 1;
                    c = ans[j];
                }
                else
                    ++count;
            }
            if(count)
                oss << count << c;
            ans = oss.str();
        }

        return ans;
    }
};


// reference solution: using regular expression matching to count (in Java)
class Solution {
public:
    string countAndSay(int n) {
        /*
          ==> (.): it defines a group containing a single character that could be of anything.

          ==> \\1: it is a backreference to whatever matches in group 1 (the pattern matched in the parenthesis). Group 1 is the only group (.).

          ==> *: this qualifier, followed by the group reference \\1, indicates that we would like to see the group repeats itself zero or more times.

          ==> So the pattern matches strings which consist of some character and then zero or more repetitions of this character after its first occurrence. It is what we need.
        */
        regex e("(.)\\1*");
        string s = "1";
        for (int i = 2; i <= n; i++) {
            string t;
            for (sregex_iterator it = sregex_iterator(s.begin(), s.end(), e);
                 it != sregex_iterator(); it++) {
                t += to_string(it->str().size()) + it->str(1);
            }
            s = t;
        }
        return s;
    }
};
