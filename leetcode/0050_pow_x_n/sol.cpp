#include "../common/common.h"

using namespace std;

// iterative approach
class Solution {
public:
  double myPow(double x, int n) {
    long long ln = n;  // in case of overflow
    if(ln < 0) {
      x = 1/x;
      ln = -ln;
    }

    // Say n = 2'b101, it can be decomposed as (2'b100 + 2'b001). In fact,
    // 2'b100==>x^4, 2'b001==>x^1, and this can be the interpreation of the
    // following iterative approach
    double ans = 1;
    while(ln) {
      if(ln % 2)
	ans *= x;
      x *= x;
      ln /= 2;
    }

    return ans;
  }
};

// iterative solution based on simulating recursion
class Solution3 {
public:
    double myPow(double x, int n) {
        long long ln = n;
        if(ln < 0) {
            ln = -ln;
            x = 1/x;
        }
        
        stack<long long> s;
        while(ln > 0) {
            s.push(ln);
            ln /= 2;
        }
        double ans = 1.0;
        while(!s.empty()) {
            long long cur = s.top();
            s.pop();
            ans *= ans;
            if(cur % 2)
                ans *= x;
        }
        return ans;
    }
};

// recursive approach
class Solution2 {
public:
  double myPow(double x, int n) {
    if(n == 0)
      return 1;

    double ans = n<0 ? 1/x : x;
    double pow = myPow(x, n/2);
    return n%2 ? ans*pow*pow : pow*pow;
  }
};

int main(int argc, char *argv[])
{
  double x = atof(argv[1]);
  int n = atoi(argv[2]);
  Solution sol;
  double res = sol.myPow(x, n);
  cout << "res: " << res << endl;

  return 0;
}
