/*
Facebook/Amazon/Apple

Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.
 

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/


// build min-heap of size k based on frequency
// O(NlgK) time
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // counting
        unordered_map<int,int> counts;
        for(int n : nums)
            ++counts[n];

        // build priority queue of size k based on freq
        auto comp = [&counts](const int n1, const int n2) {  // least frequent number at queue top
            return counts[n1] > counts[n2];
        };
        priority_queue<int,vector<int>,decltype(comp)> pq(comp);
        for(auto &p : counts) {
            pq.push(p.first);
            if(pq.size() > k)
                pq.pop();
        }

        vector<int> ans;
        while(k--) {
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};


// counting and sort by frequency
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // counting: O(N)
        unordered_map<int,int> counts;
        for(int n : nums)
            ++counts[n];

        // sort by freq: O(f*lgf), where f is the total number of frequency
        multimap<int,int,greater<int>> freq;
        for(auto &p : counts)
            freq.insert({p.second,p.first});

        // collect answer: O(k)
        vector<int> ans;
        for(auto it=freq.begin(); it!=freq.end()&&k; ++it, --k)
            ans.push_back(it->second);
        return ans;
    }
};


// ref solution: quick sort based on frequency (no need to sort the full array since we only need top k elements)
// 1. Quickselect is a textbook algorithm typically used to solve the problems "find kth something": kth smallest,
//    kth largest, kth most frequent, kth less frequent, etc.
// 2. Like quicksort, quickselect was developed by Tony Hoare and is also known as Hoare's selection algorithm.
// Time complexity: average O(N), worst O(N^2)
class Solution {
private:
    vector<int> unique;
    map<int, int> count_map;

public:
    int partition(int left, int right, int pivot_index) {
        int pivot_frequency = count_map[unique[pivot_index]];
        // 1. Move the pivot to the end
        swap(unique[pivot_index], unique[right]);

        // 2. Move all less frequent elements to the left
        int store_index = left;
        for (int i = left; i <= right; i++) {
            if (count_map[unique[i]] < pivot_frequency) {
                swap(unique[store_index], unique[i]);
                store_index += 1;
            }
        }

        // 3. Move the pivot to its final place
        swap(unique[right], unique[store_index]);

        return store_index;
    }

    void quickselect(int left, int right, int k_smallest) {
        /*
        Sort a list within left..right till kth less frequent element
        takes its place. 
        */

        // base case: the list contains only one element
        if (left == right) return;

        int pivot_index = left + rand() % (right - left + 1);

        // Find the pivot position in a sorted list
        pivot_index = partition(left, right, pivot_index);

        //If the pivot is in its final sorted position
        if (k_smallest == pivot_index) {
            return;
        } else if (k_smallest < pivot_index) {
            // go left
            quickselect(left, pivot_index - 1, k_smallest);
        } else {
            // go right
            quickselect(pivot_index + 1, right, k_smallest);
        }
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        // build hash map: element and how often it appears
        for (int n : nums) {
            count_map[n] += 1;
        }

        // array of unique elements
        int n = count_map.size();
        for (pair<int, int> p : count_map) {
            unique.push_back(p.first);
        }

        // kth top frequent element is (n - k)th less frequent.
        // Do a partial sort: from less frequent to the most frequent, till
        // (n - k)th less frequent element takes its place (n - k) in a sorted array.
        // All elements on the left are less frequent.
        // All the elements on the right are more frequent.
        quickselect(0, n - 1, n - k);
        // Return top k frequent elements
        vector<int> top_k_frequent(k);
        copy(unique.begin() + n - k, unique.end(), top_k_frequent.begin());
        return top_k_frequent;
    }
};
