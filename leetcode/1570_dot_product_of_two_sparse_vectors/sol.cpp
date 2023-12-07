/*
Given two sparse vectors, compute their dot product.

Implement class SparseVector:

SparseVector(nums) Initializes the object with the vector nums
dotProduct(vec) Compute the dot product between the instance of SparseVector and vec
A sparse vector is a vector that has mostly zero values, you should store the sparse vector efficiently and compute the dot product between two SparseVector.

Follow up: What if only one of the vectors is sparse?

 

Example 1:

Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
Output: 8
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 1*0 + 0*3 + 0*0 + 2*4 + 3*0 = 8
Example 2:

Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
Output: 0
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 0*0 + 1*0 + 0*0 + 0*0 + 0*2 = 0
Example 3:

Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
Output: 6
 

Constraints:

n == nums1.length == nums2.length
1 <= n <= 10^5
0 <= nums1[i], nums2[i] <= 100
*/

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);

class SparseVector {
public:
    
    SparseVector(vector<int> &nums) {
        for(int i=0; i<nums.size(); ++i)
            if(nums[i]) {
                // note emplace_back takes constructor form of pair, rather than init list such as {i,nums[i]}
                _v.emplace_back(i,nums[i]);

                // instead, one can also use _v.push_back({i,nums[i]});
            }
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int prod = 0;
        for(int i=0,j=0; i<_v.size()&&j<vec._v.size(); ) {
            if(_v[i].first == vec._v[j].first)  // can access private member of the same class
                prod += _v[i++].second * vec._v[j++].second;
            else if(_v[i].first < vec._v[j].first)
                ++i;
            else
                ++j;
        }
        return prod;
    }

private:
    vector<pair<int,int>> _v;
};


// Second version of storing non-zero elements as idx-->num hashmap
// Suppose to be better if only one of the vector is sparse
class SparseVector {
public:
    
    SparseVector(vector<int> &nums) {
        for(int i=0; i<nums.size(); ++i)
          if(nums[i])
            _idx2Val[i] = nums[i];
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int prod = 0;
        auto &v1 = _idx2Val.size()<=vec._idx2Val.size() ? _idx2Val : vec._idx2Val;  // v1 being the sparse one
        auto &v2 = _idx2Val.size()<=vec._idx2Val.size() ? vec._idx2Val : _idx2Val;
        for(auto it1=v1.begin(); it1!=v1.end(); ++it1) {
          auto it2 = v2.find(it1->first);
          if(it2 != v2.end())
            prod += it1->second * it2->second;
        }

        return prod;
    }

private:
  unordered_map<int,int> _idx2Val;
};

