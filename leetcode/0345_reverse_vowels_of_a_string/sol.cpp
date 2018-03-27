/*
  Write a function that takes a string as input and reverse only the vowels of a string.

  Example 1:
  Given s = "hello", return "holle".

  Example 2:
  Given s = "leetcode", return "leotcede".

  Note:
  The vowels does not include the letter "y".
*/

#include "../common/common.h"

using namespace std;

class Solution {
public:
  string reverseVowels(string s) {
    vector<int> vowel(256, 0);
    string tmp = "aeiouAEIOU";
    for(char c : tmp)
      vowel[c] = 1;

    int i = 0;
    int j = (int)s.size() - 1;
    while(1) {
      while(i<s.size() && !vowel[s[i]])
	++i;
      while(j>=0 && !vowel[s[j]])
	--j;

      if(i >= j)
	break;

      swap(s[i++], s[j--]);  // don't forget to update i and j here!
    }

    return s;
  }
};

int main(int argc, char *argv[])
{
  string s = argv[1];
  Solution sol;
  string res = sol.reverseVowels(s);
  cout << "res: " << res << endl;

  return 0;
}
