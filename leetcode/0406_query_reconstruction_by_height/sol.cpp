/*
Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100
*/

#include "../common/common.h"

using namespace std;

class Solution {
public:
  vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
    // 1. sort by height (higher people appear first) -- O(NlgN)
    auto comp = [](const pair<int,int> &p1, const pair<int,int> &p2) {
      return p1.first>p2.first || (p1.first==p2.first && p1.second<p2.second);
    };
    sort(people.begin(), people.end(), comp);

    // 2. after sorting, all elements before p (in the people array) contributes to p.second. As
    //    such, we need to insert p into the result array according to p.second -- O(N^2)
    vector<pair<int,int>> res;
    for(auto &p : people)
      res.insert(res.begin()+p.second, p);
    
    return res;
  }
};

int main(int argc, char *argv[])
{
  vector<int> nums = readVector(argc, argv);
  vector<pair<int,int>> people;
  for(int i=0; i<nums.size(); i+=2) {
    people.push_back({nums[i],nums[i+1]});
  }

  printVector(people, "Before");
  Solution sol;
  auto res = sol.reconstructQueue(people);
  printVector(res, "After");

  return 0;
}
