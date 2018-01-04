/*
Given a sorted integer array where the range of elements are in the inclusive range [lower, upper], return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].
*/

#include "../common/common.h"

using namespace std;

// A simpler version
class Solution {
public:
  vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
    vector<string> res;
    long long pre = (long long)lower -1;  // invariant: this number is not missing
    for(int i=0; i<=nums.size(); ++i) {
      long long cur = i<nums.size() ? nums[i] : (long long)upper+1;
      if(cur-pre > 1)
	res.push_back(genRange(pre+1, cur-1));
      pre = cur;
    }

    return res;
  }

  string genRange(int lo, int hi) {
    ostringstream oss;
    if(lo == hi)
      oss << lo;
    else
      oss << lo << "->" << hi;
    return oss.str();
  }

};

class Solution2 {
public:
  vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
    vector<string> res;
    if(nums.empty()) {
      res.push_back(genRange(lower, upper));
      return res;
    }

    int first = nums.front();
    if(first > lower)
      res.push_back(genRange(lower, first-1));
    for(int i=1; i<nums.size(); ++i) {
      if((long long)nums[i]-nums[i-1] > 1)  // need the cast in case of integer overflow!
	res.push_back(genRange(nums[i-1]+1, nums[i]-1));
    }
    int last = nums.back();
    if(last < upper)
      res.push_back(genRange(last+1, upper));

    return res;
  }

  string genRange(int lo, int hi) {
    ostringstream oss;
    if(lo == hi)
      oss << lo;
    else
      oss << lo << "->" << hi;
    return oss.str();
  }
};

int main(int argc, char* argv[])
{
  vector<int> nums = readVector(argc, argv);
  int upper = nums.back();
  nums.pop_back();
  int lower = nums.back();
  nums.pop_back();
  Solution sol;
  vector<string> res = sol.findMissingRanges(nums, lower, upper);
  printVector(res);

  return 0;
}
