/*
You are given a list of airline tickets where tickets[i] = [fromi, toi] represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.

All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with "JFK". If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.

For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.

 

Example 1:


Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
Output: ["JFK","MUC","LHR","SFO","SJC"]
Example 2:


Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.
 

Constraints:

1 <= tickets.length <= 300
tickets[i].length == 2
fromi.length == 3
toi.length == 3
fromi and toi consist of uppercase English letters.
fromi != toi
*/

// Optimal solution: post-order traversal (Hierholzer's Algorithm)
// time complexity could be bounded by sorting
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, deque<string>> g;  // use deque so removing first element is O(1)
        for(auto &f : tickets)
            g[f[0]].push_back(f[1]);
        
        // sort destinations
        for(auto &elem : g)
            sort(elem.second.begin(), elem.second.end());  // sort as the answer requires smallest lexical order
        
        vector<string> ans;
        dfs(g, ans, "JFK");
        reverse(ans.begin(), ans.end());
        return ans;
    }
    
private:
    // post-order traversal: O(V+E)
    void dfs(unordered_map<string,deque<string>> &g, vector<string> &ans, string cur) {
        auto &dest = g[cur];
        while(!dest.empty()) {
            string next = dest.front();
            dest.pop_front();  // remove the visited edge
            dfs(g, ans, next);
        }
        ans.push_back(cur);  // post-order
    }
};


// DFS(i.e., backgracking) + greedy order
// time complexity -- loose bound: O(E^V), i.e., the answer is E number of cities in order, and each city can be one of the V nodes
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string,vector<string>> g;  // braph
        unordered_map<string,vector<int>> used;  // whether the edge is used
        for(auto &f : tickets) {  // build graph
            g[f[0]].push_back(f[1]);
            used[f[0]].push_back(0);
        }
        for(auto it=g.begin(); it!=g.end(); ++it)
            sort(it->second.begin(), it->second.end());
        
        // DFS to greedily search answer
        vector<string> ans;
        dfs(g, tickets.size(), used, ans, "JFK", 0);
        
        return ans;
    }
    
private:
    bool dfs(unordered_map<string,vector<string>> &g, const int totalEdge, unordered_map<string,vector<int>> &used, vector<string> &ans, string cur, int usedEdge) {
        ans.push_back(cur);
        if(usedEdge == totalEdge)
            return true;
        
        for(int i=0; i<g[cur].size(); ++i) {  // for all edges
            if(used[cur][i])  // the edge is already used
                continue;
            if(i>0 && g[cur][i]==g[cur][i-1] && !used[cur][i-1])  // avoid duplicate searches
                continue;
            string next = g[cur][i];
            used[cur][i] = 1;
            if(dfs(g,totalEdge,used,ans,next,usedEdge+1))
                return true;
            used[cur][i] = 0;
        }
        
        ans.pop_back();
        return false;
    }
};


// another impl by passing const graph
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string,vector<string>> g;  // braph
        unordered_map<string,vector<int>> used;  // whether the edge is used
        for(auto &f : tickets) {  // build graph
            g[f[0]].push_back(f[1]);
            used[f[0]].push_back(0);
            g[f[1]];  // we have to at least initialze the node with empty vector, otherwise the g.at() function will throw runtime exception
            used[f[1]];
        }
        for(auto it=g.begin(); it!=g.end(); ++it)
            sort(it->second.begin(), it->second.end());
        
        // DFS to greedily search answer
        vector<string> ans;
        dfs(g, tickets.size(), used, ans, "JFK", 0);
        
        return ans;
    }
    
private:
    bool dfs(const unordered_map<string,vector<string>> &g, const int totalEdge, unordered_map<string,vector<int>> &used, vector<string> &ans, string cur, int usedEdge) {
        ans.push_back(cur);
        if(usedEdge == totalEdge)
            return true;
        
        auto &edges = g.at(cur);  // cannot use operator[] as it is non-const, i.e., inserts element when not existing
        for(int i=0; i<edges.size(); ++i) {  // for all edges
            if(used[cur][i])  // the edge is already used
                continue;
            if(i>0 && edges[i]==edges[i-1] && !used[cur][i-1])  // avoid duplicate searches
                continue;
            string next = edges[i];
            used[cur][i] = 1;
            if(dfs(g,totalEdge,used,ans,next,usedEdge+1))
                return true;
            used[cur][i] = 0;
        }
        
        ans.pop_back();
        return false;
    }
};
