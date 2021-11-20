/*
Given a string s containing only digits, return all possible valid IP addresses that can be obtained from s. You can return them in any order.

A valid IP address consists of exactly four integers, each integer is between 0 and 255, separated by single dots and cannot have leading zeros. For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses and "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses. 

 

Example 1:

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]
Example 2:

Input: s = "0000"
Output: ["0.0.0.0"]
Example 3:

Input: s = "1111"
Output: ["1.1.1.1"]
Example 4:

Input: s = "010010"
Output: ["0.10.0.10","0.100.1.0"]
Example 5:

Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
*/


// DFS
// time complexity: O(3^4)
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        string ip;
        vector<string> ans;
        if(s.size() > 12)
            return ans;
        dfs(s, 0, 0, ip, ans);
        return ans;
    }
    
private:
    bool isValid(const string &subip) {
        if(subip.size()>1 && subip[0]=='0')
            return false;
        int num = stoi(subip);
        return num<=255;
    }
    
    void dfs(const string &s, int cur, int count, string &ip, vector<string> &ans) {
        if(count==4) {  // all sub-ip found
            if(cur == s.size())
                ans.push_back(ip);
            return;
        }
        
        for(int i=cur; i<cur+3&&i<s.size(); ++i) {
            string subip = s.substr(cur, i-cur+1);
            if(isValid(subip)) {
                int len = ip.size();
                if(count)
                    ip.push_back('.');
                ip += subip;
                dfs(s, i+1, count+1, ip, ans);
                ip.resize(len);
            }
        }
    }
    
    
};


// DFS, faster impl
// time complexity: O(3^3)
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        string ip;
        vector<string> ans;
        if(s.size() > 12)
            return ans;
        dfs(s, 0, 0, ip, ans);
        return ans;
    }
    
private:
    bool isValid(const string &subip) {
        if(subip.empty() || subip.size()>1&&subip[0]=='0')
            return false;
        int num = stoi(subip);
        return num<=255;
    }
    
    void dfs(const string &s, int cur, int count, string &ip, vector<string> &ans) {
        if(count == 3) {  // last sub-ip, no need to do further search
            string subip = s.substr(cur);
            if(isValid(subip)) {
                ip.push_back('.');
                ip += subip;
                ans.push_back(ip);
            }
            return;
        }
        
        for(int i=cur; i<cur+3&&i<s.size(); ++i) {
            string subip = s.substr(cur, i-cur+1);
            if(isValid(subip)) {
                int len = ip.size();
                if(count)
                    ip.push_back('.');
                ip += subip;
                dfs(s, i+1, count+1, ip, ans);
                ip.resize(len);
            }
        }
    }
    
};


// ref impl from HuaHua
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ans;
        string ip;
        dfs(0, s, ip, ans);
        return ans;
    }
    
private: 
    void dfs(int d, string s, string ip, vector<string> &ans) {
        int l = s.length();
        if (d == 4) {
            if (l == 0) ans.push_back(ip);
            return;
        }
        
        for (int i = 1; i <= min(3, s[0] == '0' ? 1 : l); i++) {
            string ss = s.substr(0, i);      
            if (i == 3 && stoi(ss) > 255) return;      
            dfs(d + 1, s.substr(i), ip + (d == 0 ? "" : ".") + ss , ans);
        }
    }
};
