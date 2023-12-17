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

// Uses an array in cyclic manner to keep track of data elements in current window
class MovingAverage {
public:
    MovingAverage(int size) : _window(size), _data(size,0), _size(0), _sum(0), _head(0){
        
    }
    
    double next(int val) {
        if(_size < _window)
            ++_size;

        _sum = _sum - _data[_head] + val;
        _data[_head] = val;  // after the element is removed, original head becomes the tail
        _head = (_head+1)%_window;
        return (double)_sum/_size;
    }

private:
    const int _window;
    int _size;
    int _sum;
    vector<int> _data;  // used in a cyclic manner
    int _head;  // this element will be moved out of the window when new element is added
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
