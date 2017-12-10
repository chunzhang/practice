#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
#include <queue>

//xxx using namespace std;

struct Interval
{
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

std::vector<Interval> makeIntervals(int argc, char *argv[]);
void printIntervals(const std::vector<Interval> &intervals);
std::ostream& operator <<(std::ostream &os, const Interval &interval);

/* BST */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* makeTree(int argc, char *argv[]);
void printTree(TreeNode *root);
void releaseTree(TreeNode *root);

/* List */


/* Array */
template<class T>
void printVector(const std::vector<T> &vec)
{
  for(auto e : vec)
    std::cout << e << " ";
  std::cout << std::endl;
}

template<class T>
void printMatrix(const std::vector<std::vector<T>> &matrix)
{
  for(auto vec : matrix)
    printVector(vec);
}

std::vector<int> readVector(int argc, char *argv[]);

#endif
