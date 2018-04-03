/*
  Given an integer n, return the number of trailing zeroes in n!.

  Note: Your solution should be in logarithmic time complexity.
*/

// Essentially, this is converted to "count how many factor of 5 in numbers from 1...n
// -- Because for every “5” there are at least two “2” factors to match it.

// References
// https://leetcode.com/problems/factorial-trailing-zeroes/discuss/52373/Simple-CC++-Solution-(with-detailed-explaination)
// https://leetcode.com/problems/factorial-trailing-zeroes/discuss/52371/My-one-line-solutions-in-3-languages

// My first attempt is brute-force linear solution, which exceeds runtime limit
class Solution {
public:
  int trailingZeroes(int n) {
    int num = 0;
    for(int i=1; i<=n; ++i) {
      int cur = i;
      while(cur && cur%5==0) {
	++num;
	cur /= 5;
      }
    }
    return num;
  }
};

// This is O(lgN) recursive solution
class Solution {
public:
  int trailingZeroes(int n) {
    int n5 = n/5;
    return n5 + (n5 ? trailingZeroes(n5) : 0);
  }
};

// Simple iterative solution
class Solution {
public:
  int trailingZeroes(int n) {
    int num = 0;
    while(n) {
      num += (n/=5);
    }
    return num;
  }
};
