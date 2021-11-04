/*
Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).

You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).

 

Example 1:


Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
Example 2:

Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
Explanation: The answer [[-2,4],[3,3]] would also be accepted.
 

Constraints:

1 <= k <= points.length <= 10^4
-10^4 < xi, yi < 10^4
*/


// sol 1: use min heap
// time complexity: O(klgN)
// space complexity: O(N)
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        typedef pair<int,int> Elem;
        
        function<bool(const Elem&,const Elem&)> comp = [](const Elem &e1, const Elem &e2) {
            return e1.first > e2.first;
        };
        priority_queue<Elem,vector<Elem>,decltype(comp)> pq(comp);
        
        for(int i=0; i<points.size(); ++i)
            pq.push({points[i][0]*points[i][0]+points[i][1]*points[i][1],i});
        
        vector<vector<int>> ans;
        while(k--) {
            ans.emplace_back(points[pq.top().second]);
            pq.pop();
        }
        
        return ans;
    }
};


// another way of smartly use heap with comp comparing aux data
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<int> dist(points.size(), 0);

        auto comp = [&dist](int n1, int n2) {
            return dist[n1]> dist[n2];
        };
        priority_queue<int, vector<int>, decltype(comp)> heap(comp);  // store index, but compare distance
        
        for(int i=0; i<points.size(); i++)
        {
            dist[i] = points[i][0]*points[i][0] + points[i][1]*points[i][1];
            heap.push(i);
        }
        
        vector<vector<int>> res;
        for(int i=0; i<k; i++)
        {
            int val = heap.top();
            heap.pop();
            res.push_back(points[val]);
        }
        
        return res;
    }
};

// sol 2: use nth_element
// time complexity: average O(N)
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        nth_element(points.begin(), points.begin()+k-1, points.end(), 
                    [](auto &p1, auto &p2) {return p1[0]*p1[0]+p1[1]*p1[1]<p2[0]*p2[0]+p2[1]*p2[1];}
                   );
        
        return vector<vector<int>>(points.begin(), points.begin()+k);
    }
};
