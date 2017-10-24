#include "../common/common.h"

using namespace std;

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


class Solution2 {
public:
  enum Status {NUM1, NUM2, NUM3};  // NUM1.NUM2[e|E]NUM3
  bool isNumber(string s) {
    // remove starting/trailing spaces
    auto i = s.find_first_not_of(' ');
    if(i == string::npos)
      return false;
    if(s[i]=='-' || s[i]=='+')
      ++i;
    auto j = s.find_last_not_of(' ');
    if(j < i)
      return false;
    s = s.substr(i, j-i+1);

    if(s.empty())
      return false;

    bool hasNum1 = false;
    bool hasNum2 = false;
    bool hasNum3 = false;
    bool enterNum3 = false;
    
    // Use state machine
    Status st = NUM1;
    for(int i=0; i<s.size(); ++i) {
      char c = s[i];
      switch(st) {
      case NUM1:
	if(c == '.')
	  st = NUM2;
	else if(c=='e' || c=='E') {
	  if(i<s.size()-1 && (s[i+1]=='-'||s[i+1]=='+'))
	    ++i;
	  st = NUM3;
	  enterNum3 = true;
	}
	else if(c<'0' || c >'9')
	  return false;
	else
	  hasNum1 = true;
	break;
      case NUM2:
	if(c=='e' || c=='E') {
	  if(i<s.size()-1 && (s[i+1]=='-'||s[i+1]=='+'))
	    ++i;
	  st = NUM3;
	  enterNum3 = true;
	}
	else if(c<'0' || c>'9')
	  return false;
	else
	  hasNum2 = true;
	break;
      case NUM3:
	if(c<'0' || c>'9')
	  return false;
	else
	  hasNum3 = true;
	break;
      }
    }

    if( (hasNum1||hasNum2) && (!enterNum3 || (enterNum3&&hasNum3)) )
      return true;
    else
      return false;
  }
};

int main(int argc, char *argv[])
{
  string s = argv[1];
  for(int i=0; i<s.size(); ++i)
    if(s[i] == '_')
      s[i] = ' ';
  Solution sol;
  bool res = sol.isNumber(s);
  cout << "res: " << res << endl;

  return 0;
}
