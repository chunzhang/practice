/*
  Given two arrays, write a function to compute their intersection.

  Example:
  Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

  Note:
  Each element in the result must be unique.
  The result can be in any order.
*/

// Use hash table
class Solution {
public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> s;
    if(nums1.size() > nums2.size())
      nums1.swap(nums2);  // Just for reducing hash table size
    for(int n : nums1)
      s.insert(n);
        
    vector<int> ans;
    for(int n : nums2) {
      auto it = s.find(n);
      if(it != s.end()) {
	ans.push_back(n);
	s.erase(it);
      }
    }
        
    return ans;
  }
};

// If two input arrays are already sorted, we can solve it using only O(1) space
class Solution {
public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
        
    vector<int> ans;
    for(int i=0,j=0; i<nums1.size()&&j<nums2.size(); ) {
      if(nums1[i] == nums2[j]) {
	if(ans.empty() || ans.back()!=nums1[i])
	  ans.push_back(nums1[i]);
	++i;
	++j;
      }
      else if(nums1[i] < nums2[j])
	++i;
      else
	++j;
    }
        
    return ans;
  }
};
