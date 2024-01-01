/*
Facebook/VMware/Google

Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the below images.

Example 1:

Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,4,2,7,5,3,8,6,9]

Example 2:

Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i].length <= 10^5
1 <= sum(nums[i].length) <= 10^5
1 <= nums[i][j] <= 10^5
*/


// solution 2: BFS
// time: O(N)
// space: O(sqrt(N)), i.e., largest diagonal
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        // BFS
        vector<int> ans;
        queue<pair<int,int>> q;
        q.emplace(0,0);
        while(!q.empty()) {
            int sz = q.size();
            for(int k=0; k<sz; ++k) {
                int i = q.front().first;
                int j = q.front().second;
                q.pop();
                ans.push_back(nums[i][j]);

                // only search down for the first node of each diagonal
                if(k==0 && i<nums.size()-1 && j<nums[i+1].size())
                    q.emplace(i+1,j);

                // search right
                if(j<nums[i].size()-1)
                    q.emplace(i,j+1);
            }
        }

        return ans;
    }
};


// solution 1: group diagonal by i+j index
// time: O(N)
// space: O(N)
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<vector<int>> diag;
        for(int i=nums.size()-1; i>=0; --i) {
            for(int j=0; j<nums[i].size(); ++j) {
                int d = i + j;
                if(d >= diag.size())
                    diag.resize(d+1);
                diag[d].push_back(nums[i][j]);
            }
        }

        vector<int> ans;
        for(auto &v : diag)
            ans.insert(ans.end(), v.begin(), v.end());

        return ans;
    }
};
