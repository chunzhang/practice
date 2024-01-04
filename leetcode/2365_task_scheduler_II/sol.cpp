/*
Facebook/Remitly

You are given a 0-indexed array of positive integers tasks, representing tasks that need to be completed in order, where tasks[i] represents the type of the ith task.

You are also given a positive integer space, which represents the minimum number of days that must pass after the completion of a task before another task of the same type can be performed.

Each day, until all tasks have been completed, you must either:

Complete the next task from tasks, or
Take a break.
Return the minimum number of days needed to complete all tasks.

 

Example 1:

Input: tasks = [1,2,1,2,3,1], space = 3
Output: 9
Explanation:
One way to complete all tasks in 9 days is as follows:
Day 1: Complete the 0th task.
Day 2: Complete the 1st task.
Day 3: Take a break.
Day 4: Take a break.
Day 5: Complete the 2nd task.
Day 6: Complete the 3rd task.
Day 7: Take a break.
Day 8: Complete the 4th task.
Day 9: Complete the 5th task.
It can be shown that the tasks cannot be completed in less than 9 days.
Example 2:

Input: tasks = [5,8,8,5], space = 2
Output: 6
Explanation:
One way to complete all tasks in 6 days is as follows:
Day 1: Complete the 0th task.
Day 2: Complete the 1st task.
Day 3: Take a break.
Day 4: Take a break.
Day 5: Complete the 2nd task.
Day 6: Complete the 3rd task.
It can be shown that the tasks cannot be completed in less than 6 days.
 

Constraints:

1 <= tasks.length <= 10^5
1 <= tasks[i] <= 10^9
1 <= space <= tasks.length
*/


// simulate the process
// time O(N), space O(N)
class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        // simulate the process
        long long days = 0;
        unordered_map<int,long long> prevTasks;
        for(int t : tasks) {
            ++days;
            auto it = prevTasks.find(t);
            if(it != prevTasks.end()) {
                int gap = days - it->second -1 ;
                if(gap <= space)
                    days += space-gap;
            }
            prevTasks[t] = days;
        }

        return days;
    }
};

// I try to build a window to only store tasks that may block other ones, but it actually uses more memory
class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        // simulate the process
        long long days = 0;
        unordered_map<int,long long> prevTasks;
        queue<int> effTasks;  // tasks within space window that may block same type of task
        for(int t : tasks) {
            ++days;
            auto it = prevTasks.find(t);
            if(it != prevTasks.end()) {
                int gap = days - it->second -1 ;
                if(gap <= space)
                    days += space-gap;
            }

            // clean up non-blocking tasks
            while(!effTasks.empty() && days-prevTasks[effTasks.front()] >= space) {
                prevTasks.erase(effTasks.front());
                effTasks.pop();
            }

            // add current task
            effTasks.push(t);
            prevTasks[t] = days;
        }

        return days;
    }
};


// ref solution -- very neat
long long taskSchedulerII(vector<int>& tasks, int space) {
    unordered_map<int, long long> last;
    long long res = 0;
    for (int a: tasks)
        if (last.count(a))
            last[a] = res = max(res, last[a] + space) + 1;
        else
            last[a] = ++res;
    return res;
}


// ref solution: store next available day of a given task
long long taskSchedulerII(vector<int>& tasks, int space) {
    unordered_map<int, long long> next;
    long long res = 0;
    for (int a : tasks)
        next[a] = (res = max(next[a], res + 1)) + space + 1;
    return res;
}
