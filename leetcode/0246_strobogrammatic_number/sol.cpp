/*
  A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

  Write a function to determine if a number is strobogrammatic. The number is represented as a string.

  For example, the numbers "69", "88", and "818" are all strobogrammatic.
*/

#include "../common/common.h"

using namespace std;

class Solution {
public:
  bool isStrobogrammatic(string num) {
    vector<int> matching(128,-1);
    matching['0'] = '0';
    matching['1'] = '1';
    matching['6'] = '9';
    matching['8'] = '8';
    matching['9'] = '6';
    int i=0, j=num.size()-1;
    for(; i<=j; ++i,--j) {
      if(matching[num[i]] != num[j])
	return false;
    }
    return true;
  }
};

int main(int argc, char *argv[])
{
  string num = argv[1];
  Solution sol;
  bool res = sol.isStrobogrammatic(num);
  cout << "res: " << res << endl;

  return 0;
}
