/*
You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.

For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].

Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].

 

Example 1:

Input: arr = [1,2,3,5], k = 3
Output: [2,5]
Explanation: The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
The third fraction is 2/5.
Example 2:

Input: arr = [1,7], k = 1
Output: [1,7]
 

Constraints:

2 <= arr.length <= 1000
1 <= arr[i] <= 3 * 10^4
arr[0] == 1
arr[i] is a prime number for i > 0.
All the numbers of arr are unique and sorted in strictly increasing order.
1 <= k <= arr.length * (arr.length - 1) / 2
*/


// binary search of floating range
// time complexity: O(NlgW), where W is the width (in quantized units) of our binary search, (hi - lo) / 1e-9 which is 10^9
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        double l = 0.0;
        double r = 1.0;
        int idx0 = -1;
        int idx1 = -1;
        while(r-l > 1e-9) {
            double m = (l+r)/2;
            int p = -1;
            int q = -1;
            int count = countSmaller(arr, m, p, q);
            if(count >= k) {
                r = m;  // will not stuck the binary search since we're handling floating range
                idx0 = p;
                idx1 = q;
            }
            else
                l = m;
        }
        
        return {arr[idx0], arr[idx1]};
    }
    
private:
    // count number of fractions that are smaller than val
    // in addition, return (p,q) which is the max among those smaller numbers
    // O(N) time complexity -- using two pointers
    int countSmaller(const vector<int> &arr, double val, int &p, int &q) {
        int count = 0;
        const int N = arr.size();
        double maxFraction = 0.0;
        for(int i=0,j=0; i<N-1; ++i) {
            // arr[i]/arr[j] decreases monotonically
            // move j to the first index where the fraction number is smaller than val
            while(j<N && arr[i]>val*arr[j])  
                ++j;
            if(j == N)  // no more smaller numbers
                break;
            count += N-j;  // number of smaller fractions
            double fraction = arr[i]/(double)arr[j];
            if(fraction > maxFraction) {
                maxFraction = fraction;
                p = i;
                q = j;
            }
        }
        
        return count;
    }
};


// binary search impl 2
// slight exiting conditions
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        double l = 0.0;
        double r = 1.0;
        while(r-l > 1e-9) {
            double m = (l+r)/2;
            int p = -1;
            int q = -1;
            int count = countSmaller(arr, m, p, q);
            if(count == k)
                return {arr[p], arr[q]};
            if(count >= k) {
                r = m;  // will not stuck the binary search since we're handling floating range
            }
            else
                l = m;
        }
        
        return {-1, -1};  // should not reach here
    }
    
private:
    // count number of fractions that are smaller than val
    // in addition, return (p,q) which is the max among those smaller numbers
    // O(N) time complexity -- using two pointers
    int countSmaller(const vector<int> &arr, double val, int &p, int &q) {
        int count = 0;
        const int N = arr.size();
        double maxFraction = 0.0;
        for(int i=0,j=0; i<N-1; ++i) {
            // arr[i]/arr[j] decreases monotonically
            // move j to the first index where the fraction number is smaller than val
            while(j<N && arr[i]>val*arr[j])  
                ++j;
            if(j == N)  // no more smaller numbers
                break;
            count += N-j;  // number of smaller fractions
            double fraction = arr[i]/(double)arr[j];
            if(fraction > maxFraction) {
                maxFraction = fraction;
                p = i;
                q = j;
            }
        }
        
        return count;
    }
};
  

// use min-heap
// time complexity: O(KlgN), where K can be O(N^2)
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        auto comp = [&](const pair<int,int> &p1, const pair<int,int> &p2) {
            return arr[p1.first]*arr[p2.second] > arr[p2.first]*arr[p1.second];
        };
        
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> pq(comp);
        const int N = arr.size();
        for(int i=0; i<N-1; ++i)
            pq.push({i,N-1});
        
        pair<int,int> ans;
        while(k--) {
            ans = pq.top();
            pq.pop();
            if(ans.second > ans.first + 1)
                pq.push({ans.first, ans.second-1});
        }
        
        return {arr[ans.first], arr[ans.second]};
    }
};
