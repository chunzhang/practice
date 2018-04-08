/*
  Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

  Note:
  The length of num is less than 10002 and will be ≥ k.
  The given num does not contain any leading zero.
  Example 1:

  Input: num = "1432219", k = 3
  Output: "1219"
  Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
  Example 2:

  Input: num = "10200", k = 1
  Output: "200"
  Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
  Example 3:

  Input: num = "10", k = 2
  Output: "0"
  Explanation: Remove all the digits from the number and it is left with nothing which is 0.
*/

// Use a stack to keep digits in non-decreasing order
class Solution {
public:
  string removeKdigits(string num, int k) {
    vector<char> st;  // Used as a stack
    for(int i=0; i<num.size(); ++i) {
      if(st.empty() || num[i]>=st.back() || k==0) {
	st.push_back(num[i]);
	continue;
      }
            
      while(k && num[i]<st.back() && !st.empty()) {
	st.pop_back();
	--k;
      }
      st.push_back(num[i]);
    }
        
    // Don't forget final clean up, i.e., when input is
    // already in decreasing order such as num=1234567, k=2
    while(k--)
      st.pop_back();
        
    int i = 0;
    while(st[i] == '0')
      ++i;
        
    string ans;
    for(; i<st.size(); ++i)
      ans.push_back(st[i]);
    return ans.empty() ? "0" : ans;
  }
};

// A slightly cleaner implementation with the same idea
class Solution {
public:
  string removeKdigits(string num, int k) {
    int numDigits = num.size() - k;  // output shall have this number of digits (include leading zeros)
        
    vector<char> st;  // keep it in monotonically increasing order
    for(int i=0; i<num.size(); ++i) {      
      while(k && !st.empty() && num[i]<st.back()) {
	st.pop_back();
	--k;
      }
      st.push_back(num[i]);
    }
        
    // remove leading zeros
    int i = 0;
    while(i<st.size() && st[i]=='0')
      ++i;
        
    // final clean up is performed implicitly by including only needed digits
    string ans;
    while(i < numDigits)
      ans.push_back(st[i++]);
        
    return ans.empty() ? "0" : ans;
  }
};
