/*
You are given a series of video clips from a sporting event that lasted time seconds. These video clips can be overlapping with each other and have varying lengths.

Each video clip is described by an array clips where clips[i] = [starti, endi] indicates that the ith clip started at starti and ended at endi.

We can cut these clips into segments freely.

For example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event [0, time]. If the task is impossible, return -1.

 

Example 1:

Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
Output: 3
Explanation: 
We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
Then, we can reconstruct the sporting event as follows:
We cut [1,9] into segments [1,2] + [2,8] + [8,9].
Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].
Example 2:

Input: clips = [[0,1],[1,2]], time = 5
Output: -1
Explanation: We can't cover [0,5] with only [0,1] and [1,2].
Example 3:

Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], time = 9
Output: 3
Explanation: We can take clips [0,4], [4,7], and [6,9].
Example 4:

Input: clips = [[0,4],[2,8]], time = 5
Output: 2
Explanation: Notice you can have extra video after the event ends.
 

Constraints:

1 <= clips.length <= 100
0 <= starti <= endi <= 100
1 <= time <= 100
*/

// DP bottom-up, O(N^3) time complexity
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        // dp(i,j): min clips to cover time [i:j]
        // dp(i,j) = min{dp(i,l)+dp(r,j)+1}, for each clip that covers [l,r]
        
        vector<vector<int>> dp(time+1, vector<int>(time+1, 0));
        for(int len=2; len<=time+1; ++len) {
            for(int i=0,j=i+len-1; j<=time; ++i,++j) {
                dp[i][j] = INT_MAX;
                for(int c=0; c<clips.size(); ++c) {
                    int l = clips[c][0];
                    int r = clips[c][1];
                    if(r<=i || l>=j)  // no overlap with current range
                        continue;
                    int nLeft = (l>=i?dp[i][l]:0);
                    int nRight = (r<=j?dp[r][j]:0);
                    if(nLeft==INT_MAX || nRight==INT_MAX)
                        break;  // no solution exist
                    dp[i][j] = min(dp[i][j], nLeft+nRight+1);
                }
            }
        }
        
        return dp[0][time]==INT_MAX?-1:dp[0][time];
    }
};


// DP with memoization, O(N^3) time complexity
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        _mem = vector<vector<int>>(time+1, vector<int>(time+1, 0));
        int ans = dp(clips, 0, time);
        return ans==INT_MAX?-1:ans;
    }
    
private:
    vector<vector<int>> _mem;  // memoization, i.e., min clips to cover [i:j]
    int dp(const vector<vector<int>> &clips, int i, int j) {
        if(i>=j)
            return 0;
        if(_mem[i][j] != 0)
            return _mem[i][j];
        
        _mem[i][j] = INT_MAX;
        
        for(const vector<int> &clip : clips) {  // clip to use, so as to break it into sub-problems
            int l = clip[0];
            int r = clip[1];
            if(r<=i || l>=j)
                continue;
            
            int nClips = 1;
            if(i < l) {
                int nLeft = dp(clips,i,l);
                if(nLeft == INT_MAX)
                    break;  // no need to continue, as no solution could exist
                nClips += nLeft;
            }
            if(j > r) {
                int nRight = dp(clips,r,j);
                if(nRight == INT_MAX)
                    break;
                nClips += nRight;
            }
            _mem[i][j] = min(_mem[i][j], nClips);
        }
    
        return _mem[i][j];
    }
};


// reference code from Huahua, DP O(N^3)
class Solution {
public:
  int videoStitching(vector<vector<int>>& clips, int T) {
    constexpr int kInf = 101;
    // dp[i][j] := min clips to cover range [i, j]
    vector<vector<int>> dp(T + 1, vector<int>(T + 1, kInf));   
    for (const auto& c : clips) {
      int s = c[0];
      int e = c[1];
      for (int l = 1; l <= T; ++l) {
        for (int i = 0; i <= T - l; ++i) {
          int j = i + l;
          if (s > j || e < i) continue;
          if (s <= i && e >= j) dp[i][j] = 1;
          else if (e >= j) dp[i][j] = min(dp[i][j], dp[i][s] + 1);
          else if (s <= i) dp[i][j] = min(dp[i][j], dp[e][j] + 1);
          else dp[i][j] = min(dp[i][j], dp[i][s] + 1 + dp[e][j]);          
        }
      }
    }
    return dp[0][T] == kInf ? -1 : dp[0][T];
  }
};


// Greedy algorithm, O(NlgN) time complexity
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        // Greedy algorithm: for all clips that starts before current time line, pick the one that ends latest
        // O(NlgN), as each clip is scanned only once, but needs sorting
        
        sort(clips.begin(), clips.end(), [](vector<int> &a, vector<int> &b){return a[0]<b[0];});  // sort clips by starting time
        
        int timeline = 0;  // current timeline (continuously covered)
        int ans = 0;
        int i = 0;  // current clip
        while(i<clips.size()) {
            if(clips[i][0]>timeline/*cannot cover continuously*/ || timeline>=time/*already covered all time*/)
                break;
            
            int nextTimeline = timeline;  // next timeline
            // for all clips that starts before or at timeline, use the one that ends latest
            while(i<clips.size() && clips[i][0]<=timeline) {
                nextTimeline = max(nextTimeline, clips[i][1]);
                ++i;
            }
            
            timeline = nextTimeline;
            ++ans;
        }
        
        if(timeline<time)
            return -1;
        
        return ans;
    }
};
