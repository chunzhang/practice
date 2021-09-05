/*
You may recall that an array arr is a mountain array if and only if:

arr.length >= 3
There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
Given an integer array arr, return the length of the longest subarray, which is a mountain. Return 0 if there is no mountain subarray.

 

Example 1:

Input: arr = [2,1,4,7,3,2,5]
Output: 5
Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
Example 2:

Input: arr = [2,2,2]
Output: 0
Explanation: There is no mountain.
 

Constraints:

1 <= arr.length <= 104
0 <= arr[i] <= 104
 

Follow up:

Can you solve it using only one pass?
Can you solve it in O(1) space?
*/

// DP O(N) time and space complexity
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        // incr[i]: max continuous up-hill from left that ends at i-th num
        // decr[i]: max continuous down-hill to the right that starts at i-th num
        const int N = arr.size();
        vector<int> incr(N, 0);
        for(int i=1; i<N; ++i)
            if(arr[i] > arr[i-1])
                incr[i] = incr[i-1] + 1;
        vector<int> decr(N, 0);
        for(int i=N-2; i>=0; --i)
            if(arr[i] > arr[i+1])
                decr[i] = decr[i+1] + 1;
        
        // try all possible peaks
        int ans = 0;
        for(int i=1; i<N-1; ++i)
            if(incr[i] && decr[i])
                ans = max(ans, incr[i]+decr[i]+1);  // the peak itself is not counted in incr[i] and decr[i], so need to +1
        
        return ans;
    }
};


// O(1) space complexity using two-pointers
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        const int N = arr.size();
        int ans = 0;
        // scan arry once by two-pointers
        for(int i=0; i<N; ) {
            int j = i + 1;
            
            // up hill
            int up = 0;
            while(j<N && arr[j]>arr[j-1]) {  // j points to the next element of peak after exiting the loop
                ++j;
                ++up;
            }
            if(up == 0) {  // no up-hill path, we can skip down-hill search
                i = j;
                continue;
            }
            
            // donw hill
            int down = 0;
            while(j<N && arr[j]<arr[j-1]) {  // j points to the next element of valley after exiting the loop
                ++j;
                ++down;
            }
            if(down == 0) {  // no down hill path, we can skip
                i = j;
                continue;
            }
            
            ans = max(ans, j-i);  // [i,j] is a mountain path
            i = j - 1;  // j-1 so we can start from the valley point
        }
        
        return ans;
    }
};
