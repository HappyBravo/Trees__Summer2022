#include "binary_search_tree_functions.c"

int main(){
  btNode *root = NULL;
  btNode *root2 = NULL;
  root = bst_insert(root,7);
  bst_insert(root, 13);

  bst_insert(root, 6);
  bst_insert(root, 11);
  bst_insert(root, 2);
  bst_insert(root, 15);

  bst_insert(root, 5);
  bst_insert(root, 12);
  bst_insert(root, 10);
  bst_insert(root, 26);
  bst_insert(bst_insert(root, 14), 25);

  // TO CHECK BST
  root2 = createNode(7);
  insertLeft(root2, 3);
  insertRight(root2, 13);
  
  insertRight(root2->left, 6);
  insertLeft(root2->right, 11);
  insertLeft(root2->left, 2);
  insertRight(root2->right, 15);
  
  insertLeft(root2->left->right, 5);
  insertRight(root2->right->left, 12);
  insertLeft(root2->right->left, 10);
  insertRight(root2->right->left->right, 26);
  insertLeft(insertLeft(root2->right->left->right, 28), 30);
    
  print_t(root);
  printf("\n - IS BST ? %d\n", isBST(root));
  print_t(root2);
  printf("\n - IS BST ? %d\n", isBST(root2));

  // printf("\nis BST ? %d", isBST(root));
  // int n = 15;
  // printf("\n%d is Present ? %d",n, bst_isPresent(root, n));

  // printf("\nThe Min is : %d\nThe Max is %d\n", bst_findMin(root), bst_findMax(root));

  printf("\nINORDER\n");
  bt_inorder(root);

  // printf("\nInorder successor\n");
  // printf("%d", bst_inorderSuccessor(root, 6));
  // printf("\nInorder predecessor\n");
  // printf("%d", bst_inorderPredecessor(root, 6));

  printf("\n\n---deletion---\n");
  int m = 7;
  print_t(root);
  print_t(bst_delete(root, m));
  printf("\n%d deleted successfully\n", m);
  



  /*
  printf("\n---- NEW TREE----\n");
  btNode *root2 = createNode(7);
  insertLeft(root2, 3);
  insertRight(root2, 13);
  
  insertRight(root2->left, 6);
  insertLeft(root2->right, 1);
  insertLeft(root2->left, 22);// 2);
  insertRight(root2->right, 50);
  
  insertLeft(root2->left->right, 5);
//   insertRight(root->right->left, 12);
//   insertLeft(root->right->left, 10);
//   insertRight(root->right->left->right, 26);
//   insertLeft(insertLeft(root->right->left->right, 28), 30);
    print_t(root2);
    printf("\nis BST ? %d", isBST(root2));
    */
    
    return 0;
}