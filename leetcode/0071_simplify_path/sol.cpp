/*
Given a string path, which is an absolute path (starting with a slash '/') to a file or directory in a Unix-style file system, convert it to the simplified canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a double period '..' refers to the directory up a level, and any multiple consecutive slashes (i.e. '//') are treated as a single slash '/'. For this problem, any other format of periods such as '...' are treated as file/directory names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period '.' or double period '..')
Return the simplified canonical path.

 

Example 1:

Input: path = "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.
Example 2:

Input: path = "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.
Example 3:

Input: path = "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.
 

Constraints:

1 <= path.length <= 3000
path consists of English letters, digits, period '.', slash '/' or '_'.
path is a valid absolute Unix path.
*/


#include "../common/common.h"

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;  // use it as a stack
        int cur = 0;
        while(cur<path.size()) {
            while(cur<path.size() && path[cur]=='/')
                ++cur;
            if(cur >= path.size())
              break;
            int pos = cur;
            while(cur<path.size() && path[cur]!='/')
                ++cur;
            string p = path.substr(pos, cur-pos);
            if(p == "..") {
                if(!st.empty())
                  st.pop_back();
            }
            else if(p != ".") {
                st.push_back(p);
            }
        }

        // construct path
        string res;
        for(auto &p : st)
            res.append("/"+p);
        if(res.empty())
            res = "/";

        return res;
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
