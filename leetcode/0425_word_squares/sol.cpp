/*
  Given a set of words (without duplicates), find all word squares you can build from them.

  A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 ≤ k < max(numRows, numColumns).

  For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.

  b a l l
  a r e a
  l e a d
  l a d y
  Note:
  There are at least 1 and at most 1000 words.
  All words will have the exact same length.
  Word length is at least 1 and at most 5.
  Each word contains only lowercase English alphabet a-z.
  Example 1:

  Input:
  ["area","lead","wall","lady","ball"]

  Output:
  [
  [ "wall",
  "area",
  "lead",
  "lady"
  ],
  [ "ball",
  "area",
  "lead",
  "lady"
  ]
  ]

  Explanation:
  The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
  Example 2:

  Input:
  ["abat","baba","atan","atal"]

  Output:
  [
  [ "baba",
  "abat",
  "baba",
  "atan"
  ],
  [ "baba",
  "abat",
  "baba",
  "atal"
  ]
  ]

  Explanation:
  The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
*/

#include "../common/common.h"

using namespace std;

// For string with a--z only
struct TrieNode
{
  TrieNode() : _kids(26, nullptr),
	       _isEnd(false)
  {
    // Dummy
  }

  ~TrieNode() {
    // Dummy
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
      for(int i=0; i<26; ++i) {
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

// The word can be reused, so there's no need to book keep "used" words
class Solution {
public:
  vector<vector<string>> wordSquares(vector<string>& words) {
    _len = words[0].size();
    for(const string &w : words) {
      _trie.insert(w);
    }

    vector<string> square;
    for(const string &w : words) {
      square.push_back(w);
      search(square, 1);
      square.pop_back();
    }

    return _res;
  }

private:
  void search(vector<string> &square, int cur) {
    if(cur == _len) {
      _res.push_back(square);
      return;
    }

    string prefix;
    for(int i=0; i<cur; ++i) {
      prefix.push_back(square[i][cur]);
    }
    vector<string> candidates = _trie.findAll(prefix);
    for(const string &w : candidates) {
      square.push_back(w);
      search(square, cur+1);
      square.pop_back();
    }
  }

private:
  int _len;  // unique word length
  vector<vector<string>> _res;
  Trie _trie;
};

int main(int argc, char *argv[])
{
  vector<string> words = {"ulus","mity","wind","chip","pill","pugh","flux","crib","sump","piss","fils","high","pipy","rusk","cuss","miri","pung","this","knit","hisn","zins","puns","tuff","ruth","whit","wild","burd","hubs","grin","kirs","zips","migg","lump","dint","jiff","spud","pith","rill","twit","pugs","ichs","jugs","simp","crus","bury","lisp","bund","fugs","prig","dusk","dirt","inns","mild","dups","hins","nigh","ring","muds","bisk","spin","tuts","puff","jill","grig","gist","bilk","gill","buck","slur","limn","firn","surf","girl","brit","ilks","typy","yirr","whir","undy","nill","rifs","husk","flus","sift","bids","swig","fuds","bush","birr","buff","buds","sims","ywis","suck","slit","irid","guck","fist","kris","dunk","didy","iffy","snub","luny","dull","stub","spic","buts","viny","bris","tump","phut","will","guff","putt","whid","tilt","slub","sris","pfft","mull","bill","turk","kith","grip","stun","hilt","skip","piny","curl","liri","lust","mirk","birl","musk","huts","tiff","tuns","ruin","burs","girn","juju","fuji","writ","suqs","much","iglu","lulu","bulb","gild","whig","yips","lips","riff","libs","gird","tils","whin","thru","tubs","hint","mumm","till","grid","bird","curb","rung","flit","glug","gimp","fink","sins","find","tick","mill","null","flip","cigs","subs","pits","tipi","zinc","skid","plus","grit","gnus","curf","turn","tiny","miff","gibs","nick","shit","linn","tint","bull","urbs","immy","gush","fury","tins","duff","wiss","pick","chum","junk","vugs","limb","sulk","kilt","buss","curr","ping","snug","tidy","khis","mids","with","frug","jinn","yill","fill","gulf","mush","list","swum","kink","cwms","quid","lunk","chug","urus","sulu","lutz","just","funk","firs","mixt","guts","gyps","yids","brin","silt","wigs","gigs","diss","mitt","hung","ribs","bhut","drum","pups","idly","pins","titi","ritz","slim","spik","furl","tics","sirs","must","shul","tips","burr","shin","suss","rush","lull","lift","zits","milk","puds","phiz","mick","tirl","nidi","film","ruts","stir","lung","pulp","lunt","ughs","sips","mibs","pily","kirn","glim","pirn","silk","luff","syph","birk","thin","butt","hums","smug","twin","kits","rink","tuft","wins","wuss","lush","tivy","unit","dump","duly","pity","hulk","trig","grub","curn","duns","kids","wist","tsks","flic","gits","mini","wing","zing","frig","lick","nixy","swim","yins","kiwi","nuns","cups","jism","vigs","puri","nurl","impi","quit","inly","syli","mugs","lurk","rims","spiv","duds","glum","dumb","rump","fixt","tyin","dips","bibs","wits","chub","king","buhr","virl","busy","scut","urns","scum","curs","gull","idyl","sync","smut","slum","sups","blin","suds","bubs","crud","firm","djin","sung","rich","runs","runt","suit","wink","bunn","pull","brut","slut","jibs","figs","gins","digs","wyns","hind","gips","mump","jigs","spur","dims","wynn","hips","nuts","dugs","ruck","sums","ding","nisi","girt","hunt","vill","clit","mutt","umps","gulp","puny","buys","trug","guid","duty","dits","spit","dung","yuch","guls","fumy","liny","prim","scud","shun","durr","ling","muns","rust","quiz","jibb","fuci","inti","guys","dirk","ills","whys","scry","ziti","crux","kind","huic","glut","sink","fubs","bind","ting","pigs","turd","tuis","gift","iwis","putz","kick","muss","mist","chid","kifs","ruly","mink","punk","skis","burn","lint","jump","pump","curt","bums","dink","murr","pimp","huns","fuzz","rimy","hull","yuks","fuck","fins","kuru","sudd","cuts","dipt","wynd","stum","city","nims","wily","sibs","unci","isms","psst","jink","bunt","pyic","ugly","sith","funs","myth","fibs","kudu","gilt","fuss","hunh","yurt","muts","rigs","rins","inks","rick","hiss","irks","puls","jinx","bulk","curd","purr","trip","such","hili","muck","hugs","vims","vugg","puss","limy","mils","midi","vugh","drub","hill","purl","huck","imid","duct","chit","miry","muni","litu","rift","kiln","buns","kips","tits","bitt","chis","fids","nurd","slip","rips","whiz","sics","brig","rhus","sing","dish","huff","rubs","sugh","sill","punt","lits","hurt","wiry","skim","hunk","cunt","plum","sunn","luvs","muff","brim","fizz","drib","piki","rynd","shiv","fisc","kirk","quin","sinh","pyin","purs","thud","knur","migs","grum","bins","burl","spun","blip","wych","cist","blub","icky","slid","wimp","lynx","tush","yuck","tusk","snit","hits","bits","grim","hump","mirs","mums","clip","fugu","skin","jury","cubs","pips","whip","pics","typp","lily","thir","mumu","smit","disc","pfui","blur","hymn","puts","wish","pink","bibb","gyms","bigs","tung","hick","puck","milt","itch","mind","cusk","uric","furs","guvs","guns","gink","nits","lich","shri","futz","duck","cris","duci","drip","illy","burp","minx","sild","brrr","lids","yird","guru","phis","wilt","fish","luck","link","psis","plug","bump","dins","lugs","burg","tuck","kill","jilt","wisp","drug","rugs","dust","shim","jimp","duit","push","pint","dill","disk","gyri","rind","lums","mint","ghis","rids","sizy","club","slug","scup","xyst","limp","imps","tups","sibb","cuff","tiki","stud","sits","nips","trim","bust","gums","wick","turf","fund","snip","cuds","fits","chin","tugs","inch","pish","hurl","thus","glib","murk","quip","flub","drys","dibs","pili","hyps","ruby","dick","bint","lins","wich","buhl","urds","zill","biff","kist","ibis","byrl","dubs","cull","puli","bumf","juts","gids","durn","surd","twig","friz","cusp","yups","hist","skit","kins","miss","nubs","chic","lilt","buzz","sign","frit","tutu","culm","sigh","whim","hush","bugs","winy","busk","inky","gunk","numb","sick","cult","risk","rudd","bunk","iris","ditz","inby","mugg","bung","zigs","rums","dirl","nils","pubs","jins","nibs","kiss","full","dunt","sunk","ship","pixy","suns","cyst","ruff","gust","thug","cuif","spry","snib","upby","shut"};

  //xxx   for(int i=1; i<argc; ++i) {
  //xxx     words.push_back(argv[i]);
  //xxx   }
  //xxx
  
  //xxx printVector(words);

  Solution sol;
  vector<vector<string>> res = sol.wordSquares(words);
  cout << "XXX " << res.size() << endl;
  //xxx printMatrix(res);

  return 0;
}
