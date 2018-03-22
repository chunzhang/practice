/*
  Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

  For example,
  Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

  Window position                Max
  ---------------               -----
  [1  3  -1] -3  5  3  6  7      3
  1 [3  -1  -3] 5  3  6  7       3
  1  3 [-1  -3  5] 3  6  7       5
  1  3  -1 [-3  5  3] 6  7       5
  1  3  -1  -3 [5  3  6] 7       6
  1  3  -1  -3  5 [3  6  7]      7
  Therefore, return the max sliding window as [3,3,5,5,6,7].

  Note: 
  You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.

  Follow up:
  Could you solve it in linear time?
*/

#include "../common/common.h"

using namespace std;

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

int main(int argc, char *argv[])
{
  vector<int> nums = readVector(argc, argv);
  int k = nums.back();
  nums.pop_back();
  printVector(nums);
  Solution sol;
  vector<int> res = sol.maxSlidingWindow(nums, k);
  printVector(res);

  return 0;
}

/*
// https://leetcode.com/problems/sliding-window-maximum/discuss/65898/Clean-C++-O(n)-solution-using-a-deque

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> ans;
        for (int i=0; i<nums.size(); i++) {
            if (!dq.empty() && dq.front() == i-k) dq.pop_front();
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();
            dq.push_back(i);
            if (i>=k-1) ans.push_back(nums[dq.front()]);
        }
        return ans;
    }
};
*/

/*
//https://leetcode.com/problems/sliding-window-maximum/discuss/65881/O(n)-solution-in-Java-with-two-simple-pass-in-the-array

For Example: A = [2,1,3,4,6,3,8,9,10,12,56], w=4

partition the array in blocks of size w=4. The last block may have less then w.
2, 1, 3, 4 | 6, 3, 8, 9 | 10, 12, 56|

Traverse the list from start to end and calculate max_so_far. Reset max after each block boundary (of w elements).
left_max[] = 2, 2, 3, 4 | 6, 6, 8, 9 | 10, 12, 56

Similarly calculate max in future by traversing from end to start.
right_max[] = 4, 4, 4, 4 | 9, 9, 9, 9 | 56, 56, 56

now, sliding max at each position i in current window, sliding-max(i) = max{right_max(i), left_max(i+w-1)}
sliding_max = 4, 6, 6, 8, 9, 10, 12, 56

code:

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
*/
