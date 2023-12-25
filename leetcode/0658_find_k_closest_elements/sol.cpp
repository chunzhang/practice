/*
Yandex/Facebook/DoorDash

Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]
 

Constraints:

1 <= k <= arr.length
1 <= arr.length <= 104
arr is sorted in ascending order.
-104 <= arr[i], x <= 104
*/


// binary search + two pointers
// O(lgN + k)
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int j = distance(arr.begin(), lower_bound(arr.begin(),arr.end(),x));  // first element >= x
        int i = j - 1;

        // selected range is [i+1,j-1] or (i,j)
        while(k--) {
            if(i<0)
                ++j;
            else if(j>=arr.size())
                --i;
            else {
                if(x-arr[i] <= arr[j]-x)
                    --i;
                else
                    ++j;
            }
        }

        vector<int> ans;
        for(int p=i+1; p<j; ++p)
            ans.push_back(arr[p]);
        return ans;
    }
};


// reference solution: sort by abs(num-x)
// O(NlgN + klgk), since the subarry of k needs to be sorted by value again
// in Java
class Solution {
    public List<Integer> findClosestElements(int[] arr, int k, int x) {
        // Convert from array to list first to make use of Collections.sort()
        List<Integer> sortedArr = new ArrayList<Integer>();
        for (int num: arr) {
            sortedArr.add(num);
        }
        
        // Sort using custom comparator
        Collections.sort(sortedArr, (num1, num2) -> Math.abs(num1 - x) - Math.abs(num2 - x));
        
        // Only take k elements
        sortedArr = sortedArr.subList(0, k);
        
        // Sort again to have output in ascending order
        Collections.sort(sortedArr);
        return sortedArr;
    }
}
