/*
You are given two integers n and k and two integer arrays speed and efficiency both of length n. There are n engineers numbered from 1 to n. speed[i] and efficiency[i] represent the speed and efficiency of the ith engineer respectively.

Choose at most k different engineers out of the n engineers to form a team with the maximum performance.

The performance of a team is the sum of their engineers' speeds multiplied by the minimum efficiency among their engineers.

Return the maximum performance of this team. Since the answer can be a huge number, return it modulo 109 + 7.

 

Example 1:

Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
Output: 60
Explanation: 
We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.
Example 2:

Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 3
Output: 68
Explanation:
This is the same example as the first but k = 3. We can select engineer 1, engineer 2 and engineer 5 to get the maximum performance of the team. That is, performance = (2 + 10 + 5) * min(5, 4, 7) = 68.
Example 3:

Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 4
Output: 72
 

Constraints:

1 <= k <= n <= 10^5
speed.length == n
efficiency.length == n
1 <= speed[i] <= 10^5
1 <= efficiency[i] <= 10^8
*/

// related to max histogram area, but the bars do not need to be continuou in this problem
// time complexity: O(NlgN + NlgK), i.e., sorting + K-sized heap
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        // similar to histgoram, each person can be the lowest w.r.t. efficiency in the group
        // -- we want to compute max area with that person as lowest bound
        // -- to do this efficiently, we sort all the people by decreasing efficiency, so candidates for such team exist in front of that person
        // -- we use min heap to keep track of k-1 people with largest speed so far
        const int MOD = 1e9+7;
        
        
        vector<pair<int,int>> people;
        for(int i=0; i<n; ++i)
            people.push_back({efficiency[i],speed[i]});
        sort(people.begin(), people.end(), [](const pair<int,int> &p1, const pair<int,int> &p2) {return p1.first>p2.first;});  // sort by decreasing efficiency
        
        long ans = 0;
        priority_queue<int,vector<int>,greater<int>> pq;  // min-heap for k-1 people with most speed
        long sum = 0;
        for(int i=0; i<n; ++i) {
            pair<int,int> &p = people[i];    // selected as the lowest efficient person of the team
            ans = max(ans, (sum+p.second)*p.first);  // NOTE: we cannot MOD here, as otherwise we may decrease the actual answer!!!
    
            // update k-1 speedest people
            pq.push(p.second);
            sum += p.second;
            if(pq.size() > k-1) {
                sum -= pq.top();
                pq.pop();
                
            }
        }
                
        return ans%MOD;
    }
};
