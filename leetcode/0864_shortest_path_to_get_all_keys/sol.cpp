/*

You are given an m x n grid grid where:

'.' is an empty cell.
'#' is a wall.
'@' is the starting point.
Lowercase letters represent keys.
Uppercase letters represent locks.
You start at the starting point and one move consists of walking one space in one of the four cardinal directions. You cannot walk outside the grid, or walk into a wall.

If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its corresponding key.

For some 1 <= k <= 6, there is exactly one lowercase and one uppercase letter of the first k letters of the English alphabet in the grid. This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.

Return the lowest number of moves to acquire all keys. If it is impossible, return -1.

 

Example 1:


Input: grid = ["@.a.#","###.#","b.A.B"]
Output: 8
Explanation: Note that the goal is to obtain all the keys not to open all the locks.
Example 2:


Input: grid = ["@..aA","..B#.","....b"]
Output: 6
Example 3:


Input: grid = ["@Aa"]
Output: -1
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 30
grid[i][j] is either an English letter, '.', '#', or '@'.
The number of keys in the grid is in the range [1, 6].
Each key in the grid is unique.
Each key in the grid has a matching lock.
*/


// BFS
// time and space complexity: O(M*N*2^K), where K is the number of keys
class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        const int M = grid.size();
        const int N = grid[0].size();
        const vector<pair<int,int>> DIR = {{0,1},{0,-1},{1,0},{-1,0}};
        // BFS on state(n, k)
        // -- n is the current node location
        // -- k is the current acquired keys
        // -- encode the state as binary integer: highest 10-bit for node location, lowest 6-bit for acquired keys
        // -- total number of states is M*N*2^K, where K is the total number of keys
        queue<unsigned short> q;
        vector<unsigned short> visited(0x1<<16, 0);
        unsigned short allKeys = 0;
        
        // initialization
        for(int i=0; i<M; ++i) {
            for(int j=0; j<N; ++j) {
                char c = grid[i][j];
                if(c == '@') {  // starting point
                    int state = (i*N+j)<<6;
                    q.push(state);
                    visited[state] = 1;
                }
                else if(islower(c)){  // contains key
                    allKeys |= 0x1<<(c-'a');
                }
            }
        }
        
        // BFS
        int steps = 0;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                unsigned short state = q.front();
                q.pop();
                unsigned short ci = (state>>6) / N;
                unsigned short cj = (state>>6) % N;
                unsigned short ck = state & 0b111111;
                for(auto &d : DIR) {
                    unsigned short ni = ci + d.first;
                    unsigned short nj = cj + d.second;
                    if(ni<0 || ni>=M || nj<0 || nj>=N || grid[ni][nj]=='#')  // invalid move
                        continue;
                    char c = grid[ni][nj];
                    if(isupper(c) && (ck&(0x1<<(c-'A')))==0)  // does not have key
                        continue;
                    unsigned short nk = ck;
                    if(islower(c))
                        nk |= (0x1<<(c-'a'));  // get the key
                    if(nk == allKeys)
                        return steps+1;
                    unsigned short nextState = (ni*N+nj)<<6 | nk;
                    if(visited[nextState])
                        continue;
                    q.push(nextState);
                    visited[nextState] = 1;
                }
            }
            
            ++steps;
        }
        
        return -1;
    }
};


// Brute-force with memoization: try search keys in all possible orders
// time complexity: O(M*N*K!)
class Solution {
public:
    typedef pair<int,int> iPair;
    int shortestPathAllKeys(vector<string>& grid) {
        _M = grid.size();
        _N = grid[0].size();

        vector<char> keys;
        vector<iPair> keyLoc(128);  // key location
        iPair start;
        for(int i=0; i<_M; ++i) {
            for(int j=0; j<_N; ++j) {
                char c = grid[i][j];
                if(c == '@')
                    start = make_pair(i,j);
                else if(islower(c)) {
                    keys.push_back(c);
                    keyLoc[c] = make_pair(i,j);
                }
            }
        }
        
        int ans = INT_MAX;
        sort(keys.begin(), keys.end());
        do {  // try find keys in all possible order
            iPair cur = start;
            vector<int> hasKey(128, 0);
            int nMoves = 0;
            for(char k : keys) {
                // BFS search
                int moves = bfs(grid, hasKey, cur.first, cur.second, k);
                if(moves == -1) {
                    nMoves = INT_MAX;
                    break;
                }
                nMoves += moves;
                hasKey[k] = 1;
                cur = keyLoc[k];
            }
            ans = min(ans, nMoves);
        }while(next_permutation(keys.begin(), keys.end()));
        
        
        return ans==INT_MAX?-1:ans;
    }
    
private:
    int _M;
    int _N;
    const vector<iPair> _DIR = {{0,1},{0,-1},{1,0},{-1,0}};
    unordered_map<int,int> _mem;  // memoization
    
    int encode(int si, int sj, const vector<int> &hasKey, char key) {
        int code = (si*_N+sj)<<16;
        for(int i=0; i<6; ++i) {
            char c = i + 'a';
            if(hasKey[c])
                code |= (0x1)<<i;
        }
        code |= (key<<6);
        return code;
    }
    
    // min steps from cur location (si,sj) to key
    // return -1 is no such path exists
    int bfs(const vector<string> &grid, vector<int> &hasKey, int si, int sj, char key) {
        int code = encode(si, sj, hasKey, key);
        auto it = _mem.find(code);
        if(it != _mem.end())
            return it->second;
        
        int steps = 0;
        vector<vector<short>> visited(_M, vector<short>(_N,0));
        queue<iPair> q;
        q.emplace(si,sj);
        visited[si][sj] = 1;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                iPair cur = q.front();
                q.pop();
                for(auto &d : _DIR) {
                    int ni = cur.first + d.first;
                    int nj = cur.second + d.second;
                    if(ni<0 || ni>=_M || nj<0 || nj>=_N || visited[ni][nj])
                        continue;
                    char c = grid[ni][nj];
                    if(c == key) {
                        _mem[code] = steps+1;
                        return steps+1;
                    }
                    if(c=='#' || isupper(c)&&!hasKey[tolower(c)]/*no key to the locker*/)
                        continue;
                    q.emplace(ni,nj);
                    visited[ni][nj] = 1;
                }
            }
            ++steps;
        }
        
        _mem[code] = -1;
        return -1;
    }
};
