/*
On an n x n chessboard, a knight starts at the cell (row, column) and attempts to make exactly k moves. The rows and columns are 0-indexed, so the top-left cell is (0, 0), and the bottom-right cell is (n - 1, n - 1).

A chess knight has eight possible moves it can make, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.


Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly k moves or has moved off the chessboard.

Return the probability that the knight remains on the board after it has stopped moving.

 

Example 1:

Input: n = 3, k = 2, row = 0, column = 0
Output: 0.06250
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.
Example 2:

Input: n = 1, k = 0, row = 0, column = 0
Output: 1.00000
 

Constraints:

1 <= n <= 25
0 <= k <= 100
0 <= row, column <= n
*/

// My O(k*n*n) time, O(n*n) space DP solution
class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        // dp(m,n,k): probability of the knight being at (m,n) after k moves
        // dp(m,n,k) can be calculated from dp(x,y,k-1), where we can move a knight from (x,y) to (m,n)
        const vector<vector<int>> moves = {{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2}};
        vector<vector<double>> dp(n, vector<double>(n,0.0));
        dp[row][column] = 1.0;
        while(--k>=0) {
            vector<vector<double>> dpn(n, vector<double>(n,0.0));
            for(int i=0; i<n; ++i) {
                for(int j=0; j<n; ++j) {
                    if(dp[i][j] == 0.0)
                        continue;
                    for(auto &move : moves) {
                        int ni = i + move[0];
                        int nj = j + move[1];
                        if(ni>=0 && ni<n && nj>=0 && nj<n)  // stay on board
                            dpn[ni][nj] += dp[i][j]*0.125;
                    }
                }
            }
            
            dp.swap(dpn);
        }
        
        // collect result
        double ans = 0.0;
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j)
                ans += dp[i][j];
        
        return ans;
    }
};


// A reference mathematical approach
/*
Approach #2: Matrix Exponentiation [Accepted]
Intuition

The recurrence expressed in Approach #1 expressed states that transitioned to a linear combination of other states. Any time this happens, we can represent the entire transition as a matrix of those linear combinations. Then, the nn-th power of this matrix represents the transition of nn moves, and thus we can reduce the problem to a problem of matrix exponentiation.

Algorithm

First, there is a lot of symmetry on the board that we can exploit. Naively, there are N^2N 
2
  possible states the knight can be in (assuming it is on the board). Because of symmetry through the horizontal, vertical, and diagonal axes, we can assume that the knight is in the top-left quadrant of the board, and that the column number is equal to or larger than the row number. For any square, the square that is found by reflecting about these axes to satisfy these conditions will be the canonical index of that square.

This will reduce the number of states from N^2N 
2
  to approximately \frac{N^2}{8} 
8
N 
2
 
​
 , which makes the following (cubic) matrix exponentiation on this O(\frac{N^2}{8}) \times O(\frac{N^2}{8})O( 
8
N 
2
 
​
 )×O( 
8
N 
2
 
​
 ) matrix approximately 8^38 
3
  times faster.

Now, if we know that every state becomes some linear combination of states after one move, then let's write a transition matrix \mathcal{T}T of them, where the ii-th row of \mathcal{T}T represents the linear combination of states that the ii-th state goes to. Then, \mathcal{T}^nT 
n
  represents a transition of nn moves, for which we want the sum of the ii-th row, where ii is the index of the starting square.

  Complexity Analysis

Time Complexity: O(N^6 \log(K))O(N 
6
 log(K)) where N, KN,K are defined as in the problem. There are approximately \frac{N^2}{8} 
8
N 
2
 
​
  canonical states, which makes our matrix multiplication O(N^6)O(N 
6
 ). To find the KK-th power of this matrix, we make O(\log(K))O(log(K)) matrix multiplications.

Space Complexity: O(N^4)O(N 
4
 ). The matrix has approximately \frac{N^4}{64} 
64
N 
4
 
​
  elements.

*/

// Java implementation
class Solution {
    public double knightProbability(int N, int K, int sr, int sc) {
        int[] dr = new int[]{-1, -1, 1, 1, -2, -2, 2, 2};
        int[] dc = new int[]{2, -2, 2, -2, 1, -1, 1, -1};

        int[] index = new int[N * N];
        int t = 0;
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (r * N + c == canonical(r, c, N)) {
                    index[r * N + c] = t;
                    t++;
                } else {
                    index[r * N + c] = index[canonical(r, c, N)];
                }
            }
        }

        double[][] T = new double[t][t];
        int curRow = 0;
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (r * N + c == canonical(r, c, N)) {
                    for (int k = 0; k < 8; k++) {
                        int cr = r + dr[k], cc = c + dc[k];
                        if (0 <= cr && cr < N && 0 <= cc && cc < N) {
                            T[curRow][index[canonical(cr, cc, N)]] += 0.125;
                        }
                    }
                    curRow++;
                }
            }
        }

        double[] row = matrixExpo(T, K)[index[sr*N + sc]];
        double ans = 0.0;
        for (double x: row) ans += x;
        return ans;
    }

    public int canonical(int r, int c, int N) {
        if (2*r > N) r = N-1-r;
        if (2*c > N) c = N-1-c;
        if (r > c) {
            int t = r;
            r = c;
            c = t;
        }
        return r * N + c;
    }
    public double[][] matrixMult(double[][] A, double[][] B) {
        double[][] ans = new double[A.length][A.length];
        for (int i = 0; i < A.length; i++) {
            for (int j = 0; j < B[0].length; j++) {
                for (int k = 0; k < B.length; k++) {
                    ans[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return ans;
    }
    public double[][] matrixExpo(double[][] A, int pow) {
        double[][] ans = new double[A.length][A.length];
        for (int i = 0; i < A.length; i++) ans[i][i] = 1;
        if (pow == 0) return ans;
        if (pow == 1) return A;
        if (pow % 2 == 1) return matrixMult(matrixExpo(A, pow-1), A);
        double[][] B = matrixExpo(A, pow / 2);
        return matrixMult(B, B);
    }
};
