/*
In a project, you have a list of required skills req_skills, and a list of people. The ith person people[i] contains a list of skills that the person has.

Consider a sufficient team: a set of people such that for every required skill in req_skills, there is at least one person in the team who has that skill. We can represent these teams by the index of each person.

For example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].
Return any sufficient team of the smallest possible size, represented by the index of each person. You may return the answer in any order.

It is guaranteed an answer exists.

 

Example 1:

Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
Output: [0,2]
Example 2:

Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"], people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
Output: [1,2]
 

Constraints:

1 <= req_skills.length <= 16
1 <= req_skills[i].length <= 16
req_skills[i] consists of lowercase English letters.
All the strings of req_skills are unique.
1 <= people.length <= 60
0 <= people[i].length <= 16
1 <= people[i][j].length <= 16
people[i][j] consists of lowercase English letters.
All the strings of people[i] are unique.
Every skill in people[i] is a skill in req_skills.
It is guaranteed a sufficient team exists.
*/


// DP bottom-up
// time complexity: O(P*2^N), where P is the number of people, and N is the number of skills
class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        // represent each skill as one-bit in the binary
        // as such, each person can be represented as an integer number
        unordered_map<string,int> s2n;
        int id = 0;
        for(const string &s : req_skills)
            s2n[s] = id++;
        vector<int> pp;  // binary representation of people with skills
        vector<int> pmap;
        for(int i=0; i<people.size(); ++i) {
            int bin = 0;
            for(const string &s : people[i])
                bin |= (0x1<<s2n[s]);
            if(bin!=0) {
                pp.push_back(bin);
                pmap.push_back(i);
            }
        }

        const int N = req_skills.size();
        const int P = pp.size();

        
        // dp(i,j): min people required in pp[0:i) to cover binary skill set j
        // dp(i,j) = min{dp(i-1,j), dp(i-1,j&(~k))+1}, where k is the skill set of people-i
        vector<vector<int>> dp(P+1, vector<int>(0x1<<N, INT_MAX/2));
        dp[0][0] = 0;
        int target = (0x1<<N) - 1;
        for(int i=1; i<=P; ++i) {
            int k = pp[i-1];
            for(int j=0; j<=target; ++j) {
                // here we have some greedy thinking: when we're not using person-i, we remove all his skill from j;
                // the smaller the j, the less number of people needed to cover it
                // to give an example, let's say j=2'b11011, and k=2'b00011
                // we can prove that dp[i-1][2'b11000] <= dp[i-1][2'b11010] and dp[i-1][2'b11001], where the latter two
                // does not remove all 1's from k
                dp[i][j] = min(dp[i-1][j]/*not use current person*/, dp[i-1][j&(~k)]+1/*use current person*/);
            }
        }
                
        // build results
        vector<int> ans;
        for(int i=P,j=target; i>0; --i) {
            int k = pp[i-1];
            if(dp[i][j] ==  dp[i-1][j&(~k)] + 1) {  // person-i is used
                ans.push_back(pmap[i-1]);
                j = j&(~k);
            }
        }
        
        return ans;
    }

};


// DP top-down (TLE, don't know why)
class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        // represent each skill as one-bit in the binary
        // as such, each person can be represented as an integer number
        unordered_map<string,int> s2n;
        int id = 0;
        for(const string &s : req_skills)
            s2n[s] = id++;
        vector<int> pp;  // binary representation of people with skills
        vector<int> pmap;
        for(int i=0; i<people.size(); ++i) {
            int bin = 0;
            for(const string &s : people[i])
                bin |= (0x1<<s2n[s]);
            if(bin!=0) {
                pp.push_back(bin);
                pmap.push_back(i);
            }
        }

        const int N = req_skills.size();
        const int P = pp.size();

        
        // dp(i,j): min people required in pp[0:i] to cover binary skill set j
        // dp(i,j) = min{dp(i-1,j), dp(i-1,j&(~k))+1}, where k is the skill set of people-i
        _mem = vector<vector<int>>(P+1, vector<int>(0x1<<N, 0));
        int target = (0x1<<N) - 1;
        int count = dp(pp, P, target);
        cout << "count " << count << endl;
        
        // build results
        vector<int> ans;
        
        for(int i=P,j=target; i>0; --i) {
            int k = pp[i-1];
            int count = _mem[i][j];
            int notUse = _mem[i-1][j];
            int use = _mem[i-1][j&(~k)] + 1;
            if(count == use) {
                ans.push_back(pmap[i-1]);
                j = j&(~k);
            }
        }
        
        return ans;
    }
    
