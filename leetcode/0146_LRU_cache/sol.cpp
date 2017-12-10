/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

#include "../common/common.h"

using namespace std;

class LRUCache2 {
public:
  struct Node {
    Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) { }
    int key;
    int val;
    Node *prev;
    Node *next;
  };
  
  LRUCache2(int capacity) {
    sz = 0;
    cap = capacity;
    root = new Node(-1, -1);
    tail = new Node(-1, -1);
    root->next = tail;
    tail->prev = root;
  }

  ~LRUCache2() {
    for(auto &elem : elements)
      delete elem.second;
    delete root;
    delete tail;
  }
    
  int get(int key) {
    auto it = elements.find(key);
    if(it != elements.end()) {
      updateNode(it->second);
      cout << "get(" << key << "): " << it->second->val << endl;;
      return it->second->val;
    }

    cout << "get(" << key << "): " << -1 << endl;
    return -1;
  }
    
  void put(int key, int value) {
    auto it = elements.find(key);
    if(it != elements.end()) {
      Node *node = it->second;
      node->val = value;
      updateNode(node);
      return;
    }

    if(sz == cap) {
      Node *toDel = root->next;
      elements.erase(toDel->key);
      delNode(toDel);
      delete toDel;
      --sz;
    }

    Node *toAdd = new Node(key, value);
    elements[key] = toAdd;
    appendNode(toAdd);
    ++sz;
  }

private:
  // update node by moving it to the end of the list
  void updateNode(Node *node) {
    delNode(node);
    appendNode(node);
  }

  // remove node by deleting it from the list
  void delNode(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = nullptr;
    node->prev = nullptr;
  }

  // add node to the end of the list
  void appendNode(Node *node) {
    Node *prevNode = tail->prev;
    node->next = tail;
    tail->prev = node;
    node->prev = prevNode;
    prevNode->next = node;
  }

private:
  int sz;
  int cap;
  unordered_map<int, Node*> elements;
  Node *root;  // root points to the oldest value (note this is dummy root)
  Node *tail;  // tail points to the newest value (note this is dummy tail)
};

// Since std::list erase and insert operations don't invalidate iterators to untouched elements, we
// directly use it to build the LRU cache data structure
class LRUCache {
public:
  LRUCache(int capacity) {
    cap = capacity;
  }
    
  int get(int key) {
    auto it = elems.find(key);
    if(it == elems.end()) {
      return -1;
    }
    touch(it);
    return it->second.first;
  }
    
  void put(int key, int value) {
    auto it = elems.find(key);
    if(it != elems.end()) {
      it->second.first = value;
      touch(it);
    }
    else {
      if(elems.size() == cap) {
	elems.erase(elems.find(his.back()));
	his.pop_back();
      }
      his.push_front(key);
      elems.insert({key, {value, his.begin()}});
    }
  }

private:
  // touch doesn't change the key
  void touch(unordered_map<int, pair<int, list<int>::iterator>>::iterator it) {
    his.erase(it->second.second);
    his.push_front(it->first);
    it->second.second = his.begin();
  }
  
private:
  int cap;
  list<int> his;  // assume front being the newest element, store key so as to remove hash-map entry in O(1)
  unordered_map<int, pair<int, list<int>::iterator>> elems;
};


int main()
{
  LRUCache cache(1);
  cache.put(2,1);
  cache.get(2);
  cache.put(3,2);
  cache.get(2);
  cache.get(3);
  
  /*
  LRUCache cache(2);

  cache.put(1, 1);
  cache.put(2, 2);
  cache.get(1);       // returns 1
  cache.put(3, 3);    // evicts key 2
  cache.get(2);       // returns -1 (not found)
  cache.put(4, 4);    // evicts key 1
  cache.get(1);       // returns -1 (not found)
  cache.get(3);       // returns 3
  cache.get(4);       // returns 4
*/
}
