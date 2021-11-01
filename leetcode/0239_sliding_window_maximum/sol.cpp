/*
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
Example 3:

Input: nums = [1,-1], k = 1
Output: [1,-1]
Example 4:

Input: nums = [9,11], k = 2
Output: [11]
Example 5:

Input: nums = [4,-2], k = 2
Output: [4]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
*/


// use mono-queue: keep mono non-increasing order
// time complexity: O(N), i.e., each element pushed into and poped from the deque at most once
// space complexity: O(k)
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res;
    deque<int> m;  // in non-increase manner, keeps track of current max at queue front

    if(nums.empty())
      return res;

    // initial window
    for(int i=0; i<k; ++i) {
      moveIn(m, nums[i]);
    }
    res.push_back(m.front());

    // sliding window
    for(int i=k; i<nums.size(); ++i) {
      // Whether we firt move-in or move-out does not matter
      moveIn(m, nums[i]);
      moveOut(m, nums[i-k]);
      res.push_back(m.front());
    }

    return res;
  }

  void moveIn(deque<int> &m, int val) {
    while(m.size() && m.back()<val)
      m.pop_back();
    m.push_back(val);
  }

  void moveOut(deque<int> &m, int val) {
    if(m.front() == val)
      m.pop_front();
  }
};


// my from-scratch impl, slightly less elegant and efficient
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        const int N = nums.size();
        
        // mono-queue: keep mono-decrease dequeue
        deque<pair<int,int>> dq;
        for(int i=0; i<k; ++i)
            addElem(dq, nums[i], i);
        
        vector<int> ans;
        for(int i=0; i<=N-k; ++i) {
            ans.push_back(dq.front().first);
            // move to next window
            if(i<N-k) {
                delElem(dq, i);
                addElem(dq, nums[i+k], i+k);
            }
        }
        
        return ans;
    }
    
private:
    void addElem(deque<pair<int,int>> &dq, int val, int idx) {
        while(dq.size() && dq.back().first<= val)
            dq.pop_back();
        dq.push_back({val,idx});
    }
    
    void delElem(deque<pair<int,int>> &dq, int idx) {
        if(idx == dq.front().second)
            dq.pop_front();
    }
};


// DP
// https://leetcode.com/problems/sliding-window-maximum/discuss/65881/O(n)-solution-in-Java-with-two-simple-pass-in-the-array
/*
For Example: A = [2,1,3,4,6,3,8,9,10,12,56], w=4

partition the array in blocks of size w=4. The last block may have less then w.
2, 1, 3, 4 | 6, 3, 8, 9 | 10, 12, 56|

Traverse the list from start to end and calculate max_so_far. Reset max after each block boundary (of w elements).
left_max[] = 2, 2, 3, 4 | 6, 6, 8, 9 | 10, 12, 56

Similarly calculate max in future by traversing from end to start.
right_max[] = 4, 4, 4, 4 | 9, 9, 9, 9 | 56, 56, 56

now, sliding max at each position i in current window, sliding-max(i) = max{right_max(i), left_max(i+w-1)}
sliding_max = 4, 6, 6, 8, 9, 10, 12, 56
*/
// in Java
public static int[] slidingWindowMax(final int[] in, final int w) {
     final int[] max_left = new int[in.length];
     final int[] max_right = new int[in.length];
     
     max_left[0] = in[0];
     max_right[in.length - 1] = in[in.length - 1];
     
     for (int i = 1; i < in.length; i++) {
         max_left[i] = (i % w == 0) ? in[i] : Math.max(max_left[i - 1], in[i]);
         
         final int j = in.length - i - 1;
         max_right[j] = (j % w == 0) ? in[j] : Math.max(max_right[j + 1], in[j]);
     }
     
     final int[] sliding_max = new int[in.length - w + 1];
     for (int i = 0, j = 0; i + w <= in.length; i++) {
         sliding_max[j++] = Math.max(max_right[i], max_left[i + w - 1]);
     }
     
     return sliding_max;
 }

