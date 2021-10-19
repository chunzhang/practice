/*
Given n boxes, each box is given in the format [status, candies, keys, containedBoxes] where:

status[i]: an integer which is 1 if box[i] is open and 0 if box[i] is closed.
candies[i]: an integer representing the number of candies in box[i].
keys[i]: an array contains the indices of the boxes you can open with the key in box[i].
containedBoxes[i]: an array contains the indices of the boxes found in box[i].
You will start with some boxes given in initialBoxes array. You can take all the candies in any open box and you can use the keys in it to open new boxes and you also can use the boxes you find in it.

Return the maximum number of candies you can get following the rules above.

 

Example 1:

Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]], containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
Output: 16
Explanation: You will be initially given box 0. You will find 7 candies in it and boxes 1 and 2. Box 1 is closed and you don't have a key for it so you will open box 2. You will find 4 candies and a key to box 1 in box 2.
In box 1, you will find 5 candies and box 3 but you will not find a key to box 3 so box 3 will remain closed.
Total number of candies collected = 7 + 4 + 5 = 16 candy.
Example 2:

Input: status = [1,0,0,0,0,0], candies = [1,1,1,1,1,1], keys = [[1,2,3,4,5],[],[],[],[],[]], containedBoxes = [[1,2,3,4,5],[],[],[],[],[]], initialBoxes = [0]
Output: 6
Explanation: You have initially box 0. Opening it you can find boxes 1,2,3,4 and 5 and their keys. The total number of candies will be 6.
Example 3:

Input: status = [1,1,1], candies = [100,1,100], keys = [[],[0,2],[]], containedBoxes = [[],[],[]], initialBoxes = [1]
Output: 1
Example 4:

Input: status = [1], candies = [100], keys = [[]], containedBoxes = [[]], initialBoxes = []
Output: 0
Example 5:

Input: status = [1,1,1], candies = [2,3,2], keys = [[],[],[]], containedBoxes = [[],[],[]], initialBoxes = [2,1,0]
Output: 7
 

Constraints:

1 <= status.length <= 1000
status.length == candies.length == keys.length == containedBoxes.length == n
status[i] is 0 or 1.
1 <= candies[i] <= 1000
0 <= keys[i].length <= status.length
0 <= keys[i][j] < status.length
All values in keys[i] are unique.
0 <= containedBoxes[i].length <= status.length
0 <= containedBoxes[i][j] < status.length
All values in containedBoxes[i] are unique.
Each box is contained in one box at most.
0 <= initialBoxes.length <= status.length
0 <= initialBoxes[i] < status.length
*/

// Concise BFS impl (from HuaHua)
// time complexity: O(B*K)? O(B+K)?
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        // BFS
        vector<int> found(status.size(), 0);
        queue<int> q;
        for(int b : initialBoxes) {
            found[b] = 1;
            if(status[b])
                q.push(b);
        }
        int ans = 0;
        while(!q.empty()) {  // only box that can be opened is pushed to the queue
            int b = q.front();
            q.pop();
            ans += candies[b];
            for(int k : keys[b]) {
                if(!status[k] && found[k])
                    q.push(k);
                status[k] = 1;
            }
            for(int c : containedBoxes[b]) {
                found[c] = 1;
                if(status[c])
                    q.push(c);
            }
        }
        
        return ans;
    }
};

// My BFS impl
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        const int N = status.size();
        
        // BFS
        vector<int> opened(N, 0);  // opened boxes
        vector<int> parentOpened(N, 0);  // box whose parent is already opened
        queue<int> q;
        for(int n : initialBoxes) {  // init
            parentOpened[n] = 1;
            if(!status[n])
                continue;
            q.push(n);
            opened[n] = 1;
        }
        int ans = 0;
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            ans += candies[cur];
            for(int k : keys[cur]) {
                status[k] = 1;
                if(!opened[k] && parentOpened[k]) {
                    q.push(k);
                    opened[k] = 1;
                }
            }
            for(int c : containedBoxes[cur]) {
                parentOpened[c] = 1;
                if(!opened[c] && status[c]) {
                    q.push(c);
                    opened[c] = 1;
                }
            }
        }
        
        return ans;
    }
};
