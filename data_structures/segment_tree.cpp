#include <cmath>
#include <cstdlib>
#include "../leetcode/common/common.h"

using namespace std;

// Segment tree for range sum query
// -- https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
class SegmentTree
{
public:
  SegmentTree(const vector<int> &array) {
    _array = array;
    int cap = ceil(log2(array.size()));
    int sz = 2 * pow(2, cap) - 1;
    _tree.resize(sz, 0);
    _build(0, 0, _array.size()-1);
    printVector(_tree);
  }

  int querySum(int qs, int qe) {
    return _querySum(0, 0, _array.size()-1, qs, qe);
  }

  void update(int index, int val) {
    int delta = val - _array[index];
    _array[index] = val;
    _update(0, 0, _array.size()-1, index, delta);
  }

private:
  // Build the tree recursively
  int _build(int cur,         // current node
	     int s, int e)    // current node range start/end
  {
    if(s == e) {
      _tree[cur] = _array[s];
      return _tree[cur];
    }

    int mid = (s + e) / 2;
    _tree[cur] = _build(cur*2+1, s, mid) + _build(cur*2+2, mid+1, e);  // segment of each node is implicitly represented
    return _tree[cur];
  }

  int _querySum(int cur,          // current node
		int s, int e,     // current node range start/end
		int qs, int qe)   // query range start/end
  {
    if(qs<=s && qe>=e) {  // full overlap
      return _tree[cur];
    }
    else if(e<qs || s>qe) {  // no overlap
      return 0;
    }
    else {
      int mid = (s + e) / 2;
      return _querySum(cur*2+1, s, mid, qs, qe) + _querySum(cur*2+2, mid+1, e, qs, qe);
    }    
  }

  void _update(int cur,         // current node
	       int s, int e,    // current node range start/end
	       int index,       // index of updated node in the original array
	       int delta)       // value update delta
  {
    if(index<s || index>e)
      return;
    _tree[cur] += delta;
    if(s == e)  // leaf reached
      return;
    int mid = (s + e) / 2;
    _update(cur*2+1, s, mid, index, delta);
    _update(cur*2+2, mid+1, e, index, delta);
  }
  
private:
  vector<int> _array;  // original array
  vector<int> _tree;   // array-based segment tree
};

class NaiveGolden
{
public:
  NaiveGolden(const vector<int> &array) {
    _array = array;
  }

  int querySum(int qs, int qe) {
    int sum = 0;
    for(int i=qs; i<=qe; ++i)
      sum += _array[i];
    return sum;
  }

  void update(int index, int val) {
    _array[index] = val;
  }

private:
  vector<int> _array;
};

int main(int argc, char *argv[])
{
  vector<int> array = readVector(argc, argv);
  int sz = array.size();
  printVector(array);
  SegmentTree st(array);
  NaiveGolden golden(array);
  for(int i=0; i<10; ++i) {
    int qs = rand() % sz;
    int qe = qs + rand()%(sz-qs);
    int sum1 = st.querySum(qs, qe);
    int sum2 = golden.querySum(qs, qe);
    cout << "querySum(" << qs << "," << qe << ") -- " << sum1 << " vs. " << sum2 << endl;

    int index = rand() % sz;
    int val = rand() % 200 - 100;
    cout << "update(" << index << "," << val << ")" << endl;
    st.update(index, val);
    golden.update(index, val);
  }

  return 0;
}
