/*
  Design a hit counter which counts the number of hits received in the past 5 minutes.

  Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made to the system in chronological order (ie, the timestamp is monotonically increasing). You may assume that the earliest timestamp starts at 1.

  It is possible that several hits arrive roughly at the same time.

  Example:
  HitCounter counter = new HitCounter();

  // hit at timestamp 1.
  counter.hit(1);

  // hit at timestamp 2.
  counter.hit(2);

  // hit at timestamp 3.
  counter.hit(3);

  // get hits at timestamp 4, should return 3.
  counter.getHits(4);

  // hit at timestamp 300.
  counter.hit(300);

  // get hits at timestamp 300, should return 4.
  counter.getHits(300);

  // get hits at timestamp 301, should return 3.
  counter.getHits(301); 
  Follow up:
  What if the number of hits per second could be very large? Does your design scale?
*/

#include "../common/common.h"

using namespace std;

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter obj = new HitCounter();
 * obj.hit(timestamp);
 * int param_2 = obj.getHits(timestamp);
 */

// Solution 1 -- use queue
class HitCounter {
public:
  /** Initialize your data structure here. */
  HitCounter() {
    _count = 0;
  }
    
  /** Record a hit.
      @param timestamp - The current timestamp (in seconds granularity). */
  void hit(int timestamp) {
    update(timestamp);
    if(_q.size() && _q.back().first==timestamp)
      _q.back().second += 1;
    else
      _q.push(make_pair(timestamp,1));
    ++_count;
  }
    
  /** Return the number of hits in the past 5 minutes.
      @param timestamp - The current timestamp (in seconds granularity). */
  int getHits(int timestamp) {
    update(timestamp);
    return _count;
  }

private:
  // remove out-dated hits
  void update(int timestamp) {
    while(_q.size() && _q.front().first+300<=timestamp) {
      _count -= _q.front().second;
      _q.pop();
    }
  }
    
private:
  queue<pair<int,int>> _q;
  int _count;
};

// Implement my own cyclic queue
template <class T>
class MyCyclicQueue {
public:
  MyCyclicQueue(int capacity) : _data(capacity),
				_capacity(capacity),
				_start(0),
				_end(0),
				_size(0)     
  {
    // Dummy
  }
    
  bool empty() const {
    return _size == 0;
  }
    
  bool full() const {
    return _size == _capacity;
  }
    
  int size() const {
    return _size;
  }
    
  void push(const T &elem) {
    if(full()) {
      throw out_of_range("Fail to push element -- queue is full");
    }
    _data[_end] = elem;
    _end = (_end + 1) % _capacity;
    ++_size;
  }
    
  void pop() {
    if(empty()) {
      throw out_of_range("Fail to pop element -- queue is empty");
    }
    _start = (_start + 1) % _capacity;
    --_size;
  }
    
  T& front() {
    if(empty()) {
      throw out_of_range("Fail to get front element -- queue is empty");
    }
    return _data[_start];
  }
    
  T& back() {
    if(empty()) {
      throw out_of_range("Fail to get back element -- queue is empty");
    }
    return _data[_end];
  }
    
private:
  vector<T> _data;
  int _capacity;
  int _start;
  int _end;
  int _size;
};

class HitCounter2 {
public:
  /** Initialize your data structure here. */
  HitCounter2() : _q(300)
  {
    _count = 0;
  }
    
  /** Record a hit.
      @param timestamp - The current timestamp (in seconds granularity). */
  void hit(int timestamp) {
    update(timestamp);
    if(_q.size() && _q.back().first==timestamp)
      _q.back().second += 1;
    else
      _q.push(make_pair(timestamp,1));
    ++_count;
  }
    
  /** Return the number of hits in the past 5 minutes.
      @param timestamp - The current timestamp (in seconds granularity). */
  int getHits(int timestamp) {
    update(timestamp);
    return _count;
  }

private:
  // remove out-dated hits
  void update(int timestamp) {
    while(_q.size() && _q.front().first+300<=timestamp) {
      _count -= _q.front().second;
      _q.pop();
    }
  }
    
private:
  MyCyclicQueue<pair<int,int>> _q;
  int _count;
};

int main()
{
  HitCounter2 counter;
  counter.hit(1);
  
  counter.hit(2); 
  counter.hit(3);
  cout << counter.getHits(4) << endl;
  counter.hit(300);
  cout << counter.getHits(300) << endl;
  cout << counter.getHits(301) << endl; 

  return 0;
}
