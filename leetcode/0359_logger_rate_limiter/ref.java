// We only need to store past 10s informtion
// https://leetcode.com/problems/logger-rate-limiter/discuss/83256/Java-Circular-Buffer-Solution-similar-to-Hit-Counter
public class Logger {
    private int[] buckets;
    private Set[] sets;
    /** Initialize your data structure here. */
    public Logger() {
	buckets = new int[10];  //* keep timestamps
	sets = new Set[10];     //* keep messages
	for (int i = 0; i < sets.length; ++i) {
	    sets[i] = new HashSet<String>();
	}
    }
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
	If this method returns false, the message will not be printed.
	The timestamp is in seconds granularity. */
    public boolean shouldPrintMessage(int timestamp, String message) {
	int idx = timestamp % 10;
	if (timestamp != buckets[idx]) {
	    sets[idx].clear();
	    buckets[idx] = timestamp;
	}
	for (int i = 0; i < buckets.length; ++i) {
	    if (timestamp - buckets[i] < 10) {
		if (sets[i].contains(message)) {
		    return false;
		}
	    }
	} 
	sets[idx].add(message);
	return true;
    }
}

// Instead of logging print times, I store when it’s ok for a message to be printed again. 
public class Logger {

    private Map<String, Integer> ok = new HashMap<>();

    public boolean shouldPrintMessage(int timestamp, String message) {
        if (timestamp < ok.getOrDefault(message, 0))
            return false;
        ok.put(message, timestamp + 10);
        return true;
    }
}

