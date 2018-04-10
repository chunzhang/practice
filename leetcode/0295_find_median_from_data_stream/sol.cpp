/*
  Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

  Examples: 
  [2,3,4] , the median is 3

  [2,3], the median is (2 + 3) / 2 = 2.5

  Design a data structure that supports the following two operations:

  void addNum(int num) - Add a integer number from the data stream to the data structure.
  double findMedian() - Return the median of all elements so far.
  For example:

  addNum(1)
  addNum(2)
  findMedian() -> 1.5
  addNum(3) 
  findMedian() -> 2
*/

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */

// Use max-heap to keep lower half of elements, and min-heap to keep upper half of elements
// Let lower half has at most one more element than upper half
class MedianFinder {
public:
  /** initialize your data structure here. */
  MedianFinder() {
  }
    
  void addNum(int num) {
    if(_lower.empty() || num<=_lower.top()) {
      _lower.push(num);
      if(_lower.size() > _upper.size()+1) {
	_upper.push(_lower.top());
	_lower.pop();
      }
    }
    else {
      _upper.push(num);
      if(_upper.size() > _lower.size()) {
	_lower.push(_upper.top());
	_upper.pop();
      }
    }
  }
    
  double findMedian() {
    return _lower.size()==_upper.size() ? (double)(_lower.top()+_upper.top())/2 : _lower.top();
  }

private:
  priority_queue<int> _lower;  // max heap
  priority_queue<int, vector<int>, greater<int>> _upper;  // min heap
};

// A more concise version of using two heaps
class MedianFinder {
public:
  /** initialize your data structure here. */
  MedianFinder() {
  }
    
  void addNum(int num) {
    _lower.push(num);
        
    // validate two halves
    _upper.push(_lower.top());
    _lower.pop();
        
    // validate size of two halves
    if(_lower.size() < _upper.size()) {
      _lower.push(_upper.top());
      _upper.pop();
    }
  }
    
  double findMedian() {
    return _lower.size()==_upper.size() ? (double)(_lower.top()+_upper.top())/2 : _lower.top();
  }

private:
  priority_queue<int> _lower;  // max heap
  priority_queue<int, vector<int>, greater<int>> _upper;  // min heap
};

// Use BST to keep order
class MedianFinder {
public:
  /** initialize your data structure here. */
  MedianFinder() {
        
  }
    
  void addNum(int num) {
    _tree.insert(num);  // In case of element equivalence, the element is inserted in upper_bound()
    if(_tree.size() == 1) {
      _itL = _itH = _tree.begin();
      return;
    }
        
    if(num >= *_itH) {  // num is inserted after itH
      _itL!=_itH ? ++_itL : ++_itH;
    }
    else if(num < *_itL) {  // num is inserted before itH
      _itL!=_itH ? --_itH : --_itL;
    }
    else {  // num is inserted between itL and itH (note here we can't have itL==itH)
      ++_itL;
      --_itH;
    }
  }
    
  double findMedian() {
    return 0.5*(*_itL + *_itH);
  }

private:
  multiset<int> _tree;
  multiset<int>::const_iterator _itL;
  multiset<int>::const_iterator _itH;
};
