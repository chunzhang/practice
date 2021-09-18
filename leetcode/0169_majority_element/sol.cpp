/*
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
 

Follow-up: Could you solve the problem in linear time and in O(1) space?
*/

// Reference for Boyer-Moore voting algorithm
// https://gregable.com/2013/10/majority-vote-algorithm-find-majority.html


// O(N) time, O(1) space
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // since majority element takes more than half of the array elements, and it's guaranteed to exist
        // any other element will be canceled out with majority element
        int ans = 0;
        int count = 0;
        for(int num : nums) {
            if(count == 0) {
                ans = num;  // new majority element candidate
                ++count;
            }
            else {
                count = num==ans?(count+1):(count-1);  // add up or cancel out
            }
        }
        
        return ans;
    }
};


// A more concise implementation
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int num = 0;    // This initial number doesn't matter as its count is set to 0
        int count = 0;
        for(int n : nums) {
            // This is the key
            // -- Whenever count equals 0, we effectively forget 
            //    about everything in nums up to the current index 
            //    and consider the current number as the candidate 
            //    for majority element
            // -- This is because 0 means all occurrence of previous
            //    numbers are just "cancelled out"
            if(count == 0)
                num = n;
            count += num==n ? 1 : -1;
        }
        
        return num;
    }
};



// counting with unordered_map
// time: O(N), spece: O(N)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> count;
        const int n = nums.size();
        for (const int num : nums)
            if (++count[num] > n / 2) return num;
        return -1;
    }
};


// counting with map
// time: O(NlgN), space: O(N)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int, int> count;
        const int n = nums.size();
        for (const int num : nums)
            if (++count[num] > n / 2) return num;
        return -1;
    }
};

// randomization
// time: average O(N), space: O(1)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        srand(time(nullptr));
        const int n = nums.size();
        while (true) {
            const int index = rand() % n;
            const int majority = nums[index];
            int count = 0;
            for (const int num : nums)
                if (num == majority && ++count > n/2) return num;
        }
        return -1;
    }
};


// bit voting
// time: O(32*N), space: O(1)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        const int n = nums.size();
        int majority = 0;        
        for (int i = 0; i < 32; ++i) {
            int mask = 1 << i;
            int count = 0;
            for (const int num : nums)
                if ((num & mask) && (++count > n /2)) {
                    majority |= mask;
                    break;
                }
        }
        return majority;
    }
};

// full sorting
// time: O(NlgN), space: O(1)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        return nums[nums.size()/2];
    }
};

// partial sorting
// time: average O(N), space: O(1)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
        return nums[nums.size() / 2];
    }
};


// divide and conquer impl 1
// time: O(NlgN), space: O(lgN)
lass Solution {
public:
    int majorityElement(vector<int>& nums) {
        return majorityElement(nums, 0, nums.size() - 1);
    }
private:
    int majorityElement(const vector<int>& nums, int l, int r) {
        if (l == r) return nums[l];
        const int m = l + (r - l) / 2;
        const int ml = majorityElement(nums, l, m);
        const int mr = majorityElement(nums, m + 1, r);
        if (ml == mr) return ml;
        return count(nums.begin() + l, nums.begin() + r + 1, ml) >
               count(nums.begin() + l, nums.begin() + r + 1, mr)
               ? ml : mr;
    }
};

// divide and conquer impl 2
// time: O(NlgN), space: O(lgN)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        return majorityElement(nums, 0, nums.size() - 1).first;
    }
private:
    pair<int, int> majorityElement(const vector<int>& nums, int l, int r) {
        if (l == r) return {nums[l], 1};
        int mid = l + (r - l) / 2;
        auto ml = majorityElement(nums, l, mid);
        auto mr = majorityElement(nums, mid + 1, r);
        if (ml.first == mr.first) return { ml.first, ml.second + mr.second };
        if (ml.second > mr.second)
            return { ml.first, ml.second + count(nums.begin() + mid + 1, nums.begin() + r + 1, ml.first) };
        else
            return { mr.first, mr.second + count(nums.begin() + l, nums.begin() + mid + 1, mr.first) };
    }
};
