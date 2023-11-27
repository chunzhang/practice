/*
There are n buildings in a line. You are given an integer array heights of size n that represents the heights of the buildings in the line.

The ocean is to the right of the buildings. A building has an ocean view if the building can see the ocean without obstructions. Formally, a building has an ocean view if all the buildings to its right have a smaller height.

Return a list of indices (0-indexed) of buildings that have an ocean view, sorted in increasing order.

 

Example 1:

Input: heights = [4,2,3,1]
Output: [0,2,3]
Explanation: Building 1 (0-indexed) does not have an ocean view because building 2 is taller.
Example 2:

Input: heights = [4,3,2,1]
Output: [0,1,2,3]
Explanation: All the buildings have an ocean view.
Example 3:

Input: heights = [1,3,2,4]
Output: [3]
Explanation: Only building 3 has an ocean view.
 

Constraints:

1 <= heights.length <= 105
1 <= heights[i] <= 109
*/

// solution 1: keep max height on the right
class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        vector<int> res;
        int highest = 0;
        for(int i=heights.size()-1; i>=0; --i) {
            if(heights[i] > highest) {
                res.push_back(i);
                highest = heights[i];
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

// solution 2: maintain mono height-decreasing stack
class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        // maintain monotonically height decreasing stack (by storing index in the stack)
        stack<int> st;
        for(int i=0; i<heights.size(); ++i) {
            while(!st.empty() && heights[st.top()]<=heights[i]) {
                st.pop();
            }
            st.push(i);
        }

        vector<int> res(st.size());
        for(int i=res.size()-1; i>=0; --i) {
            res[i] = st.top();
            st.pop();
        }
        return res;
    }
};
