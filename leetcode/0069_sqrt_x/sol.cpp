#include "../common/common.h"

using namespace std;

// A better solution w/o using long long
class Solution {
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
