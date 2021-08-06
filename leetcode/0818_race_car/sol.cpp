/*
Your car starts at position 0 and speed +1 on an infinite number line. Your car can go into negative positions. Your car drives automatically according to a sequence of instructions 'A' (accelerate) and 'R' (reverse):

When you get an instruction 'A', your car does the following:
position += speed
speed *= 2
When you get an instruction 'R', your car does the following:
If your speed is positive then speed = -1
otherwise speed = 1
Your position stays the same.
For example, after commands "AAR", your car goes to positions 0 --> 1 --> 3 --> 3, and your speed goes to 1 --> 2 --> 4 --> -1.

Given a target position target, return the length of the shortest sequence of instructions to get there.

 

Example 1:

Input: target = 3
Output: 2
Explanation: 
The shortest instruction sequence is "AA".
Your position goes from 0 --> 1 --> 3.
Example 2:

Input: target = 6
Output: 5
Explanation: 
The shortest instruction sequence is "AAARA".
Your position goes from 0 --> 1 --> 3 --> 7 --> 7 --> 6.
 

Constraints:

1 <= target <= 10^4
*/

// BFS solution: O(2^D) time complexity where D is the depth of the expansion tree
class Solution {
public:
    int racecar(int target) {
        // Intuitively, I can use BFS to find the min steps
        // However, this requires some pruning, and some of them I cannot fully prove though
        
        queue<pair<int,int>> q;  // each node is (pos, speed) pair
        unordered_set<string> visited;  // use string key of "pos_speed" to mark visited node
        q.push(make_pair(0,1));  // starting point
        visited.insert("0_1");
        visited.insert("0_-1");  // Intuitively, we don't want to reverse at the starting point, though I can't strictly prove it
        int steps = 0;
        while(!q.empty()) {  // BFS
            int sz = q.size();
            while(sz--) {  // expand next level
                pair<int,int> cur = q.front();
                q.pop();
                int p = cur.first;   // position
                int s = cur.second;  // speed
                // 'A' action
                {
                    int p1 = p + s;
                    int s1 = s*2;
                    if(p1 == target)
                        return steps+1;
                    
                    // Pruning 1: since the number of (pos,speed) states is huge, marking all of them visited take exessive memory and hash table query time; 
                    //            idea is that the chance of encountering the same node is low (except for speed=+1/-1 case), I can skip the check for most of them
                    /*
                    string key = to_string(p1) + "_" + to_string(s1);
                    if(visited.find(key)!=visited.end())
                        continue;
                    */
                    
                    // Pruning 2: I don't want the car to go too far from target, though I can't prove; intuitively, the car oscillates around target, 
                    //            with the amplitude (i.e., distance from target) becoming smaller and smaller
                    if(p1>=0 && p1<=2*target) {
                        q.push(make_pair(p1,s1));
                        /*visited.insert(key);*/
                    }
                }         
                // 'R' action
                {
                    int p2 = p;
                    int s2 = s>0?-1:1;
                    // A possible improvement is to use integer a key; since speed is either +1 or -1, one can encode the key as
                    // int key = (p2<<2)|(s2+1)
                    string key = to_string(p2) + "_" + to_string(s2);
                    if(visited.find(key)!=visited.end())
                        continue;
                    q.push(make_pair(p2,s2));
                    visited.insert(key);
                }
            }
            
            ++steps;
        }
        
        return -1;  // should not reach here as solution always exists
    }
};


// A very smart DP solution with memoization
// Time complexity is O(TlogT) where T is target distance: T possible sub-problems, and each sub-problem requires log(T) to solve 
// Space complexity is O(T+logT), where T is the memoization of all sub-problems, and logT is the recursion depth
class Solution {
public:
    int racecar(int target) {
        // This is kind of DP with greedy strategies. Define dp(i) as the min steps to reach target; at any point facing target with speed of 1 (target can
        // be on either right of left of current position, which is symmetric), one can greedily perform one of the following two strategies:
        // -- 1) Accelerate N steps until it is at or just passes the target, i.e., 2^N-1>=target ==> N=ceil(log2(target+1)), and then reverse back
        // -- 2) Accelerate N-1 steps (because N step will pass the target), Reverse, Accelrate m steps, Reverse again
        // The greedy strategies are not proved; instead, the intuition is that the car should oscillate around target and getting closer and closer to it
        
        // Let's use memoization since the bottom-up order is not straightforward
        _mem = vector<int>(target+1, 0);
        return dp(target);
    }
    
private:
    int dp(int target) {
        if(_mem[target] != 0)
            return _mem[target];
        
        int N = ceil(log2(target+1));  // Least number of continuous A's to reach or go beyond target
        
        // with N accelration starting from speed 1, my total traveld distance is (2^N - 1)
        if(target == (1<<N)-1) {  // special case, reach target exactly!
            _mem[target] = N;
            return N;
        }
        
        // strategy 1: accelerate N times (i.e., goes beyond target), and then reverse
        int ans = N+1/*N accelration and one reverse*/ + dp((1<<N)-1 - target )/*remaining distance*/;
        
        // strategy 2: accelerate N-1 times (i.e., one more acceleration goes beyond target), reverse, acceleate m (i.e., 0<=m<=N-1 because we don't want to go beyond original starting point) times, and then reverse again
        for(int m=0; m<N-1; ++m) {
            ans = min(ans, N+m+1/*N-1 A, R, m A, R*/+dp(target - (1<<(N-1)) + (1<<m))/*remaining distance*/);
        }
    
        _mem[target] = ans;
        return ans;
    }
    
private:
    vector<int> _mem;
};
