/*
Facebook/Amazon/Google

You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:

You only have two baskets, and each basket can only hold a single type of fruit. There is no limit on the amount of fruit each basket can hold.
Starting from any tree of your choice, you must pick exactly one fruit from every tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
Given the integer array fruits, return the maximum number of fruits you can pick.

Example 1:

Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.

Example 2:

Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].

Example 3:

Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].
 

Constraints:

1 <= fruits.length <= 10^5
0 <= fruits[i] < fruits.length
*/

// two pointers/sliding window: find longest sequence with at most two unique numbers
// time: O(N)
// space: O(1)
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int ans = 0;
        unordered_map<int,int> count;  // count fruit type and amount in current sliding window
        for(int i=0,j=0; j<fruits.size(); ) {  // [i,j) is valid sequence
            bool valid = false;
            if(count.size()<2 || count.count(fruits[j])) {
                count[fruits[j++]]++;
                ans = max(ans, j-i);
                valid = true;
            }

            // current fruit not added, move i
            if(!valid) {
                if(--count[fruits[i]] == 0)
                    count.erase(fruits[i]);
                ++i;
            }
        }

        return ans;
    }
};


// same idea, slightly faster (i.e., less max call)
// time: O(N), space: O(1)
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        // find longest sequence with at most two unique numbers
        // two pointers for sliding window
        int ans = 0;
        unordered_map<int,int> count;  // count fruit type and amount in current sliding window
        for(int i=0,j=0; j<fruits.size(); ++j) {  // [i,j) is valid sequence
            count[fruits[j]]++;
            // move i to make [i,j] valid
            while(count.size() > 2) {
                if(--count[fruits[i]] == 0)
                    count.erase(fruits[i]);
                ++i;
            }

            ans = max(ans, j-i+1);
        }

        return ans;
    }
};


// another ref sol (not very intuitive in terms of sliding window move, as the window may not always be valid during the loop)
// time: O(N), space: O(N)
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        // Hash map 'basket' to store the types of fruits.
        unordered_map<int, int> basket;
        int left, right;
        
        // Add fruit from the right index (right) of the window.
        for (left = 0, right = 0; right < fruits.size(); ++right) {
            basket[fruits[right]]++;
            
            // If the current window has more than 2 types of fruit,
            // we remove one fruit from the left index (left) of the window.
            if (basket.size() > 2) {
                basket[fruits[left]]--;
                if (basket[fruits[left]] == 0)
                    basket.erase(fruits[left]);
                left++;
            }
        }
        
        // Once we finish the iteration, the indexes left and right 
        // stands for the longest valid subarray we encountered.
        return right - left;
    }
};
