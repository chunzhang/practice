/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".
*/

class Solution {
public:
  string fractionToDecimal(int numerator, int denominator) {
    bool negative = false;
    if(numerator<0&&denominator>0 || numerator>0&&denominator<0)
      negative = true;
    long long n = abs((long long)numerator);
    long long m = abs((long long)denominator);
        
    unsigned long long intPart = n / m;
    n -= m*intPart;  // n < m upon here
    int loopStart = -1;
    map<int,int> nums;  // for loop detection
    string frac;
    while(n) {
      if(nums.find(n) != nums.end()) {
	loopStart = nums[n];  // starting index of loop in the frac string
	break;
      }
      nums[n] = frac.size();
      n *= 10;
      int dig = n / m;
      n -= m * dig;
      frac.push_back('0'+dig);
    }
        
    string res = (negative?"-":"") + to_string(intPart);
    if(frac.size()) {
      if(loopStart != -1)
	res += "." + frac.substr(0, loopStart) + "(" + frac.substr(loopStart) + ")";
      else
	res += "." + frac;
    }
        
    return res;
  }
};

/*
Official solution:

public String fractionToDecimal(int numerator, int denominator) {
    if (numerator == 0) {
        return "0";
    }
    StringBuilder fraction = new StringBuilder();
    // If either one is negative (not both)
    if (numerator < 0 ^ denominator < 0) {
        fraction.append("-");
    }
    // Convert to Long or else abs(-2147483648) overflows
    long dividend = Math.abs(Long.valueOf(numerator));
    long divisor = Math.abs(Long.valueOf(denominator));
    fraction.append(String.valueOf(dividend / divisor));
    long remainder = dividend % divisor;
    if (remainder == 0) {
        return fraction.toString();
    }
    fraction.append(".");
    Map<Long, Integer> map = new HashMap<>();
    while (remainder != 0) {
        if (map.containsKey(remainder)) {
            fraction.insert(map.get(remainder), "(");
            fraction.append(")");
            break;
        }
        map.put(remainder, fraction.length());
        remainder *= 10;
        fraction.append(String.valueOf(remainder / divisor));
        remainder %= divisor;
    }
    return fraction.toString();
}
*/
