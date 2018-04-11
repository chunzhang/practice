/*
  Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

  You may assume that the array is non-empty and the majority element always exist in the array.
*/

// Reference for Boyer-Moore voting algorithm
// https://gregable.com/2013/10/majority-vote-algorithm-find-majority.html

// My initial implementation
class Solution {
public:
  int majorityElement(vector<int>& nums) {
    int num = nums[0];  // current majority number
    int count = 1;
    for(int i=1; i<nums.size(); ++i) {
      if(nums[i] == num) {
	++count;
      }
      else {
	if(count == 0) {
	  num = nums[i];
	  count = 1;
	}
	else
	  --count;
      }
    }
        
    return num;
  }
};

// A more concise implementation
class Solution {
public:
  int majorityElement(vector<int>& nums) {
    int num = 0;    // This initial number doesn't matter as its count is set to 0
    int count = 0;
    for(int n : nums) {
      // This is the key
      // -- Whenever count equals 0, we effectively forget 
      //    about everything in nums up to the current index 
      //    and consider the current number as the candidate 
      //    for majority element
      // -- This is because 0 means all occurrence of previous
      //    numbers are just "cancelled out"
      if(count == 0)
	num = n;
      count += num==n ? 1 : -1;
    }
        
    return num;
  }
};

