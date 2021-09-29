/*
There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal is to visit all the rooms. However, you cannot enter a locked room without having its key.

When you visit a room, you may find a set of distinct keys in it. Each key has a number on it, denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.

Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i, return true if you can visit all the rooms, or false otherwise.

 

Example 1:

Input: rooms = [[1],[2],[3],[]]
Output: true
Explanation: 
We visit room 0 and pick up key 1.
We then visit room 1 and pick up key 2.
We then visit room 2 and pick up key 3.
We then visit room 3.
Since we were able to visit every room, we return true.
Example 2:

Input: rooms = [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can not enter room number 2 since the only key that unlocks it is in that room.
 

Constraints:

n == rooms.length
2 <= n <= 1000
0 <= rooms[i].length <= 1000
1 <= sum(rooms[i].length) <= 3000
0 <= rooms[i][j] < n
All the values of rooms[i] are unique.
*/


// BFS
// time complexity: O(V+E)
// space complexity: O(V)
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        // BFS
        vector<int> visited(rooms.size(), 0);
        
        queue<int> q;
        q.push(0);
        visited[0] = 1;
        int nVisited = 1;
        while(q.size()) {
            int cur = q.front();
            q.pop();
            for(int next : rooms[cur]) {
                if(!visited[next]) {
                    q.push(next);
                    visited[next] = 1;
                    ++nVisited;
                }
            }
        }

        return nVisited==rooms.size();
    }
};

// DFS
// time complexity: O(V+E)
// space complexity: O(V)
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        // DFS
        vector<int> visited(rooms.size(), 0);
        int nVisited = dfs(rooms, visited, 0);
        return nVisited==rooms.size();
    }
    
private:
    // return number of room visited
    int dfs(const vector<vector<int>> &rooms, vector<int> &visited, int cur) {
        int nVisited = 1;
        visited[cur] = 1;
        for(int next : rooms[cur])
            if(!visited[next])
                nVisited += dfs(rooms, visited, next);
        
        return nVisited;
    }
};


// DFS simulated with stack -- impl 1
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<int> visited(rooms.size(), 0);
        stack<int> st;
        st.push(0);
        visited[0] = 1;
        int nVisited = 1;
        while(st.size()) {
            int cur = st.top();
            st.pop();
            for(int next : rooms[cur]) {
                if(!visited[next]) {
                    st.push(next);
                    visited[next] = 1;
                    ++nVisited;
                }
            }
        }
        
        return nVisited==rooms.size();
    }
    
};


// DFS simulated with stack -- impl 2
// different location to set visited flag -- less efficient
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        // DFS simulated with stack
        vector<int> visited(rooms.size(), 0);
        stack<int> st;
        st.push(0);
        int nVisited = 0;
        while(st.size()) {
            int cur = st.top();
            st.pop();
            if(visited[cur])
                continue;
            visited[cur] = 1;
            ++nVisited;
            for(int next : rooms[cur]) {
                st.push(next);
            }
        }
        
        return nVisited==rooms.size();
    }
    
};
