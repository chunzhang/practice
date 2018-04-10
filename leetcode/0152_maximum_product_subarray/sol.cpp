/*
  Find the contiguous subarray within an array (containing at least one number) which has the largest product.

  For example, given the array [2,3,-2,4],
  the contiguous subarray [2,3] has the largest product = 6.
*/

// DP solution
class Solution {
public:
  // Define minProd[i] and maxProd[i] being the min/max product among all subarrays ends at i
  // Then, minProd[i] = min(nums[i], minProd[i-1]*nums[i], maxProd[i-1]*nums[i])
  int maxProduct(vector<int>& nums) {
    // Based on the dependency, the DP relationship can be implemented using const space easily
    int ans = INT_MIN;
    int minProd = 1;
    int maxProd = 1;
    for(int val : nums) {
      // Key is
      // -- Not forget the subarray that contains nums[i] only
      // -- Or the current min/max product can be built from two previous end points (i.e., previous min/max product)
      int minProdNext = min(val, val>=0?minProd*val:maxProd*val);
      int maxProdNext = max(val, val>=0?maxProd*val:minProd*val);
      minProd = minProdNext;
      maxProd = maxProdNext;
      if(maxProd > ans)
	ans = maxProd;
    }
        
    return ans;
  }
};

// DP solution with slightly different transition function write up
class Solution {
public:
  // Define minProd[i] and maxProd[i] being the min/max product among all subarrays ends at i
  // Then, minProd[i] = min(nums[i], minProd[i-1]*nums[i], maxProd[i-1]*nums[i])
  int maxProduct(vector<int>& nums) {
    // Based on the dependency, the DP relationship can be implemented using const space easily
    int ans = INT_MIN;
    int minProd = 1;
    int maxProd = 1;
    for(int val : nums) {
      // Key is
      // -- Not forget the subarray that contains nums[i] only
      // -- Or the current min/max product can be built from two previous end-points (i.e., previous min/max product)
      int minProdNext = min(val, min(minProd*val, maxProd*val));
      int maxProdNext = max(val, max(minProd*val, maxProd*val));
      minProd = minProdNext;
      maxProd = maxProdNext;
      if(maxProd > ans)
	ans = maxProd;
    }
        
    return ans;
  }
};

// DP solution with cleanest implementation!
class Solution {
public:
  // Define minProd[i] and maxProd[i] being the min/max product among all subarrays ends at i
  // Then, minProd[i] = min(nums[i], minProd[i-1]*nums[i], maxProd[i-1]*nums[i])
  int maxProduct(vector<int>& nums) {
    // Based on the dependency, the DP relationship can be implemented using const space easily
    int ans = INT_MIN;
    int minProd = 1;
    int maxProd = 1;
    for(int val : nums) {
      if(val < 0)
	swap(minProd, maxProd);
      minProd = min(val, minProd*val);
      maxProd = max(val, maxProd*val);
      ans = max(ans, maxProd);
    }
        
    return ans;
  }
};
