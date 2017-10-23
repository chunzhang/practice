#include "../common/common.h"

using namespace std;

class Solution {
public:
  int countNumbersWithUniqueDigits(int n) {
    if(n < 0)
      return 0;

    if(n > 10)
      n = 10;

    // Let N[i] be the number of i-digit unique numbers, then
    // N[i] = P(10, i) = N[i-1]*(10-i+1)
    vector<int> N(n+1, 0);
    N[0] = 1;  // Just for convenience
    int count = 0;
    for(int i=1; i<=n; ++i) {
      N[i] = N[i-1] * (10-i+1);
      count += N[i]*9/10;  // 1/10 of the numbers are led by 0, so remove them
    }

    return count + 1;  // adding 0
  }
};

int main(int argc, char *argv[])
{
  int n = atoi(argv[1]);
  Solution sol;
  int count = sol.countNumbersWithUniqueDigits(n);
  cout << "count: " << count << endl;

  return 0;
}
