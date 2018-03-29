/*
  On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.

  Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.

  Return the smallest possible value of D.

  Example:

  Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
  Output: 0.500000
  Note:

  stations.length will be an integer in range [10, 2000].
  stations[i] will be an integer in range [0, 10^8].
  K will be an integer in range [1, 10^6].
  Answers within 10^-6 of the true value will be accepted as correct.
*/

#include "../common/common.h"

using namespace std;

// The DP solution has too high complexity
// -- O(N*K^2)
class Solution1 {
public:
  double minmaxGasDist(vector<int>& stations, int K) {
    // Define DP[s][k] as the min max-dist in [0, ..., s] when k more
    // stations are added within that range
    int N = stations.size();
    vector<vector<double>> DP(N, vector<double>(K+1, 0.0));
        
    for(int s=1; s<N; ++s) {
      for(int k=0; k<=K; ++k) {
	double minmax = INT_MAX;
	for(int k2=0; k2<=k; ++k2) {
	  double maxDist = max(DP[s-1][k2], ((double)stations[s]-(double)stations[s-1])/(double)(k-k2+1));
	  minmax = min(minmax, maxDist);
	}
	DP[s][k] = minmax;
      }
    }
        
    return DP[N-1][K];
  }
};

// DP solution can be easily modified to use 1-D array
class Solution2 {
public:
  double minmaxGasDist(vector<int>& stations, int K) {
    // Define DP[s][k] as the min max-dist in [0, ..., s] when k more
    // stations are added within that range
    int N = stations.size();
    vector<double> DP(K+1, 0.0);  // make it 1-D to save some memory
        
    for(int s=1; s<N; ++s) {
      vector<double> DPN(K+1, 0.0);
      for(int k=0; k<=K; ++k) {
	double minmax = INT_MAX;
	for(int k2=0; k2<=k; ++k2) {
	  double maxDist = max(DP[k2], ((double)stations[s]-(double)stations[s-1])/(double)(k-k2+1));
	  minmax = min(minmax, maxDist);
	}
	DPN[k] = minmax;
      }
      DP.swap(DPN);
    }
        
    return DP[K];
  }
};

// Greedy solution
// -- Add station one by one. Each time, the station needs to be added to the interval
//    with current max distance
// -- Use a heap to keep track of which interval has max distance
// -- Runtime complexity is O(K*lg(N)), which is still too high (given input ranges)
class Solution3 {
public:
  double minmaxGasDist(vector<int>& stations, int K) {
    auto comp = [](const pair<int,int> &d1, const pair<int,int> &d2) {
      // pair.first is distance between to original stations (i.e., stations[i+1]-stations[i])
      // pair.second is the number of additionally added stations + 1
      return (double)d1.first/d1.second > (double)d2.first/d2.second;
    };
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> q(comp);
    for(int i=0; i<stations.size()-1; ++i) {
      q.push(make_pair(stations[i+1]-stations[i], 1));  // initially no station is added
    }

    // Greedily add station one by one
    for(int i=0; i<K; ++i) {
      pair<int,int> interval = q.top();
      q.pop();
      interval.second += 1;
      q.push(interval);
    }

    return (double)q.top().first / q.top().second;
  }
};

// Binary search solution
// -- Guess a max distance D, and see if this can be satisfied by adding at most K stations
// -- Complexity is O(N*lg(D)), where D is the distance between first and last original station
class Solution {
public:
  double minmaxGasDist(vector<int>& stations, int K) {
    double lo = 0;
    double hi = stations.back()-stations.front();  // this can effectively reduce search range
    while(hi-lo > 10e-6) {
      double mid = (hi+lo) / 2;
      int num = numStationsNeeded(stations, mid);
      if(num > K)
	lo = mid;
      else
	hi = mid;
    }

    return (hi+lo)/2;
  }

  // Compute how many stations needs to be added such that
  // the max distance between stations does not go beyond targetDist
  int numStationsNeeded(const vector<int> &stations, double targetDist) {
    int num = 0;
    for(int i=0; i<stations.size()-1; ++i)
      num += (stations[i+1]-stations[i]) / targetDist;
    return num;
  }
};


int main(int argc, char *argv[])
{
  vector<int> stations = readVector(argc, argv);
  int K = stations.back();
  stations.pop_back();

  Solution sol;
  double res = sol.minmaxGasDist(stations, K);
  cout << "res: " << res << endl;

  return 0;
}
