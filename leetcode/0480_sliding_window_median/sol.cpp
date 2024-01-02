/*
Facebook/Flipkart/Snowflake

The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.

For examples, if arr = [2,3,4], the median is 3.
For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
Explanation: 
Window position                Median
---------------                -----
[1  3  -1] -3  5  3  6  7        1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7        3
 1  3  -1  -3 [5  3  6] 7        5
 1  3  -1  -3  5 [3  6  7]       6
Example 2:

Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
 

Constraints:

1 <= k <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
*/


// maintain two sorted trees: one minTree for the upper half, and the other maxTree for the lower half
// time: O((N-k)*lgK)
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> ans;
        for(int i=0; i<nums.size(); ++i) {
            insert(nums[i]);
            if(i >= k)
                erase(nums[i-k]);
                        
            if(i >= k-1) {
                if(k%2)  // odd
                    ans.push_back(*m_minTree.begin());
                else  // even
                    ans.push_back( (*m_minTree.begin())*0.5 + (*m_maxTree.begin())*0.5 );
            }
        }

        return ans;
    }

private:
    void insert(int val) {
        if(m_minTree.empty() || val>=*m_minTree.begin())
            m_minTree.insert(val);
        else
            m_maxTree.insert(val);

        // balance the two trees
        balance();
    }

    void erase(int val) {
        if(val >= *m_minTree.begin())
            m_minTree.erase(m_minTree.find(val));
        else
            m_maxTree.erase(m_maxTree.find(val));

        balance();
    }

    // balance the two trees: in case of odd k, minTree has one more element than maxTree
    void balance() {
        while(m_minTree.size()!=m_maxTree.size() && m_minTree.size()!=m_maxTree.size()+1) {
            if(m_minTree.size() > m_maxTree.size()) {
                m_maxTree.insert(*m_minTree.begin());
                m_minTree.erase(m_minTree.begin());
            }
            else {
                m_minTree.insert(*m_maxTree.begin());
                m_maxTree.erase(m_maxTree.begin());
            }
        }
    }

private:
    multiset<int> m_minTree;
    multiset<int,greater<int>> m_maxTree;
};


// ref solution: same idea as my solution
vector<double> medianSlidingWindow(vector<int>& nums, int k)
{
    vector<double> medians;
    multiset<int> lo, hi;

    for (int i = 0; i < nums.size(); i++) {
        //remove outgoing element
        if (i >= k) {
            if (nums[i - k] <= *lo.rbegin())
                lo.erase(lo.find(nums[i - k]));
            else
                hi.erase(hi.find(nums[i - k]));
        }

        // insert incoming element
        lo.insert(nums[i]);

        // balance the sets
        hi.insert(*lo.rbegin());
        lo.erase(prev(lo.end()));

        if (lo.size() < hi.size()) {
            lo.insert(*hi.begin());
            hi.erase(hi.begin());
        }

        // get median
        if (i >= k - 1) {
            medians.push_back(k & 1 ? *lo.rbegin() : ((double)(*lo.rbegin()) + (double)(*hi.begin())) * 0.5);
        }
    }

    return medians;
}


// ref solution: one multiset and maintain iterator pointer (i.e., upper median)
// this reduces const factor but still has complexity of O((N-k)lgK)
vector<double> medianSlidingWindow(vector<int>& nums, int k)
{
    vector<double> medians;
    multiset<int> window(nums.begin(), nums.begin() + k);

    auto mid = next(window.begin(), k / 2);

    for (int i = k;; i++) {

        // Push the current median
        medians.push_back(((double)(*mid) + *next(mid, k % 2 - 1)) * 0.5);

        // If all done, break
        if (i == nums.size())
            break;

        // Insert incoming element
        window.insert(nums[i]);
        if (nums[i] < *mid)
            mid--;                  // same as mid = prev(mid)

        // Remove outgoing element
        if (nums[i - k] <= *mid)
            mid++;                  // same as mid = next(mid)

        window.erase(window.lower_bound(nums[i - k]));
    }

    return medians;
}


// ref solution: two heaps with lazy deletion: use hash-tables to keep track of invalidated elements.
// Once they reach the heap tops, we remove them from the heaps.
// Note the two heap needs to be kept balanced
vector<double> medianSlidingWindow(vector<int>& nums, int k)
{
    vector<double> medians;
    unordered_map<int, int> hash_table;
    priority_queue<int> lo;                                 // max heap
    priority_queue<int, vector<int>, greater<int> > hi;     // min heap

    int i = 0;      // index of current incoming element being processed

    // initialize the heaps
    while (i < k)
        lo.push(nums[i++]);
    for (int j = 0; j < k / 2; j++) {
        hi.push(lo.top());
        lo.pop();
    }

    while (true) {
        // get median of current window
        medians.push_back(k & 1 ? lo.top() : ((double)lo.top() + (double)hi.top()) * 0.5);

        if (i >= nums.size())
            break;                          // break if all elements processed

        int out_num = nums[i - k],          // outgoing element
            in_num = nums[i++],             // incoming element
            balance = 0;                    // balance factor

        // number `out_num` exits window
        balance += (out_num <= lo.top() ? -1 : 1);
        hash_table[out_num]++;

        // number `in_num` enters window
        if (!lo.empty() && in_num <= lo.top()) {
            balance++;
            lo.push(in_num);
        }
        else {
            balance--;
            hi.push(in_num);
        }

        // re-balance heaps
        if (balance < 0) {                  // `lo` needs more valid elements
            lo.push(hi.top());
            hi.pop();
            balance++;
        }
        if (balance > 0) {                  // `hi` needs more valid elements
            hi.push(lo.top());
            lo.pop();
            balance--;
        }

        // remove invalid numbers that should be discarded from heap tops
        while (hash_table[lo.top()]) {
            hash_table[lo.top()]--;
            lo.pop();
        }
        while (!hi.empty() && hash_table[hi.top()]) {
            hash_table[hi.top()]--;
            hi.pop();
        }
    }

    return medians;
}
