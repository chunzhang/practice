/*
  Given an array of integers nums, sort the array in ascending order.

 

  Example 1:

  Input: nums = [5,2,3,1]
  Output: [1,2,3,5]
  Example 2:

  Input: nums = [5,1,1,2,0,0]
  Output: [0,0,1,1,2,5]
 

  Constraints:

  1 <= nums.length <= 5 * 10^4
  -5 * 10^4 <= nums[i] <= 5 * 10^4
*/


// mrege sort
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // merge sort
        return mergeSort(nums, 0, nums.size()-1);
    }
    
private:
    vector<int> mergeSort(vector<int> &nums, int l, int h) {
        if(l == h)
            return {nums[l]};
        
        int mid = l + (h-l)/2;
        vector<int> left = mergeSort(nums, l, mid);
        vector<int> right = mergeSort(nums, mid+1, h);
        
        vector<int> ans;
        int i=0;
        int j=0;
        while(i<left.size() && j<right.size()) {
            if(left[i]<right[j])
                ans.push_back(left[i++]);
            else
                ans.push_back(right[j++]);
        }
        
        if(i < left.size())
            ans.insert(ans.end(), left.begin()+i, left.end());
        else
            ans.insert(ans.end(), right.begin()+j, right.end());
        
        return ans;
    }
};


// merge sort -- do not pass sorted array as return value to save some array copy cost
// time complexity: O(NlgN)
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // merge sort
        mergeSort(nums, 0, nums.size()-1);
        return nums;
    }
    
private:
    void mergeSort(vector<int> &nums, int l, int h) {
        if(l == h)
            return;
        
        int mid = l + (h-l)/2;
        mergeSort(nums, l, mid);
        mergeSort(nums, mid+1, h);
        
        vector<int> ans;
        int i=l;
        int j=mid+1;
        while(i<=mid && j<=h) {
            if(nums[i]<nums[j])
                ans.push_back(nums[i++]);
            else
                ans.push_back(nums[j++]);
        }
        
        if(i <= mid)
            ans.insert(ans.end(), nums.begin()+i, nums.begin()+mid+1);
        else
            ans.insert(ans.end(), nums.begin()+j, nums.begin()+h+1);
        
        for(int k=l; k<=h; ++k)
            nums[k] = ans[k-l];
    }
};


// randomized in-place quick sort
// time complexity: amortized O(NlgN)
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        srand(time(NULL));
        // in-place quick sort
        quickSort(nums, 0, nums.size()-1);
        return nums;
    }
    
private:
    void quickSort(vector<int> &nums, int l, int h) {
        if(l >= h)
            return;
        
        int pivot = l + rand()%(h-l+1);  // randomly select pivot element
        int pivotNum = nums[pivot];
        swap(nums[pivot], nums[h]);  // move pivot element to the end to simplify coding

        // partition the array such that nums[l...partition-1] <= pivotNum <= nums[partition...h]
        int partition = l;
        for(int i=l; i<h; ++i) {
            if(nums[i]<pivotNum || (nums[i]==pivotNum&&i<pivot)) {
                swap(nums[partition], nums[i]);
                ++partition;
            }
        }
        
        swap(nums[partition], nums[h]);
        quickSort(nums, l, partition-1);
        quickSort(nums, partition+1, h);
    }
};


// heap sort (using max heap)
// time complexity: O(NlgN)
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // heap sort -- using max heap
        buildMaxHeap(nums);
        heapSort(nums);
        return nums;
    }
    
private:
    void heapSort(vector<int> &nums) {
        for(int last=nums.size()-1; last>=0; --last) {
            swap(nums[last], nums[0]);
            maxHeapify(nums, 0, last);
        }
    }
    
    void buildMaxHeap(vector<int> &nums) {
        for(int i=nums.size()/2; i>=0; --i)
            maxHeapify(nums, i, nums.size());
    }
    
    // max heapify i-th node (i.e., top-down)
    void maxHeapify(vector<int> &nums, int i, int sz) {
        int left = i*2 + 1;
        int right = i*2 + 2;
        int largest = i;  // index to largest number among root, left and right
        if(left<sz && nums[left]>nums[largest])
            largest = left;
        if(right<sz && nums[right]>nums[largest])
            largest = right;
        
        if(largest != i) {
            swap(nums[largest], nums[i]);
            maxHeapify(nums, largest, sz);
        }
    }
};


// reference from HuaHua
// quick sort
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        function<void(int, int)> quickSort = [&](int l, int r) {
            if (l >= r) return;      
            int i = l;
            int j = r;
            int p = nums[l + rand() % (r - l + 1)];
            while (i <= j) {
                while (nums[i] < p) ++i;
                while (nums[j] > p) --j;
                if (i <= j)
                    swap(nums[i++], nums[j--]);
            }
            quickSort(l, j);
            quickSort(i, r);
        };
        quickSort(0, nums.size() - 1);
        return nums;
    }
};

// counting sort
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        auto [min_it, max_it] = minmax_element(begin(nums), end(nums));
        int l = *min_it, r = *max_it;
        vector<int> count(r - l + 1);
        for (int n : nums) ++count[n - l];
        int index = 0;
        for (int i = 0; i < count.size(); ++i)
            while (count[i]--) nums[index++] = i + l;
        return nums;
    }
};


// heap sort 1 -- using priority queue
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        priority_queue<int> q(begin(nums), end(nums));
        int i = nums.size();
        while (!q.empty()) {
            nums[--i] = q.top();
            q.pop();
        }
        return nums;
    }
};


// heap sort 2 -- from scratch
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        auto heapify = [&](int i, int e) {
            while (i <= e) {
                int l = 2 * i + 1;
                int r = 2 * i + 2;
                int j = i;
                if (l <= e && nums[l] > nums[j]) j = l;
                if (r <= e && nums[r] > nums[j]) j = r;
                if (j == i) break;
                swap(nums[i], nums[j]);
                swap(i, j);
            }
        };
    
        const int n = nums.size();
    
        // Init heap
        for (int i = n / 2; i >= 0; i--)
            heapify(i, n - 1);
    
        // Get min.
        for (int i = n - 1; i >= 1; i--) {
            swap(nums[0], nums[i]);
            heapify(0, i - 1);    
        }
    
        return nums;
    }
};

// merge sort
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        vector<int> t(nums.size());
        function<void(int, int)> mergeSort = [&](int l, int r) {
            if (l + 1 >= r) return;
            int m = l + (r - l) / 2;
            mergeSort(l, m);
            mergeSort(m, r);
            int i1 = l;
            int i2 = m;
            int index = 0;
            while (i1 < m || i2 < r)
                if (i2 == r || (i1 < m && nums[i1] < nums[i2]))
                    t[index++] = nums[i1++];
                else
                    t[index++] = nums[i2++];      
            std::copy(begin(t), begin(t) + index, begin(nums) + l);
        };
    
        mergeSort(0, nums.size());
        return nums;
    }
};


// use BST
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        multiset<int> s(begin(nums), end(nums));
        return {begin(s), end(s)};
    }
};

