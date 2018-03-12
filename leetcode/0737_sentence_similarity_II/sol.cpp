/*
Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.

For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].

Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.

Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.

Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.

Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].

Note:

The length of words1 and words2 will not exceed 1000.
The length of pairs will not exceed 2000.
The length of each pairs[i] will be 2.
The length of each words[i] and pairs[i][j] will be in the range [1, 20].
*/

#include "../common/common.h"

using namespace std;

// The union-find based solution
class Solution1 {
public:
  bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
    if(words1.size() != words2.size())
      return false;

    // 1. make unions
    _sets.resize(pairs.size()*2);
    for(int i=0; i<_sets.size(); ++i)
      _sets[i] = i;
    
    int id = 0;
    for(int i=0; i<pairs.size(); ++i) {
      string w1 = pairs[i].first;
      string w2 = pairs[i].second;
      if(_words.find(w1) == _words.end()) {
	_words[w1] = id++;
      }
      if(_words.find(w2) == _words.end()) {
	_words[w2] = id++;
      }
      makeUnion(_words[w1], _words[w2]);
    }

    // 2. checking
    for(int i=0; i<words1.size(); ++i) {
      string w1 = words1[i];
      string w2 = words2[i];
      if(w1 == w2)
	continue;
      if(_words.find(w1)==_words.end() || _words.find(w2)==_words.end())
	return false;
      if(findParent(_words[w1]) != findParent(_words[w2]))
	return false;
    }

    return true;
  }

private:
  int findParent(int id) {
    if(_sets[id] != id)
      _sets[id] = findParent(_sets[id]);  // path compression on the fly
    return _sets[id];
  }

  void makeUnion(int id1, int id2) {
    _sets[findParent(id1)] = findParent(id2);
  }
  
  unordered_map<string, int> _words;  // each word in the "pairs" is assigned a unique ID
  vector<int> _sets;  // parent of each word ID, -1 means the word doesn't exist
};

// The DFS based solution
class Solution {
public:
  bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
    if(words1.size() != words2.size())
      return false;
    
    // 1. build graph
    for(int i=0; i<pairs.size(); ++i) {
      _graph[pairs[i].first].insert(pairs[i].second);
      _graph[pairs[i].second].insert(pairs[i].first);
    }

    // 2. checking
    for(int i=0; i<words1.size(); ++i) {
      if(words1[i] == words2[i])
	continue;
      if(_graph.find(words1[i])==_graph.end() || _graph.find(words2[i])==_graph.end())
	return false;

      _visited.clear();
      if(!dfs(words1[i], words2[i]))
	return false;
    }

    return true;
  }

  bool dfs(const string &from, const string &target) {
    _visited.insert(from);
    for(const string &neig : _graph[from]) {
      if(_visited.count(neig))
	continue;
      if(neig==target || dfs(neig,target))
	return true;
    }
    return false;
  }

private:
  unordered_map<string, set<string>> _graph;
  unordered_set<string> _visited;
};

