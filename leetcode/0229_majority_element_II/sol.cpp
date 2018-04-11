/*
  Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
*/

class Solution {
public:
  vector<int> majorityElement(vector<int>& nums) {
    int n1=0, n2=1, c1=0, c2=0;  // Initial value doesn't matter as its count is set to 0
    for(int n : nums) {
      if(n == n1) {
	++c1;
      }
      else if(n == n2) {
	++c2;
      }
      else {
	if(c1 == 0) {
	  n1 = n;
	  c1 = 1;
	}
	else if(c2 == 0) {
	  n2 = n;
	  c2 = 1;
	}
	else {    // Key is to decrement both count
	  --c1;
	  --c2;
	}
      }
    }

    // Final verification as the majority element may not exist
    vector<int> ans;
    int threshold = nums.size() / 3;
    c1 = c2 = 0;
    for(int n : nums) {
      if(n1 == n)
	++c1;
      if(n2 == n)
	++c2;
    }
    if(c1 > threshold)
      ans.push_back(n1);
    if(c2 > threshold)
      ans.push_back(n2);
        
    return ans;
  }
};
