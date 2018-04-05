/*
  Given a non-empty string, encode the string such that its encoded length is the shortest.

  The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

  Note:
  k will be a positive integer and encoded string will not be empty or have extra space.
  You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
  If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.
  Example 1:

  Input: "aaa"
  Output: "aaa"
  Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.
  Example 2:

  Input: "aaaaa"
  Output: "5[a]"
  Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
  Example 3:

  Input: "aaaaaaaaaa"
  Output: "10[a]"
  Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".
  Example 4:

  Input: "aabcaabcd"
  Output: "2[aabc]d"
  Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
  Example 5:

  Input: "abbbabbbcabbbabbbc"
  Output: "2[2[abbb]c]"
  Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
*/

// DP based solution
class Solution {
public:
  string encode(string s) {
    if(s.size() < 4)
      return s;
        
    // coding[i][j] is the min encoding for s[i...j]
    // coding[i][j] = min(coding[i][j], coding[i][k]+coding[k+1][j], repeat patten of s[i...] itself)
    vector<vector<string>> coding(s.size(), vector<string>(s.size(), ""));
    for(int j=0; j<s.size(); ++j) {  // Note the dependency here
      for(int i=j; i>=0; --i) {
	string sub = s.substr(i, j-i+1);
	coding[i][j] = sub;  // option 1: itself without encoding
	if(j-i+1 < 4) {   // too short, no encoding can reduce length
	  continue;
	}
                
	// option 2: formed from substring encoding
	for(int k=i; k<j; ++k) {
	  if(coding[i][k].size() + coding[k+1][j].size() < coding[i][j].size())
	    coding[i][j] = coding[i][k] + coding[k+1][j];
	}
                                
	// option 3: repeated pattern from itself
	size_t pos = (sub+sub).find(sub, 1);  // Useful trick to search repeated pattern!
	if(pos < sub.size()) {  // find repeated pattern
	  // Don't forget to further encoding repeated pattern
	  string temp = to_string(sub.size()/pos) + "[" + coding[i][i+pos-1] + "]";  
	  if(temp.size() < coding[i][j].size())
	    coding[i][j] = temp;
	}
                
      }
    }
        
    return coding[0][s.size()-1];
  }
};