int main()
{
//xxx   vector<string> words1 = {"great","acting","skills"};
//xxx   vector<string> words2 = {"fine","drama","talent"};
//xxx   vector<pair<string, string>> pairs = {{"great","good"},{"fine","good"},{"drama","acting"},{"skills","talent"}};
//xxx
  
  //xxx vector<string> words1 = {"this","summer","thomas","get","really","very","rich","and","have","any","actually","wonderful","and","good","truck","every","morning","he","drives","an","extraordinary","truck","around","the","nice","city","to","eat","some","extremely","extraordinary","food","as","his","meal","but","he","only","entertain","an","few","well","fruits","as","single","lunch","he","wants","to","eat","single","single","and","really","healthy","life"};
  //xxx vector<string> words2 = {"this","summer","thomas","get","very","extremely","rich","and","possess","the","actually","great","and","wonderful","vehicle","every","morning","he","drives","unique","extraordinary","automobile","around","unique","fine","city","to","drink","single","extremely","nice","meal","as","his","super","but","he","only","entertain","a","few","extraordinary","food","as","some","brunch","he","wants","to","take","any","some","and","really","healthy","life"};
  vector<string> words1 = {"this","summer","thomas","get","really"};
  vector<string> words2 = {"this","summer","thomas","get","very"};
  vector<pair<string, string>> pairs = {{"good","wonderful"},{"nice","well"},{"fine","extraordinary"},{"excellent","good"},{"wonderful","nice"},{"well","fine"},{"extraordinary","excellent"},{"great","wonderful"},{"one","the"},{"a","unique"},{"single","some"},{"an","one"},{"the","a"},{"unique","single"},{"some","an"},{"any","the"},{"car","wagon"},{"vehicle","car"},{"auto","vehicle"},{"automobile","auto"},{"wagon","automobile"},{"truck","wagon"},{"have","have"},{"take","take"},{"eat","eat"},{"drink","drink"},{"entertain","entertain"},{"meal","food"},{"lunch","breakfast"},{"super","brunch"},{"dinner","meal"},{"food","lunch"},{"breakfast","super"},{"brunch","dinner"},{"fruits","food"},{"own","own"},{"have","have"},{"keep","keep"},{"possess","own"},{"very","very"},{"super","super"},{"really","really"},{"actually","actually"},{"extremely","extremely"}};

//xxx   vector<string> words1 = {"this","summer","thomas","get","super","extremely","rich","and","have","the","actually","great","and","great","auto","every","morning","he","drives","unique","great","wagon","around","a","extraordinary","city","to","eat","some","extremely","excellent","lunch","as","his","brunch","but","he","only","entertain","one","few","fine","fruits","as","an","fruits","he","wants","to","entertain","an","one","and","really","healthy","life"};
//xxx   vector<string> words2 = {"this","summer","thomas","get","really","super","rich","and","own","one","super","wonderful","and","good","automobile","every","morning","he","drives","the","fine","automobile","around","single","good","city","to","take","single","super","wonderful","breakfast","as","his","breakfast","but","he","only","drink","a","few","fine","dinner","as","the","fruits","he","wants","to","entertain","some","the","and","extremely","healthy","life"};
//xxx   vector<pair<string, string>> pairs = {{"good","wonderful"},{"nice","well"},{"fine","extraordinary"},{"excellent","good"},{"wonderful","nice"},{"well","fine"},{"extraordinary","excellent"},{"great","wonderful"},{"one","the"},{"a","unique"},{"single","some"},{"an","one"},{"the","a"},{"unique","single"},{"some","an"},{"any","the"},{"car","wagon"},{"vehicle","car"},{"auto","vehicle"},{"automobile","auto"},{"wagon","automobile"},{"truck","wagon"},{"have","have"},{"take","take"},{"eat","eat"},{"drink","drink"},{"entertain","entertain"},{"meal","food"},{"lunch","breakfast"},{"super","brunch"},{"dinner","meal"},{"food","lunch"},{"breakfast","super"},{"brunch","dinner"},{"fruits","food"},{"own","own"},{"have","have"},{"keep","keep"},{"possess","own"},{"very","very"},{"super","super"},{"really","really"},{"actually","actually"},{"extremely","extremely"}};
//xxx

  Solution1 sol1;
  bool res1 = sol1.areSentencesSimilarTwo(words1, words2, pairs);
  cout << "res1: " << res1 << endl;
  
  Solution sol;
  bool res = sol.areSentencesSimilarTwo(words1, words2, pairs);
  cout << "res: " << res << endl;

  return 0;
}


/*
Official solution 1: DFS

class Solution {
    public boolean areSentencesSimilarTwo(
            String[] words1, String[] words2, String[][] pairs) {
        if (words1.length != words2.length) return false;
        Map<String, List<String>> graph = new HashMap();
        for (String[] pair: pairs) {
            for (String p: pair) if (!graph.containsKey(p)) {
                graph.put(p, new ArrayList());
            }
            graph.get(pair[0]).add(pair[1]);
            graph.get(pair[1]).add(pair[0]);
        }

        for (int i = 0; i < words1.length; ++i) {
            String w1 = words1[i], w2 = words2[i];
            Stack<String> stack = new Stack();
            Set<String> seen = new HashSet();
            stack.push(w1);
            seen.add(w1);
            search: {
                while (!stack.isEmpty()) {
                    String word = stack.pop();
                    if (word.equals(w2)) break search;
                    if (graph.containsKey(word)) {
                        for (String nei: graph.get(word)) {
                            if (!seen.contains(nei)) {
                                stack.push(nei);
                                seen.add(nei);
                            }
                        }
                    }
                }
                return false;
            }
        }
        return true;
    }
}
*/

/*
Official solution 2: union find

class Solution {
    public boolean areSentencesSimilarTwo(String[] words1, String[] words2, String[][] pairs) {
        if (words1.length != words2.length) return false;
        Map<String, Integer> index = new HashMap();
        int count = 0;
        DSU dsu = new DSU(2 * pairs.length);
        for (String[] pair: pairs) {
            for (String p: pair) if (!index.containsKey(p)) {
                index.put(p, count++);
            }
            dsu.union(index.get(pair[0]), index.get(pair[1]));
        }

        for (int i = 0; i < words1.length; ++i) {
            String w1 = words1[i], w2 = words2[i];
            if (w1.equals(w2)) continue;
            if (!index.containsKey(w1) || !index.containsKey(w2) ||
                    dsu.find(index.get(w1)) != dsu.find(index.get(w2)))
                return false;
        }
        return true;
    }
}

class DSU {
    int[] parent;
    public DSU(int N) {
        parent = new int[N];
        for (int i = 0; i < N; ++i)
            parent[i] = i;
    }
    public int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    public void union(int x, int y) {
        parent[find(x)] = find(y);
    }
}
*/
