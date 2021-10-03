/*
You are given an integer array of unique positive integers nums. Consider the following graph:

There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
Return the size of the largest connected component in the graph.

 

Example 1:


Input: nums = [4,6,15,35]
Output: 4
Example 2:


Input: nums = [20,50,9,63]
Output: 2
Example 3:


Input: nums = [2,3,6,7,4,12,21,39]
Output: 8
 

Constraints:

1 <= nums.length <= 2 * 10^4
1 <= nums[i] <= 10^5
All the values of nums are unique.
*/


// union-find: merge the number with all its valid factors
// time complexity: O(sum(sqrt(number))
class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        // union find
        vector<int> parent(*max_element(nums.begin(),nums.end()) + 1);
        for(int n=0; n<parent.size(); ++n)
            parent[n] = n;
        
        function<int(int)> getParent = [&](int n) {
            if(parent[n] != n)
                parent[n] = getParent(parent[n]);
            return parent[n];
        };
        
        function<void(int,int)> merge = [&](int n1, int n2) {
            parent[getParent(n1)] = getParent(n2);  // path compression, no merge by ranking
        };
        
        // key idea: merge the number with all its factors
        for(int n : nums) {
            for(int f=2; f<=sqrt(n); ++f) {  // all possible factors
                if(n%f == 0) {  // valid factor
                    merge(n, f);
                    merge(n, n/f);
                }
            }
        }
        
        // compute size of each cluster
        unordered_map<int,int> counts;
        for(int n : nums)
            ++counts[getParent(n)];
        int ans = 0;
        for(auto &e : counts)
            ans = max(ans, e.second);
        return ans;
    }
};


// brute-force with union-find -- TLE
// time complexity: O(N^2), i.e., try find larget-common-factor of every pair of numbers
class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        build(nums.size());
        for(int i=0; i<nums.size()-1; ++i) {
            for(int j=i+1; j<nums.size(); ++j) {
                if(lcf(nums[i], nums[j]) > 1)
                    merge(i,j);
            }
        }
        
        int ans = 0;
        unordered_map<int,int> counts;
        for(int i=0; i<nums.size(); ++i)
            counts[getParent(i)]++;
        for(auto &e : counts)
            ans = max(ans, e.second);
        return ans;
    }
    
private:
    // find largest common factor
    int lcf(int n1, int n2) {
        if(n1 < n2)
            swap(n1,n2);
        
        int r;
        while(r=n1%n2) {            
            n1 = n2;
            n2 = r;
        }
        
        return n2;
    }
    
    // for union-find
    vector<int> _parent;
    void build(int size) {
        _parent = vector<int>(size);
        for(int i=0; i<size; ++i)
            _parent[i] = i;
    }
    int getParent(int n) {
        if(_parent[n] != n)
            _parent[n] = getParent(_parent[n]);
        return _parent[n];
    }
    void merge(int n1, int n2) {
        _parent[getParent(n1)] = getParent(n2);
    }
};


// ref impl: merge the number with all its prime factors (in Java)
class Solution {

    public int largestComponentSize(int[] A) {
        int maxValue = Arrays.stream(A).reduce(A[0], (x, y) -> x > y ? x : y);
        DisjointSetUnion dsu = new DisjointSetUnion(maxValue);

        HashMap<Integer, Integer> numFactorMap = new HashMap<>();

        // Union-Find on the prime factors.
        for (int num : A) {
            // find all the unique prime factors.
            List<Integer> primeFactors = new ArrayList<>(new HashSet<>(this.primeDecompose(num)));

            // map a number to its first prime factor
            numFactorMap.put(num, primeFactors.get(0));
            // Merge all the groups that contain the prime factors.
            for(int i=0; i<primeFactors.size()-1; ++i)
                dsu.union(primeFactors.get(i), primeFactors.get(i+1));
        }

        // count the size of group one by one
        int maxGroupSize = 0;
        HashMap<Integer, Integer> groupCount = new HashMap<>();
        for (int num : A) {
            Integer groupId = dsu.find(numFactorMap.get(num));
            Integer count = groupCount.getOrDefault(groupId, 0);
            groupCount.put(groupId, count+1);
            maxGroupSize = Math.max(maxGroupSize, count+1);
        }

        return maxGroupSize;
    }

    // sieve of Eratosthenes
    protected List<Integer> primeDecompose(int num) {
        List<Integer> primeFactors = new ArrayList<Integer>();
        int factor = 2;
        while (num >= factor * factor) {
            if (num % factor == 0) {
                primeFactors.add(factor);
                num = num / factor;
            } else {
                factor += 1;
            }
        }
        primeFactors.add(num);
        return primeFactors;
    }

}


class DisjointSetUnion {
    private int[] parent;
    private int[] size;

    public DisjointSetUnion(int size) {
        this.parent = new int[size + 1];
        this.size = new int[size + 1];
        for (int i = 0; i < size + 1; ++i) {
            this.parent[i] = i;
            this.size[i] = 1;
        }
    }

    /** return the component id that the element x belongs to. */
    public int find(int x) {
        if (this.parent[x] != x)
            this.parent[x] = this.find(this.parent[x]);
        return this.parent[x];
    }

    /**
     * merge the two components that x, y belongs to respectively, 
     * and return the merged component id as the result.
     */
    public int union(int x, int y) {
        int px = this.find(x);
        int py = this.find(y);

        // the two nodes share the same group
        if (px == py)
            return px;

        // otherwise, connect the two sets (components)
        if (this.size[px] > this.size[py]) {
            // add the node to the union with less members.
            // keeping px as the index of the smaller component
            int temp = px;
            px = py;
            py = temp;
        }

        // add the smaller component to the larger one
        this.parent[px] = py;
        this.size[py] += this.size[px];
        return py;
    }
};
