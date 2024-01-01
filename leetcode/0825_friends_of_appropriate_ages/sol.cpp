/*
Facebook

There are n persons on a social media website. You are given an integer array ages where ages[i] is the age of the ith person.

A Person x will not send a friend request to a person y (x != y) if any of the following conditions is true:

age[y] <= 0.5 * age[x] + 7
age[y] > age[x]
age[y] > 100 && age[x] < 100
Otherwise, x will send a friend request to y.

Note that if x sends a request to y, y will not necessarily send a request to x. Also, a person will not send a friend request to themself.

Return the total number of friend requests made.

 

Example 1:

Input: ages = [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: ages = [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: ages = [20,30,100,110,120]
Output: 3
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
 

Constraints:

n == ages.length
1 <= n <= 2 * 10^4
1 <= ages[i] <= 120
*/


// since there's only limited number of ages, use counting sort: O(N)
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        vector<int> counts(121, 0);
        for(int y : ages)
            ++counts[y];

        int ans = 0;
        for(int y=15; y<=120; ++y) {  // no solution for y<=14
            if(!counts[y])
                continue;
            int cur = counts[y] - 1;
            for(int x=y+1; x<counts.size()&&x<2*(y-7); ++x)
                cur += counts[x];
            ans += cur*counts[y];
        }

        return ans;
    }
};


// improved binary search: y <= x < 2*(y-7)
// 1) directly filter y with no solution
// 2) count only once for same number
// 3) only search hi bound
// still O(NlgN)
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(), ages.end());

        int ans = 0;
        int prevCount = 0;
        for(int i=0; i<ages.size(); ++i) {  // for each y = ages[i]
            if(ages[i] <= 14)  // there is no solution when y>=2*(y-7) ==> y<=14
                continue;

            if(i>0 && ages[i]==ages[i-1]) {  // same anser -- no need to compute again
                ans += prevCount;
                continue;
            }

            int hi = lower_bound(ages.begin()+i, ages.end(), 2*(ages[i]-7)) - ages.begin();
            prevCount = hi-i-1;
            ans += prevCount;
        }

        return ans;
    }
};


// straightforward binary search: y <= x < 2*(y-7)
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(), ages.end());

        int ans = 0;
        // binary search for [lo,hi) that y will send a friend request
        for(int y : ages) {
            int lo = lower_bound(ages.begin(), ages.end(), y) - ages.begin();
            int hi = lower_bound(ages.begin(), ages.end(), 2*(y-7)) - ages.begin();
            if(hi>lo)
                ans += hi-lo-1;
        }

        return ans;
    }
};
