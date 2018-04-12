/*
  Given two arrays, write a function to compute their intersection.

  Example:
  Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

  Note:
  Each element in the result should appear as many times as it shows in both arrays.
  The result can be in any order.
  Follow up:
  What if the given array is already sorted? How would you optimize your algorithm?
  What if nums1's size is small compared to nums2's size? Which algorithm is better?
  What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
*/

// Using hash table
class Solution {
public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int,int> m;
    if(nums1.size() > nums2.size())  // Build hash table on smaller input
      nums1.swap(nums2);
        
    for(int n : nums1)
      ++m[n];
        
    vector<int> ans;
    for(int n : nums2) {
      auto it = m.find(n);
      if(it != m.end()) {
	ans.push_back(it->first);
	if(--(it->second) == 0)
	  m.erase(it);
      }
    }
        
    return ans;
  }
};

// Assume inputs are sorted, we can use two pointers with O(1) space
class Solution {
public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
        
    vector<int> ans;
    for(int i=0,j=0; i<nums1.size()&&j<nums2.size(); ) {
      if(nums1[i] == nums2[j]) {
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
