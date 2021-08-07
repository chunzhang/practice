/*
Given an integer array nums, return the length of the longest strictly increasing subsequence.

A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].

 

Example 1:

Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
Example 2:

Input: nums = [0,1,0,3,2,3]
Output: 4
Example 3:

Input: nums = [7,7,7,7,7,7,7]
Output: 1
 

Constraints:

1 <= nums.length <= 2500
-104 <= nums[i] <= 104
 

Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
*/

// DP O(N^2)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // dp(i): longest increase sub-sequence that ends at i
        // dp(i) = max{dp(j)+1 if nums[i]>nums[j] else 1, for 0<=j<i}
        int ans = 1;
        vector<int> dp(nums.size(), 1);
        for(int i=1; i<nums.size(); ++i) {
            for(int j=0; j<i; ++j) {
                if(nums[i] > nums[j])
                    dp[i] = max(dp[i], dp[j]+1);
            }
            ans = max(ans, dp[i]);
        }
        
        return ans;
    }
};


// A very smart way of intelligent build the sequence with O(NlgN) time complexity
/*
As stated in the previous approach, the difficult part of this problem is deciding if an element is worth using or not. Consider the example nums = [8, 1, 6, 2, 3, 10]. Let's try to build an increasing subsequence starting with an empty one: sub = [].

At the first element 8, we might as well take it since it's better than nothing, so sub = [8].

At the second element 1, we can't increase the length of the subsequence since 8 >= 1, so we have to choose only one element to keep. Well, this is an easy decision, let's take the 1 since there may be elements later on that are greater than 1 but less than 8, now we have sub = [1].

At the third element 6, we can build on our subsequence since 6 > 1, now sub = [1, 6].

At the fourth element 2, we can't build on our subsequence since 6 >= 2, but can we improve on it for the future? Well, similar to the decision we made at the second element, if we replace the 6 with 2, we will open the door to using elements that are greater than 2 but less than 6 in the future, so sub = [1, 2].

At the fifth element 3, we can build on our subsequence since 3 > 2. Notice that this was only possible because of the swap we made in the previous step, so sub = [1, 2, 3].

At the last element 10, we can build on our subsequence since 10 > 3, giving a final subsequence sub = [1, 2, 3, 10]. The length of sub is our answer.

It appears the best way to build an increasing subsequence is: for each element num, if num is greater than the largest element in our subsequence, then add it to the subsequence. Otherwise, perform a linear scan through the subsequence starting from the smallest element and replace the first element that is greater than or equal to num with num. This opens the door for elements that are greater than num but less than the element replaced to be included in the sequence.

One thing to add: this algorithm does not always generate a valid subsequence of the input, but the length of the subsequence will always equal the length of the longest increasing subsequence. For example, with the input [3, 4, 5, 1], at the end we will have sub = [1, 4, 5], which isn't a subsequence, but the length is still correct. The length remains correct because the length only changes when a new element is larger than any element in the subsequence. In that case, the element is appended to the subsequence instead of replacing an existing element.
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // O(NlgN) algorithm with a super smart way to build the sequence
        // One can view as DP too, i.e., seq(i): smallest tailing number of a increasing subsequence of length i+1 (since i starts from 0)
        vector<int> seq;
        for(int n : nums) {
            if(seq.empty() || n>seq.back()) {
                seq.push_back(n);
                continue;
            }

            // we want to keep n into the seq so it can grow in the future;
            // but where to put n? replace the first number in seq that is greater or equal to n;
            // this doesn't make the sequence valid, but the max length of the sequence is always correct
                
            // binary search to find location
            int l = 0;
            int r = seq.size();
            while(l<r) {
                int mid = l + (r-l)/2;
                if(seq[mid] >= n)  // if there's already a number that equals to n exist in seq, we must replace it or otherwise we will over count the size
                    r = mid;
                else
                    l = mid + 1;
            }
            seq[l] = n;

            // NOTE one can also directly C++ API for the binary search
            /*
            auto pos = lower_bound(seq.begin(), seq.end(), n);
            *pos = n;
            */
        }
        
        return seq.size();
    }
};
