#include "./common.h"

using namespace std;

int main(int argc, char *argv[])
{
  TreeNode *root = makeTree(argc, argv);
  printTree(root);
  releaseTree(root);

  return 0;
}
