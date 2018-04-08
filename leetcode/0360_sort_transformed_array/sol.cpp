/*
  Given a sorted array of integers nums and integer values a, b and c. Apply a quadratic function of the form f(x) = ax2 + bx + c to each element x in the array.

  The returned array must be in sorted order.

  Expected time complexity: O(n)

  Example:
  nums = [-4, -2, 2, 4], a = 1, b = 3, c = 5,

  Result: [3, 9, 15, 33]

  nums = [-4, -2, 2, 4], a = -1, b = 3, c = 5

  Result: [-23, -5, 1, 7]
*/

// My first solution
// -- Expand from the symmetric axis
// -- This is good but little over engineering, and we have to
//    consider the case when a==0 separately
class Solution {
public:
  vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
    vector<int> res(nums.size(), 0);
    if(a == 0) {
      for(int i=0; i<nums.size(); ++i)
	res[i] = nums[i] * b + c;
      if(b < 0)
	reverse(res.begin(), res.end());
      return res;
    }
        
    double sym = b/(-2.0*a);  // symmetrical axis of the quadratic function
    auto it2 = lower_bound(nums.begin(), nums.end(), sym);  // first element greater or equal to sym
    auto it1 = it2 - 1;
    for(int i=0; i<nums.size(); ++i) {
      int num;
      if(it1>=nums.begin() && it2<nums.end()) {
	if(abs(*it1-sym) <= abs(*it2-sym))
	  num = *(it1--);
	else
	  num = *(it2++);
      }
      else if(it1>=nums.begin()) {
	num = *(it1--);
      }
      else if(it2<nums.end()) {
	num = *(it2++);
      }
            
      res[i] = a*num*num + b*num + c;
    }
        
    if(a < 0)
      reverse(res.begin(), res.end());
        
    return res;
  }
};

// Best solutiona
// -- Max/min value can only happen at the two end points!
// -- Case a==0 is covered implicitly
class Solution {
public:
  // Idea is that the next value can only be picked from two current ending points
  // -- Case when a==0 is covered implicitly
  vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
    vector<int> res(nums.size());
    int index = (a>=0 ? nums.size()-1 : 0);  // if a>=0, ending point is the next max value
    for(int i=0,j=nums.size()-1; i<=j; ) {
      int num1 = quad(nums[i], a, b, c);
      int num2 = quad(nums[j], a, b, c);
      if(a >= 0) {
	// pick from max to min
	if(num1 >= num2) {
	  res[index--] = num1;
	  ++i;
	}
	else {
	  res[index--] = num2;
	  --j;
	}
      }
      else {
	// pick from min to max
	if(num1 <= num2) {
	  res[index++] = num1;
	  ++i;
	}
	else {
	  res[index++] = num2;
	  --j;
	}
      }
    }
        
    return res;
  }
    
private:
  int quad(int num, int a, int b, int c) {
    return a*num*num + b*num + c;
  }
};
