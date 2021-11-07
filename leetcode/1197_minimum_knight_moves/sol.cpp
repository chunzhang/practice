/*
In an infinite chess board with coordinates from -infinity to +infinity, you have a knight at square [0, 0].

A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.


Return the minimum number of steps needed to move the knight to the square [x, y]. It is guaranteed the answer exists.

 

Example 1:

Input: x = 2, y = 1
Output: 1
Explanation: [0, 0] → [2, 1]
Example 2:

Input: x = 5, y = 5
Output: 4
Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]
 

Constraints:

-300 <= x, y <= 300
*/


// BFS: one-directional
// time complexity: O(max(|x|,|y|)^2), i.e., rough area covered by target point
class Solution {
public:
    int minKnightMoves(int x, int y) {
        if(x==0 && y==0)
            return 0;
        
        const int DIR[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
        //vector<vector<int>> visited(605, vector<int>(605, 0));
        int visited[605][605];
        memset(visited, 0, sizeof(visited));
        queue<pair<int,int>> q;
        q.push({0,0});
        visited[0][0] = 1;
        int steps = 0;
        while(!q.empty()) {
            ++steps;
            int sz = q.size();
            while(sz--) {
                auto cur = q.front();
                q.pop();
                int dist = abs(x-cur.second) + abs(y-cur.first);  // current manhattan distance
                for(int d=0; d<8; ++d) {
                    int ni = cur.first + DIR[d][0];
                    int nj = cur.second + DIR[d][1];
                    if(ni==y && nj==x)
                        return steps;
                    int dist2 = abs(x-nj) + abs(y-ni);  // next manhattan distance
                    if(dist2>dist+1)  // pruning: we don't want to move away from destination too far
                        continue;
                    if(!visited[ni+302][nj+302]) {
                        q.push({ni,nj});
                        visited[ni+302][nj+302] = 1;
                    }
                }
            }
        }
        
        return -1;  // should not reach here
    }
};


// BFS: bi-directional, passes when convert the coordinate to 1-D
// time complexity: half of one-directional BFS
class Solution {
public:
    int minKnightMoves(int x, int y) {
        if(x==0 && y==0)
            return 0;
        
        const int M = 305;
        const int OFFSET = 1;  // max distance to go beyond current quadrant
        
        x = abs(x) + OFFSET;   // important pruning: only search in one quadrant
        y = abs(y) + OFFSET;
        
        const int DIR[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
        unordered_set<int> q1;
        unordered_set<int> q2;
        int visited[M][M];
        memset(visited, 0, sizeof(visited));
        q1.insert(OFFSET*M + OFFSET);  // origin
        q2.insert(y*M + x);
        visited[OFFSET][OFFSET] = 1;
        visited[y][x] = 1;
        int steps = 0;
        while(!q1.empty() && !q2.empty()) {
            if(q1.size() > q2.size())
                q1.swap(q2);
            
            ++steps;
             unordered_set<int> nq;
            for(int cur : q1) {
                for(int d=0; d<8; ++d) {
                    int nx = cur%M + DIR[d][0];
                    int ny = cur/M + DIR[d][1];
                     if(nx<0 || nx>=M || ny<0 || ny>=M)
                        continue;
                    int next = ny*M + nx;
                    if(q2.count(next))
                        return steps;
                    if(!visited[ny][nx]) {
                        nq.insert(next);
                        visited[ny][nx] = 1;
                    }
                }
            }
            q1.swap(nq);
        }        
        
        return -1;  // should not reach here
    }
};

// BFS: bi-directional
// TLE -- due to hash table???
class Solution {
public:
    int minKnightMoves(int x, int y) {
        if(x==0 && y==0)
            return 0;
        
        const int DIR[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
        unordered_set<pair<int,int>, HashPair> q1;
        unordered_set<pair<int,int>, HashPair> q2;
        q1.insert({0,0});
        q2.insert({x,y});
        int steps = 0;
        while(!q1.empty() && !q2.empty()) {
            if(q1.size() > q2.size())
                q1.swap(q2);
            
            ++steps;
            unordered_set<pair<int,int>, HashPair> nq;
            for(auto &cur : q1) {
                for(int d=0; d<8; ++d) {
                    pair<int,int> next = {cur.first+DIR[d][0],cur.second+DIR[d][1]};
                    if(q2.count(next))
                        return steps;
                    if(!nq.count(next)) {
                        nq.insert(next);
                    }
                }
            }
            q1.swap(nq);
        }
        
        
        return -1;  // should not reach here
    }
    
private:
    struct HashPair {
        size_t operator()(const pair<int,int> &p) const {  // NOTE: this must be a const function
            return p.first ^ p.second;
        }  
    };
};


// most optimal top-down DP, i.e., DFS with memoization
// time complexity: O(|x|*|y|)
class Solution {
public:
    int minKnightMoves(int x, int y) {
        memset(_mem, -1, sizeof(_mem));
        return dp(x,y);
    }
    
private:
    int _mem[301][301];
    int dp(int x, int y) {
        x = abs(x);
        y = abs(y);
        if(_mem[x][y] != -1)
            return _mem[x][y];
        
        if(x+y == 0)
            return 0;
        else if(x+y == 2)  // this is key here
            return 2;
        else {
            int ans = min(dp(x-2,y-1), dp(x-1,y-2)) + 1;
            _mem[x][y] = ans;
            return ans;
        }
    }
};
