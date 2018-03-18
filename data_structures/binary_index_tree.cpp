#include "../leetcode/common/common.h"

using namespace std;

// 1-D binary index tree
// https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
class BinaryIndexTree
{
public:
  BinaryIndexTree(const vector<int> &array) {
    _array.resize(array.size(), 0);  // since _array is to be updated through tree building, it must be all zeros initially
    _tree.resize(array.size()+1, 0);

    // build the tree
    for(int i=0; i<array.size(); ++i)
      update(i, array[i]);
  }

  // update _array[i] to val
  void update(int index, int val) {
    int delta = val - _array[index];
    _array[index] = val;
    for(int i=index+1; i<_tree.size(); i+=(i&-i))
      _tree[i] += delta;
  };

  // sum of range [0:index]
  int querySum(int qe) {
    int sum = 0;
    for(int i=qe+1; i>0; i-=(i&-i))
      sum += _tree[i];
    return sum;
  }

  // sum of range [s:e]
  int querySum(int qs, int qe) {
    return querySum(qe) - querySum(qs) + _array[qs];
  }

private:
  vector<int> _array;
  vector<int> _tree;  // _tree[0] is the dummy root that has value 0
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
  BinaryIndexTree bit(array);
  NaiveGolden golden(array);
  for(int i=0; i<10; ++i) {
    int qs = rand() % sz;
    int qe = qs + rand()%(sz-qs);
    int sum1 = bit.querySum(qs, qe);
    int sum2 = golden.querySum(qs, qe);
    cout << "querySum(" << qs << "," << qe << ") -- " << sum1 << " vs. " << sum2 << endl;

    int index = rand() % sz;
    int val = rand() % 200 - 100;
    cout << "update(" << index << "," << val << ")" << endl;
    bit.update(index, val);
    golden.update(index, val);
  }

  return 0;
}
