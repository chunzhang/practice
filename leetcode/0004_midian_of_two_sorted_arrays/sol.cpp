/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

 

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
Example 3:

Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000
Example 4:

Input: nums1 = [], nums2 = [1]
Output: 1.00000
Example 5:

Input: nums1 = [2], nums2 = []
Output: 2.00000
 

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6
*/

// binary search
// time complexity: O(lg(min(N1, N2)), where N1, N2 is the size of the two input arrays
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // assume N1=A.size(), N2=B.size()
        // define k=(N1+N2+1)/2, then in the hypothetically merged sorted array C
        // -- C[k] is the right median (if exists)
        // -- If N1+N2 is odd, actual median is C[k-1]
        // -- If N1+N2 is even, actual median is (C[k-1]+C[k])/2
        // next, let's say in C we have m1 elements from A and m2 elements from B, which forms the first k elements of C
        // -- m1+m2 = k
        // Further, we have
        // -- C[k-1] = max(A[m1-1], B[m2-1])
        // -- C[k] = min(A[m1], B[m2])
               
        if(nums1.size() > nums2.size())
            swap(nums1, nums2);
        
        const int N1 = nums1.size();
        const int N2 = nums2.size();
        const int k = (N1+N2+1)/2;  // index to right median
        
        // now, our task becomes to find first element in A s.t. there're at least k elements from A and B that are smaller than or equal to it (not including the element itself)
        // we use binary search to do this in log time complexity
        int l = 0;
        int r = N1;
        while(l < r) {
            int m1 = l + (r-l)/2;
            int m2 = k - m1;
            if(nums1[m1] >= nums2[m2-1])  // this means there're at least k elements smaller than or equal to nums[m1] (not including nums[m1] itself)
                r = m1;
            else
                l = m1 + 1;
        }
        
        const int m1 = l;
        const int m2 = k - m1;
        const int leftMedian = max(m1>0?nums1[m1-1]:INT_MIN, m2>0?nums2[m2-1]:INT_MIN);
        if((N1+N2)%2)  // odd
            return leftMedian;
        
        const int rightMedian = min(m1<N1?nums1[m1]:INT_MAX, m2<N2?nums2[m2]:INT_MAX);
        return (leftMedian+rightMedian)/2.0;
    }
};
