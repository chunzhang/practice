/*
You are given two integer arrays of the same length nums1 and nums2. In one operation, you are allowed to swap nums1[i] with nums2[i].

For example, if nums1 = [1,2,3,8], and nums2 = [5,6,7,4], you can swap the element at i = 3 to obtain nums1 = [1,2,3,4] and nums2 = [5,6,7,8].
Return the minimum number of needed operations to make nums1 and nums2 strictly increasing. The test cases are generated so that the given input always makes it possible.

An array arr is strictly increasing if and only if arr[0] < arr[1] < arr[2] < ... < arr[arr.length - 1].

 

Example 1:

Input: nums1 = [1,3,5,4], nums2 = [1,2,3,7]
Output: 1
Explanation: 
Swap nums1[3] and nums2[3]. Then the sequences are:
nums1 = [1, 3, 5, 7] and nums2 = [1, 2, 3, 4]
which are both strictly increasing.
Example 2:

Input: nums1 = [0,3,5,8,9], nums2 = [2,1,4,6,9]
Output: 1
 

Constraints:

2 <= nums1.length <= 10^5
nums2.length == nums1.length
0 <= nums1[i], nums2[i] <= 2 * 10^5
*/

class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        // At each i, one can either swap or keep the current number
        // As such, I define DP as
        // -- swap[i]: min steps needed to make the sequence to up i-th strictly increasing when i-th numbers are swapped
        // -- keep[i]: min steps needed to make the sequence to up i-th strictly increasing when i-th numbers are kept, i.e., not swept
        // Then, based on the values of (i-1)-th and i-th numbers, we can come up with the correct transition
        
        int n = nums1.size();
        vector<int> keep(n, INT_MAX);
        vector<int> swap(n, INT_MAX);
        keep[0] = 0;
        swap[0] = 1;
        for(int i=1; i<n; ++i) {
            bool cond1 = (nums1[i]>nums1[i-1] && nums2[i]>nums2[i-1]);
            bool cond2 = (nums1[i]>nums2[i-1] && nums2[i]>nums1[i-1]);
            
            keep[i] = min((cond1?keep[i-1]:INT_MAX)/*keep both (i-1)-th and i-th*/, (cond2?swap[i-1]:INT_MAX)/*keep i-th, swap (i-1)-th*/);
            swap[i] = min((cond1?swap[i-1]+1:INT_MAX)/*swap both (i-1)-th and i-th*/, (cond2?keep[i-1]+1:INT_MAX)/*swap i-th, keep (i-1)-th*/);
        }
        
        return min(keep[n-1], swap[n-1]);
    }
};


// DFS solution -- TLE
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        // This is the brute-force solution with DFS, i.e., for i-th numnber it can be either swapped or kept
        int ans = INT_MAX;
        dfs(nums1, nums2, 0, 0, ans);
        return ans;
    }
    
private:
    void dfs(vector<int> &nums1, vector<int> &nums2, int cur/*cur index*/, int swaps/*number of swaps so far*/, int &ans/*global answer*/) {
        if(cur==nums1.size()) {
            ans = min(ans, swaps);
            return;
        }
        
        if(swaps>=ans)
            return;   // pruning because "swaps" monotonically increase
        
        if(cur==0 || nums1[cur]>nums1[cur-1] && nums2[cur]>nums2[cur-1]) {  // try keep cur-th number
            dfs(nums1, nums2, cur+1, swaps, ans);
        }
        
        if(cur==0 || nums1[cur]>nums2[cur-1] && nums2[cur]>nums1[cur-1]) {  // try swap cur-th number
            swap(nums1[cur], nums2[cur]);
            dfs(nums1, nums2, cur+1, swaps+1, ans);
            swap(nums1[cur], nums2[cur]);  // must restore previous status
        }
    }
};
