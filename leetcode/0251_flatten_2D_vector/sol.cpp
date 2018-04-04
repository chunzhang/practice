/*
  Implement an iterator to flatten a 2d vector.

  For example,
  Given 2d vector =

  [
  [1,2],
  [3],
  [4,5,6]
  ]
  By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

  Follow up:
  As an added challenge, try to code it using only iterators in C++ or iterators in Java.
*/

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */

// O(N) space
class Vector2D {
public:
  Vector2D(vector<vector<int>>& vec2d) {
    _vec2d = vec2d;
    _i = 0;
    _j = 0;
    findNextValid();
  }

  int next() {
    int val = _vec2d[_i][_j++];
    if(_j == _vec2d[_i].size()) {
      ++_i;
      _j = 0;
      findNextValid();
    }
    return val;
  }

  bool hasNext() {
    return _i<_vec2d.size();
  }
    
private:
  void findNextValid() {
    for( ; _i<_vec2d.size(); ++_i)
      if(!_vec2d[_i].empty())
	break;
  }
    
private:
  vector<vector<int>> _vec2d;
  int _i;
  int _j;
};

// O(1) space with iterator only
class Vector2D {
public:
  Vector2D(vector<vector<int>>& vec2d) {
    _cur = vec2d.begin();
    _end = vec2d.end();
    _col = 0;
    findNextValid();
  }

  int next() {
    int val = (*_cur)[_col++];
    if(_col == _cur->size()) {
      ++_cur;
      _col = 0;
      findNextValid();
    }
    return val;
  }

  bool hasNext() {
    return _cur != _end;
  }
    
private:
  void findNextValid() {
    for( ; _cur!=_end; ++_cur)
      if(!_cur->empty())
	break;
  }
    
private:
  vector<vector<int>>::iterator _cur, _end;
  int _col;
};
