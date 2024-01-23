/*
Facebook/Apple/Twitter/Yandex/Netflix/LinkedIn

You are given a nested list of integers nestedList. Each element is either an integer or a list whose elements may also be integers or other lists. Implement an iterator to flatten it.

Implement the NestedIterator class:

NestedIterator(List<NestedInteger> nestedList) Initializes the iterator with the nested list nestedList.
int next() Returns the next integer in the nested list.
boolean hasNext() Returns true if there are still some integers in the nested list and false otherwise.
Your code will be tested with the following pseudocode:

initialize iterator with nestedList
res = []
while iterator.hasNext()
    append iterator.next() to the end of res
return res
If res matches the expected flattened list, then your code will be judged as correct.

 

Example 1:

Input: nestedList = [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].
Example 2:

Input: nestedList = [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].
 

Constraints:

1 <= nestedList.length <= 500
The values of the integers in the nested list is in the range [-10^6, 10^6].
*/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

// Sol 1: brute-force pre-build the flattern integer vector through recursion
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        build(nestedList);
        m_cur = 0;
    }
    
    int next() {
        return m_nums[m_cur++];
    }
    
    bool hasNext() {
        return m_cur < m_nums.size();
    }

private:
    void build(const vector<NestedInteger> &nestedList) {
        for(const NestedInteger &ni : nestedList) {
            if(ni.isInteger())
                m_nums.push_back(ni.getInteger());
            else
                build(ni.getList());
        }
    }

private:
    vector<int> m_nums;
    int m_cur;
};


// Sol 2: iterative approach
// -- key is to let hasNext() update the stack in a way such that top element is an Integer
// -- if stack top is an nested array, push them (in reverse order) to the stack until stack top is an Integer
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(int i=nestedList.size()-1; i>=0; --i)
            m_st.push(&nestedList[i]);
    }
    
    int next() {
        int num = m_st.top()->getInteger();
        m_st.pop();
        return num;
    }
    
    bool hasNext() {  // makes stack top an Integer
        while(m_st.size() && !m_st.top()->isInteger()) {
            const vector<NestedInteger> &vec = m_st.top()->getList();
            m_st.pop();
            for(int i=vec.size()-1; i>=0; --i) {
                m_st.push(&vec[i]);
            }
        }

        return m_st.size();
    }

private:
    stack<const NestedInteger*> m_st;
};


// Sol 3: better iterative approach
// -- key is to let hasNext() update the stack in a way such that top element is an Integer
// -- keeps the vector<NestedInteger> and the next element index at stack top
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        m_st.push(nestedList);
        m_st_idx.push(0);
    }
    
    int next() {  // simply get the number as stack top is guaranteed to be Integer
        int num = m_st.top()[m_st_idx.top()].getInteger();
        m_st_idx.top()++;  // move to next element
        return num;
    }
    
    bool hasNext() {  // guarantees that stack top is an Integer
        prepareInteger();
        return m_st.size();
    }

private:
    void prepareInteger() {  // make stack top an Integer type
        while(m_st.size()) {
            int curIdx = m_st_idx.top();
            if(curIdx >= m_st.top().size()) {  // current vector is fully consumed
                m_st.pop();
                m_st_idx.pop();
                continue;
            }

            if(m_st.top()[curIdx].isInteger())  // finished: stack top is an Integer
                break;
            else {  // stack top is vector<NestedInteger>, push another level on the stack
                m_st_idx.top()++;  // move to next element as the vector<NestedInteger> will be pushed to stack
                m_st.push(m_st.top()[curIdx].getList());
                m_st_idx.push(0);  // starting index of next 
            }
        }
    }

private:
    stack<vector<NestedInteger>> m_st;
    stack<int> m_st_idx;
};
