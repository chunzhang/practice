/*
You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the smallest possible weight of the left stone. If there are no stones left, return 0.

 

Example 1:

Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation: 
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of the last stone.
Example 2:

Input: stones = [1]
Output: 1
 

Constraints:

1 <= stones.length <= 30
1 <= stones[i] <= 1000
*/

// O(NlgN) using priority queue
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;
        for(int s : stones)
            pq.push(s);
        
        while(pq.size() >=2 ) {
            int s1 = pq.top();
            pq.pop();
            int s2 = pq.top();
            pq.pop();
            int s3 = abs(s1-s2);
            if(s3)
                pq.push(s3);
        }
        
        return pq.size() ? pq.top() : 0;
    }
};



// A reference solution using bucket counting (in Java)
/*
This approach is only viable when the maximum stone weight is small, or is at least smaller than the number of stones.

Let WW be the maximum stone weight in the input array. We can create a bucket array of size W + 1W+1, where each index of the bucket array represents a stone weight. Then, we can bucket "sort" the stones in O(N)O(N) time by iterating over them and incrementing the relevant bucket array index by 1.

Complexity Analysis

Time complexity : O(N + W)O(N+W).

Putting the NN stones of the input array into the bucket array is O(N)O(N), because inserting each stone is an O(1)O(1) operation.

In the worst case, the main loop iterates through all of the WW indexes of the bucket array. Processing each bucket is an O(1)O(1) operation. This, therefore, is O(W)O(W).

Seeing as we don't know which is larger out of NN and WW, we get a total of O(N + W)O(N+W).

Technically, this algorithm is pseudo-polynomial, as its time complexity is dependent on the numeric value of the input. Pseudo-polynomial algorithms are useful when there is no "true" polynomial alternative, but in situations such as this one where we have an O(N \, \log \, N)O(NlogN) alternative (Approach 3), they are only useful for very specific inputs.

With the small values of WW that your code is tested against for this question here on LeetCode, this approach turns out to be faster than Approach 3. But that does not make it the better approach.

Space complexity : O(W)O(W).

We allocated a new array of size WW.

When I looked through the discussion forum for this question, I was surprised to see a number of people arguing that this approach is O(N)O(N), on the basis that we could say WW is a constant, due to the problem description stating it has a maximum value of 10001000. The trouble with this argument is that NN also has a maximum specified (of 3030, in fact), and so it is arbitrary to argue that WW is a constant, yet NN is not. These constraints on LeetCode problems are intended to help you determine whether or not your algorithm will be fast enough. They are not supposed to imply some variables can be treated as "constants". A correct time/ space complexity should treat them as unbounded.
*/
class Solution {
    
    public int lastStoneWeight(int[] stones) {
        
        // Set up the bucket array.
        int maxWeight = stones[0];
        for (int stone: stones) {
            maxWeight = Math.max(maxWeight, stone);
        }
        int[] buckets = new int[maxWeight + 1];

        // Bucket sort.
        for (int weight : stones) {
            buckets[weight]++;
        }

        // Scan through the buckets.
        int biggestWeight = 0;
        int currentWeight = maxWeight;
        while (currentWeight > 0) {
            if (buckets[currentWeight] == 0) {
                currentWeight--;
            } else if (biggestWeight == 0) {
                buckets[currentWeight] %= 2;
                if (buckets[currentWeight] == 1) {
                    biggestWeight = currentWeight;
                }
                currentWeight--;
            } else {
                buckets[currentWeight]--;
                if (biggestWeight - currentWeight <= currentWeight) {
                    buckets[biggestWeight - currentWeight]++;
                    biggestWeight = 0;
                } else {
                    biggestWeight -= currentWeight;
                }
            }
        }
        return biggestWeight;
    }
};
