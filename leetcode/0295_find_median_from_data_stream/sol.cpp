/*
  The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value and the median is the mean of the two middle values.

  For example, for arr = [2,3,4], the median is 3.
  For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
  Implement the MedianFinder class:

  MedianFinder() initializes the MedianFinder object.
  void addNum(int num) adds the integer num from the data stream to the data structure.
  double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
 

  Example 1:

  Input
  ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
  [[], [1], [2], [], [3], []]
  Output
  [null, null, null, 1.5, null, 2.0]

  Explanation
  MedianFinder medianFinder = new MedianFinder();
  medianFinder.addNum(1);    // arr = [1]
  medianFinder.addNum(2);    // arr = [1, 2]
  medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
  medianFinder.addNum(3);    // arr[1, 2, 3]
  medianFinder.findMedian(); // return 2.0
 

  Constraints:

  -10^5 <= num <= 10^5
  There will be at least one element in the data structure before calling findMedian.
  At most 5 * 104 calls will be made to addNum and findMedian.
 

  Follow up:

  If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
  If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
*/

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */

// Use max-heap to keep lower half of elements, and min-heap to keep upper half of elements
// Let lower half has at most one more element than upper half
// time complexity: addNum--O(lgN), findMedian--O(1)
// space complexity: O(N)
class MedianFinder {
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(_pqMax.size() == _pqMin.size()) {  // insert into _pqMax
            if(_pqMin.empty() || _pqMin.top()>=num) {
                _pqMax.push(num);
            }
            else {
                _pqMax.push(_pqMin.top());
                _pqMin.pop();
                _pqMin.push(num);
            }
        }
        else {  // insert into _pqMin
            if(_pqMax.top() <= num) {
                _pqMin.push(num);
            }
            else {
                _pqMin.push(_pqMax.top());
                _pqMax.pop();
                _pqMax.push(num);
            }
        }
    }
    
    double findMedian() {
        if((_pqMax.size()+_pqMin.size())%2 == 1) {
            return _pqMax.top();
        }
        else {
            return (_pqMax.top()+_pqMin.top())/2.0;
        }
    }
    
private:
    priority_queue<int,vector<int>> _pqMax;  // for lower half
    priority_queue<int,vector<int>,greater<int>> _pqMin;  // for higher half
};


// use max-heap and min-heap -- another impl
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
