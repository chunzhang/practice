#include "../common/common.h"

using namespace std;

class Solution {
public:
  string licenseKeyFormatting(string S, int K) {
    string res;
    const int delta = 'a' - 'A';
    for(int i=S.size()-1; i>=0; --i) {
      char c = S[i];
      if(c != '-') {
	if(res.size()%(K+1) == K)  // best way I found so far for inserting '-'
	  res.push_back('-');
	char nc = c<'a' ? c : c-delta;
	res.push_back(nc);
      }
    }

    reverse(res.begin(), res.end());
    return res;
  }
};

int main(int argc, char *argv[])
{
  string S = argv[1];
  int K = atoi(argv[2]);
  Solution sol;
  string res = sol.licenseKeyFormatting(S, K);
  cout << "res: " << res << endl;

  return 0;
}
