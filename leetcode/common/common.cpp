#include <stack>
#include <fstream>

#include "./common.h"

using namespace std;

// Convert [1,null,2,3] to BST
TreeNode* makeTree(int argc, char *argv[])
{
  if(argc < 2)
    return nullptr;
  
  vector<TreeNode*> nodes(argc-1, nullptr);
  for(int i=1; i<argc; ++i) {
    if(strcmp(argv[i], "null"))
       nodes[i-1] = new TreeNode(atoi(argv[i]));
  }

  int skip = 0;
  for(int i=0; i<nodes.size(); ++i) {
    if(!nodes[i]) {
      skip += 2;
      continue;
    }

    int left = 2*i - skip + 1;
    int right = 2*i - skip + 2;
    nodes[i]->left = left<nodes.size() ? nodes[left] : nullptr;
    nodes[i]->right = right<nodes.size() ? nodes[right] : nullptr;
    /*
    cout << nodes[i]->val << ": ";
    if(nodes[i]->left)
      cout << nodes[i]->left->val << ", ";
    else
      cout << "null, ";
    if(nodes[i]->right)
      cout << nodes[i]->right->val << endl;
    else
      cout << "null" << endl;
    */
  }

  return nodes[0];
}

// Generate dot for visualization
void printTree(TreeNode *root)
{
  vector<TreeNode*> nodes;
  stack<TreeNode*> stk;
  if(root)
    stk.push(root);
  // BFS to collect nodes
  while(!stk.empty()) {
    TreeNode *node = stk.top();
    nodes.push_back(node);
    stk.pop();
    if(node->right)
      stk.push(node->right);
    if(node->left)
      stk.push(node->left);
  }

  ofstream ofs("bst.dot");
  if(!ofs)
    return;

  ofs << "digraph g{" << endl;
  ofs << "node [shape = record,height = .1];" << endl;
  unordered_map<TreeNode*, int> node2Id;
  for(int i=0; i<nodes.size(); ++i) {
    node2Id[nodes[i]] = i;
    ofs << "\tnode" << i << "[label = \"<f0> | <f1> " << nodes[i]->val << " | <f2>\"];" << endl;
  }
  for(int i=0; i<nodes.size(); ++i) {
    TreeNode *node = nodes[i];
    TreeNode *left = node->left;
    TreeNode *right = node->right;
    if(left)
      ofs << "\t\"node" << node2Id[node] << "\":f0->\"node" << node2Id[left] << "\":f1;" << endl;
    if(right)
      ofs << "\t\"node" << node2Id[node] << "\":f2->\"node" << node2Id[right] << "\":f1;" << endl;
  }
  ofs << "}" << endl;

  ofs.close();
}

void releaseTree(TreeNode *root)
{
  if(!root)
    return;
  releaseTree(root->left);
  releaseTree(root->right);
  /*cout << "release: " << root->val << endl;*/
  delete root;
}


std::vector<int> readVector(int argc, char *argv[])
{
  std::vector<int> vec(argc-1, 0);
  for(int i=1; i<argc; ++i)
    vec[i-1] = atoi(argv[i]);

  return vec;
}
