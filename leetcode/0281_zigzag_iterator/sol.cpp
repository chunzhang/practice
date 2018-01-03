/*
Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question - Update (2015-09-18):
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

[1,2,3]
[4,5,6,7]
[8,9]
It should return [1,4,8,2,5,9,3,6,7].
*/


/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

#include "../common/common.h"

using namespace std;

// Support any number of input vectors
class ZigzagIterator {
public:
  ZigzagIterator(const vector<vector<int>> &vecs) : data(vecs)
  {
    for(int i=0; i<data.size(); ++i)
      if(data[i].size())
	q.push({i,0});    
  }

  int next() {
    pair<int,int> cur = q.front();
    q.pop();
    int val = data[cur.first][cur.second];
    if(++cur.second < data[cur.first].size())
      q.push(cur);
    return val;
  }

  bool hasNext() {
    return !q.empty();
  }

private:
  queue<pair<int,int>> q;  // data[pair.first][pair.last] is the next element
  const vector<vector<int>> &data;
};


// This works, but is slow...
class ZigzagIterator2 {
public:
  ZigzagIterator2(vector<int>& v1, vector<int>& v2) 
  {
    vecs.push_back(v1);
    vecsIdx.push_back(0);
    vecs.push_back(v2);
    vecsIdx.push_back(0);
    idx = vecs[0].size() ? 0 : 1;
  }

  int next() {
    int val = vecs[idx][vecsIdx[idx]++];
    int idxNext = idx ^ 0x1;
    if(vecsIdx[idxNext] < vecs[idxNext].size())
      idx = idxNext;
    return val;
  }

  bool hasNext() {
    return vecsIdx[idx] < vecs[idx].size();
  }

private:
  vector<vector<int>> vecs;
  vector<int> vecsIdx;
  int idx;
};

int main()
{
  vector<vector<int>> vecs = {{1,2,3}, {4,5,6,7}, {8,9}};
  ZigzagIterator zigzag(vecs);
  while(zigzag.hasNext())
    cout << zigzag.next() << endl;

  return 0;
}
