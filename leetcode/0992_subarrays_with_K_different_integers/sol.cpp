/*
  Given an integer array nums and an integer k, return the number of good subarrays of nums.

  A good array is an array where the number of different integers in that array is exactly k.

  For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
  A subarray is a contiguous part of an array.

 

  Example 1:

  Input: nums = [1,2,1,2,3], k = 2
  Output: 7
  Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
  Example 2:

  Input: nums = [1,2,1,3,4], k = 3
  Output: 3
  Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
 

  Constraints:

  1 <= nums.length <= 2 * 10^4
  1 <= nums[i], k <= nums.length
*/



// use two pointers to compute #subarrays with <=k unique integers
// use indirection to compute answer=#subarrays(k)-#subarrays(k-1)
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return f(nums,k) - f(nums, k-1);
    }
    
private:
    // count #subarrays with less or equal to k unique integers
    int f(const vector<int> &nums, int k) {
        vector<int> count(nums.size()+1, 0);
        int diff = 0;
        int ans = 0;

        // compute all such subarrays that starts at i
        for(int i=0,j=0; i<nums.size(); ++i) {
            while(j<nums.size()) {
                if(diff<k || count[nums[j]]!=0) {  // only add j if it does not violate k
                    if(count[nums[j]]++ == 0)
                        ++diff;
                    ++j;
                }
                else
                    break;
            }
            
            ans += j-i;  // all subarrays in [i,j) has <=k unique integers
            if(count[nums[i]]-- == 1)
                --diff;
        }
        
        return ans;
    }
};


// use two pointers -- HuaHua
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        // Returns the number of subarrays with k or less distinct numbers.
        auto subarrys = [&A](int k) {
            vector<int> count(A.size() + 1);
            int ans = 0;
            int i = 0;
            for (int j = 0; j < A.size(); ++j) {  // for subarry tht ends at j
                if (count[A[j]]++ == 0) 
                    --k;
                while (k < 0)
                    if (--count[A[i++]] == 0)
                        ++k;
                ans += j - i + 1;
            }
            return ans;
        };
        return subarrys(K) - subarrys(K - 1);
    }
};



// a less elegant impl
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return f(nums,k) - f(nums, k-1);
    }
    
private:
    // count #subarrays with less or equal to k unique integers
    int f(const vector<int> &nums, int k) {
        vector<int> count(nums.size()+1, 0);
        int diff = 0;
        int ans = 0;
        // loop invariant: subarray [i,j) has less or equal to k number of unique integers
        // using this property, the orirignal O(N^2) complexity can be reduced to O(N)
        for(int i=0,j=0; i<nums.size(); ) {  // for subarray starting at i
            ans += j-i;
            
            for(; j<nums.size(); ) {
                if(count[nums[j]]++ == 0)
                    ++diff;
                if(diff <= k) {
                    ++ans;
                    ++j;
                }
                else {
                    count[nums[j]]--;
                    --diff;
                    break;
                }
            }
            
            // move i to next
            if(count[nums[i]]-- == 1)
                --diff;
            ++i;
        }
        
        return ans;
    }
};

