/*
Apple/WarnerMedia/Microsoft/Amazon/Palantir/Facebook/Snowflake/Oracle


Convert a non-negative integer num to its English words representation.

Example 1:

Input: num = 123
Output: "One Hundred Twenty Three"

Example 2:

Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"

Example 3:

Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
 

Constraints:

0 <= num <= 2^31 - 1
*/


// my initial implementation
class Solution {
public:
    string numberToWords(int num) {
        if(!num)
            return "Zero";

        string ans;
        int unit = 0;
        do {    
            int num2 = num % 1000;  // last three digits
            num /= 1000;
            if(num2) {
                string english = threeDigits(num2);
                if(unit)
                    english += " " + units[unit];
                ans = english + (ans.size()?" ":"") + ans;
            }
            ++unit;
        } while(num);

        return ans;
    }

private:
    // convert any number in [0,999]
    string threeDigits(int num) {
        if(num <= 10)
            return oneDigit[num];
        else if(num <= 19)
            return tenPlus[num-10];
        
        string english;
        int d1 = (num/100) % 10;
        int d2 = (num/10) % 10;
        int d3 = num % 10;
        if(d1)
            english += oneDigit[d1] + " " + "Hundred";
        
        if(d2)
            english += (english.size()?" ":"") + (d2==1?tenPlus[d3]:twoDigit[d2]);
        
        if(d3) {
            if(d2 != 1)
                english += (english.size()?" ":"") + oneDigit[d3];
        }
        else {
            english += english.size() ? "" : "zero";
        }
        return english;
    }

private:
    vector<string> oneDigit = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
    vector<string> twoDigit = {"X", "X", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> tenPlus = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> units = {"X", "Thousand", "Million", "Billion"};
};


// ref sol -- more cleaner, and let helper function always return trailing space except for 0
class Solution {
public:
    string numberToWords(int num) {
        if(!num)
            return "Zero";

        string ans;
        int u = 0;  // unit
        while(num) {
            if(num % 1000) {  // non-zero three digits
                ans = helper(num%1000) + units[u] + ans;
            }
            num /= 1000;
            ++u;
        }

        // remove trailing spaces
        while(ans.back() == ' ')
            ans.pop_back();

        return ans;
    }

private:
    // convert any number in [0,999] to english
    // always add a trailing space except for 0
    string helper(int num) {
        if(num == 0)
            return "";
        else if(num < 20)
            return less20[num] + " ";
        else if(num < 100)
            return tens[num/10] + " " + helper(num%10);
        else
            return less20[num/100] + " Hundred " + helper(num%100);
    }

private:
    vector<string> less20 = {""/*important to return empty string for 0*/, "One", "Two", "Three", "Four", "Five", 
    "Six", "Seven", "Eight", "Nine", "Ten",
    "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
    "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> units = {"", "Thousand "/*notice the trailing zero*/, "Million ", "Billion "};
};
