#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

template<class T>
void printVector(const vector<T> &vec)
{
  for(auto e : vec)
    cout << e << " ";
  cout << endl;
}

template<class T>
void printMatrix(const vector<vector<T>> &matrix)
{
  for(auto vec : matrix)
    printVector(vec);
}
