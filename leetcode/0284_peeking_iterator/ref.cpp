// Same idea as what I have implemented
// https://leetcode.com/problems/peeking-iterator/discuss/72598/Another-C++-solution-with-one-line-in-peek()-and-hasNext()-AC
class PeekingIterator : public Iterator {
private:
  int m_next;
  bool m_hasnext;
public:
  PeekingIterator(const vector<int>& nums) : Iterator(nums) {
    m_hasnext = Iterator::hasNext();
    if (m_hasnext) m_next = Iterator::next();
  }

  int peek() {
    return m_next;
  }

  int next() {
    int t = m_next;
    m_hasnext = Iterator::hasNext();
    if (m_hasnext) m_next = Iterator::next();
    return t;
  }

  bool hasNext() const {
    return m_hasnext;
  }
};

// Kind of cheating -- since Iterator has a copy constructor, we can just use it
// https://leetcode.com/problems/peeking-iterator/discuss/72554/Simple-C++-solution-(1-line-per-method)-without-extra-member-variables
class PeekingIterator : public Iterator
{
public:
  PeekingIterator(const vector<int> &nums) : Iterator(nums)
  {
  }

  int peek()
  {
    return Iterator(*this).next();
  }

  int next()
  {
    return Iterator::next();
  }

  bool hasNext() const
  {
    return Iterator::hasNext();
  }
};
