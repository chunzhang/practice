/*
An image is represented by an m x n integer grid image where image[i][j] represents the pixel value of the image.

You are also given three integers sr, sc, and newColor. You should perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with newColor.

Return the modified image after performing the flood fill.

 

Example 1:


Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.
Example 2:

Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, newColor = 2
Output: [[2,2,2],[2,2,2]]
 

Constraints:

m == image.length
n == image[i].length
1 <= m, n <= 50
0 <= image[i][j], newColor < 216
0 <= sr < m
0 <= sc < n
*/

// DFS
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if(image[sr][sc] != newColor)
            dfs(image, sr, sc, image[sr][sc], newColor);
        return image;
    }
    
private:
    void dfs(vector<vector<int>> &image, int i, int j, int oldColor, int newColor) {
        if(i<0 || i>=image.size() || j<0 || j>=image[0].size() || image[i][j]!=oldColor)
            return;
        image[i][j] = newColor;
        dfs(image, i+1, j, oldColor, newColor);
        dfs(image, i-1, j, oldColor, newColor);
        dfs(image, i, j+1, oldColor, newColor);
        dfs(image, i, j-1, oldColor, newColor);
    }
};


// BFS
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        const vector<pair<int,int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
        const int M = image.size();
        const int N = image[0].size();
        // BFS
        int oldColor = image[sr][sc];
        queue<pair<int,int>> q;
        if(oldColor != newColor) {
            q.push({sr,sc});
            image[sr][sc] = newColor;  // mark as visited
        }
        while(q.size()) {
            auto node = q.front();
            q.pop();
            for(auto &d : dir) {
                int ni = node.first + d.first;
                int nj = node.second + d.second;
                if(ni>=0 && ni<M && nj>=0 && nj<N && image[ni][nj]==oldColor) {
                    image[ni][nj] = newColor;  // mark as visited
                    q.push({ni,nj});
                }
            }
        }
        
        return image;
    }
};
