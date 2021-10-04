/*
In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.

If the town judge exists, then:

The town judge trusts nobody.
Everybody (except for the town judge) trusts the town judge.
There is exactly one person that satisfies properties 1 and 2.
You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi.

Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.

 

Example 1:

Input: n = 2, trust = [[1,2]]
Output: 2
Example 2:

Input: n = 3, trust = [[1,3],[2,3]]
Output: 3
Example 3:

Input: n = 3, trust = [[1,3],[2,3],[3,1]]
Output: -1
Example 4:

Input: n = 3, trust = [[1,2],[2,3]]
Output: -1
Example 5:

Input: n = 4, trust = [[1,3],[1,4],[2,3],[2,4],[4,3]]
Output: 3
 

Constraints:

1 <= n <= 1000
0 <= trust.length <= 10^4
trust[i].length == 2
All the pairs of trust are unique.
ai != bi
1 <= ai, bi <= n
*/

// compute in and out degress of each node
// time and space complexity: O(N)
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> inputs(n+1, 0);
        vector<int> outputs(n+1, 0);
        for(auto &t : trust) {
            ++outputs[t[0]];
            ++inputs[t[1]];
        }
        
        for(int p=1; p<=n; ++p)
            if(inputs[p]==n-1 && outputs[p]==0)
                return p;
        return -1;
    }
};


// a even smarter solution, i.e., use only one vector
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> degree(n+1, 0);  // inout degrees, i.e., #inputs-#outputs
        for(auto &t : trust) {
            --degree[t[0]];
            ++degree[t[1]];
        }
        
        for(int p=1; p<=n; ++p)
            if(degree[p]==n-1)
                return p;
        return -1;
    }
};
