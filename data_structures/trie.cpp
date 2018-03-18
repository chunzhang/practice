#include "../leetcode/common/common.h"

using namespace std;

// For string with a--z only
struct TrieNode
{
  TrieNode() : _kids(26, nullptr),
	       _isEnd(false)
  {
    //xxx cout << "TrieNode created" << endl;
  }

  ~TrieNode() {
    //xxx cout << "TrieNode released" << endl;
  }

  // This node can be removed
  bool noKids() {
    for(TrieNode *k : _kids)
      if(k)
	return false;
    return true;
  }
  
  vector<TrieNode*> _kids;
  bool _isEnd;
};

class Trie
{
public:
  Trie() {
    _root = new TrieNode();
  }

  ~Trie() {
    _release(_root);
    cout << "Trie is released" << endl;
  }

  void insert(const string &s) {
    TrieNode *cur = _root;
    for(int i=0; i<s.size(); ++i) {
      int idx = s[i] - 'a';
      if(cur->_kids[idx] == nullptr) {
	cur->_kids[idx] = new TrieNode();
      }
      cur = cur->_kids[idx];
    }
    cur->_isEnd = true;
  }

  // return true if Trie contains s
  bool contains(const string &s) {
    TrieNode *cur = _root;
    for(int i=0; i<s.size(); ++i) {
      int idx = s[i] - 'a';
      if(cur->_kids[idx] == nullptr)
	return false;
      cur = cur->_kids[idx];
    }
    return cur->_isEnd;
  }

  void remove(const string &s) {
    _remove(_root, s);
  }


  // find all strings with given prefix
  vector<string> findAll(const string &prefix) {
    vector<string> res;
    string s;
    _findAll(_root, prefix, res, s);
    return res;
  }

private:
  // recursive destruction
  void _release(TrieNode *cur) {
    for(TrieNode *nd : cur->_kids) {
      if(nd)
	_release(nd);
    }
    delete cur;
  }
  
  // return true if cur is literally deleted
  bool _remove(TrieNode *cur, string s) {
    if(s.empty()) {  // reach bottom of the search -- s exists in the Trie
      if(cur->_isEnd)
	cur->_isEnd = false;
      if(cur->noKids() && !cur->_isEnd) {
	delete cur;
	return true;
      }
      else
	return false;
    }

    // s is non-empty
    int idx = s[0] - 'a';
    TrieNode *next = cur->_kids[idx];
    if(!next)
      return false;
    bool ret = _remove(next, s.substr(1));
    if(!ret)
      return false;
    cur->_kids[idx] = nullptr;
    if(cur->noKids() && !cur->_isEnd) {  // if cur is leaf, it can't be deleted
      delete cur;
      return true;
    }
    return false;
  }
  
  void _findAll(TrieNode *cur, string prefix, vector<string> &res, string &s) {
    if(prefix.size()) {
      char c = prefix[0];
      TrieNode *next = cur->_kids[c-'a'];
      if(!next)
	return;
      s.push_back(c);
      _findAll(next, prefix.substr(1), res, s);
    }
    else {
      if(cur->_isEnd)
	res.push_back(s);
      for(int i=0; i<25; ++i) {
	TrieNode *next = cur->_kids[i];
	if(next) {
	  s.push_back('a'+i);
	  _findAll(next, "", res, s);
	  s.pop_back();
	}
      }
    }
  }
  
private:
  TrieNode *_root;
};

int main()
{
  Trie t;
  vector<string> s1 = {"ab", "abc", "bcd"};
  for(auto s : s1) {
    cout << "insert(" << s << ")" << endl;
    t.insert(s);
  }

  vector<string> s2 = {"", "a", "abc", "bc", "bcd", "abcd", "ab"};
  for(auto s : s2) {
    cout << "contains(" << s << ") --> " << t.contains(s) << endl; 
  }

  vector<string> s3 = {"", "a", "ab", "abc", "abcd", "bc", "bcd", "bcc"};
  for(auto s : s3) {
    cout << "findAll(" << s << ")\n\t";
    auto res = t.findAll(s);
    printVector(res);
  }

  vector<string> s4 = {"abc", "bcde", "bcd"};
  for(auto s : s4) {
    cout << "remove(" << s << ")" << endl;
    t.remove(s);
  }
  for(auto s : s3) {
    cout << "findAll(" << s << ")\n\t";
    auto res = t.findAll(s);
    printVector(res);
  }


  return 0;  
}
