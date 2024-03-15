/*

Given a positive integer num, return true if num is a perfect square or false otherwise.

A perfect square is an integer that is the square of an integer. In other words, it is the product of some integer with itself.

You must not use any built-in library function, such as sqrt.

Example 1:

Input: num = 16
Output: true
Explanation: We return true because 4 * 4 = 16 and 4 is an integer.

Example 2:

Input: num = 14
Output: false
Explanation: We return false because 3.742 * 3.742 = 14 and 3.742 is not an integer.
 

Constraints:

1 <= num <= 2^31 - 1
*/

// binary search
class Solution {
public:
    bool isPerfectSquare(int num) {
        long l = 1;
        long r = (long)num+1;
        while(l<r) {
            long mid = l + (r-l)/2;
            long sq = mid*mid;
            if(sq == num)
                return true;
            else if(sq > num)
                r = mid;
            else
                l = mid+1;
        }
        return false;
    }
};

// newton's method: solving x^2-num = 0 (in Java)
class Solution {
  public boolean isPerfectSquare(int num) {
    if (num < 2) return true;

    long x = num / 2;
    while (x * x > num) {
      x = (x + num / x) / 2;
    }
    return (x * x == num);
  }
}
