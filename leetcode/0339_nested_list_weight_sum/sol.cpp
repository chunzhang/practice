/*
You are given a nested list of integers nestedList. Each element is either an integer or a list whose elements may also be integers or other lists.

The depth of an integer is the number of lists that it is inside of. For example, the nested list [1,[2,2],[[3],2],1] has each integer's value set to its depth.

Return the sum of each integer in nestedList multiplied by its depth.

 

Example 1:


Input: nestedList = [[1,1],2,[1,1]]
Output: 10
Explanation: Four 1's at depth 2, one 2 at depth 1. 1*2 + 1*2 + 2*1 + 1*2 + 1*2 = 10.
Example 2:


Input: nestedList = [1,[4,[6]]]
Output: 27
Explanation: One 1 at depth 1, one 4 at depth 2, and one 6 at depth 3. 1*1 + 4*2 + 6*3 = 27.
Example 3:

Input: nestedList = [0]
Output: 0
 

Constraints:

1 <= nestedList.length <= 50
The values of the integers in the nested list is in the range [-100, 100].
The maximum depth of any integer is less than or equal to 50.
*/

/*
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */


// DFS solution
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        return rec(nestedList, 1);
    }

    // DFS recursion
    int rec(const vector<NestedInteger> &nestedList, int depth) {
        int sum = 0;
        for(auto &li : nestedList) {
            if(li.isInteger())
                sum += li.getInteger()*depth;
            else
                sum += rec(li.getList(), depth+1);
        }
        return sum;
    }
};

// BFS solution
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        // Solve by BFS
        queue<const NestedInteger*> q;  // note such container cannot take non-assignable type such as reference
        for(auto &li: nestedList)
            q.push(&li);

        int sum = 0;
        int depth = 1;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                auto p_li = q.front();
                q.pop();
                if(p_li->isInteger())
                    sum += p_li->getInteger()*depth;
                else
                    for(auto &li: p_li->getList())
                        q.push(&li);
            }
            ++depth;
        }

        return sum;
    }
};
