/*
We are given a list schedule of employees, which represents the working time for each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.

Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.

(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).  Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.

 

Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]
 

Constraints:

1 <= schedule.length , schedule[i].length <= 50
0 <= schedule[i].start < schedule[i].end <= 10^8
*/


// sol 1: sort all intervals
// time complexity: O(N*lgN), where N is the total number of intervals
// space complexity: O(N)
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        function<bool(const Interval&,const Interval&)> comp = [](const Interval &t1, const Interval &t2) {
            if(t1.start != t2.start)
                return t1.start > t2.start;
            else
                return t1.end > t2.end;
        };
      
        vector<Interval> ans;
        priority_queue<Interval,vector<Interval>,decltype(comp)> pq(comp);
        for(auto &p : schedule)
            for(auto &t : p)
                pq.push(t);
        
        int busyUntil = pq.top().start;
        while(!pq.empty()) {
            Interval t = pq.top();
            pq.pop();
            if(t.start <= busyUntil) {
                busyUntil = max(busyUntil, t.end);
            }
            else {
                ans.emplace_back(busyUntil,t.start);
                busyUntil = t.end;
            }
        }
        
        return ans;
    }
};


// since each person's schedule is sorted, we can use similiar technique as "merge N sorted arrays"
// i.e., only push one schedule of each person into the priority queue
// time complexity: O(NlgP), where N is total number of intervals, P is totoal number of employees
// space complexity: O(P)
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        const int P = schedule.size();
        vector<int> next(P, 0);
        
        function<bool(const pair<Interval,int>&,const pair<Interval,int>&)> comp = [](const pair<Interval,int> &t1, const pair<Interval,int> &t2) {
            if(t1.first.start != t2.first.start)
                return t1.first.start > t2.first.start;
            else
                return t1.first.end > t2.first.end;
        };
      
        vector<Interval> ans;
        priority_queue<pair<Interval,int>,vector<pair<Interval,int>>,decltype(comp)> pq(comp);
        for(int p=0; p<P; ++p)
            pq.push({schedule[p][next[p]++],p});
        
        int busyUntil = pq.top().first.start;
        while(!pq.empty()) {
            Interval t = pq.top().first;
            int p = pq.top().second;
            pq.pop();
            if(next[p] < schedule[p].size())
                pq.push({schedule[p][next[p]++], p});
            
            if(t.start <= busyUntil) {
                busyUntil = max(busyUntil, t.end);
            }
            else {
                ans.emplace_back(busyUntil,t.start);
                busyUntil = t.end;
            }
        }
        
        return ans;
    }
};
