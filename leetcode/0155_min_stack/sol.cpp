/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */

#include "../common/common.h"

using namespace std;

class MinStack2 {
public:
  /** initialize your data structure here. */
  MinStack2() {
    // Dummy
  }
    
  void push(int x) {
    s.push(x);
    if(sMin.empty() || x<=sMin.top())
      sMin.push(x);
  }
    
  void pop() {
    if(s.empty())
      return;
    int x = s.top();
    s.pop();
    if(x == sMin.top())
      sMin.pop();
  }
    
  int top() {
    if(s.empty())
      return -1;
    return s.top();
  }
    
  int getMin() {
    if(sMin.empty())
      return -1;
    return sMin.top();
  }

private:
  stack<int> s;
  stack<int> sMin;  // with top being the min val so far
};

// solution using only one stack -- https://discuss.leetcode.com/topic/4953/share-my-java-solution-with-only-one-stack
class MinStack {
public:
  /** initialize your data structure here. */
  MinStack() {
    min = 0;
  }
    
  void push(int x) {
    if(deltas.empty()) {
      deltas.push(0);
      min = x;
    }
    else {
      deltas.push(x-min);
      if(x < min)
	min = x;
    }

    cout << "deltas.top() " << deltas.top() << endl;
  }
    
  void pop() {
    long long delta = deltas.top();
    deltas.pop();
    if(delta < 0)  // the poped top element is the min
      min = min - delta;  // recover previous min
  }
    
  int top() {
    long long delta = deltas.top();
    if(delta < 0)
      return min;
    else
      return min+delta;
  }
    
  int getMin() {
    return min;
  }

private:
  stack<long long> deltas;  // deltas to min -- since we're using "long long" instead of "int", not actually saving much spaces
  long long min;
};

int main()
{
  MinStack minStack;

  /*
  minStack.push(2147483646);
  minStack.push(2147483646);
  minStack.push(2147483647);
  cout << minStack.top() << endl;
  minStack.pop();
  cout << minStack.getMin() << endl;
  minStack.pop();
  cout << minStack.getMin() << endl;
  minStack.pop();
  */
  
  minStack.push(2147483647);
  //cout << minStack.top() << endl;
  //cout << minStack.getMin() << endl;
  minStack.push(-2147483648);
  //cout << minStack.top() << endl;
  //cout << minStack.getMin() << endl;
  minStack.pop();
  cout << minStack.getMin() << endl;
  
  /*
  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  cout << minStack.getMin() << endl;;
  minStack.pop();
  cout << minStack.top() << endl;
  cout << minStack.getMin() << endl;
  */
  
  return 0;
}
