/*
  An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:

  a) it                      --> it    (no abbreviation)

  1
  b) d|o|g                   --> d1g

  1    1  1
  1---5----0----5--8
  c) i|nternationalizatio|n  --> i18n

  1
  1---5----0
  d) l|ocalizatio|n          --> l10n
  Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.

  Example: 
  Given dictionary = [ "deer", "door", "cake", "card" ]

  isUnique("dear") -> false
  isUnique("cart") -> true
  isUnique("cane") -> false
  isUnique("make") -> true
*/

#include "../common/common.h"

using namespace std;

// Actually, this problem asks "if you add another word into the dictionary, would this create a non-unqiue abbreviation
// for the dictionary?"

class ValidWordAbbr {
public:
  ValidWordAbbr(vector<string> dictionary) {
    for(const string &word : dictionary) {
      _abbr[genAbbr(word)].insert(word);  // assume dictionary doesn't contain duplicates
    }
  }
    
  bool isUnique(string word) {
    auto it = _abbr.find(genAbbr(word));
    if(it==_abbr.end() || (it->second.size()==1 && it->second.find(word)!=it->second.end())) // note the corner case for same word...
      return true;
    else
      return false;
  }
    
private:
  string genAbbr(const string &s) {
    if(s.size() <= 2)
      return s;
    else
      return s.front() + to_string(s.size()-2) + s.back();
  }
    
private:
  unordered_map<string, unordered_set<string>> _abbr;
};

class ValidWordAbbr {
public:
  ValidWordAbbr(vector<string> dictionary) {
    for(const string &word : dictionary) {
      string abbr = genAbbr(word);
      auto it = _abbr.find(abbr);
      if(it == _abbr.end())
	_abbr[abbr] = word;
      else if(it->second != word)  // note dictionary may contain duplicated words
	_abbr[abbr] = "";  // found non-unique abbreviation!
    }
  }
    
  bool isUnique(string word) {
    auto it = _abbr.find(genAbbr(word));
    return it==_abbr.end() || it->second==word;
  }
    
private:
  string genAbbr(const string &s) {
    if(s.size() <= 2)
      return s;
    else
      return s.front() + to_string(s.size()-2) + s.back();
  }
    
private:
  unordered_map<string, string> _abbr;
};

