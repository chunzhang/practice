/*
  An array is squareful if the sum of every pair of adjacent elements is a perfect square.

  Given an integer array nums, return the number of permutations of nums that are squareful.

  Two permutations perm1 and perm2 are different if there is some index i such that perm1[i] != perm2[i].

 

  Example 1:

  Input: nums = [1,17,8]
  Output: 2
  Explanation: [1,8,17] and [17,8,1] are the valid permutations.
  Example 2:

  Input: nums = [2,2,2]
  Output: 1
 

  Constraints:

  1 <= nums.length <= 12
  0 <= nums[i] <= 109
*/


// DFS + pruning
// O(N!) time complexity, O(N) space complexity
class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        _ans = 0;
        sort(nums.begin(), nums.end());  // important for avoiding duplicates
        vector<int> perm;
        vector<int> used(nums.size(), 0);
        dfs(nums, perm, used);
        return _ans;
    }
    
private:
    int _ans;
    
    bool isSquareful (int a, int b) {
        int s = sqrt(a+b);
        return s*s==a+b;
    }
    
    void dfs(const vector<int> &nums, vector<int> &perm/*current squareful permutation*/, vector<int> &used/*whether nums[i] is already used*/) {
        if(perm.size() == nums.size()) {
            ++_ans;
            return;
        }
        
        for(int i=0; i<nums.size(); ++i) {
            if(used[i])  // current number is already used in permutation
                continue;
            
            // avoid duplicates, i.e., answer for [2,2,2] should be 1 instead of 6
            // in other words, for a consecutive numbers of same value, only try to use the first number
            if(i!=0 && nums[i-1]==nums[i] && !used[i-1])
                continue;
            
            // cannot form square, invalid
            if(perm.size() && !isSquareful(nums[i], perm.back()))
                continue;
            
            // try add num into the current permutation
            perm.push_back(nums[i]);
            used[i] = 1;
            dfs(nums, perm, used);
            perm.pop_back();
            used[i] = 0;
        }
            
    }
};


// a less efficient isSquareful() implementation
bool isSquareful (int a, int b) {
    int target = a + b;
    for(int i=0; i<=target; ++i) {
        int s = i*i;
        if(s == target)
            return true;
        else if(s > target)
            break;
    }
        
    return false;
}


// DP based on Hamiltonian path
// PUSH style
// O(N*N*2^N) time complexity, O(N*2^N) space complexity
class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // for avoid duplicates
        
        // whether nums[i] and nums[j] is squareful
        const int N = nums.size();
        vector<vector<int>> sq(N, vector<int>(N, 0));
        for(int i=0; i<N; ++i) {
            for(int j=i+1; j<N; ++j) {
                if(isSquareful(nums[i], nums[j])) {
                    sq[i][j] = 1;
                    sq[j][i] = 1;
                }
            }
        }
                
        // dp[s][j]: number of squareful arrays of state s and ends at j-th number
        // -- s is bit-map of numbers that are used already
        // dp[s|(1<<j)][j] += dp[s][i], if nums[i] and nums[j] is squareful
        const int NS = 1<<N;
        vector<vector<int>> dp(NS, vector<int>(N, 0));
        for(int i=0; i<N; ++i) {
            if(i==0 || nums[i]!=nums[i-1])  // base case, also need to avoid duplicates
                dp[1<<i][i] = 1;
        }
        
        // PUSH style
        for(int s=0; s<NS; ++s) {
            for(int i=0; i<N; ++i) {
                if((s&(1<<i)) == 0)  // invalid state
                    continue;
                if(dp[s][i] == 0)  // nothing to push
                    continue;
                for(int j=0; j<N; ++j) {
                    if(!sq[i][j])
                        continue;
                    if(s&(1<<j))  // j is already used
                        continue;
                    if(j>0 && nums[j]==nums[j-1] && (s&(1<<(j-1)))==0)  // avoid duplicate, i.e., only use the first number
                        continue;
                    dp[s|(1<<j)][j] += dp[s][i];
                }
            }
        }
        
        // collect answer
        int ans = 0;
        for(int i=0; i<N; ++i)
            ans += dp[NS-1][i];
        
        return ans;
    }
    
private:
    bool isSquareful (int a, int b) {
        int s = sqrt(a+b);
        return s*s==a+b;
    }
    
};


// DP PULL style
class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // for avoid duplicates
        
        // whether nums[i] and nums[j] is squareful
        const int N = nums.size();
        vector<vector<int>> sq(N, vector<int>(N, 0));
        for(int i=0; i<N; ++i) {
            for(int j=i+1; j<N; ++j) {
                if(isSquareful(nums[i], nums[j])) {
                    sq[i][j] = 1;
                    sq[j][i] = 1;
                }
            }
        }
                
        // dp[s][j]: number of squareful arrays of state s and ends at j-th number
        // -- s is bit-map of numbers that are used already
        // dp[s][j] += dp[s&(~(1<<j))][i], if nums[i] and nums[j] is squareful
        const int NS = 1<<N;
        vector<vector<int>> dp(NS, vector<int>(N, 0));
        for(int i=0; i<N; ++i) {
            if(i==0 || nums[i]!=nums[i-1])  // base case, also need to avoid duplicates
                dp[1<<i][i] = 1;
        }
        
        // PULL style
        for(int s=1; s<NS; ++s) {
            for(int j=0; j<N; ++j) {
                if((s&(1<<j)) == 0)  // invalid state
                    continue;
                if(j>0 && nums[j]==nums[j-1] && (s&(1<<(j-1)))==0)  // avoid duplicate, i.e., only use the first number
                    continue;
                int ps = s&(~(1<<j));  // previous state
                for(int i=0; i<N; ++i) {
                    if((ps&(1<<i)) == 0)  // invalid state
                        continue;
                    if(!sq[i][j])
                        continue;
                    dp[s][j] += dp[ps][i];
                }
            }
        }
                
        // collect answer
        int ans = 0;
        for(int i=0; i<N; ++i)
            ans += dp[NS-1][i];
        
        return ans;
    }
    
private:
    bool isSquareful (int a, int b) {
        int s = sqrt(a+b);
        return s*s==a+b;
    }
    
};
