/*
  The API: int read4(char *buf) reads 4 characters at a time from a file.

  The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

  By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

  Note:
  The read function will only be called once for each test case.
*/

// Forward declaration of the read4 API.
int read4(char *buf);

// My first solution
class Solution {
public:
  /**
   * @param buf Destination buffer
   * @param n   Maximum number of characters to read
   * @return    The number of characters read
   */
  int read(char *buf, int n) {
    int count = 0;
    while(n) {
      int num = min(n, read4(buf+count));  // Little inefficient as the min is inside the loop
      count += num;
      n -= num;
      if(num < 4)
	break;
    }
        
    return count;
  }
};

// Slightly more efficient as the min is outside the loop
class Solution {
public:
  /**
   * @param buf Destination buffer
   * @param n   Maximum number of characters to read
   * @return    The number of characters read
   */
  int read(char *buf, int n) {
    int count = 0;  // total number of characters from read4()
    int N = n / 4;  // number of times read4 needs to be called to get n characters
    for(int i=0; i<=N; ++i) {
      int num = read4(buf+count);
      count += num;
      if(num != 4)
	break;
    }
        
    return min(n, count);
  }
};
