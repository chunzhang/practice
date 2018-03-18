/*
  Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

  The update(i, val) function modifies nums by updating the element at index i to val.
  Example:
  Given nums = [1, 3, 5]

  sumRange(0, 2) -> 9
  update(1, 2)
  sumRange(0, 2) -> 8
  Note:
  The array is only modifiable by the update function.
  You may assume the number of calls to update and sumRange function is distributed evenly.
*/

#indlude "../common/common.h"

using namespace std;

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

// 1-D Binary indexed tree (Fenwick tree) based solution
// https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
class NumArray {
public:
  NumArray(vector<int> nums) {
    _nums.resize(nums.size(), 0);
    _tree.resize(nums.size()+1, 0);
    for(int i=0; i<nums.size(); ++i)
      update(i, nums[i]);
  }
    
  void update(int i, int val) {
    int delta = val - _nums[i];
    _nums[i] = val;
    for(int index=i+1; index<_tree.size(); index+=(index&-index))
      _tree[index] += delta;
  }

  int sum(int i) {
    int sum = 0;
    for(int index=i+1; index>0; index-=(index&-index))
      sum += _tree[index];
    return sum;
  }
    
  int sumRange(int i, int j) {
    return sum(j) - sum(i) + _nums[i];
  }
private:
  vector<int> _nums;
  vector<int> _tree;
};


