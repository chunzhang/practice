/*
  Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

  For example,
  MovingAverage m = new MovingAverage(3);
  m.next(1) = 1
  m.next(10) = (1 + 10) / 2
  m.next(3) = (1 + 10 + 3) / 3
  m.next(5) = (10 + 3 + 5) / 3
*/

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */

#include "../common/common.h"

using namespace std;

// This solution keeps a long long int for current summation; in addition, it uses an array in cyclic manner as queue
class MovingAverage {
public:
  /** Initialize your data structure here. */
  MovingAverage(int size) : _data(size,0),
			    _tail(0),
			    _cap(size),
			    _sz(0),
			    _sum(0)
  {
    // Dummy
  }
    
  double next(int val) {
    _sum = _sum - _data[_tail] + val;
    _data[_tail++] = val;
    _tail %= _cap;
    if(++_sz > _cap)
      _sz = _cap;
    return (double)_sum / _sz;
  }

private:
  vector<int> _data;  // used as queue
  int _tail;  // tail of the queue
  int _cap;
  int _sz;
  long long int _sum;  // to avoid integer overflow  
};

// This solution keeps a double of current average -- requires a multiplication to compute next average
class MovingAverage2 {
public:
  /** Initialize your data structure here. */
  MovingAverage2(int size) {
    _cap = size;
    _ave = 0.0;
  }
    
  double next(int val) {
    double org = _ave * _data.size();
    _data.push(val);
    int del = 0;
    if(_data.size() > _cap) {
      del = _data.front();
      _data.pop();
    }
    _ave = (org - del + val) / _data.size();
    return _ave;
  }

private:
  int _cap;
  double _ave;
  queue<int> _data;
};

int main(int argc, char *argv[])
{
  vector<int> data = readVector(argc, argv);
  MovingAverage average(data[0]);
  for(int i=1; i<data.size(); ++i) {
    cout << "data.next(" << data[i] << ") is " << average.next(data[i]) << endl;
  }

  return 0;
}
