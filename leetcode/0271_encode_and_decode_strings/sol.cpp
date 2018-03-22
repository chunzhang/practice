/*
Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

Machine 1 (sender) has the function:

string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
Machine 2 (receiver) has the function:
vector<string> decode(string s) {
  //... your code
  return strs;
}
So Machine 1 does:

string encoded_string = encode(strs);
and Machine 2 does:

vector<string> strs2 = decode(encoded_string);
strs2 in Machine 2 should be the same as strs in Machine 1.

Implement the encode and decode methods.

Note:
The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.
*/

#include "../common/common.h"

using namespace std;

// Solution 1: attache raw bytes as size of each sub-string
// -- kind of over-engineering
// -- need to consider address alignment of the "size header"
class Codec {
public:
    Codec() : N(sizeof(size_t)) {
        
    }

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string res;
        for(int i=0; i<strs.size(); ++i) {
            // convert size into raw byte representation
            size_t sz = strs[i].size();
            char *header = (char*)(&sz);
            for(int i=0; i<N; ++i)
                res.push_back(header[i]);
            res += strs[i];
            // for size_t alignment
            int m = res.size() % N;
            if(m) {  // size_t type must be aligned for it to be read in decode()
                int gap = N - m;
                for(int i=0; i<gap; ++i)
                    res.push_back('X');
            }
        }
        
        return res;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> res;
        for(size_t i=0; i<s.size(); ) {
            const char *start = s.c_str() + i;
            size_t sz = *((size_t*)start);
            string str(start+N, sz);
            res.push_back(str);
            i += N + sz;
            // for alignment
            int m = sz % N;
            if(m) {
                int gap = N - m;
                i += gap;
            }
        }
        
        return res;
    }
    
private:
    const int N;  // number of bytes of header
};

// A simpler implementation
class Codec2 {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string res;
        for(const string &s : strs) {
            res += to_string(s.size()) + "@";  // header with size
            res += s;
        }
        return res;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> res;
        for(size_t cur=0; cur<s.size(); ) {
            size_t sep = s.find_first_of('@', cur);
            size_t sz = stoll(s.substr(cur, sep-cur));
            res.push_back(s.substr(sep+1, sz));
            cur = sep + sz + 1;
        }
        return res;
    }
};


int main(int argc, char *argv[])
{
  vector<string> strs;
  for(int i=1; i<argc; ++i)
    strs.push_back(argv[i]);
  printVector(strs);
  Codec codec;
  vector<string> strs2 = codec.decode(codec.encode(strs));
  printVector(strs2);
  Codec2 codec2;
  vector<string> strs3 = codec2.decode(codec2.encode(strs));
  printVector(strs3);
  

  return 0;
}