private:
    vector<vector<int>> _mem;
    vector<int> _ans;
    int dp(const vector<int> &pp, int i, int j) {
        if(i == 0)
            return j==0?0:INT_MAX/2;
        
        if(_mem[i][j])
            return _mem[i][j];
        
        int k = pp[i-1];  // skill of current person
        int ans = min(dp(pp, i-1, j)/*not use current person*/, dp(pp, i-1, j&(~k))+1/*use current person*/);
        _mem[i][j] = ans;
        return ans;
    }
};



// ref implementation 1 from HuaHua
class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        // represent each skill as one-bit in the binary
        // as such, each person can be represented as an integer number
        unordered_map<string,int> s2n;
        int id = 0;
        for(const string &s : req_skills)
            s2n[s] = id++;
        vector<int> pp;  // binary representation of people with skills
        for(int i=0; i<people.size(); ++i) {
            int bin = 0;
            for(const string &s : people[i])
                bin |= (0x1<<s2n[s]);
            pp.push_back(bin);
        }
        
        // dp(i,j): min team size in people[0:i) consitutes skill-set j, where j is binary representation of the skill set
        // dp(i,j|k) = min{dp(i-1,j|k)/*not use i*/, dp(i-1,j)+1/*use i*/}
        // dp(P, target) is the final answer
        const int N = req_skills.size();
        const int target = (0x1<<N) - 1;  // all skills need to be acquired
        const int P = pp.size();
        vector<int> dp(0x1<<N, INT_MAX-1);  // since dp(i) only depends on dp(i-1), we can collapse the i-th dimension
        dp[0] = 0;  // no people needed to constitue 0 skills
        vector<pair<int,int>> path(0x1<<N);  // transition path: for each skill-set state, pair.first is the previous skill-set state, and pair.second is the person used
        for(int i=0; i<P; ++i) {
            int k = pp[i];
            if(k == 0)  // current person has no skill, we can skip 
                continue;
            // since j <= j|k, we start from j=target so it won't overwirte values we need --> no need to have a rolling vector
            for(int j=target; j>=0; --j) {
                if(dp[j]+1/*use current person*/ < dp[j|k]/*not use i*/) {
                    dp[j|k] = dp[j] + 1;
                    path[j|k] = make_pair(j,i);
                }
            }
        }
        
        // construct answer
        vector<int> ans;
        int t = target;
        while(t) {
            ans.push_back(path[t].second);
            t = path[t].first;
        }
        return ans;
    }

};

// ref implementation from HuaHua
class Solution {
public:
  vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {    
    const int n = req_skills.size();    
    
    vector<int> skills;
    for (const auto& p : people) {
      int mask = 0;
      for (const string& s: p)
        mask |= (1 << find(begin(req_skills), end(req_skills), s) - begin(req_skills));
      skills.push_back(mask);
    }
    
    unordered_map<int, vector<int>> dp;
    dp[0] = {};
            
    for (int i = 0; i < people.size(); ++i) {      
      unordered_map<int, vector<int>> tmp(dp);
      for (const auto& kv : dp) {
        int k = kv.first | skills[i];
        if (!tmp.count(k) || kv.second.size() + 1 < tmp[k].size()) {
          tmp[k] = kv.second;
          tmp[k].push_back(i);
        }        
      }
      tmp.swap(dp);
    }    
      
    return dp[(1 << n) - 1];
  }
};
