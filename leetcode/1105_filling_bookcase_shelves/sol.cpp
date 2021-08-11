/*
We have a sequence of books: the i-th book has thickness books[i][0] and height books[i][1].

We want to place these books in order onto bookcase shelves that have total width shelf_width.

We choose some of the books to place on this shelf (such that the sum of their thickness is <= shelf_width), then build another level of shelf of the bookcase so that the total height of the bookcase has increased by the maximum height of the books we just put down.  We repeat this process until there are no more books to place.

Note again that at each step of the above process, the order of the books we place is the same order as the given sequence of books.  For example, if we have an ordered list of 5 books, we might place the first and second book onto the first shelf, the third book on the second shelf, and the fourth and fifth book on the last shelf.

Return the minimum possible height that the total bookshelf can be after placing shelves in this manner.

 

Example 1:


Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelf_width = 4
Output: 6
Explanation:
The sum of the heights of the 3 shelves are 1 + 3 + 2 = 6.
Notice that book number 2 does not have to be on the first shelf.
 

Constraints:

1 <= books.length <= 1000
1 <= books[i][0] <= shelf_width <= 1000
1 <= books[i][1] <= 1000
*/

class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
        // dp(i): min height after placing the i-th book
        // For book i, it can be placed on the same shelf with previous books
        // dp(i) = min{dp[k-1]+max-height-of-book{k, k+1, ..., i}} for all k while total width of book [k, i] <= shelf_width
        
        const int N = books.size();
        vector<int> dp(N, 0);
        dp[0] = books[0][1];  // first book
        for(int i=1; i<N; ++i) {
            dp[i] = dp[i-1] + books[i][1];  // book-i on a new shelve alone
            int width = books[i][0];
            int height = books[i][1];
            for(int k=i-1; k>=0; --k) {  // book-i can be placed in the same shelve with previous books, i.e., enumerate all possibilities
                width += books[k][0];
                height = max(height, books[k][1]);
                if(width > shelf_width)    // shelve is full
                    break;
                dp[i] = min(dp[i], (k>0?dp[k-1]:0)+height);
            }
        }
        
        return dp[N-1];
    }
};
