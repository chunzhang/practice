/*
  You have 4 cards each containing a number from 1 to 9. You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.

  Example 1:
  Input: [4, 1, 8, 7]
  Output: True
  Explanation: (8-4) * (7-1) = 24
  Example 2:
  Input: [1, 2, 1, 2]
  Output: False
  Note:
  The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
  Every operation done is between two numbers. In particular, we cannot use - as a unary operator. For example, with [1, 1, 1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
  You cannot concatenate numbers together. For example, if the input is [1, 2, 1, 2], we cannot write this as 12 + 12.
*/

// Solution by searching post-fix expression computation
class Solution {
public:
  bool judgePoint24(vector<int>& nums) {
    _ops.push_back('+');
    _ops.push_back('-');
    _ops.push_back('*');
    _ops.push_back('/');
        
    vector<char> expr;
    return helper(nums, expr, 0, 0);
  }
    
private:
  bool helper(vector<int> &nums, vector<char> &expr, int nNum, int nOp) {
    if(nNum==4 && nOp==3) {
      double res = eval(expr);
      return abs(res-24.0) < 1e-6;
    }
        
    // Try select a number
    for(int i=0; i<nums.size(); ++i) {
      int n = nums[i];
      if(n) {
	nums[i] = 0;
	expr.push_back('0'+n);
	if(helper(nums, expr, nNum+1, nOp))
	  return true;
	expr.pop_back();
	nums[i] = n;
      }
    }
        
    // Try select an operator
    if(nNum-nOp >= 2) {
      for(char op : _ops) {
	expr.push_back(op);
	if(helper(nums, expr, nNum, nOp+1))
	  return true;
	expr.pop_back();
      }
    }
        
    return false;
  }
    
  // evaluate post-fix expression
  double eval(const vector<char> &expr) {
    stack<double> s;
    for(int i=0; i<expr.size(); ++i) {
      char c = expr[i];
      if(c>='0' && c<='9') {
	s.push(c - '0');
      }
      else {
	double n2 = s.top();
	s.pop();
	double n1 = s.top();
	s.pop();
	double res = -1;
	if(c=='+')
	  res = n1 + n2;
	else if(c=='-')
	  res = n1 - n2;
	else if(c=='*')
	  res = n1 * n2;
	else if(c=='/' && n2)
	  res = n1 / n2;
                
	if(res == -1)
	  return -1;
	s.push(res);
      }
    }
        
    return s.top();
  }
    
private:
  vector<char> _ops;
};

// A better DFS solution
// -- Every time, pick two numbers and compute them
// -- Utilize commutative of + and - operations for some pruning
class Solution {
public:
  bool judgePoint24(vector<int>& nums) {
    vector<double> numsDouble(nums.begin(), nums.end());
    return solve(numsDouble);
  }
    
private:
  bool solve(const vector<double> nums) {
    if(nums.size() == 1)
      return abs(nums[0]-24.0) < 1e-6;  // to account for rounding errors
        
    // pick to number, compute them, and recursively search forward
    for(int i=0; i<nums.size(); ++i) {
      for(int j=0; j<nums.size(); ++j) {
	if(i == j)    // must pick two different numbers
	  continue;
            
	vector<double> nums2;  // numbers for next level search
	for(int k=0; k<nums.size(); ++k)
	  if(k!=i && k!=j)
	    nums2.push_back(nums[k]);
            
	// +, *, -, /
	for(int k=0; k<4; ++k) {
	  if(k<2 && i>j)  // + and - operations are commutative, so don't double computing
	    continue;
	  double res = -1;
	  if(k==0)
	    res = nums[i] + nums[j];
	  else if(k==1)
	    res = nums[i] * nums[j];
	  else if(k==2)
	    res = nums[i] - nums[j];
	  else if(k==3 && nums[j]!=0)
	    res = nums[i] / nums[j];
                
	  if(res == -1)
	    continue;
                    
	  nums2.push_back(res);
	  if(solve(nums2))
	    return true;
	  nums2.pop_back();
	}
      }
    }
        
    return false;
  }
};
