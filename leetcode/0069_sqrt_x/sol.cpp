/*

Given a non-negative integer x, compute and return the square root of x.

Since the return type is an integer, the decimal digits are truncated, and only the integer part of the result is returned.

Note: You are not allowed to use any built-in exponent function or operator, such as pow(x, 0.5) or x ** 0.5.

 

Example 1:

Input: x = 4
Output: 2
Example 2:

Input: x = 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since the decimal part is truncated, 2 is returned.
 

Constraints:

0 <= x <= 231 - 1
*/

#include "../common/common.h"

using namespace std;

// A third solution with clean binary search implementation
// Be mindful of possible integer overflow
class Solution {
public:
    int mySqrt(int x) {
        long l = 0;
        long r = (long)x + 1;  // search space is [0, x+1)
        while(l < r) {
            long m = l + (r-l)/2;
            if(m*m > x)
                r = m;
            else
                l = m + 1;
        }
        return l - 1;  // l is the first element that has l*l>x
    }
};


// A better solution w/o using long long
class Solution2 {
public:
  int mySqrt(int x) {
    if(x < 0)
      return numeric_limits<int>::min();

    if(x == 0)
      return 0;

    int lo = 1;
    int hi = x;
    while(1) {
      int mid = lo + (hi-lo)/2;  // avoid overflow
      if(mid > x/mid) {  // use divide to avoid overflow
	hi = mid - 1;
      }
      else {  // mid*mid <= x
	if(mid+1 > x/(mid+1))
	  return mid;
	lo = mid + 1;
      }
    }
  }

};

class Solution1 {
public:
  int mySqrt(int x) {
    if(x < 0)
      return numeric_limits<int>::min();

    long long lo = 0;        // always points to numnber that is <=sqrt(x)
    long long hi = x + 1ll;  // always points to number that is >sqrt(x)
    while(hi-lo > 1) {
      long long mid = (lo+hi) / 2;
      long long prod = mid*mid;
      if(prod == x)
	return mid;
      else if(prod < x)
	lo = mid;
      else
	hi = mid;
    }

    return lo;
  }
};

int main(int argc, char *argv[])
{
  int x = atoi(argv[1]);
  Solution sol;
  int res = sol.mySqrt(x);
  cout << "res: " << res << endl;

  return 0;
}
