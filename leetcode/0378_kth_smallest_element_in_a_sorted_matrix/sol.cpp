/*
Given an n x n matrix where each of the rows and columns are sorted in ascending order, return the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

 

Example 1:

Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
Example 2:

Input: matrix = [[-5]], k = 1
Output: -5
 

Constraints:

n == matrix.length
n == matrix[i].length
1 <= n <= 300
-10^9 <= matrix[i][j] <= 10^9
All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.
1 <= k <= n^2
*/

// binary search: find first element that the matrix has >=k numbers smaller or equal to it
// time complexity: O(NlgW), where W is the span of max-min value in the matrix
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int l = matrix[0][0];
        int r = matrix.back().back() + 1;
        while(l < r) {
            // find first number that the matrix has >=k numbers smaller than it
            int m = l + (r-l)/2;
            int count = countSmallerOrEqual(matrix, m);
            if(count>=k)
                r = m;
            else
                l = m + 1;
        }
        
        return l;
    }
    
private:
    // count numer of elements in matrix that is smaller or equal to val
    // O(N)
    int countSmallerOrEqual(const vector<vector<int>> &matrix, int val) {
        int count = 0;
        const int M = matrix.size();
        const int N = M?matrix[0].size():0;
        for(int i=M-1,j=0; i>=0&&j<N; ) {
            if(matrix[i][j] <= val) {
                count += i+1;
                ++j;
            }
            else
                --i;
        }
        return count;
    }
};


// binary search: find first element that the matrix has >=k numbers smaller or equal to it
// time complexity: O(NlgNlgW), where W is the span of max-min value in the matrix
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int l = matrix[0][0];
        int r = matrix.back().back() + 1;
        while(l < r) {
            int m = l + (r-l)/2;
            int count = countSmallerOrEqual(matrix, m);
            if(count>=k)
                r = m;
            else
                l = m + 1;
        }
        
        return l;
    }
    
private:
    // count numer of elements in matrix that is smaller or equal to val
    // O(NlgN)
    int countSmallerOrEqual(const vector<vector<int>> &matrix, int val) {
        int count = 0;
        for(int i=0; i<matrix.size(); ++i)
            count += distance(matrix[i].begin(), upper_bound(matrix[i].begin(), matrix[i].end(), val));
        
        return count;
    }
};

// Solution 2: Min-heap
// time complexity: O(X+KlgX), where X=min(K,N) -- O(X) to build heap, and K heap pop/push, each takes O(lgX) time
// heap node
struct HeapNode {
    HeapNode(int val, int row, int col) : v(val),r(row),c(col) {}
    int v;  // value
    int r;  // row
    int c;  // col
};

auto myComp = [](const HeapNode &n1, const HeapNode &n2) { return n1.v > n2.v;};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // in this solution, we treat this problem the same way as sorting N sorted list;
        // use a min-heap to keep track of current smallest element
        priority_queue<HeapNode, vector<HeapNode>, decltype(myComp)> hp(myComp);  // min-heap
        const int N = matrix.size();
        for(int i=0; i<min(N,k); ++i)  // we at most need min(n,k) elements in the heap since elements in the same column are also sorted
            hp.push(HeapNode(matrix[i][0],i,0));
        
        int res;
        while(k--) {
            HeapNode n = hp.top();
            hp.pop();
            res = n.v;
            int nr = n.r;  // next row
            int nc = n.c + 1;  // next col
            if(nc < N)
                hp.push(HeapNode(matrix[nr][nc], nr, nc));
        }
        
        return res;
    }
};
