/*
  Facebook/Google/Amazon

  Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

  Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

  After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

 

  Example 1:

  Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
  Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
  Explanation:
  The first and second John's are the same person as they have the common email "johnsmith@mail.com".
  The third John and Mary are different people as none of their email addresses are used by other accounts.
  We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
  ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
  Example 2:

  Input: accounts = [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
  Output: [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]
 

  Constraints:

  1 <= accounts.length <= 1000
  2 <= accounts[i].length <= 10
  1 <= accounts[i][j] <= 30
  accounts[i][0] consists of English letters.
  accounts[i][j] (for j > 0) is a valid email.
*/


// union-find: email-->account ID, so we can merge account ID directly
// time complexity: O(N*M), where N is number of accounts, and M is average number of email associated with the account
// space complexity: O(N*M)
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {        
        // union find
        vector<int> parent(accounts.size());
        for(int i=0; i<parent.size(); ++i)
            parent[i] = i;
        function<int(int)> getParent = [&](int i) {
            if(parent[i] != i)
                parent[i] = getParent(parent[i]);
            return parent[i];
        };
        function<void(int,int)> merge = [&](int i1, int i2) {
            parent[getParent(i1)] = getParent(i2);
        };
        
        // merge by email -- O(N*M) where N is the number accounts and M is average number of email associated with each account
        unordered_map<string,int> email2acc;  // email --> representative account ID
        for(int i=0; i<accounts.size(); ++i) {
            for(int j=1; j<accounts[i].size(); ++j) {
                const string &email = accounts[i][j];
                auto it = email2acc.find(email);
                if(it == email2acc.end())
                    email2acc[email] = i;
                else
                    merge(it->second, i);
            }
        }
        
        // build merged accounts
        unordered_map<int, set<string>> acc;  // account ID --> merged emails
        for(int i=0; i<accounts.size(); ++i) {
            int p = getParent(i);
            for(int j=1; j<accounts[i].size(); ++j)
                acc[p].insert(accounts[i][j]);
        }
        vector<vector<string>> ans;
        for(auto &entry : acc) {
            vector<string> a;
            a.push_back(accounts[entry.first][0]);
            a.insert(a.end(), entry.second.begin(),entry.second.end());
            ans.emplace_back(std::move(a));  // in-place construction
        }
        return ans;
    }
};


// union-find: ref impl from HuaHua
// email-->email ID, so for emails from the same account vector, we can merge email IDs
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string_view, int> ids;   // email to id
        unordered_map<int, string_view> names; // id to name
        vector<int> p(10000);
        iota(begin(p), end(p), 0);
    
        function<int(int)> find = [&](int x) {
            if (p[x] != x) p[x] = find(p[x]);
            return p[x];
        };
    
        auto getIdByEmail = [&](string_view email) {  // what is string_view?
            auto it = ids.find(email);
            if (it == ids.end()) {
                int id = ids.size();
                return ids[email] = id;
            }
            return it->second;
        };
 
        for (const auto& account : accounts) {      
            int u = find(getIdByEmail(account[1]));      
            for (int i = 2; i < account.size(); ++i) 
                p[find(u)] = find(getIdByEmail(account[i]));  // merge
            names[find(u)] = string_view(account[0]);
        }
 
        unordered_map<int, set<string>> mergered;
        for (const auto& account : accounts)
            for (int i = 1; i < account.size(); ++i) {
                int id = find(getIdByEmail(account[i]));
                mergered[id].insert(account[i]);
            }    
 
        vector<vector<string>> ans;
        for (const auto& kv : mergered) {
            ans.push_back({string(names[kv.first])});
            ans.back().insert(ans.back().end(), kv.second.begin(), kv.second.end());
        }
 
        return ans;
    }
};


// DFS to find all connected components
// Further enhancement: build email-->nodeID mapping, i.e., use int as node
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // DFS to find connected components

        // 1. build graph (i.e., emails belonging to same account are connected)
        unordered_map<string, unordered_set<string>> g;
        for(auto &acc : accounts) {
            //g[acc[1]];
            for(int j=2; j<acc.size(); ++j) {
                g[acc[1]].insert(acc[j]);
                g[acc[j]].insert(acc[1]);
            }
        }

        // 2. DFS
        unordered_set<string> visited;
        vector<vector<string>> ans;
        for(auto &acc : accounts) {
            if(visited.count(acc[1]))
                continue;
            unordered_set<string> emails;
            dfs(g, visited, acc[1], emails);
            ans.push_back(vector<string>(1,acc[0]));
            ans.back().insert(ans.back().end(), emails.begin(), emails.end());
            sort(ans.back().begin()+1, ans.back().end());
        }

        return ans;
    }

private:
    void dfs(unordered_map<string, unordered_set<string>> &g, unordered_set<string> &visited,  const string &cur, unordered_set<string> &res) {
        visited.insert(cur);
        res.insert(cur);
        for(const string &next : g[cur]) {
            if(!visited.count(next))
                dfs(g,visited,next,res);
        }
    }
};
