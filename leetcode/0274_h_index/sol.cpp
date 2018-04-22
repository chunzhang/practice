/*
  Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

  According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

  For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

  Note: If there are several possible values for h, the maximum one is taken as the h-index.
*/

// O(N) solution based on bucketization
// -- For N papers, the h-index can only range from [0, N]
// -- Each bucket keeps the number of papers with that citation number. The
//    key is that for paper with citation greater than N, it also falls into
//    bucket[N] as it anyway contributes to h-index
// -- The cumulative sum from buckets[N...i] is the number of papers with citations
//    >= i
class Solution {
public:
  int hIndex(vector<int>& citations) {
    int N = citations.size();
    vector<int> buckets(N+1, 0);
    for(int c : citations) {
      if(c >= N)
	buckets[N]++;
      else
	buckets[c]++;
    }
        
    int csum = 0;
    for(int h=N; h>=0; --h) {
      csum += buckets[h];  // number of papers with citations >= h so far
      if(csum >= h)
	return h;
    }
        
    return 0;  // We can't reach here, but add this final return anyway
  }
};

// O(NlgN) sorting based approach
class Solution {
public:
  int hIndex(vector<int>& citations) {
    sort(citations.begin(), citations.end(), greater<int>());
    int hIdx = 0;
    for(int i=0; i<citations.size(); ++i) {
      if(citations[i] >= i+1)
	hIdx = i + 1;
      else
	break;
    }
    return hIdx;
  }
};
