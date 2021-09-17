/*
  Given the head of a linked list, return the list after sorting it in ascending order.

  Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?

 

  Example 1:


  Input: head = [4,2,1,3]
  Output: [1,2,3,4]
  Example 2:


  Input: head = [-1,5,3,4,0]
  Output: [-1,0,3,4,5]
  Example 3:

  Input: head = []
  Output: []
 

  Constraints:

  The number of nodes in the list is in the range [0, 5 * 10^4].
  -10^5 <= Node.val <= 10^5
*/

// merge sort
// use slow/fast pointer to get list middle point (instead, one can also pass list length to achieve the same)
// time complexity: O(NlgN)
// space complexity: O(lgN) -- from recursive depth
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next)
            return head;
        
        // use slow/fast pointer to break the list into two halves
        ListNode *slow = head;
        ListNode *fast = head;
        while(fast) {
            fast = fast->next;
            fast = fast?fast->next:nullptr;
            if(fast)
                slow = slow->next;
        }
        
        ListNode *head2 = slow->next;
        slow->next = nullptr;
        return merge2Lists(sortList(head), sortList(head2));  // divid and conquer
    }
    
private:
    ListNode *merge2Lists(ListNode *l1, ListNode *l2) {
        ListNode dh(0);  // dummy head
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


// bottom-up merge sort
// time complexity: O(NlgN)
// space complexity: O(1)
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        // bottom-up merge, iterate through list size from 1, 2, 4, ...
        ListNode dh(0);  // dummy head
        dh.next = head;
        const int len = length(head);
        for(int sz=1; sz<len; sz*=2) {
            ListNode *tail = &dh;  // tail of processed portion of the list
            ListNode *cur = dh.next;  // starting node to be sorted
            while(cur) {
                ListNode *h1 = cur;
                ListNode *t1 = getList(h1, sz);
                ListNode *h2 = t1?t1->next:nullptr;
                ListNode *t2 = getList(h2, sz);
                cur = t2?t2->next:nullptr;
                
                if(t1) t1->next = nullptr;
                if(t2) t2->next = nullptr;
                auto sorted = merge2Lists(h1,h2);
                tail->next = sorted.first;
                tail = sorted.second;
                tail->next = cur;
            }
        }

        return dh.next;
    }
    
private:
    // compute length of the list
    int length(ListNode *head) {
        int len = 0;
        while(head) {
            ++len;
            head = head->next;
        }
        return len;
    }
    
    // extract list of given size, and return its tail
    ListNode* getList(ListNode *head, int sz) {
        while(--sz>0 && head) {
            head = head->next;
        }
        
        return head;
    }
    
    // merge two sorted list, return {head, tail} of the merged list
    pair<ListNode*,ListNode*> merge2Lists(ListNode *l1, ListNode *l2) {
        ListNode dh(0);  // dummy head
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
        while(cur->next)
            cur = cur->next;
        return {dh.next,cur};
    }
};


// bottom-up ref impl from HuaHua
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        // 0 or 1 element, we are done.
        if (!head || !head->next) return head;
    
        int len = 1;
        ListNode* cur = head;
        while (cur = cur->next) ++len;
    
        ListNode dummy(0);
        dummy.next = head;
        ListNode* l;
        ListNode* r;
        ListNode* tail;
        for (int n = 1; n < len; n <<= 1) {      
            cur = dummy.next; // partial sorted head
            tail = &dummy;
            while (cur) {
                l = cur;
                r = split(l, n);
                cur = split(r, n);
                auto merged = merge(l, r);
                tail->next = merged.first;
                tail = merged.second;
            }
        }      
        return dummy.next;
    }
private:
    // Splits the list into two parts, first n element and the rest.
    // Returns the head of the rest.
    ListNode* split(ListNode* head, int n) {    
        while (--n && head)
            head = head->next;
        ListNode* rest = head ? head->next : nullptr;
        if (head) head->next = nullptr;
        return rest;
    }
  
    // Merges two lists, returns the head and tail of the merged list.
    pair<ListNode*, ListNode*> merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val > l2->val) swap(l1, l2);
            tail->next = l1;
            l1 = l1->next;
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        while (tail->next) tail = tail->next;
        return {dummy.next, tail};
    }
};
