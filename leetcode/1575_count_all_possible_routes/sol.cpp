/*
You are given an array of distinct positive integers locations where locations[i] represents the position of city i. You are also given integers start, finish and fuel representing the starting city, ending city, and the initial amount of fuel you have, respectively.

At each step, if you are at city i, you can pick any city j such that j != i and 0 <= j < locations.length and move to city j. Moving from city i to city j reduces the amount of fuel you have by |locations[i] - locations[j]|. Please notice that |x| denotes the absolute value of x.

Notice that fuel cannot become negative at any point in time, and that you are allowed to visit any city more than once (including start and finish).

Return the count of all possible routes from start to finish.

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
Output: 4
Explanation: The following are all possible routes, each uses 5 units of fuel:
1 -> 3
1 -> 2 -> 3
1 -> 4 -> 3
1 -> 4 -> 2 -> 3
Example 2:

Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
Output: 5
Explanation: The following are all possible routes:
1 -> 0, used fuel = 1
1 -> 2 -> 0, used fuel = 5
1 -> 2 -> 1 -> 0, used fuel = 5
1 -> 0 -> 1 -> 0, used fuel = 3
1 -> 0 -> 1 -> 0 -> 1 -> 0, used fuel = 5
Example 3:

Input: locations = [5,2,1], start = 0, finish = 2, fuel = 3
Output: 0
Explanation: It's impossible to get from 0 to 2 using only 3 units of fuel since the shortest route needs 4 units of fuel.
Example 4:

Input: locations = [2,1,5], start = 0, finish = 0, fuel = 3
Output: 2
Explanation: There are two possible routes, 0 and 0 -> 1 -> 0.
Example 5:

Input: locations = [1,2,3], start = 0, finish = 2, fuel = 40
Output: 615088286
Explanation: The total number of possible routes is 2615088300. Taking this number modulo 10^9 + 7 gives us 615088286.
 

Constraints:

2 <= locations.length <= 100
1 <= locations[i] <= 10^9
All integers in locations are distinct.
0 <= start, finish < locations.length
1 <= fuel <= 200
*/


// DP top down with memoization
// time complexity: O(N*M), N is number of cities, M is starting fuel
class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        // dp(i,k): number of routes to reach destination starting from i-th city with k-fuel
        // dp(i,k) = sum{dp(j,k-dist)}, where dist is the distance between city i and j
        // DP with memoization: since the fuel monotonically decreases, there is no cyclic dependencies of states
        _mem = vector<vector<int>>(100, vector<int>(201, -1));
        int ans = dp(locations, start, finish, fuel);
        return ans;
    }
    
private:
    vector<vector<int>> _mem;
    const int MOD = 1e9+7;
    int dp(const vector<int> &locations, int cur, int dest, int fuel) {
        if(fuel < 0)
            return 0;
        if(_mem[cur][fuel] != -1)
            return _mem[cur][fuel];
        
        int total = (cur==dest?1:0);
        for(int next=0; next<locations.size(); ++next) {
            if(next != cur) {
                total = (total+dp(locations, next, dest, fuel-abs(locations[next]-locations[cur]))) % MOD;
            }
        }
        
        _mem[cur][fuel] = total;
        return total;
    }
};


// same DP, sort array so it runs faster
// time complexity: O(N*M)
class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int locStart = locations[start];    // location of start city
        int locFinish = locations[finish];  // location of finish city
        sort(locations.begin(), locations.end());
        for(int i=0; i<locations.size(); ++i) {
            if(locations[i] == locStart)
                start = i;
            if(locations[i] == locFinish)  // note start and finish can point to same city
                finish = i;
        }
        
        // dp(i,k): number of routes to reach destination starting from i-th city with k-fuel
        // dp(i,k) = sum{dp(j,k-dist)}, where dist is the distance between city i and j
        // DP with memoization: since the fuel monotonically decreases, there is no cyclic dependencies of states
        _mem = vector<vector<int>>(100, vector<int>(201, -1));
        int ans = dp(locations, start, finish, fuel);
        return ans;
    }
    
private:
    vector<vector<int>> _mem;
    const int MOD = 1e9+7;
    int dp(const vector<int> &locations, int cur, int dest, int fuel) {
        if(_mem[cur][fuel] != -1)
            return _mem[cur][fuel];
        
        int total = (cur==dest?1:0);
        for(int next=cur+1; next<locations.size(); ++next) {
            int cost = locations[next]-locations[cur];
            if(cost > fuel)
                break;
            total = (total+dp(locations, next, dest, fuel-cost)) % MOD;
        }
        for(int next=cur-1; next>=0; --next) {
            int cost = locations[cur] - locations[next];
            if(cost > fuel)
                break;
            total = (total+dp(locations, next, dest, fuel-cost)) % MOD;
        }
        
        _mem[cur][fuel] = total;
        return total;
    }
};


// saem DP, use array instead of vector
// fastest and smallest memory footprint
class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int locStart = locations[start];    // location of start city
        int locFinish = locations[finish];  // location of finish city
        sort(locations.begin(), locations.end());
        for(int i=0; i<locations.size(); ++i) {
            if(locations[i] == locStart)
                start = i;
            if(locations[i] == locFinish)  // note start and finish can point to same city
                finish = i;
        }
        
        // dp(i,k): number of routes to reach destination starting from i-th city with k-fuel
        // dp(i,k) = sum{dp(j,k-dist)}, where dist is the distance between city i and j
        // DP with memoization: since the fuel monotonically decreases, there is no cyclic dependencies of states
        memset(_mem, -1, sizeof(_mem));
        int ans = dp(locations, start, finish, fuel);
        return ans;
    }
    
private:
    int _mem[100][201];
    const int MOD = 1e9+7;
    int dp(const vector<int> &locations, int cur, int dest, int fuel) {
        if(_mem[cur][fuel] != -1)
            return _mem[cur][fuel];
        
        int total = (cur==dest?1:0);
        for(int next=cur+1; next<locations.size(); ++next) {
            int cost = locations[next]-locations[cur];
            if(cost > fuel)
                break;
            total = (total+dp(locations, next, dest, fuel-cost)) % MOD;
        }
        for(int next=cur-1; next>=0; --next) {
            int cost = locations[cur] - locations[next];
            if(cost > fuel)
                break;
            total = (total+dp(locations, next, dest, fuel-cost)) % MOD;
        }
        
        _mem[cur][fuel] = total;
        return total;
    }
};
