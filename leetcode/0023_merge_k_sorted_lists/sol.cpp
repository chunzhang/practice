/*
  You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

  Merge all the linked-lists into one sorted linked-list and return it.

 

  Example 1:

  Input: lists = [[1,4,5],[1,3,4],[2,6]]
  Output: [1,1,2,3,4,4,5,6]
  Explanation: The linked-lists are:
  [
  1->4->5,
  1->3->4,
  2->6
  ]
  merging them into one sorted list:
  1->1->2->3->4->4->5->6
  Example 2:

  Input: lists = []
  Output: []
  Example 3:

  Input: lists = [[]]
  Output: []
 

  Constraints:

  k == lists.length
  0 <= k <= 10^4
  0 <= lists[i].length <= 500
  -10^4 <= lists[i][j] <= 10^4
  lists[i] is sorted in ascending order.
  The sum of lists[i].length won't exceed 10^4.
*/

// iterative, using prioirty queue
// O(NlogK) time complexity, O(K) space complexity
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto comp = [](const ListNode *n1, ListNode *n2) {
            return n1->val > n2->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> pq(comp);
        for(ListNode *node : lists) {
            if(node)
                pq.push(node);
        }
        
        ListNode dummyHead(0);
        ListNode *cur = &dummyHead;
        while(!pq.empty()) {
            ListNode *node = pq.top();
            pq.pop();
            cur->next = node;
            cur = node;
            if(node->next)
                pq.push(node->next);
        }
        
        return dummyHead.next;
    }
};


// divide and conquer: recursively merge two lists
// time complexity: O(NlgK), i.e., lgK of recursion depth, and at each recursion we need to merge each node once (totally N nodes)
// space complexity: O(lgK), i.e., recursion depth
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size());
    }
    
private:
    // divide and conquer, recursively merge two lists
    ListNode* merge(const vector<ListNode*> &lists, int lo, int hi) {
        if(lo >= hi)
            return nullptr;
        if(hi-lo == 1)
            return lists[lo];
        
        int mid = lo + (hi-lo)/2;
        ListNode *list1 = merge(lists, lo, mid);
        ListNode *list2 = merge(lists, mid, hi);
        return merge2Lists(list1, list2);
    }
    
    // merge two lists
    ListNode* merge2Lists(ListNode *l1, ListNode *l2) {
        ListNode dh(0);
        ListNode *cur = &dh;
        while(l1 && l2) {
            if(l1->val <= l2->val) {
                cur->next = l1;
                l1 = l1->next;
            }
            else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        
        cur->next = l1?l1:l2;
        return dh.next;
    }
};


// ref impl from HuaHua
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
private:
    ListNode* merge(vector<ListNode*>& lists, int l, int r) {
        if (l > r) return nullptr;
        if (l == r) return lists[l];
        if (l + 1 == r) return mergeTwoLists(lists[l], lists[r]);
        int m = l + (r - l) / 2;
        auto l1 = merge(lists, l, m);
        auto l2 = merge(lists, m + 1, r);
        return mergeTwoLists(l1, l2);
    }
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val > l2->val) swap(l1, l2);                
            tail->next = l1;
            l1 = l1->next;
            tail = tail->next;
        }        
        if (l1) tail->next = l1;
        if (l2) tail->next = l2;        
        return dummy.next;
    }
};
