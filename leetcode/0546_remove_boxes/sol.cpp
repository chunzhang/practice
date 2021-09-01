/*
  You are given several boxes with different colors represented by different positive numbers.

  You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), remove them and get k * k points.

  Return the maximum points you can get.

 

  Example 1:

  Input: boxes = [1,3,2,2,2,3,4,3,1]
  Output: 23
  Explanation:
  [1, 3, 2, 2, 2, 3, 4, 3, 1] 
  ----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
  ----> [1, 3, 3, 3, 1] (1*1=1 points) 
  ----> [1, 1] (3*3=9 points) 
  ----> [] (2*2=4 points)
  Example 2:

  Input: boxes = [1,1,1]
  Output: 9
  Example 3:

  Input: boxes = [1]
  Output: 1
 

  Constraints:

  1 <= boxes.length <= 100
  1 <= boxes[i] <= 100
*/

// DP with memoization, O(N^4) time complexity, O(N^3) space complexity
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        // dp(l,r,k): max score using boxes[l,...,r] and k trailing boxes same as boxes[r], i.e., boxes[r]==boxes[r+1]==boxes[r+k]
        // -- by adding the k-th dimension, we captures the "order" of removal, i.e., some boxes after r are removed first to make boxes[r]==boxes[r+1]==boxes[r+k]
        // -- it can be noted that dp(l,r,k)==dp(l,r+1,k-1)==...==dp(l,r+k,0)
        // -- case 1: we can remove the trailing (k+1) boxes first, i.e., dp(l,r-1,0)+(k+1)^2
        // -- case 2: for boxes[p]==boxes[r], l<=p<r, we can remove everything between p and j first, and then remove p with the (k+1) trailing boxes
        //            dp(l,r,k) = max{dp(l,p,k+1)+dp(p+1,j-1,0)}
        memset(_mem, 0, sizeof(_mem));
        return dp(boxes, 0, boxes.size()-1, 0);
    }
    
private:
    int _mem[100][100][100];
    int dp(vector<int> &boxes, int l, int r, int k) {
        if(l > r)
            return 0;
        if(_mem[l][r][k])
            return _mem[l][r][k];
        
        int ans = dp(boxes,l,r-1,0) + (k+1)*(k+1);  // case 1
        for(int p=l; p<r; ++p) {
            if(boxes[p] == boxes[r]) {
                ans = max(ans, dp(boxes, l,p,k+1)+dp(boxes, p+1,r-1,0));  // case 2
            }
        }
        
        _mem[l][r][k] = ans;
        return ans;
    }
};

// Same idea with DP, faster
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        memset(_mem, 0, sizeof(_mem));
        return dp(boxes, 0, boxes.size()-1, 0);
    }
    
private:
    int _mem[100][100][100];
    int dp(vector<int> &boxes, int l, int r, int k) {
        if(l > r)
            return 0;
        
        // since dp(l,r,k)==dp(l,r+1,k-1)=..., we only need to solve the base case
        while(r>0 && boxes[r]==boxes[r-1]) {
            --r;
            ++k;
        }

        if(_mem[l][r][k])
            return _mem[l][r][k];

        
        int ans = dp(boxes,l,r-1,0) + (k+1)*(k+1);  // case 1
        for(int p=l; p<r; ++p) {
            if(boxes[p] == boxes[r]) {
                ans = max(ans, dp(boxes, l,p,k+1)+dp(boxes, p+1,r-1,0));  // case 2
            }
        }
        
        _mem[l][r][k] = ans;
        return ans;
    }
};


// Same idea with DP, but even faster
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        memset(_mem, 0, sizeof(_mem));
        return dp(boxes, 0, boxes.size()-1, 0);
    }
    
private:
    int _mem[100][100][100];
    int dp(vector<int> &boxes, int l, int r, int k) {
        if(l > r)
            return 0;
        if(_mem[l][r][k])
            return _mem[l][r][k];
        
        // since dp(l,r,k)==dp(l,r+1,k-1)=..., we only need to solve the base case
        int delta = 0;
        while(r>0 && boxes[r]==boxes[r-1]) {
            --r;
            ++k;
            ++delta;
        }
        
        int ans = dp(boxes,l,r-1,0) + (k+1)*(k+1);  // case 1
        for(int p=l; p<r; ++p) {
            if(boxes[p] == boxes[r]) {
                ans = max(ans, dp(boxes, l,p,k+1)+dp(boxes, p+1,r-1,0));  // case 2
            }
        }
        
        _mem[l][r][k] = ans;
        for(int i=1; i<=delta; ++i) {
            _mem[l][r+i][k-i] = ans;
        }
        
        return ans;
    }
};


// reference code from HuaHua, even faster
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        len_ = vector<int>(boxes.size());
        for (int i = 1; i < boxes.size(); ++i)
            if (boxes[i] == boxes[i - 1]) len_[i] = len_[i - 1] + 1;  // collapse length
        return dfs(boxes, 0, boxes.size() - 1, 0);
    }
private:
    unordered_map<int, int> m_;
    vector<int> len_;
    int dfs(const vector<int>& boxes, int l, int r, int k) {
        if (l > r) return 0;
        k += len_[r];
        r -= len_[r];
        int key = (l * 100 + r) * 100 + k;
        auto it = m_.find(key);
        if (it != m_.end()) return it->second;    
        int& ans = m_[key];
        ans = dfs(boxes, l, r - 1, 0) + (k + 1) * (k + 1);
        for (int i = l; i < r; ++i)
            if (boxes[i] == boxes[r])
                ans = max(ans, dfs(boxes, l, i, k + 1) + dfs(boxes, i + 1, r - 1, 0));
        return ans;
    }
};

// official brute-force solution (in Java)
public class Solution {
    public int removeBoxes(int[] boxes) {
        return remove(boxes);
    }
   
    public int remove(int[] boxes) {
        if (boxes.length == 0) {
            return 0;
        }
        
        int res = 0;
    
        for (int i = 0, j = i + 1; i < boxes.length; i++) {
            while (j < boxes.length && boxes[i] == boxes[j]) {
                j++;
            }
            
            int[] newboxes = new int[boxes.length - (j - i)];
            for (int k = 0, p = 0; k < boxes.length; k++) {
                if (k == i) {
                    k = j;
                }
                if (k < boxes.length) {
                    newboxes[p++] = boxes[k];
                }
            }
            res = Math.max(res, remove(newboxes) + (j - i) * (j - i));
        }
    
        return res;
    }
};
