/*
Facebook
  

There are two mice and n different types of cheese, each type of cheese should be eaten by exactly one mouse.

A point of the cheese with index i (0-indexed) is:

reward1[i] if the first mouse eats it.
reward2[i] if the second mouse eats it.
You are given a positive integer array reward1, a positive integer array reward2, and a non-negative integer k.

Return the maximum points the mice can achieve if the first mouse eats exactly k types of cheese.

Example 1:

Input: reward1 = [1,1,3,4], reward2 = [4,4,1,1], k = 2
Output: 15
Explanation: In this example, the first mouse eats the 2nd (0-indexed) and the 3rd types of cheese, and the second mouse eats the 0th and the 1st types of cheese.
The total points are 4 + 4 + 3 + 4 = 15.
It can be proven that 15 is the maximum total points that the mice can achieve.

Example 2:

Input: reward1 = [1,1], reward2 = [1,1], k = 2
Output: 2
Explanation: In this example, the first mouse eats the 0th (0-indexed) and 1st types of cheese, and the second mouse does not eat any cheese.
The total points are 1 + 1 = 2.
It can be proven that 2 is the maximum total points that the mice can achieve.
 

Constraints:

1 <= n == reward1.length == reward2.length <= 10^5
1 <= reward1[i], reward2[i] <= 1000
0 <= k <= n
*/

// greedy: mouse-1 eats top K cheese with max delta[i]=reward1[i]-reward2[i]
// -- use priority queue to book keep such top k cheese eaten by mouse-1
// time: O(NlgK)
// space: O(K)
lass Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        // let delta[i] = reward1[i] - reward2[i]
        // then, mouse1 wants to eat the top-K delta, which can be maintained through the k-sized priority queue
        // O(N*lgK)
        auto comp = [](const pair<int,int> &p1, const pair<int,int> &p2) {
            return p1.first > p2.first;
        };
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(comp)> pq(comp);
        for(int i=0; i<reward1.size(); ++i) {
            int delta = reward1[i] - reward2[i];
            if(pq.size()<k || (!pq.empty() && pq.top().first<delta)) {
                pq.emplace(delta,i);
                if(pq.size() > k)
                    pq.pop();
            }
        }

        // build result
        int ans = 0;
        while(!pq.empty()) {
            int idx = pq.top().second;  // eaten by mouse 1
            pq.pop();
            ans += reward1[idx];
            reward1[idx] = 0;  // mark eaten by mouse 1
        }
        for(int i=0; i<reward2.size(); ++i)
            if(reward1[i])  // not eaten by mouse 1
                ans += reward2[i];

        return ans;
    }
};


// same idea, but better and without using priority queue
// -- first assume all eaten by mouse-2
// -- then, adjust the top-K delta to be eaten by mouse-1
// time: O(NlgN)
// space: O(N)
class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int ans = 0;
        vector<int> delta(reward1.size());
        for(int i=0; i<reward2.size(); ++i) {
            ans += reward2[i];  // assume all eaten by mouse-2 first
            delta[i] = reward1[i] - reward2[i];
        }
        sort(delta.begin(), delta.end(), greater<int>());
        for(int i=0; i<k; ++i)  // top-K delta cheese will be eaten by mouse-1 instead
            ans += delta[i];

        return ans;
    }
};
