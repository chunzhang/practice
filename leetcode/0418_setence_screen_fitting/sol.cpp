/*
  Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.

  Note:

  A word cannot be split into two lines.
  The order of words in the sentence must remain unchanged.
  Two consecutive words in a line must be separated by a single space.
  Total words in the sentence won't exceed 100.
  Length of each word is greater than 0 and won't exceed 10.
  1 ≤ rows, cols ≤ 20,000.
  Example 1:

  Input:
  rows = 2, cols = 8, sentence = ["hello", "world"]

  Output: 
  1

  Explanation:
  hello---
  world---

  The character '-' signifies an empty space on the screen.
  Example 2:

  Input:
  rows = 3, cols = 6, sentence = ["a", "bcd", "e"]

  Output: 
  2

  Explanation:
  a-bcd- 
  e-a---
  bcd-e-

  The character '-' signifies an empty space on the screen.
  Example 3:

  Input:
  rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]

  Output: 
  1

  Explanation:
  I-had
  apple
  pie-I
  had--

  The character '-' signifies an empty space on the screen.
*/

#include "../common/common.h"

using namespace std;

// https://leetcode.com/problems/sentence-screen-fitting/discuss/90845/
// -- Maintaining effective length of formatted string
// -- Even better version by pre-compute the length justification needed
class Solution {
public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    string s;
    for(const string &w : sentence)
      s += w + " ";  // s is the full formatted sentence
    int sLen = s.size();

    // pre-compute length justification
    vector<int> justify(sLen, 0);
    for(int i=1; i<sLen; ++i)
      justify[i] = s[i]==' ' ? 1 : justify[i-1]-1;

    // compute effective length
    int effLen = 0;
    for(int i=0; i<rows; ++i) {
      effLen += cols;
      effLen += justify[effLen%sLen];
    }

    return effLen / sLen;
  }

};

// https://leetcode.com/problems/sentence-screen-fitting/discuss/90845/
// -- Maintaining effective length of formatted string
class Solution4 {
public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    string s;
    for(const string &w : sentence)
      s += w + " ";  // s is the full formatted sentence
    int sLen = s.size();

    int effLen = 0;  // effective length with invariant that each row ends with exactly one space
    for(int i=0; i<rows; ++i) {
      effLen += cols;
      if(s[effLen%sLen] == ' ') {  // perfect matching
	++effLen;  // keeps invariant: row must end with ' '
      }
      else {
	// truncate row end as word can't be splitted
	// -- Actually, this loop can be optimized with a pre-computed arrary that keeps number of characters to truncated
	while(effLen>0 && s[(effLen-1)%sLen]!= ' ')
	  --effLen;
      }
    }

    return effLen / sLen;
  }

};


// If a line can fit one or more sentences, we don't need to change the "cur" index
class Solution3 {
public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    int sLen = 0;  // total length of the sentence (includs seprating spaces)
    for(const string &w : sentence)
      sLen += w.size() + 1;
    int nFull = (cols+1) / sLen;  // number of full sentence a row can fit
    int spacesLeft = cols - nFull * sLen;  // spaces left after fitting full sentences
    int cur = 0;
    int count = 0;
    for(int i=0; i<rows; ++i) {
      count += nFull;  // fitting entire sentence doesn't change "cur"
      int spaces = spacesLeft;
      while(spaces >= (int)sentence[cur].size()) {  // note the cast is important as "spaces" may go negative
	spaces -= sentence[cur++].size() + 1;
	if(cur == sentence.size()) {
	  cur = 0;
	  ++count;
	}
      }
    }
    return count;
  }

};

// simulation based solution -- reach runtime limit...
class Solution2 {
public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    int count = 0;
    int cur = 0;  // index to next word in sentence
    for(int i=0; i<rows; ++i) {
      int spaces = cols;
      while(spaces >= sentence[cur].size()) {
	//xxx cout << sentence[cur];
	spaces -= sentence[cur++].size();
	if(spaces > 0) {
	  spaces -= 1;
	  //xxx cout << "_";
	}
	if(cur == sentence.size()) {
	  cur = 0;
	  ++count;
	}
      }
      //xxx cout << endl;
    }

    return count;
  }
};

int main(int argc, char *argv[])
{
  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);
  vector<string> sentence;
  for(int i=3; i<argc; ++i)
    sentence.push_back(argv[i]);
  Solution sol;
  int count = sol.wordsTyping(sentence, rows, cols);
  cout << "count: " << count << endl;

  return 0;
}
