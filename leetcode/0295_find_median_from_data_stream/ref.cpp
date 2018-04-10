// Approach #1 Simple Sorting [Time Limit Exceeded]
class MedianFinder {
  vector<double> store;

public:
  // Adds a number into the data structure.
  void addNum(int num)
  {
    store.push_back(num);
  }

  // Returns the median of current data stream
  double findMedian()
  {
    sort(store.begin(), store.end());

    int n = store.size();
    return (n & 1 ? (store[n / 2 - 1] + store[n / 2]) * 0.5 : store[n / 2]);
  }
};

// Approach #2 Insertion Sort [Time Limit Exceeded]
class MedianFinder {
  vector<int> store; // resize-able container

public:
  // Adds a number into the data structure.
  void addNum(int num)
  {
    if (store.empty())
      store.push_back(num);
    else
      store.insert(lower_bound(store.begin(), store.end(), num), num);     // binary search and insertion combined
  }

  // Returns the median of current data stream
  double findMedian()
  {
    int n = store.size();
    return n & 1 ? store[n / 2] : (store[n / 2 - 1] + store[n / 2]) * 0.5;
  }
};

// Approach #3 Two Heaps! [Accepted]
class MedianFinder {
  priority_queue<int> lo;                              // max heap
  priority_queue<int, vector<int>, greater<int>> hi;   // min heap

public:
  // Adds a number into the data structure.
  void addNum(int num)
  {
    lo.push(num);                                    // Add to max heap

    hi.push(lo.top());                               // balancing step
    lo.pop();

    if (lo.size() < hi.size()) {                     // maintain size property
      lo.push(hi.top());
      hi.pop();
    }
  }

  // Returns the median of current data stream
  double findMedian()
  {
    return lo.size() > hi.size() ? (double) lo.top() : (lo.top() + hi.top()) * 0.5;
  }
};

// Approach #4 Multiset and Two Pointers [Accepted]
class MedianFinder {
  multiset<int> data;
  multiset<int>::iterator lo_median, hi_median;

public:
  MedianFinder()
    : lo_median(data.end())
    , hi_median(data.end())
  {
  }

  void addNum(int num)
  {
    const size_t n = data.size();   // store previous size

    data.insert(num);               // insert into multiset

    if (!n) {
      // no elements before, one element now
      lo_median = hi_median = data.begin();
    }
    else if (n & 1) {
      // odd size before (i.e. lo == hi), even size now (i.e. hi = lo + 1)

      if (num < *lo_median)       // num < lo
	lo_median--;
      else                        // num >= hi
	hi_median++;            // insertion at end of equal range
    }
    else {
      // even size before (i.e. hi = lo + 1), odd size now (i.e. lo == hi)

      if (num > *lo_median && num < *hi_median) {
	lo_median++;                    // num in between lo and hi
	hi_median--;
      }
      else if (num >= *hi_median)         // num inserted after hi
	lo_median++;
      else                                // num <= lo < hi
	lo_median = --hi_median;        // insertion at end of equal range spoils lo
    }
  }

  double findMedian()
  {
    return (*lo_median + *hi_median) * 0.5;
  }
};

// A much shorter (but harder to understand), one pointer version 3 of this solution
class MedianFinder {
  multiset<int> data;
  multiset<int>::iterator mid;

public:
  MedianFinder()
    : mid(data.end())
  {
  }

  void addNum(int num)
  {
    const int n = data.size();
    data.insert(num);

    if (!n)                                 // first element inserted
      mid = data.begin();
    else if (num < *mid)                    // median is decreased
      mid = (n & 1 ? mid : prev(mid));
    else                                    // median is increased
      mid = (n & 1 ? next(mid) : mid);
  }

  double findMedian()
  {
    const int n = data.size();
    return (*mid + *next(mid, n % 2 - 1)) * 0.5;
  }
};
