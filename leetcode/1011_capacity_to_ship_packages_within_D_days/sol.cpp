/*
Facebook/Flipkart/Google


A conveyor belt has packages that must be shipped from one port to another within days days.

The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.

 

Example 1:

Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10

Note that the cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.
Example 2:

Input: weights = [3,2,2,4,1,4], days = 3
Output: 6
Explanation: A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2
2nd day: 2, 4
3rd day: 1, 4
Example 3:

Input: weights = [1,2,3,1,1], days = 4
Output: 3
Explanation:
1st day: 1
2nd day: 2
3rd day: 3
4th day: 1, 1
 

Constraints:

1 <= days <= weights.length <= 5 * 10^4
1 <= weights[i] <= 500
*/

// binary search: find the first capacity that can ship all packages within days
// time complexity: O(NlgS), where S is the sum of all package weights
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int l = 0;
        int r = 0;
        for(int w: weights) {
            l = max(l, w);
            r += w;
        }
        ++r;
        
        while(l < r) {
            int m = l + (r-l)/2;
            if(canShip(weights, days, m))
                r = m;
            else
                l = m + 1;
        }
        
        return l;
    }
    
private:
    // whether all packages can be shipped within days of the given ship cap
    bool canShip(const vector<int> &weights, int days, int cap) {
        int i = 0;
        int size = 0;
        while(days && i<weights.size()) {
            size += weights[i];
            if(size > cap) {
                size = 0;
                --days;
            }
            else
                ++i;
        }
        
        return i==weights.size()?true:false;
    }
};
