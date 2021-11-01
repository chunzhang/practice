/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, and /. Each operand may be an integer or another expression.

Note that division between two integers should truncate toward zero.

It is guaranteed that the given RPN expression is always valid. That means the expression would always evaluate to a result, and there will not be any division by zero operation.

 

Example 1:

Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
 

Constraints:

1 <= tokens.length <= 104
tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].
*/


// use stack
// time and space complexity: O(N)
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(const string &s : tokens) {
            if(isdigit(s.back())) {  // check last character also works for negative string number, i.e., "-123"
                st.push(stoi(s));
            }
            else {
                int num1 = st.top();
                st.pop();
                int num2 = st.top();
                st.pop();
                //cout << num2 << s << num1 << endl;
                if(s == "+")
                    st.push(num2+num1);
                else if(s == "-")
                    st.push(num2-num1);
                else if(s == "*")
                    st.push(num2*num1);
                else
                    st.push(num2/num1);
            }
        }
        
        return st.top();
    }
};


// using lambda
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        function<int(const int,const int)> op[128];
        op['+'] = [](const int n1, const int n2) {return n1+n2;};
        op['-'] = [](const int n1, const int n2) {return n1-n2;};
        op['*'] = [](const int n1, const int n2) {return n1*n2;};
        op['/'] = [](const int n1, const int n2) {return n1/n2;};
        
        
        stack<int> st;
        for(const string &s : tokens) {
            if(isdigit(s.back())) {  // check last character also works for negative string number, i.e., "-123"
                st.push(stoi(s));
            }
            else {
                int num1 = st.top();
                st.pop();
                int num2 = st.top();
                st.pop();
                st.push(op[s[0]](num2,num1));
            }
        }
        
        return st.top();
    }
};
