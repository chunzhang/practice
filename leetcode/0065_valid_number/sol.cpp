/*
  A valid number can be split up into these components (in order):

  A decimal number or an integer.
  (Optional) An 'e' or 'E', followed by an integer.
  A decimal number can be split up into these components (in order):

  (Optional) A sign character (either '+' or '-').
  One of the following formats:
  One or more digits, followed by a dot '.'.
  One or more digits, followed by a dot '.', followed by one or more digits.
  A dot '.', followed by one or more digits.
  An integer can be split up into these components (in order):

  (Optional) A sign character (either '+' or '-').
  One or more digits.
  For example, all the following are valid numbers: ["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"], while the following are not valid numbers: ["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"].

  Given a string s, return true if s is a valid number.

 

  Example 1:

  Input: s = "0"
  Output: true
  Example 2:

  Input: s = "e"
  Output: false
  Example 3:

  Input: s = "."
  Output: false
 

  Constraints:

  1 <= s.length <= 20
  s consists of only English letters (both uppercase and lowercase), digits (0-9), plus '+', minus '-', or dot '.'.
*/

// My latest solution
class Solution {
public:
    bool isNumber(string s) {
        int cur = 0;

        bool isValidNum1 = isValidNum(s, cur, true);
        if(cur == s.size())
            return isValidNum1;

        if(s[cur] == '.') {
            ++cur;
            bool isValidNum2 = isValidNum(s, cur, false);
            if(!isValidNum1 && !isValidNum2)
                return false;
        }
        else if(!isValidNum1)
            return false;

        if(cur == s.size())
            return true;

        if(s[cur]=='e' || s[cur]=='E') {
            ++cur;
            bool isValidNum3 = isValidNum(s, cur, true);
            if(!isValidNum3)
                return false;
        }

        return cur==s.size();
    }

private:
    // help function to extract an integer part with optional sign
    bool isValidNum(const string &s, int &cur, bool includeSign) {
        // sign can only appear at the beginning
        if(cur<s.size() && (s[cur]=='+'||s[cur]=='-')) {
            if(includeSign)
                ++cur;
            else
                return false;
        }

        int digLen = 0;
        while(cur<s.size() && isdigit(s[cur])) {
            ++digLen;
            ++cur;
        }

        return digLen;
    }
};


// My older solution
class Solution {
public:
    bool isNumber(string s) {
        string::size_type i = s.find_first_not_of(' ');
        if(i == string::npos)
            return false;
        string::size_type j = s.find_first_of("eE", i);
        if(!isValid(s, i, (j==string::npos ? s.find_last_not_of(' ') : j-1), true))
            return false;

        if(j != string::npos) {
            i = j + 1;
            j = s.find_last_not_of(' ');
            if(!isValid(s, i, j, false))
                return false;
        }

        return true;
    }

private:
    bool isValid(const string &s, string::size_type start, string::size_type end, bool allowDot) {
        if(end < start)
            return false;
        if(s[start]=='-' || s[start]=='+')
            ++start;
        bool hasNum = false;  // must have numeric value
        bool hasDot = false;  // only one dot allowed
        for(string::size_type i=start; i<=end; ++i) {
            if(s[i]>='0' && s[i]<='9') {
                hasNum = true;
            }
            else if(s[i] == '.' && allowDot && !hasDot) {
                hasDot = true;
                continue;
            }
            else
                return false;
        }

        return hasNum;
    }
    
};


// ref solution by following the rules (Java)
class Solution {
    public boolean isNumber(String s) {
        boolean seenDigit = false;
        boolean seenExponent = false;
        boolean seenDot = false;
        
        for (int i = 0; i < s.length(); i++) {
            char curr = s.charAt(i);
            if (Character.isDigit(curr)) {
                seenDigit = true;
            } else if (curr == '+' || curr == '-') {
                if (i > 0 && s.charAt(i - 1) != 'e' && s.charAt(i - 1) != 'E') {
                    return false;
                }
            } else if (curr == 'e' || curr == 'E') {
                if (seenExponent || !seenDigit) {
                    return false;
                }
                seenExponent = true;
                seenDigit = false;
            } else if (curr == '.') {
                if (seenDot || seenExponent) {
                    return false;
                }
                seenDot = true;
            } else {
                return false;
            }
        }
        
        return seenDigit;
    }
}

// ref solution with status machine
class Solution {
    // This is the DFA we have designed above
    private static final List<Map<String, Integer>> dfa = List.of(
        Map.of("digit", 1, "sign", 2, "dot", 3),
        Map.of("digit", 1, "dot", 4, "exponent", 5), 
        Map.of("digit", 1, "dot", 3), 
        Map.of("digit", 4), 
        Map.of("digit", 4, "exponent", 5),
        Map.of("sign", 6, "digit", 7),
        Map.of("digit", 7),
        Map.of("digit", 7)
    );

    // These are all of the valid finishing states for our DFA.
    private static final Set<Integer> validFinalStates = Set.of(1, 4, 7);

    public boolean isNumber(String s) {
        int currentState = 0;
        String group = "";
        
        for (int i = 0; i < s.length(); i++) {
            char curr = s.charAt(i);
            if (Character.isDigit(curr)) {
                group = "digit";
            } else if (curr == '+' || curr == '-') {
                group = "sign";
            } else if (curr == 'e' || curr == 'E') {
                group = "exponent";
            } else if (curr == '.') {
                group = "dot";
            } else {
                return false;
            }
            
            if (!dfa.get(currentState).containsKey(group)) {
                return false;
            }
            
            currentState = dfa.get(currentState).get(group);
        }
        
        return validFinalStates.contains(currentState);
    }
}
