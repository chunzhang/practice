/*
  Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.

  Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).


  Example 1:

  rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [3,2,4,4],
  [1,3,2,4],
  [2,3,3,4]
  ]

  Return true. All 5 rectangles together form an exact cover of a rectangular region.

  Example 2:

  rectangles = [
  [1,1,2,3],
  [1,3,2,4],
  [3,1,4,2],
  [3,2,4,4]
  ]

  Return false. Because there is a gap between the two rectangular regions.

  Example 3:

  rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [3,2,4,4]
  ]

  Return false. Because there is a gap in the top center.

  Example 4:

  rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [2,2,4,4]
  ]

  Return false. Because two of the rectangles overlap with each other.
*/


// A perfect rectangle must satisfy following conditions
// -- Area adds up exactly as bounding box area
// -- For all rectangle corners (except the four bounding box corner), it must
//    be overlapped for exactly two or four times
// -- Each overlapping cannot must be from different type of corners (e.g., TL and TL )
//    can't overlap on the same corner grid
/*
  TL-0x1    TR-0x2
  ----------
  |        |
  |        |
  |        |
  ----------
  BL-0x4    BR-0x8
*/
class Solution {
public:
  bool isRectangleCover(vector<vector<int>>& rectangles) {
    // Compute bounding box
    int left = INT_MAX;
    int bottom = INT_MAX;
    int right = 0;
    int up = 0;
    int area = 0;
    unordered_map<string, int> overlaps;  // to count overlapping of rectangle corners
    vector<int> bitmask = {0x1, 0x2, 0x4, 0x8};  // for corner type
        
    // 1. count corners and areas
    for(int i=0; i<rectangles.size(); ++i) {
      int l = rectangles[i][0];
      int b = rectangles[i][1];
      int r = rectangles[i][2];
      int t = rectangles[i][3];
      vector<pair<int,int>> corners = {{l,t}, {r,t}, {l,b}, {r,b}};
      for(int i=0; i<4; ++i) {
	string key = to_string(corners[i].first) + "_" + to_string(corners[i].second);
	if(overlaps[key]&bitmask[i])  // overlapping of same type of corners is invalid
	  return false;
	overlaps[key] += bitmask[i];
      }
                      
      left = min(left, rectangles[i][0]);
      bottom = min(bottom, rectangles[i][1]);
      right = max(right, rectangles[i][2]);
      up = max(up, rectangles[i][3]);
      area += (r-l)*(t-b);
    }
        
    // 2. sanity check on corner overlapping
    int count = 0;
    for(auto item : overlaps) {
      int m = item.second;
      if(m==3 || m==10 || m==12 || m==5  // on bounding box boundary
	 || m==15) {   // inside bounding box
      }
      else if(m==1 || m==2 || m==4 || m==8) {  // on bounding box corner
	++count;
	if(count > 4)
	  return false;
      }
      else
	return false;
    }
        
    if(count != 4)
      return false;
        
    return area==(right-left)*(up-bottom);
  }
    
};


// My O(N^2) solution with rectangle overlapping detection
class Solution {
public:
  bool isRectangleCover(vector<vector<int>>& rectangles) {
    // Compute bounding box
    int left = INT_MAX;
    int bottom = INT_MAX;
    int right = 0;
    int up = 0;
    int count = 0;  // number of grids being covered
    for(int i=0; i<rectangles.size(); ++i) {
      for(int j=0; j<i; ++j) {  // detecting overlap
	if(overlap(rectangles[i], rectangles[j]))
	  return false;
      }
      left = min(left, rectangles[i][0]);
      bottom = min(bottom, rectangles[i][1]);
      right = max(right, rectangles[i][2]);
      up = max(up, rectangles[i][3]);
      count += (rectangles[i][2]-rectangles[i][0])*(rectangles[i][3]-rectangles[i][1]);
    }
        
    return count==(right-left)*(up-bottom);
  }
    
private:
  bool overlap(const vector<int> &rect1, const vector<int> &rect2) {
    bool xOverlap = !(rect1[2]<=rect2[0] || rect1[0]>=rect2[2]);
    bool yOverlap = !(rect1[1]>=rect2[3] || rect1[3]<=rect2[1]);
    return xOverlap&&yOverlap;
  }
};
