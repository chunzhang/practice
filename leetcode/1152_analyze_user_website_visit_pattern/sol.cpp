/*
You are given two string arrays username and website and an integer array timestamp. All the given arrays are of the same length and the tuple [username[i], website[i], timestamp[i]] indicates that the user username[i] visited the website website[i] at time timestamp[i].

A pattern is a list of three websites (not necessarily distinct).

For example, ["home", "away", "love"], ["leetcode", "love", "leetcode"], and ["luffy", "luffy", "luffy"] are all patterns.
The score of a pattern is the number of users that visited all the websites in the pattern in the same order they appeared in the pattern.

For example, if the pattern is ["home", "away", "love"], the score is the number of users x such that x visited "home" then visited "away" and visited "love" after that.
Similarly, if the pattern is ["leetcode", "love", "leetcode"], the score is the number of users x such that x visited "leetcode" then visited "love" and visited "leetcode" one more time after that.
Also, if the pattern is ["luffy", "luffy", "luffy"], the score is the number of users x such that x visited "luffy" three different times at different timestamps.
Return the pattern with the largest score. If there is more than one pattern with the same largest score, return the lexicographically smallest such pattern.

 

Example 1:

Input: username = ["joe","joe","joe","james","james","james","james","mary","mary","mary"], timestamp = [1,2,3,4,5,6,7,8,9,10], website = ["home","about","career","home","cart","maps","home","home","about","career"]
Output: ["home","about","career"]
Explanation: The tuples in this example are:
["joe","home",1],["joe","about",2],["joe","career",3],["james","home",4],["james","cart",5],["james","maps",6],["james","home",7],["mary","home",8],["mary","about",9], and ["mary","career",10].
The pattern ("home", "about", "career") has score 2 (joe and mary).
The pattern ("home", "cart", "maps") has score 1 (james).
The pattern ("home", "cart", "home") has score 1 (james).
The pattern ("home", "maps", "home") has score 1 (james).
The pattern ("cart", "maps", "home") has score 1 (james).
The pattern ("home", "home", "home") has score 0 (no user visited home 3 times).
Example 2:

Input: username = ["ua","ua","ua","ub","ub","ub"], timestamp = [1,2,3,4,5,6], website = ["a","b","a","a","b","c"]
Output: ["a","b","a"]
 

Constraints:

3 <= username.length <= 50
1 <= username[i].length <= 10
timestamp.length == username.length
1 <= timestamp[i] <= 109
website.length == username.length
1 <= website[i].length <= 10
username[i] and website[i] consist of lowercase English letters.
It is guaranteed that there is at least one user who visited at least three websites.
All the tuples [username[i], timestamp[i], website[i]] are unique.
*/


// brute-force
// time complexity: O(N*L^3), N is number of users, L is number of website visited by the user
class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        // brute-force
        
        // 1. organize input data
        // O(N)
        unordered_map<string,vector<pair<int,string>>> data;
        for(int i=0; i<username.size(); ++i) {
            data[username[i]].push_back({timestamp[i],website[i]});
        }
        
        // 2. find all patterns
        // O(N*(LlgL+L^3))
        unordered_map<string,int> count;
        for(auto &item : data) {
            auto &v = item.second;
            sort(v.begin(), v.end());
            unordered_set<string> found;
            for(int i=0; i<v.size(); ++i) {
                for(int j=i+1; j<v.size(); ++j) {
                    for(int k=j+1; k<v.size(); ++k) {
                        string s = v[i].second+" "+v[j].second+" "+v[k].second;
                        if(!found.count(s)) {  // each user is count only once
                            ++count[s];
                            found.emplace(s);
                        }
                    }
                }
            }
        }
        
        // 3. find max pattern
        // O(N*L^3)
        int c = 0;
        string s;
        for(auto it=count.begin(); it!=count.end(); ++it) {
            if(it->second > c) {
                c = it->second;
                s = it->first;
            }
            else if(it->second == c) {
                if(it->first < s)
                    s = it->first;
            }
        }

        
        // 4. rebuild answer
        // O(1)
        istringstream iss(s);
        string tmp;
        vector<string> ans;
        while(iss>>tmp)
            ans.push_back(tmp);
        
        return ans;
    }
};
