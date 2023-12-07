/*
You are given a 0-indexed array of positive integers w where w[i] describes the weight of the ith index.

You need to implement the function pickIndex(), which randomly picks an index in the range [0, w.length - 1] (inclusive) and returns it. The probability of picking an index i is w[i] / sum(w).

For example, if w = [1, 3], the probability of picking index 0 is 1 / (1 + 3) = 0.25 (i.e., 25%), and the probability of picking index 1 is 3 / (1 + 3) = 0.75 (i.e., 75%).
 

Example 1:

Input
["Solution","pickIndex"]
[[[1]],[]]
Output
[null,0]

Explanation
Solution solution = new Solution([1]);
solution.pickIndex(); // return 0. The only option is to return 0 since there is only one element in w.
Example 2:

Input
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
Output
[null,1,1,1,1,0]

Explanation
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // return 1. It is returning the second element (index = 1) that has a probability of 3/4.
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 0. It is returning the first element (index = 0) that has a probability of 1/4.

Since this is a randomization problem, multiple answers are allowed.
All of the following outputs can be considered correct:
[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......
and so on.
 

Constraints:

1 <= w.length <= 104
1 <= w[i] <= 105
pickIndex will be called at most 104 times.
*/

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

// imagine the array is expanded based on the weight
class Solution {
public:
    Solution(vector<int>& w) : _w(w), _ends(w.size(), 0) {
        //srand(time(0));
        _ends[0] = w[0] - 1;
        for(int i=1; i<_ends.size(); ++i)
            _ends[i] = _ends[i-1] + w[i];
    }
    
    int pickIndex() {
        // generate random number in [0, lastIdx] in expanded array
        unsigned long r = rand()%(_ends.back()+1);
        auto idx = lower_bound(_ends.begin(), _ends.end(), r) - _ends.begin();  // first idx where _ends[idx]>=r
        return idx;
    }

private:
    vector<int> &_w;
    vector<unsigned long> _ends;  // ending index of the "imaginary expanded array"
};


// implement own binary search
class Solution {
public:
    Solution(vector<int>& w) : _w(w), _ends(w.size(), 0) {
        //srand(time(0));
        _ends[0] = w[0] - 1;
        for(int i=1; i<_ends.size(); ++i)
            _ends[i] = _ends[i-1] + w[i];
    }
    
    int pickIndex() {
        // generate random number in [0, lastIdx] in expanded array
        unsigned long rnd = rand()%(_ends.back()+1);

        // binary search
        int l = 0;
        int r = _ends.size();
        while(l<r) {
            int mid = l + (r-l)/2;
            if(_ends[mid] >= rnd)  // first elem where this condidion is met
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }

private:
    vector<int> &_w;
    vector<unsigned long> _ends;  // ending index of the "imaginary expanded array"
};
