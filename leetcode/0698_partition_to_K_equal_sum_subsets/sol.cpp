/*
  Given an integer array nums and an integer k, return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.

 

  Example 1:

  Input: nums = [4,3,2,3,5,2,1], k = 4
  Output: true
  Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
  Example 2:

  Input: nums = [1,2,3,4], k = 3
  Output: false
 

  Constraints:

  1 <= k <= nums.length <= 16
  1 <= nums[i] <= 10^4
  The frequency of each element is in the range [1, 4].
*/

// DFS with pruning
// time complexity: O(k*2^N), i.e., each element can be either selected or unselected for each subset
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = 0;
        for(int num : nums)
            total += num;
        
        if(total%k != 0)
            return false;
        
        int target = total / k;
        unsigned used = 0;
        return dfs(nums, target, used, 0, 0, k);
    }
    
private:
    bool dfs(const vector<int> &nums, const int target, unsigned &used, int cur, int sum, int k) {
        if(sum > target)
            return false;        
        else if(sum == target) {  // need to start a new partition
            cur = 0;
            sum = 0;
            --k;
        }
        
        if(k == 1)  // as long as we find k-1 satisfied sets, we know the last one also exists!!!
            return true;
        
        for(int i=cur; i<nums.size(); ++i) {  // important pruning: do not search back, i.e., sum is independent of element selection order
            if(used&(0x1<<i))  // number is already used
                continue;
            used |= (0x1<<i);
            if(dfs(nums,target, used, i+1, sum+nums[i], k))
                return true;
            used ^= (0x1<<i);
        }
        
        return false;
    }
};


// a slightly different impl
// time complexity: O(k*2^N), i.e., each element can be either selected or unselected for each subset
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = 0;
        for(int num : nums)
            total += num;
        
        if(total%k != 0)
            return false;
        
        int target = total / k;
        unsigned used = 0;
        return dfs(nums, target, used, 0, 0, k);
    }
    
private:
    bool dfs(const vector<int> &nums, const int target, unsigned used, int cur, int sum, int k) {
        if(k == 1)  // as long as we find k-1 satisfied sets, we know the last one also exists!!!
            return true;
        
        for(int i=cur; i<nums.size(); ++i) {
            if(used&(0x1<<i))  // invalid
                continue;
            int newSum = sum+nums[i];
            if(newSum > target)
                continue;
            if(newSum==target && dfs(nums,target,used|(0x1<<i), 0, 0, k-1))  // to start find a new partition
                return true;
            else if(dfs(nums,target,used|(0x1<<i),i+1,newSum,k))  // add to existing partition
                return true;
        }
        
        return false;
    }
};



// naive DFS -- TLE
// time complexity: O(N*N!), i.e, permutation ==> different order of elements being picked up ==> answer
/*
  The idea is that for each recursive call, we will iterate over N elements and make another recursive call. Assume we picked one element, then we iterate over the array and make recursive calls for the next N−1 elements and so on. Therefore, in the worst-case scenario, the total number of recursive calls will be N*(N-1)*(N-2)* ... *2*1 = N! and in each recursive call we perform an O(N) time operation.
*/
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = 0;
        for(int num : nums)
            total += num;
        
        if(total%k != 0)
            return false;
        
        int target = total / k;
        unsigned used = 0;
        return dfs(nums, target, used, 0, k);
    }
    
private:
    bool dfs(const vector<int> &nums, const int target, unsigned &used, int sum, int k) {
        if(sum > target)
            return false;        
        else if(sum == target) {
            sum = 0;
            --k;
        }
        
        if(k == 1)
            return true;
        
        for(int i=0; i<nums.size(); ++i) {
            if(used&(0x1<<i))  // invalid
                continue;
            used |= (0x1<<i);
            if(dfs(nums,target, used, sum+nums[i], k))
                return true;
            used ^= (0x1<<i);
        }
        
        return false;
    }
};
