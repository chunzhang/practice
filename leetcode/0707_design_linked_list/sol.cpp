/*
Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node.
If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.

Implement the MyLinkedList class:

MyLinkedList() Initializes the MyLinkedList object.
int get(int index) Get the value of the indexth node in the linked list. If the index is invalid, return -1.
void addAtHead(int val) Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
void addAtTail(int val) Append a node of value val as the last element of the linked list.
void addAtIndex(int index, int val) Add a node of value val before the indexth node in the linked list. If index equals the length of the linked list, the node will be appended to the end of the linked list. If index is greater than the length, the node will not be inserted.
void deleteAtIndex(int index) Delete the indexth node in the linked list, if the index is valid.
 

Example 1:

Input
["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
[[], [1], [3], [1, 2], [1], [1], [1]]
Output
[null, null, null, null, 2, null, 3]

Explanation
MyLinkedList myLinkedList = new MyLinkedList();
myLinkedList.addAtHead(1);
myLinkedList.addAtTail(3);
myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
myLinkedList.get(1);              // return 2
myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
myLinkedList.get(1);              // return 3
 

Constraints:

0 <= index, val <= 1000
Please do not use the built-in LinkedList library.
At most 2000 calls will be made to get, addAtHead, addAtTail, addAtIndex and deleteAtIndex.
*/

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */


// using singlely linked list
class MyLinkedList {
public:
    /** Initialize your data structure here. */
    MyLinkedList() : _dh(0), _len(0) {
        _tail = &_dh;
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        //cout << "get(" << index << ")" << endl;
        if(index<0 || index>=_len)
            return -1;
        ListNode *node = _dh.next;
        while(index--)
            node = node->next;
        return node->val;
        //debug();
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        //cout << "addAtHead(" << val << ")" << endl;
        ListNode *node = new ListNode(val);
        node->next = _dh.next;
        _dh.next = node;
        if(!_len)
            _tail = node;
        ++_len;
        //debug();
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        //cout << "addAtTail(" << val << ")" << endl;
        ListNode *node = new ListNode(val);
        _tail->next = node;
        _tail = node;
        ++_len;
        //debug();
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        //cout << "addAtIndex(" << index << "," << val << ")" << endl;
        if(index<0 || index>_len)
            return;
        ListNode *node = new ListNode(val);
        ListNode *prev = &_dh;  // insert after this node
        int idx = index;
        while(idx--)
            prev = prev->next;
        node->next = prev->next;
        prev->next = node;
        if(index == _len)
            _tail = node;
        ++_len;
        //debug();
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        //cout << "deleteAtIndex(" << index << ")"  << endl;
        if(index<0 || index>=_len)
            return;
        
        ListNode *prev = &_dh;  // delete the node after this
        int idx = index;
        while(idx--)
            prev = prev->next;
        ListNode *node = prev->next;  // node to be deleted
        prev->next = node->next;
        if(index == _len-1)
            _tail = prev;
        delete node;
        --_len;
        //debug();
    }
    
private:
    ListNode _dh;  // dummy head
    ListNode *_tail;
    int _len;
    
    void debug() {
        cout << "length=" << _len << ", tail val=" << _tail->val << endl;
        for(ListNode *node=_dh.next; node; node=node->next)
            cout << node->val << ", ";
        cout << endl;
    }
};
