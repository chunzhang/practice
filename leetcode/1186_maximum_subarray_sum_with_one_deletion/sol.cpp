/*
Amazon/Facebook
  
Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion. In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.

Note that the subarray needs to be non-empty after deleting one element.

 

Example 1:

Input: arr = [1,-2,0,3]
Output: 4
Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
Example 2:

Input: arr = [1,-2,-2,3]
Output: 3
Explanation: We just choose [3] and it's the maximum sum.
Example 3:

Input: arr = [-1,-1,-1,-1]
Output: -1
Explanation: The final subarray needs to be non-empty. You can't choose [-1] and delete -1 from it, then get an empty subarray to make the sum equals to 0.
 

Constraints:

1 <= arr.length <= 10^5
-10^4 <= arr[i] <= 10^4
*/


// Sol 1: three pass DP on top of 0053
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        const int N = arr.size();

        // use DP to get max subarry sum start and end at i (no element removal)
        // dp_end[i] = max(arr[i],dp_end[i-1]+arr[i])
        // dp_start[i] = max(arr[i], dp_start[i+1]+arr[i])
        int res = arr[0];
        vector<int> dp_end = arr;
        for(int i=1; i<N; ++i) {
            dp_end[i] = max(arr[i], arr[i]+dp_end[i-1]);
            res = max(res,dp_end[i]);
        }

        vector<int> dp_start = arr;
        for(int i=N-2; i>=0; --i) {
            dp_start[i] = max(arr[i], arr[i]+dp_start[i+1]);
            // no need to update res here as it overlaps the result got in the previous iteration
        }

        // now, if we remove any element at index i, the additional benefit we get (i.e., not
        // counted previously) is dp_end[i-1]+dp_start[i+1]
        // - note there's no need to try remove first and last element -- they're already part of above solution
        for(int i=1; i<N-1; ++i) {
            if(arr[i] < 0)  // only need try remove negative number
                res = max(res, dp_end[i-1]+dp_start[i+1]);
        }
        return res;
    }
};


// Sol 2: one pass DP by extending Kadane's Algorithm
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        // dp_del[i]: max sum subarray that ends at i with one deletion
        // dp_no_del[i]: max sum subarray that ends at i with no deletion
        int res = arr[0];
        vector<int> dp_del = arr;
        dp_del[0] = 0;  // base case: arr[0] is deleted
        vector<int> dp_no_del = arr;
        for(int i=1; i<arr.size(); ++i) {
            dp_del[i] = max(dp_del[i-1]+arr[i]/*extend previous deletion*/, dp_no_del[i-1]/*delete current number*/);
            dp_no_del[i] = max(dp_no_del[i-1]+arr[i], arr[i]);
            res = max({res, dp_del[i], dp_no_del[i]});  // note the use of {}
        }

        return res;
    }
};


// smae idea as Sol 2, but reduce to single variable (no need to fully build the DP array)
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        // dp_del[i]: max sum subarray that ends at i with one deletion
        // dp_no_del[i]: max sum subarray taht ends at i with no deletion
        // since this is one pass left to right scan, we can use single var to replace the dp array
        int res = arr[0];
        int dp_del = 0;
        int dp_no_del = arr[0];
        for(int i=1; i<arr.size(); ++i) {
            dp_del = max(dp_del+arr[i]/*extend previous deletion*/,dp_no_del/*delete current number*/);
            dp_no_del = max(dp_no_del+arr[i], arr[i]);
            res = max({res, dp_del, dp_no_del});
        }

        return res;
    }
};
