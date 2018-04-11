/*
  The API: int read4(char *buf) reads 4 characters at a time from a file.

  The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

  By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

  Note:
  The read function may be called multiple times.
*/

// Forward declaration of the read4 API.
int read4(char *buf);

// My initial solution
class Solution {
public:
  Solution() {
    _len = 0;
  }
  /**
   * @param buf Destination buffer
   * @param n   Maximum number of characters to read
   * @return    The number of characters read
   */
  int read(char *buf, int n) {
    // 1. use characters from internal buffer first
    int count = min(n, _len);
    memcpy(buf, _buf, count);
    n -= count;
    _len -= count;
    memcpy(_buf, _buf+count, _len);

    // 2. read more if needed
    return n ? readMore(buf+count, n)+count : count;
  }
    
private:
  // Read more using read4()
  // -- _buf is empty before calling this API
  // -- this API populates _buf with unused characters from last read4()
  int readMore(char *buf, int n) {
    int N = n / 4;
    int count = 0;  // total number of bytes read from file so far
    for(int i=0; i<=N; ++i) {
      int num = read4(buf+count);
      count += num;
      if(num != 4)
	break;
    }
        
    if(count > n) {  // there're some characters left
      _len = count - n;
      memcpy(_buf, buf+count-_len, _len);
    }
        
    return min(n, count);
  }

  // Just for debugging
  void printBuf() {
    cout << "\"";
    for(int i=0; i<_len; ++i)
      cout << _buf[i];
    cout << "\"" << endl;
  }
    
private:
  char _buf[4];  // characters left from last read call
  int  _len;     // number of valid characters in _buf
};

// Always direct read4 into internal buffer
class Solution {
public:
  Solution() : _next(0),
	       _end(0)
  {
    // Dummy
  }
    
  /**
   * @param buf Destination buffer
   * @param n   Maximum number of characters to read
   * @return    The number of characters read
   */
  int read(char *buf, int n) {
    int i = 0;
    // read from buffer first
    while(i<n && _next<_end)
      buf[i++] = _buf[_next++];
        
    // now use read4() to get more
    while(i<n) {  // Note: can's use while(1) as it would always call read4() at least once, which might overwrite unused characters in _buf
      _end = read4(_buf);  // always read into internal buffer first
      _next = 0;
      while(i<n && _next<_end)
	buf[i++] = _buf[_next++];
      if(i==n || _end!=4)
	break;
    }
        
    return i;
  }
    
private:
  int _next;     // next valid char in the buffer
  int _end;      // buffer end
  char _buf[4];  // buffer
};
