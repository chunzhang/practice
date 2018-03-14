/*
  A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

  Find all strobogrammatic numbers that are of length = n.

  For example,
  Given n = 2, return ["11","69","88","96"].
*/

#include "../common/common.h"

using namespace std;

class Solution {
public:
  vector<string> findStrobogrammatic(int n) {
    _m['0'] = '0';
    _m['1'] = '1';
    _m['6'] = '9';
    _m['8'] = '8';
    _m['9'] = '6';
    _single.push_back('0');
    _single.push_back('1');
    _single.push_back('8');

    vector<string> res;
    string str(n, 'x');
    search(res, 0, n-1, str);

    return res;
  }

  void search(vector<string> &res, int i, int j, string &str) {
    if(i > j) {
      res.push_back(str);
      return;
    }

    if(i == j) {
      for(char c : _single) {
	str[i] = c;
	res.push_back(str);
      }
      return;
    }

    for(auto elem : _m) {
      if(i==0 && elem.first=='0')
	continue;
      str[i] = elem.first;
      str[j] = elem.second;
      search(res, i+1, j-1, str);
    }
  }

private:
  map<char,char> _m;
  vector<char> _single;
};

int main(int argc, char *argv[])
{
  int n = atoi(argv[1]);
  Solution sol;
  auto nums = sol.findStrobogrammatic(n);
  printVector(nums);

  return 0;
}
