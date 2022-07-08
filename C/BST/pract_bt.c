#include "binary_tree_functions.c"
#include <time.h>

int main(){
  // root = makeNode(7);
  // root->left = makeNode(3);
  // root->right = makeNode(13);
  
  // root->left->right = makeNode(6);
  // root->right->left = makeNode(11);
  // root->right->right = makeNode(15);
  
  // root->left->right->left = makeNode(5);
  // root->right->left->right = makeNode(12);
  btNode *root = createNode(7);
  insertLeft(root, 3);
  insertRight(root, 13);
  
  insertRight(root->left, 6);
  insertLeft(root->right, 11);
  insertLeft(root->left, 2);
  insertRight(root->right, 15);
  
  insertLeft(root->left->right, 5);
  insertRight(root->right->left, 12);
  insertLeft(root->right->left, 10);
  insertRight(root->right->left->right, 26);
  insertLeft(insertLeft(root->right->left->right, 28), 30);


  
  btNode *emproot = NULL;
  print_t(root);
  // printf("deepest node = %d", bt_deepestNodeAddress(root, btheight(root))->data);
  printf("\n\n----Deleting-----\n");
  print_t(bt_deleteNode(root, 11));

  printf("\nSearching Element\n");
  btNode *searched = searchElement(root, 30);
  if(searched)  printf("%d", searched->data);
  else printf("Not Present");

  node *l = NULL;
  srand(time(NULL));
  for (int i =0; i< 20; i++){
      l = python_append(l, rand()%100);
  }
  //   l = create_list(atoi(python_input("\nEnter length of list : ")));
  printList(l);

  btNode *arr2bt = NULL;
  arr2bt = makeBtfromArr(arr2bt, l);
  print_t(arr2bt);

  printf("\nFinding Max element : \n");
  printf("Max element is %d", (bt_findMax(arr2bt))->data);
  printf("\nFinding Min element : \n");
  printf("Min element is %d", (bt_findMin(arr2bt))->data);
  root = arr2bt;

  // printf("%d\n\n\n", isEmpty(root));
  // print_t(root);
  // printf("\n---- INORDER RECURSIVE\n");
  // bt_inorder(root);
  // printf("\n\nINORDER NON RECURSIVE\n");
  // bt_inorder_nonrec(root);

  // printf("\n");
  // printf("\n---- PREORDER RECURSIVE\n");
  // bt_preorder(root);
  // // printf("\n");
  // printf("\n\nPREORDER NON RECURSIVE\n");
  // bt_preorder_nonrec(root);
  // // bt_postorder(root);
  // printf("\n---- POSTORDER RECURSIVE\n");
  // bt_postorder(root);
  // // printf("\n");
  // printf("\n\nPOSTORDER NON RECURSIVE\n");
  // bt_postorder_nonrec(root);
  // printf("\nHeight = %d\n", btheight(root));
  // printf("\n\nLEVEL ORDER TRAVERSAL\n");
  // bt_levelorder(root);
  
  printf("\nChecking Internal : \n");
  printf("%d", isInternal(root, atoi(python_input("Enter Element : "))));
  printf("\nChecking External : \n");
  printf("%d", isExternal(root, atoi(python_input("Enter Element : "))));
  printf("\nChecking Children : \n");
  printList(bt_children(root, atoi(python_input("Enter Element : "))));
  printf("\nHeight of tree : %d\n", btheight(root));
  int n = atoi(python_input("Enter Element : "));
  printf("\nLevel of %d is %d\n", n, btNode_level(root, n));
  printf("\nParent of %d is %d\n", n, bt_parent(root, n));
  
  // printf("\n\n---- NEW TREE ----\n");
  // btNode *new_tree;
  // new_tree = createNode(1);
  // insertLeft(insertRight(insertLeft(new_tree, 15), 16), 17);
  // print_t(new_tree);
 
  // int h;
  // int di = 100;
  // printf("\nPrinting Ancestors");
  // h = btNode_depth(root, di);
  // node *anc = create_list(0);
  // while (h-- && h>0){
  //   di = parent(root, di);
  //   if (python_count(anc, di) == 0){
  //     anc = python_append(anc, di);
  //   }
  // }
  // printList(anc);

  return 0;
}