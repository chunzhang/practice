/*
Facebook/Bloomberg/Google

Design a data structure that is initialized with a list of different words. Provided a string, you should determine if you can change exactly one character in this string to match any word in the data structure.

Implement the MagicDictionary class:

MagicDictionary() Initializes the object.
void buildDict(String[] dictionary) Sets the data structure with an array of distinct strings dictionary.
bool search(String searchWord) Returns true if you can change exactly one character in searchWord to match any string in the data structure, otherwise returns false.
 

Example 1:

Input
["MagicDictionary", "buildDict", "search", "search", "search", "search"]
[[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
Output
[null, null, false, true, false, false]

Explanation
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // return False
magicDictionary.search("hhllo"); // We can change the second 'h' to 'e' to match "hello" so we return True
magicDictionary.search("hell"); // return False
magicDictionary.search("leetcoded"); // return False
 

Constraints:

1 <= dictionary.length <= 100
1 <= dictionary[i].length <= 100
dictionary[i] consists of only lower-case English letters.
All the strings in dictionary are distinct.
1 <= searchWord.length <= 100
searchWord consists of only lower-case English letters.
buildDict will be called only once before search.
At most 100 calls will be made to search.
*/

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */

// brute-force
// time: O(M*L), where M is the number of words in the dictionary, L is the average length of the word
// space: O(M*L)
class MagicDictionary {
public:
    MagicDictionary() {
        
    }
    
    void buildDict(vector<string> dictionary) {
        m_dict = move(dictionary);
    }
    
    bool search(string searchWord) {
        for(const string &word : m_dict) {
            if(word.size() != searchWord.size())
                continue;
            int count = 0;
            for(int i=0; i<word.size(); ++i) {
                if(word[i] == searchWord[i])
                    continue;
                if(++count > 1)
                    break;
            }
            if(count == 1)
                return true;
        }
        return false;
    }

private:
    vector<string> m_dict;
};


// pre-build changed word --> original char mapping with two tricks
//   1) use '*' to represent changed char
//   2) use '?' to represent original char when there're multiple ones
// time: O(L)
// space: O(M*L^2)
class MagicDictionary {
public:
    MagicDictionary() {
        
    }
    
    // pre-build all changed words
    void buildDict(vector<string> dictionary) {
        for(string &word : dictionary) {
            for(int i=0; i<word.size(); ++i) {
                char c = word[i];
                word[i] = '*';
                m_dict[word] = m_dict.count(word) ? '?' : c;  // '?' means there're more than one original chars
                word[i] = c;
            }
        }
    }
    
    bool search(string searchWord) {
        for(int i=0; i<searchWord.size(); ++i) {
            char c = searchWord[i];
            searchWord[i] = '*';
            auto it = m_dict.find(searchWord);
            // note '?' plays a role here: if there're multiple orig char, at least one of it matches
            if(it!=m_dict.end() && c!=it->second)
                return true;
            searchWord[i] = c;
        }
        return false;
    }

private:
    unordered_map<string,char> m_dict;  // changed word --> original char mapping
};
