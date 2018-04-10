/*
  Design a logger system that receive stream of messages along with its timestamps, each message should be printed if and only if it is not printed in the last 10 seconds.

  Given a message and a timestamp (in seconds granularity), return true if the message should be printed in the given timestamp, otherwise returns false.

  It is possible that several messages arrive roughly at the same time.

  Example:

  Logger logger = new Logger();

  // logging string "foo" at timestamp 1
  logger.shouldPrintMessage(1, "foo"); returns true; 

  // logging string "bar" at timestamp 2
  logger.shouldPrintMessage(2,"bar"); returns true;

  // logging string "foo" at timestamp 3
  logger.shouldPrintMessage(3,"foo"); returns false;

  // logging string "bar" at timestamp 8
  logger.shouldPrintMessage(8,"bar"); returns false;

  // logging string "foo" at timestamp 10
  logger.shouldPrintMessage(10,"foo"); returns false;

  // logging string "foo" at timestamp 11
  logger.shouldPrintMessage(11,"foo"); returns true;
*/

/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * bool param_1 = obj.shouldPrintMessage(timestamp,message);
 */

// Straightforward solution that keeps message-->timestamp mapping
// -- This can suffer from space blow up since all old messages are always kept
class Logger {
public:
  /** Initialize your data structure here. */
  Logger() {
        
  }
    
  /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
      If this method returns false, the message will not be printed.
      The timestamp is in seconds granularity. */
  bool shouldPrintMessage(int timestamp, string message) {
    auto it = _m.find(message);
    if(it==_m.end() || timestamp-it->second>=10) {
      _m[message] = timestamp;
      return true;
    }
        
    return false;
  }
    
private:
  unordered_map<string, int> _m;
};

// Solution that avoids space blow up
// -- Cleanup old messages when necessary
class Logger {
public:
  /** Initialize your data structure here. */
  Logger() {
        
  }
    
  /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
      If this method returns false, the message will not be printed.
      The timestamp is in seconds granularity. */
  bool shouldPrintMessage(int timestamp, string message) {
    _m.erase(_m.begin(), _m.upper_bound(timestamp-10));  // cleanup old messages
    for(auto log : _m)
      if(log.second.count(message))
	return false;
    _m[timestamp].insert(message);
    return true;
  }
    
private:
  map<int, unordered_set<string>> _m;
};
