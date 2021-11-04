/*
a)	需要将timestamp tokenized成数字表示的字符，  - “mon 11:00 am”： mon -> 1, 11:00 am -> 11:00 输出 “11100”-  “fri 2:00 pm”:   mon -> 1,  2:00 pm -> 14:00 输出 “51400”
b)	将这个time range离散化成每五分钟一个的timestamp后输出 - “mon 11:00 am”，  “mon 11:20 am” 输出 "11100","11105","11110","11115","11120"
*/


#include "../common/common.h"

struct Time {
    Time(int d, int h, int m) : dd(d), hh(h), mm(m) {}
    int getTime() {return dd*10000+hh*100+mm;}
    void addMins(int m) {
        mm += m;
        if(mm >= 60) {
            mm -= 60;
            ++hh;
        }
        if(hh >= 24) {
            hh -= 24;
            ++dd;
        }
        if(dd >= 7) {
            assert(0);  // no spec to handle this situation
        }
    }
    
    int dd;
    int hh;
    int mm;
};

ostream& operator<<(ostream &os, const Time &t) {
    os << t.dd << ", " << t.hh << ", " << t.mm;
    return os;
}



class Solution {
public:    
    vector<int> timeSeries(const string &open, const string &close) {
        Time from = decodeTime(open);
        Time to = decodeTime(close);
        cout << from << endl;
        cout << to << endl;

        vector<int> ans;
        while(from.dd<to.dd || from.hh<to.hh || from.mm<to.mm) {
            ans.push_back(from.getTime());
            from.addMins(5);
        }
        ans.push_back(to.getTime());
        
        return ans;
    }

private:
    unordered_map<string,int> _day = {{"mon",1},{"tue",2},{"wed",3},{"thu",4},{"fri",5},{"sat",6},{"sun",7}};    
    Time decodeTime(const string &calendarTime) {
        istringstream iss(calendarTime);
        string day;
        string time;
        string ampm;
        iss >> day >> time >> ampm;
        return Time(_day[day], stoi(time.substr(0,2))+(ampm=="am"?0:12), stoi(time.substr(3,2)));
    }

};


int main(int argc, char *argv[]) {
    Solution sol;
    auto ans = sol.timeSeries("mon 11:23 pm", "tue 11:39 pm");
    for(int t : ans)
        cout << t << endl;

    return 0;
}
