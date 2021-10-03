/*
You are given an array of strings equations that represent relationships between variables where each string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.

Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.

 

Example 1:

Input: equations = ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
There is no way to assign the variables to satisfy both equations.
Example 2:

Input: equations = ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
Example 3:

Input: equations = ["a==b","b==c","a==c"]
Output: true
Example 4:

Input: equations = ["a==b","b!=c","c==a"]
Output: false
Example 5:

Input: equations = ["c==c","b==d","x!=z"]
Output: true
 

Constraints:

1 <= equations.length <= 500
equations[i].length == 4
equations[i][0] is a lowercase letter.
equations[i][1] is either '=' or '!'.
equations[i][2] is '='.
equations[i][3] is a lowercase letter.
*/

// union find
// time complexity: O(N)
// space complexity: O(1)
class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        // union find
        vector<char> parent(128);
        for(char c=0; c<parent.size(); ++c)
            parent[c] = c;
        
        function<char(char)> getParent = [&](char c) {
            if(parent[c] != c)
                parent[c] = getParent(parent[c]);
            return parent[c];
        };
        
        function<void(char,char)>  merge = [&](char c1, char c2) {
            parent[getParent(c1)] = getParent(c2);
        };
        
        for(auto &eq : equations) {
            if(eq[1] == '=')
                merge(eq[0], eq[3]);
        }
        
        for(auto &eq : equations) {
            if(eq[1]=='!' && getParent(eq[0])==getParent(eq[3]))
                return false;
        }
        
        return true;
    }
};


// ref impl: DFS to find connected components with coloring (in Java)
// time complexity: O(N)
// space complexity: O(1)
class Solution {
    public boolean equationsPossible(String[] equations) {
        ArrayList<Integer>[] graph = new ArrayList[26];
        for (int i = 0; i < 26; ++i)
            graph[i] = new ArrayList();

        for (String eqn: equations) {
            if (eqn.charAt(1) == '=') {
                int x = eqn.charAt(0) - 'a';
                int y = eqn.charAt(3) - 'a';
                graph[x].add(y);
                graph[y].add(x);
            }
        }

        int[] color = new int[26];
        int t = 0;
        for (int start = 0; start < 26; ++start) {
            if (color[start] == 0) {
                t++;
                Stack<Integer> stack = new Stack();
                stack.push(start);
                while (!stack.isEmpty()) {
                    int node = stack.pop();
                    for (int nei: graph[node]) {
                        if (color[nei] == 0) {
                            color[nei] = t;
                            stack.push(nei);
                        }
                    }
                }
            }
        }

        for (String eqn: equations) {
            if (eqn.charAt(1) == '!') {
                int x = eqn.charAt(0) - 'a';
                int y = eqn.charAt(3) - 'a';
                if (x == y || color[x] != 0 && color[x] == color[y])
                    return false;
            }
        }

        return true;
    }
};
