/*
  You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.

  The lock initially starts at '0000', a string representing the state of the 4 wheels.

  You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

  Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.

 

  Example 1:

  Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
  Output: 6
  Explanation:
  A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
  Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
  because the wheels of the lock become stuck after the display becomes the dead end "0102".
  Example 2:

  Input: deadends = ["8888"], target = "0009"
  Output: 1
  Explanation:
  We can turn the last wheel in reverse to move from "0000" -> "0009".
  Example 3:

  Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
  Output: -1
  Explanation:
  We can't reach the target without getting stuck.
  Example 4:

  Input: deadends = ["0000"], target = "8888"
  Output: -1
 

  Constraints:

  1 <= deadends.length <= 500
  deadends[i].length == 4
  target.length == 4
  target will not be in the list deadends.
  target and deadends[i] consist of digits only.
*/


// BFS: one-directional w/o building the graph
// time complexity: O(N*10^N+D), where N is number of digits of a lock
// -- 10^N possible lock patterns, for each pattern, it takes O(N) to emunerate all its neighbors
// -- O(D) for building the hashset for deadends
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        if(target == "0000")
            return 0;
        
        unordered_set<string> blocked(deadends.begin(), deadends.end());
        if(blocked.count("0000") || blocked.count(target))
            return -1;
        
        const int N = 10;
        const vector<int> delta = {1, -1};
        
        // BFS: one directional
        unordered_set<string> visited;
        queue<string> q;
        q.push("0000");
        visited.emplace("0000");
        int steps = 0;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                string lock = q.front();
                q.pop();
                for(int i=0; i<lock.size(); ++i) {
                    int digit = lock[i] - '0';
                    for(int d : delta) {
                        lock[i] = (digit+d+N)%N + '0';
                        if(lock == target)
                            return steps+1;
                        if(blocked.count(lock) || visited.count(lock))
                            continue;
                        q.push(lock);
                        visited.emplace(lock);
                    }
                    lock[i] = digit + '0';
                }
            }
            ++steps;
        }
        
        return -1;
    }
};


// BFS: bi-directional w/o building the graph
// time complexity: same as one-directional, but with const factor improved
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        if(target == "0000")
            return 0;
        
        unordered_set<string> blocked(deadends.begin(), deadends.end());
        if(blocked.count("0000") || blocked.count(target))
            return -1;
        
        const int N = 10;
        const vector<int> delta = {1, -1};
        
        // BFS: bi-directional
        unordered_set<string> visited;
        unordered_set<string> q1, q2;
        q1.emplace("0000");
        visited.emplace("0000");
        q2.emplace(target);
        visited.emplace(target);
        int steps = 0;
        while(!q1.empty() && !q2.empty()) {
            if(q1.size() > q2.size())  // heuristic: always expand from smaller frontier
                q1.swap(q2);
            
            unordered_set<string> nq;  // next level
            for(string lock : q1) {
                for(int i=0; i<lock.size(); ++i) {  // enumerate
                    int digit = lock[i] - '0';
                    for(int d : delta) {
                        lock[i] = (digit+d+N)%N + '0';
                        if(q2.count(lock))
                            return steps+1;
                        if(blocked.count(lock) || visited.count(lock))
                            continue;
                        nq.emplace(lock);
                        visited.emplace(lock);
                    }
                    lock[i] = digit + '0';
                }
            }
            q1.swap(nq);
            ++steps;           
        }
        
        return -1;
    }
};


// ref impl from HuaHua
// bi-directional BFS with integer repr of the lock string
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        constexpr int kMaxN = 10000;
        const vector<int> bases{1, 10, 100, 1000};
        const int start = 0;
        const int goal = stoi(target);
    
        queue<int> q1;
        queue<int> q2;
        vector<int> v1(kMaxN, 0);
        vector<int> v2(kMaxN, 0);  
        for (const string& deadend : deadends)
            v1[stoi(deadend)] = v2[stoi(deadend)] = -1;
    
        if (v1[start] == -1) return -1;
        if (start == goal) return 0;
    
        v1[start] = 1;
        v2[goal] = 1;
    
        int s1 = 0;
        int s2 = 0;
        q1.push(start);
        q2.push(goal);
        while (!q1.empty() && !q2.empty()) {      
            if (!q1.empty()) ++s1;
            const int size = q1.size();
            for (int i = 0; i < size; ++i) {
                const int curr = q1.front(); 
                q1.pop();
                for (int i = 0; i < 4; ++i) {
                    int r = (curr / bases[i]) % 10;
                    for (int j = -1; j <= 1; j += 2) {
                        const int next = curr + ((r + j + 10) % 10 - r) * bases[i];
                        if (v2[next] == 1) return s1 + s2;
                        if (v1[next]) continue;            
                        q1.push(next);
                        v1[next] = 1;
                    }
                }
            }
            swap(q1, q2);
            swap(v1, v2);
            swap(s1, s2);
        }    
        return -1;
    }
};
