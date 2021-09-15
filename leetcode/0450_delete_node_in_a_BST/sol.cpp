/*
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Follow up: Can you solve it with time complexity O(height of tree)?

 

Example 1:


Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

Example 2:

Input: root = [5,3,6,2,4,null,7], key = 0
Output: [5,3,6,2,4,null,7]
Explanation: The tree does not contain a node with value = 0.
Example 3:

Input: root = [], key = 0
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 10^4].
-10^5 <= Node.val <= 10^5
Each node has a unique value.
root is a valid binary search tree.
-10^5 <= key <= 10^5
*/

// O(h) time complexity, but does not generate balanced BST
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root)
            return nullptr;
        
        // found node to be deleted
        TreeNode *newRoot = nullptr;
        if(root->val == key) {
            if(root->left && root->right) {
                // always make right child as the new root
                TreeNode *pCur = root->right;
                while(pCur->left)  // note this will create unbalanced BST
                    pCur = pCur->left;
                pCur->left = root->left;
                newRoot = root->right;
            }
            else if(root->left)
                newRoot = root->left;
            else if(root->right)
                newRoot = root->right;
            
            // delete root;
            return newRoot;
        }
        
        if(key < root->val)
            root->left = deleteNode(root->left, key);
        else if(key > root->val)
            root->right = deleteNode(root->right, key);
        return root;

    }
    
};


// Solution that keeps the BST balanced
// key idea is to replace the to-be-deleted node with its successor
// O(H) space and time complexity
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root)
            return nullptr;
        if(root->val > key) {
            root->left=deleteNode(root->left, key);
            return root;
        }
        else if(root->val < key) {
            root->right=deleteNode(root->right, key);
            return root;
        }
        
        // root->val==key, so it is the node to be deleted
        TreeNode *newRoot = nullptr;
        if(root->left && root->right) {
            // idea is to replace the to-be-deleted node with its successor
            newRoot = root;
            TreeNode *successor = findSuccessor(root);
            newRoot->val = successor->val;
            newRoot->right = deleteNode(newRoot->right, successor->val);  // successor needs to be further deleted from right subtree
        }
        else {
            newRoot = root->left?root->left:root->right;
            delete root;
        }
        
        return newRoot;
    }
    
private:
    TreeNode* findSuccessor(TreeNode *node) {
        TreeNode *successor = node?node->right:nullptr;
        while(successor && successor->left)
            successor = successor->left;
        return successor;
    }
};


// a different tree node re-organization from HuaHua
class Solution {
public:
  TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;
    if (key > root->val) {
      root->right = deleteNode(root->right, key);
    } else if (key < root->val) {
      root->left = deleteNode(root->left, key);
    } else {
      TreeNode* new_root = nullptr;
      if (root->left == nullptr) {
        new_root = root->right;
      } else if (root->right == nullptr) {
        new_root = root->left;
      } else {
        // Find the min node in the right sub tree
        TreeNode* parent = root;
        new_root = root->right;
        while (new_root->left != nullptr) {
          parent = new_root;
          new_root = new_root->left;  // new_root will be the successor of root
        }
        
        if (parent != root) {
          parent->left = new_root->right;
          new_root->right = root->right;
        }
        
        new_root->left = root->left;      
      }
      
      delete root;
      return new_root;
    }
    
    return root;
  }
};


// official ref sol (in Java)
class Solution {
  /*
  One step right and then always left
  */
  public int successor(TreeNode root) {
    root = root.right;
    while (root.left != null) root = root.left;
    return root.val;
  }

  /*
  One step left and then always right
  */
  public int predecessor(TreeNode root) {
    root = root.left;
    while (root.right != null) root = root.right;
    return root.val;
  }

  public TreeNode deleteNode(TreeNode root, int key) {
    if (root == null) return null;

    // delete from the right subtree
    if (key > root.val) root.right = deleteNode(root.right, key);
    // delete from the left subtree
    else if (key < root.val) root.left = deleteNode(root.left, key);
    // delete the current node
    else {
      // the node is a leaf
      if (root.left == null && root.right == null) root = null;
      // the node is not a leaf and has a right child
      else if (root.right != null) {
        root.val = successor(root);
        root.right = deleteNode(root.right, root.val);
      }
      // the node is not a leaf, has no right child, and has a left child    
      else {
        root.val = predecessor(root);
        root.left = deleteNode(root.left, root.val);
      }
    }
    return root;
  }
};
