/*
Given an array arr of positive integers, consider all binary trees such that:

Each node has either 0 or 2 children;
The values of arr correspond to the values of each leaf in an in-order traversal of the tree.
The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree, respectively.
Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node. It is guaranteed this sum fits into a 32-bit integer.

A node is a leaf if and only if it has zero children.

 

Example 1:


Input: arr = [6,2,4]
Output: 32
Explanation: There are two possible trees shown.
The first has a non-leaf node sum 36, and the second has non-leaf node sum 32.
Example 2:


Input: arr = [4,11]
Output: 44
 

Constraints:

2 <= arr.length <= 40
1 <= arr[i] <= 15
It is guaranteed that the answer fits into a 32-bit signed integer (i.e., it is less than 2^31).
*/

// DP O(N^3) time complexity
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        // dp(i,j): sum of non-leaf nodes of min-cost-tree (MST) of arr[i:j]
        // dp(i,j) = min{dp(i,k)+max(i,k)*max(k+1,j)+dp(k+1,j)}, for i<=k<j
        const int N = arr.size();
        
        vector<vector<int>> m(N, vector<int>(N,0));  // max val in arr[i:j]
        // now, compute MST
        vector<vector<int>> dp(N, vector<int>(N,INT_MAX));
        for(int i=0; i<N; ++i) {
            m[i][i] = arr[i];
            dp[i][i] = 0;
        }
        // bottom up by length
        for(int l=2; l<=N; ++l) {
            for(int i=0,j=i+l-1; j<N; ++i,++j) {
                m[i][j] = max(m[i][j-1], arr[j]);
                for(int k=i; k<j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k]+m[i][k]*m[k+1][j]+dp[k+1][j]);
                }
            }
        }
        
        return dp[0][N-1];
    }
};


// O(N) greedy solution using mono-stack
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        // O(N) mono-stack solution
        // greedy algorithm: always multiply two small numbers first, i.e., put smaller leafs deeper into the tree
        // let's maintain a mono-decrease stack; as soon as we encounter a val>=st.top(), we select from the new val or the second top to build tree
        // we can pad the first element of stack as INT_MAX to simply coding
        int ans = 0;
        stack<int> st;
        st.push(INT_MAX);  // padding to simply coding
        for(int val : arr) {
            while(st.top()<=val) {  // due to padding, the stack can't be empty
                int leaf = st.top();
                st.pop();
                ans += leaf * min(st.top(), val);
            }
            st.push(val);
        }
        
        while(st.size()>2) {
            int val = st.top();
            st.pop();
            ans += val*st.top();
        }
        
        return ans;
    }
};
