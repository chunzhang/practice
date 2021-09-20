/*
You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

 

Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Example 2:

Input: nums = [-1]
Output: [0]
Example 3:

Input: nums = [-1,-1]
Output: [0,0]
 

Constraints:

1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
*/

// when we do merge sort, we knows the number of elements on the right sub-array that are moved in front of any node on the left sub-array
// ==> by counting this, we can build the answer in O(NlgN) time
// in this implementation, we sort the array of indexes to original nums
// ==> before sort: nums=[2,1,3], indexes=[0,1,2]
// ==> after sort: nums=[1,2,3], indexes=[1,0,2]
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        _count = vector(nums.size(), 0);
        vector<int> indexes(nums.size(), 0);
        for(int i=1; i<indexes.size(); ++i)  // index mapping to nums array
            indexes[i] = i;
        merge(nums, indexes, 0, nums.size());
        return _count;
    }
    
private:
    vector<int> _count;
    vector<int> merge(const vector<int> &nums, vector<int> &indexes, int l, int r) {
        if(r-l == 1)
            return {indexes[l]};
        int mid = l + (r-l)/2;
        vector<int> left = merge(nums, indexes, l, mid);
        vector<int> right = merge(nums, indexes, mid, r);
        vector<int> ans;
        
        int i = 0;
        int j = 0;
        while(i<left.size() || j<right.size()) {
            // use left node
            if(i<left.size() && (j>=right.size() || nums[left[i]]<=nums[right[j]])) {
                ans.push_back(left[i]);
                _count[left[i]] += j;  // this is the number of elements moved before any left element is added to the sorted array
                ++i;
            }
            else {  // use right node
                ans.push_back(right[j]);
                ++j;
            }
        }
        
        return ans;
    }
};


// same idea, but do not return vector --> we update it in-place at the end
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        _count = vector(nums.size(), 0);
        vector<int> indexes(nums.size(), 0);
        for(int i=1; i<indexes.size(); ++i)  // index mapping to nums array
            indexes[i] = i;
        merge(nums, indexes, 0, nums.size());
        return _count;
    }
    
private:
    vector<int> _count;
    void merge(const vector<int> &nums, vector<int> &indexes, int l, int r) {
        if(r-l == 1)
            return;
        int mid = l + (r-l)/2;
        merge(nums, indexes, l, mid);
        merge(nums, indexes, mid, r);
        vector<int> ans;
        
        int i = l;
        int j = mid;
        while(i<mid || j<r) {
            // use left node
            if(i<mid && (j>=r || nums[indexes[i]]<=nums[indexes[j]])) {
                ans.push_back(indexes[i]);
                _count[indexes[i]] += j-mid;  // this is the number of elements moved before any left element is added to the sorted array
                ++i;
            }
            else {  // use right node
                ans.push_back(indexes[j]);
                ++j;
            }
        }

        move(ans.begin(), ans.end(), indexes.begin()+l);

    }
};
