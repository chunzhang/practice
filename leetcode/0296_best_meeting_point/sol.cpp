/*
Facebook/Google/Expedia

Given an m x n binary grid grid where each 1 marks the home of one friend, return the minimal total travel distance.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

 

Example 1:


Input: grid = [[1,0,0,0,1],[0,0,0,0,0],[0,0,1,0,0]]
Output: 6
Explanation: Given three friends living at (0,0), (0,4), and (2,2).
The point (0,2) is an ideal meeting point, as the total travel distance of 2 + 2 + 2 = 6 is minimal.
So return 6.
Example 2:

Input: grid = [[1,1]]
Output: 1
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
grid[i][j] is either 0 or 1.
There will be at least two friends in the grid.
*/


// convert 2-D problem to two 1-D problems
// in the 1-D problem, best meeting location is the median of people
// O(MN*lgMN) since sorting is needed
class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        // 1. We can convert the 2-D problem to two 1-D problems. When we
        // calculate the horizontally best meeting point, it is independent 
        // of which row it is assigned: horizontal mahattan distance is 
        // the same whichever row it is.
        //
        // 2. For the 1-D problem, location of the median person is the best 
        // meeting point!
        // 2.1) In the case of odd number of people (one a line), location of 
        // the median person is the only best meetin point.
        // 2.2) In the case of even number of people, any location between 
        // [left-median, left-median] is the best meeting point

        const int M = grid.size();
        const int N = grid[0].size();
        vector<int> iLoc;  // vertical location of all people in sorted order
        vector<int> jLoc;  // horizontal location of all people in sorted order

        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(grid[i][j]) {
                    iLoc.push_back(i);
                    jLoc.push_back(j);
                }

        // note iLoc is already in sorted order
        sort(jLoc.begin(), jLoc.end());

        // best meeting point is the median (apply to both odd and even case)
        int mi = iLoc[iLoc.size()/2];
        int mj = jLoc[jLoc.size()/2];
        int dist = 0;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(grid[i][j])
                    dist += abs(i-mi) + abs(j-mj);

        return dist;
    }
};


// avoid sorting by two traversal of the grid (one in the order of i and another in the order of j)
// O(M*N)
class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        // 1. We can convert the 2-D problem to two 1-D problems. When we
        // calculate the horizontally best meeting point, it is independent 
        // of which row it is assigned: horizontal mahattan distance is 
        // the same whichever row it is.
        //
        // 2. For the 1-D problem, location of the median person is the best 
        // meeting point!
        // 2.1) In the case of odd number of people (one a line), location of 
        // the median person is the only best meetin point.
        // 2.2) In the case of even number of people, any location between 
        // [left-median, left-median] is the best meeting point

        const int M = grid.size();
        const int N = grid[0].size();
        vector<int> iLoc;  // vertical location of all people in sorted order
        vector<int> jLoc;  // horizontal location of all people in sorted order

        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(grid[i][j])
                    iLoc.push_back(i);
        
        // avoid sorting by building jLoc in order through another traversal
        for(int j=0; j<N; ++j)
            for(int i=0; i<M; ++i)
                if(grid[i][j])
                    jLoc.push_back(j);

        // best meeting point is the median (apply to both odd and even case)
        int mi = iLoc[iLoc.size()/2];
        int mj = jLoc[jLoc.size()/2];
        int dist = 0;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(grid[i][j])
                    dist += abs(i-mi) + abs(j-mj);

        return dist;
    }
};


// brute-force: O(M^2*N^2)
class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        const int M = grid.size();
        const int N = grid[0].size();
        vector<pair<int,int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};

        // brute force
        vector<pair<int,int>> origSources;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(grid[i][j])
                    origSources.emplace_back(i,j);

        int ans = INT_MAX;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j) {
                int dist = 0;
                for(auto &p : origSources)
                    dist += abs(i-p.first)+abs(j-p.second);
                ans = min(ans,dist);
            }
        
        return ans;
    }
};
