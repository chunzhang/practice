/*
Facebook

You are given a string sentence that consist of words separated by spaces. Each word consists of lowercase and uppercase letters only.

We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.) The rules of Goat Latin are as follows:

If a word begins with a vowel ('a', 'e', 'i', 'o', or 'u'), append "ma" to the end of the word.
For example, the word "apple" becomes "applema".
If a word begins with a consonant (i.e., not a vowel), remove the first letter and append it to the end, then add "ma".
For example, the word "goat" becomes "oatgma".
Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
For example, the first word gets "a" added to the end, the second word gets "aa" added to the end, and so on.
Return the final sentence representing the conversion from sentence to Goat Latin.

Example 1:

Input: sentence = "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"

Example 2:

Input: sentence = "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
 

Constraints:

1 <= sentence.length <= 150
sentence consists of English letters and spaces.
sentence has no leading or trailing spaces.
All the words in sentence are separated by a single space.
*/

// follow the rules
class Solution {
public:
    string toGoatLatin(string sentence) {
        string ans;
        vector<char> isVowel(128, 0);
        for(char c : "aeiouAEIOU")
            isVowel[c] = 1;
        for(int i=0,j=0,count=0; j<=sentence.size(); ++j) {  // make sure we get the last word
            if(j==sentence.size() || sentence[j]==' ') {  // found a word of range [i,j)
                if(!ans.empty())
                    ans.push_back(' ');
                if(isVowel[sentence[i]]) {
                    ans += sentence.substr(i,j-i) + "ma";
                }
                else {
                    ans += sentence.substr(i+1,j-i-1) + string(1,sentence[i]) + "ma";
                }
                ans += string(++count,'a');
                i = j + 1;  // move to the beginning of next word
            }
        }

        return ans;
    }
};


// ref sol: using istringstream
class Solution {
public:
    string toGoatLatin(string S) {
        unordered_set<char> vowel({'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'});
        istringstream iss(S);
        string res, w;
        int i = 0, j;
        while (iss >> w) {
            res += ' ' + (vowel.count(w[0]) ? w : w.substr(1) + w[0]) + "ma";
            i++;
            for (j = 0; j < i; ++j) 
                res += "a";
        }
        return res.substr(1);
    }
};
