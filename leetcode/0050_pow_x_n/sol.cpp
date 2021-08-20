#include "../common/common.h"

using namespace std;

// iterative approach
class Solution {
public:
    double myPow(double x, int n) {
        long ln = n;  // to avoid overflow when we get -INT_MIN
        if(ln < 0) {
            x = 1/x;
            ln = -ln;
        }
        
        
        // n can be represented in binary format. Let's say n=101, which is n=2'b101
        // ==> x^n = x^(2'b101) = x^(2'b100+2'b001) = x^(2'b100) * x^(2'b001)
        // ==> by keeping track of base, and multiply the result with base when LSB is 1, we can get the answer
        double ans = 1;
        double base = x;
        while(ln) {
            if(ln & 0x1)  // LSB is 1, need to multiply base
                ans *= base;
            base *= base;
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
