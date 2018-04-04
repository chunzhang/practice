/*
  There is a fence with n posts, each post can be painted with one of the k colors.

  You have to paint all the posts such that no more than two adjacent fence posts have the same color.

  Return the total number of ways you can paint the fence.

  Note:
  n and k are non-negative integers.
*/

// O(N) space
class Solution {
public:
  int numWays(int n, int k) {
    if(n<=0 || k<=0)
      return 0;
        
    vector<int> A(n, 0);  // ways to paint with same color of previous post
    vector<int> B(n, 0);  // ways to paint with different color of previous post
    A[0] = 0;
    B[0] = k;
    for(int i=1; i<n; ++i) {
      A[i] = B[i-1];
      B[i] = (A[i-1] + B[i-1]) * (k-1);
    }
        
    return A[n-1] + B[n-1];
  }
};

// O(1) space
class Solution {
public:
  int numWays(int n, int k) {
    if(n<=0 || k<=0)
      return 0;
        
    int sameColor = 0;
    int diffColor = k;
    for(int i=1; i<n; ++i) {
      int temp = sameColor;
      sameColor = diffColor;
      diffColor = (temp + diffColor)*(k-1);
    }
        
    return sameColor + diffColor;
  }
};
