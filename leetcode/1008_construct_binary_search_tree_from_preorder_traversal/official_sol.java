// Approach 1: Construct binary tree from preorder and inorder traversal
class Solution {
  // start from first preorder element
  int pre_idx = 0;
  int[] preorder;
  HashMap<Integer, Integer> idx_map = new HashMap<Integer, Integer>();

  public TreeNode helper(int in_left, int in_right) {
    // if there is no elements to construct subtrees
    if (in_left == in_right)
      return null;

    // pick up pre_idx element as a root
    int root_val = preorder[pre_idx];
    TreeNode root = new TreeNode(root_val);

    // root splits inorder list
    // into left and right subtrees
    int index = idx_map.get(root_val);

    // recursion 
    pre_idx++;
    // build left subtree
    root.left = helper(in_left, index);
    // build right subtree
    root.right = helper(index + 1, in_right);
    return root;
  }

  public TreeNode bstFromPreorder(int[] preorder) {
    this.preorder = preorder;
    int [] inorder = Arrays.copyOf(preorder, preorder.length);
    Arrays.sort(inorder);

    // build a hashmap value -> its index
    int idx = 0;
    for (Integer val : inorder)
      idx_map.put(val, idx++);
    return helper(0, inorder.length);
  }
}


// Approach 2: Recursion
class Solution {
  int idx = 0;
  int[] preorder;
  int n;

  public TreeNode helper(int lower, int upper) {
    // if all elements from preorder are used
    // then the tree is constructed
    if (idx == n) return null;

    int val = preorder[idx];
    // if the current element 
    // couldn't be placed here to meet BST requirements
    if (val < lower || val > upper) return null;

    // place the current element
    // and recursively construct subtrees
    idx++;
    TreeNode root = new TreeNode(val);
    root.left = helper(lower, val);
    root.right = helper(val, upper);
    return root;
  }

  public TreeNode bstFromPreorder(int[] preorder) {
    this.preorder = preorder;
    n = preorder.length;
    return helper(Integer.MIN_VALUE, Integer.MAX_VALUE);
  }
}

// Approach 3: Iteration
class Solution {
  public TreeNode bstFromPreorder(int[] preorder) {
    int n = preorder.length;
    if (n == 0) return null;

    TreeNode root = new TreeNode(preorder[0]);
    Deque<TreeNode> deque = new ArrayDeque<TreeNode>();
    deque.push(root);

    for (int i = 1; i < n; i++) {
      // take the last element of the deque as a parent
      // and create a child from the next preorder element
      TreeNode node = deque.peek();
      TreeNode child = new TreeNode(preorder[i]);
      // adjust the parent 
      while (!deque.isEmpty() && deque.peek().val < child.val)
        node = deque.pop();

      // follow BST logic to create a parent-child link
      if (node.val < child.val) node.right = child;
      else node.left = child;
      // add the child into deque
      deque.push(child);
    }
    return root;
  }
}
