/*
You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given by the array sweetness.

You want to share the chocolate with your k friends so you start cutting the chocolate bar into k + 1 pieces using k cuts, each piece consists of some consecutive chunks.

Being generous, you will eat the piece with the minimum total sweetness and give the other pieces to your friends.

Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.

 

Example 1:

Input: sweetness = [1,2,3,4,5,6,7,8,9], k = 5
Output: 6
Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]
Example 2:

Input: sweetness = [5,6,7,8,9,1,2,3,4], k = 8
Output: 1
Explanation: There is only one way to cut the bar into 9 pieces.
Example 3:

Input: sweetness = [1,2,2,1,2,2,1,2,2], k = 2
Output: 5
Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]
 

Constraints:

0 <= k < sweetness.length <= 10^4
1 <= sweetness[i] <= 10^5
*/


// binary search
// this problem is max-min problem, where as 0410-Split Array Largest Sum is min-max problem
// same technique here: find smallest sweetness that does not satify, so that number-1 is the largest one that satisfies
class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        int lo = *min_element(sweetness.begin(), sweetness.end());
        int hi = accumulate(sweetness.begin(), sweetness.end(), 0)/(k+1)+1;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            if(g(sweetness, mid, k) < k+1)  // find first/smallest sweetness that is not enough to share with k+1 people (including myself)
                hi = mid;
            else
                lo = mid + 1;
        }
        
        return lo-1;  // lo points to the smallest number that is not enough, so lo-1 is the max of min-sweetness satifying to share
    }
    
private:
    // return number of people who can get chocolate chunks with minSweetness
    int g(const vector<int> &s, int minSweetness, int k) {
        int sum = 0;
        int p = 0;
        for(int i=0; i<s.size(); ++i) {
            sum += s[i];
            if(sum >= minSweetness) {
                ++p;
                sum = 0;
            }
            
            if(p >= k+1)  // pruning: already have enough people
                return p;
        }
        
        return p;
    }
};
