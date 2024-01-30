/*
Facebook/Amazon/Apple
  
Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area covered by the two rectangles.

The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner (ax2, ay2).

The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).

 

Example 1:

Rectangle Area
Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
Output: 45
Example 2:

Input: ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2, bx1 = -2, by1 = -2, bx2 = 2, by2 = 2
Output: 16
 

Constraints:

-10^4 <= ax1 <= ax2 <= 10^4
-10^4 <= ay1 <= ay2 <= 10^4
-10^4 <= bx1 <= bx2 <= 10^4
-10^4 <= by1 <= by2 <= 10^4
*/

// compute overlap of two line segments
class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        // area1 + area2 - overlap
        return (ax2-ax1)*(ay2-ay1) + (bx2-bx1)*(by2-by1) - overlap(ax1,ax2,bx1,bx2)*overlap(ay1,ay2,by1,by2);
    }

private:
    // compute overlap of two lines [s1,e1] and [s2,e2]
    int overlap(int s1, int e1, int s2, int e2) {
        int res = min(e1,e2)-max(s1,s2);
        return res>=0?res:0;  // negative means no overlap
    }
};
