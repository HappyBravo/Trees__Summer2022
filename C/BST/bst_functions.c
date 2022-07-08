#include <stdio.h>
#include <stdlib.h>

struct btElement { // DEFINING ELEMENT FOR BINARY TREE
  int data;
  struct btElement *left;
  struct btElement *right;
};
typedef struct btElement btNode;

// FINDING THE HEIGHT OF THE NODE
int btheight(btNode *root){
  int left = 1;
  int right = 1;
  
  if(!(root)) return 0;

  if (root->left){
    left = 1 + btheight(root->left);
  }
  if (root->right){
    right = 1 + btheight(root->right);
  }
  return (right>left) ? right : left;
}

// MAKING NODE
btNode *createNode(int d){
    btNode *newNode = malloc(sizeof(btNode));
    newNode->data = d;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// RETURNS THE ADDRESS OF THE ELEMENT
// CHECKS IF THE PASSES ELEMENT IS PRESENT IN THE TREE OR NOT
btNode *bst_search(btNode *root, int d){
    if (!(root)) return root;
    if (root->data == d) return root;
    else if (root->data > d) return bst_search(root->left, d);
    else if (root->data < d) return bst_search(root->right, d);
}

// INSERTING AN ELEMENT IN THE BST
btNode *bst_insert(btNode *root, int d){
    if (!(root)) return createNode(d);

    if (d == root->data) ;//printf("\r%d IS ALREADY PRESENT!!!", d);
    else if (d < root->data) root->left = bst_insert(root->left, d);
    else if (d > root->data) root->right = bst_insert(root->right, d);
    return root;
}

btNode *bst_insert_iter(btNode *root, int d){
    btNode *temp = root, *new_node, *parent;
    while(temp != NULL){
        parent = temp;
        if (d < temp->data) temp = temp->left;
        else if (d > temp->data) temp = temp->right;
        else {
            // printf("\r%d IS ALREADY PRESENT!!!", d);
            return root;
            // break;
        }
    }
    new_node = createNode(d);
    if (root == NULL) root = new_node;
    else if (d < parent->data) parent->left = new_node;
    else if (d > parent->data) parent->right = new_node;
    return root;
     
}

// FINDING THE MINIMUM ELEMENT IN THE BST, RETURNS THE ADDRESS OF THE MINIMUM ELEMENT
btNode *bst_findMin(btNode *root){
    if (!(root)) return root;
    if (!(root->left)) return root;
    else bst_findMin(root->left);
}

// FUNCTION TO DELETE AN ELEMENT FROM THE TREE
btNode *bst_delete_main(btNode *root, int d){
    if (d < root->data) root->left = bst_delete_main(root->left, d);
    else if (d > root->data) root->right = bst_delete_main(root->right, d);
    else{
        // IF ELEMENT MATCHES,
        // CHECK FOR ITS CHILDREN,
        // IF ONE OR NO CHILD,
        btNode *temp = NULL;
        if (!(root->left)){
            temp = root->right;
            root = NULL;
            return temp;
        }
        else if (!(root->right)){
            temp = root->left;
            root = NULL;
            return temp;
        }
        // ELSE IT HAS TWO CHILDREN,
        // WE MAKE THE INORDER-SUCCESSOR AS THE ROOT THAT BRANCH
        temp = bst_findMin(root->right);
        root->data = temp->data;
        root->right = bst_delete_main(root->right, temp->data);
    }
    return root;
}

btNode *bst_delete(btNode *root, int d){
    if(!(root)) return root;
    btNode *to_delete = bst_search(root, d);
    if (!(to_delete)) {
        printf("\n>>> %d is NOT presesnt !\n");
        return root;
    }
    return bst_delete_main(root, d); 
}

// %%%%%%%%%% TREE DISPLAY FUNCTION %%%%%%%%%%%%%%
int _print_t(btNode *tree, int is_left, int offset, int depth, char s[20][512])
{
    char b[20];
    // char s[20][255];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->data);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } 
    else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void print_t(btNode *tree)
{
    int h = btheight(tree)*2;
    char s[h][512]; //s[h][255] 

    for (int i = 0; i < h; i++)
        sprintf(s[i], "%255s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < h; i++)
        printf("%s\n", s[i]);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%