/*
Design a time-based key-value data structure that can store multiple values for the same key at different time stamps and retrieve the key's value at a certain timestamp.

Implement the TimeMap class:

TimeMap() Initializes the object of the data structure.
void set(String key, String value, int timestamp) Stores the key key with the value value at the given time timestamp.
String get(String key, int timestamp) Returns a value such that set was called previously, with timestamp_prev <= timestamp. If there are multiple such values, it returns the value associated with the largest timestamp_prev. If there are no values, it returns "".
 

Example 1:

Input
["TimeMap", "set", "get", "get", "set", "get", "get"]
[[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]
Output
[null, null, "bar", "bar", null, "bar2", "bar2"]

Explanation
TimeMap timeMap = new TimeMap();
timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
timeMap.get("foo", 1);         // return "bar"
timeMap.get("foo", 3);         // return "bar", since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 is "bar".
timeMap.set("foo", "bar2", 4); // store the key "foo" and value "ba2r" along with timestamp = 4.
timeMap.get("foo", 4);         // return "bar2"
timeMap.get("foo", 5);         // return "bar2"
 

Constraints:

1 <= key.length, value.length <= 100
key and value consist of lowercase English letters and digits.
1 <= timestamp <= 10^7
All the timestamps timestamp of set are strictly increasing.
At most 2 * 10^5 calls will be made to set and get.
*/

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */


// binary search of timestamp
class TimeMap {
public:
    /** Initialize your data structure here. */
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        _data[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        auto it = _data.find(key);
        if(it == _data.end())
            return "";
        
        // binary search to find first element grater timestamp, i.e., upper_bound
        auto &values = it->second;
        int l = 0;
        int r = values.size();
        while(l<r) {
            int mid = l + (r-l)/2;
            if(values[mid].first > timestamp)
                r = mid;
            else
                l = mid + 1;
        }
        return l>0?values[l-1].second:"";
    }

private:
    unordered_map<string, vector<pair<int,string>>> _data;  // for a given key, values are sorted by timestamp according to the problem definition
};


// binary search using C++ APIs
class TimeMap {
public:
    /** Initialize your data structure here. */
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        _data[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        auto it = _data.find(key);
        if(it == _data.end())
            return "";
        
        // binary search to find first element grater timestamp, i.e., upper_bound
        auto &values = it->second;
        auto comp = [](const pair<int,string> &p1, const pair<int,string> &p2){return p1.first<p2.first;};
        int upper = distance(values.begin(), upper_bound(values.begin(), values.end(), make_pair(timestamp,""), comp));
        return upper>0?it->second[upper-1].second:"";
    }

private:
    //xxx function<bool(const pair<int,string>&, const pair<int,string>&)> comp = [](const pair<int,string> &p1, const pair<int,string> &p2){return p1.first<p2.first;};
    unordered_map<string, vector<pair<int,string>>> _data;  // for a given key, values are sorted by timestamp according to the problem definition
};


// using std::map
class TimeMap {
public:
    /** Initialize your data structure here. */
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        _data[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        auto it = _data.find(key);
        if(it == _data.end())
            return "";
        auto timeIt = it->second.upper_bound(timestamp);
        return timeIt==it->second.begin()?"":prev(timeIt)->second;
    }
    
private:
    unordered_map<string, map<int,string>> _data;
};
