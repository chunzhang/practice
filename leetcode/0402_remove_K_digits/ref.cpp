// By maintaining a “top” index (i.e., use vector as a stack), there’s no need to really delete an element out of the vector
// https://leetcode.com/problems/remove-k-digits/discuss/88660/A-greedy-method-using-stack-O(n)-time-and-O(n)-space
public class Solution {
    public String removeKdigits(String num, int k) {
      int digits = num.length() - k;
      char[] stk = new char[num.length()];
      int top = 0;
      // k keeps track of how many characters we can remove
      // if the previous character in stk is larger than the current one
      // then removing it will get a smaller number
      // but we can only do so when k is larger than 0
      for (int i = 0; i < num.length(); ++i) {
	char c = num.charAt(i);
	while (top > 0 && stk[top-1] > c && k > 0) {
	  top -= 1;
	  k -= 1;
	}
	stk[top++] = c;
      }
      // find the index of first non-zero digit
      int idx = 0;
      while (idx < digits && stk[idx] == '0') idx++;
      return idx == digits? "0": new String(stk, idx, digits - idx);
    }
};

// Brute-force solution -- O(k*N)
// https://leetcode.com/problems/remove-k-digits/discuss/88678/Two-algorithms-with-detailed-explaination
/*
  The first algorithm is straight-forward. Let’s think about the simplest case: how to remove 1 digit from the number so that the new number is the smallest possible？ Well, one can simply scan from left to right, and remove the first “peak” digit; the peak digit is larger than its right neighbor. One can repeat this procedure k times, and obtain the first algorithm:
*/
string removeKdigits(string num, int k) {
  while (k > 0) {
    int n = num.size();
    int i = 0;
    while (i+1<n && num[i]<=num[i+1])  i++;
    num.erase(i, 1);
    k--;
  }
  // trim leading zeros
  int s = 0;
  while (s<(int)num.size()-1 && num[s]=='0')  s++;
  num.erase(0, s);
        
  return num=="" ? "0" : num;
};

// Same idea using stack
// https://leetcode.com/problems/remove-k-digits/discuss/88678/Two-algorithms-with-detailed-explaination
/*
  One can simulate the above procedure by using a stack, and obtain a O(n) algorithm. Note, when the result stack (i.e. res) pop a digit, it is equivalent as remove that “peak” digit.
*/
string removeKdigits(string num, int k) {
  string res;
  int keep = num.size() - k;
  for (int i=0; i<num.size(); i++) {
    while (res.size()>0 && res.back()>num[i] && k>0) {
      res.pop_back();
      k--;
    }
    res.push_back(num[i]);
  }
  res.erase(keep, string::npos);
        
  // trim leading zeros
  int s = 0;
  while (s<(int)res.size()-1 && res[s]=='0')  s++;
  res.erase(0, s);
        
  return res=="" ? "0" : res;
};
