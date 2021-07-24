/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

 

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4
Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30
Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23
 

Constraints:

1 <= piles.length <= 10^4
piles.length <= h <= 10^9
1 <= piles[i] <= 10^9
*/

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        // binary search to find the first k that can finish all bananas within h hours
        int l = 1;  // eat at least one banana per hour
        int r = INT_MIN;
        for(int p : piles)
            r = max(r, p);
        r += 1;  // no need to eat more than this
        
        while(l < r) {
            int m = l + (r-l)/2;
            int time = 0;  // how many hours needed to finish all piles
            for(int p : piles) {
                time += (p+m-1)/m;  // ceiling of integer division
            }
            if(time <= h)
                r = m;
            else
                l = m + 1;
        }
        
        return l;
    }
};
