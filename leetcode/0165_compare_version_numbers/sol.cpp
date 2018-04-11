/*
  Compare two version numbers version1 and version2.
  If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

  You may assume that the version strings are non-empty and contain only digits and the . character.
  The . character does not represent a decimal point and is used to separate number sequences.
  For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

  Here is an example of version numbers ordering:

  0.1 < 1.1 < 1.2 < 13.37
*/

// My initial solution
class Solution {
public:
  int compareVersion(string version1, string version2) {
    int i1=0, i2=0;
    while(1) {
      if(i1>=version1.size() && i2>=version2.size())
	return 0;
            
      int v1 = 0;  // This is for handling trailing zeros in version such as 1.0.0
      if(i1 < version1.size()) {
	int j1 = i1;
	while(j1<version1.size() && version1[j1]!='.')
	  ++j1;
	v1 = stoi(version1.substr(i1, j1-i1));
	i1 = j1 + 1;
      }
            
      int v2 = 0;
      if(i2 < version2.size()) {
	int j2 = i2;
	while(j2<version2.size() && version2[j2]!='.')
	  ++j2;
	v2 = stoi(version2.substr(i2, j2-i2));
	i2 = j2 + 1;
      }
            
      if(v1 != v2)
	return v1>v2 ? 1 : -1;
    }
  }
};

// A more concise implementation w/o calling any string API
class Solution {
public:
  int compareVersion(string version1, string version2) {
    int i1=0, i2=0;
    int v1=0, v2=0;
    while(i1<version1.size() || i2<version2.size()) {
      // For handling the case that 1.0.0 == 1, we make
      // default version number as 0
      v1 = v2 = 0;
            
      // compute v1
      while(i1<version1.size() && version1[i1]!='.') {
	v1 = v1*10 + version1[i1] - '0';
	++i1;
      }
            
      // compute v2
      while(i2<version2.size() && version2[i2]!='.') {
	v2 = v2*10 + version2[i2] - '0';
	++i2;
      }
            
      if(v1 != v2) {
	return v1>v2 ? 1 : -1;
      }
      else {
	++i1;  // move to the first character after '.'
	++i2;
      }
    }
        
    return 0;  // Don't forget this
  }
};
