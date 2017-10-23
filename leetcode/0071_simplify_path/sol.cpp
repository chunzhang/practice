#include "../common/common.h"

using namespace std;

class Solution {
public:
  string simplifyPath(string path) {
    path.push_back('/'); // always ends at '/' to simplify the code
    vector<string> myStack;
    string::size_type start = 0;
    while(1) {
      string::size_type end = path.find_first_of('/', start);
      if(end == string::npos)
	break;
      string p = path.substr(start, end-start);
      start = end + 1;

      if(p.empty() || p==".")
	continue;
      else if(p == "..") {
	if(!myStack.empty())
	  myStack.pop_back();
      }
      else
	myStack.push_back(p);
    }

    string res;
    for(auto &p : myStack)
      res += "/" + p;

    return res.empty() ? "/" : res;
  }
};

int main(int argc, char *argv[])
{
  string path = argc==2 ? argv[1] : "";
  Solution sol;
  string res = sol.simplifyPath(path);
  cout << "res: " << res << endl;

  return 0;
}
