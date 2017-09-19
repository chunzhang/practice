#include "../common/common.h"

class Solution {
public:
  int findSubstringInWraproundString(string p) {
    // Let D[i] be the max length of continuous substring that ends at i (e.g., i
    // can be 'a', 'b', ..., 'z')
    // -- Then, num of unique substring that ends at i is D[i]
    vector<int> maxLengths(26, 0);

    // go through p to update maxLengths
    int total = 0;
    int maxLen;
    for(int i=0; i<p.size(); ++i) {
      int cur = p[i] - 'a';
      char ch = (cur+25)%26 + 'a';  // prev character if continuous
      if(i==0 || p[i-1]!=ch)
	maxLen = 1;
      else
	++maxLen;

      if(maxLen > maxLengths[cur]) {
	total += maxLen - maxLengths[cur];
	maxLengths[cur] = maxLen;
      }
    }
    return total;
  }
};

int main(int argc, char *argv[])
{
  string p = argv[1];
  Solution sol;
  int total = sol.findSubstringInWraproundString(p);
  cout << "total: " << total << endl;

  return 0;
}
