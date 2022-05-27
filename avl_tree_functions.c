#include <stdio.h>
#include <stdlib.h>
// #include "binary_search_tree_functions.c"

/*
AVL tree is a type of Self Balanced BST.
So basically a BST with self balancing property.
when the left and right branch is unbalanced, i.e. the difference is >2, the tree would automatically balance itself.
*/

struct avl_element{ // DEFINING THE ELEMENT STRUCTURE FOR AVL TREE
    int data;
    struct avl_element *left;
    struct avl_element *right;
    int height;
};

typedef struct avl_element avlNode;
//avlNode *root = NULL;

// FUNCTION TO FIND MAXIMUM NUMBER FROM 2 NUMBERS
int max_2num(int num1, int num2){
    return (num1>num2)?num1:num2;
}

// MAKING THE BRANCH EMPTY
void makeEmpty(avlNode *root){ // DELETING NODE AND THEIR CHILDREN
    if (!(root)) return;
    makeEmpty(root->left);
    makeEmpty(root->right);
    free(root);
}

// RETURN HEIGHT OF THE NODE
int avl_height(avlNode *root){
    if (!(root)) return -1;
    return root->height;
}

// FUNCTION TO RIGHT ROTATE A NODE.
avlNode *avl_oneRightRotate(avlNode *root){
    avlNode *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max_2num(avl_height(root->left), avl_height(root->right))+1;
    temp->height = max_2num(avl_height(temp->right), root->height)+1;
    return temp;
}

// FUNCTION TO LEFT ROTATE A NODE
avlNode *avl_oneLeftRotate(avlNode *root){
    avlNode *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = max_2num(avl_height(root->left), avl_height(root->right))+1;
    temp->height = max_2num(avl_height(root->right), root->height)+1 ;
    return temp;
}

// FUNCTION TO RIGHT ROTATE A NODE TWO TIMES
avlNode *avl_twoRightRotate(avlNode *root){
    root->left = avl_oneLeftRotate(root->left);
    return avl_oneRightRotate(root);
}

// FUNCTION TO LEFT ROTATE A NODE TWO TIMES
avlNode *avl_twoLeftRotate(avlNode *root){
    root->right = avl_oneRightRotate(root->right);
    return avl_oneLeftRotate(root);
}

// FUNCTION TO INSERT ELEMENT INTO THE AVL TREE
avlNode *avl_insert(avlNode *root, int data){
    if (!(root)){
        avlNode *new_node;
        new_node = (avlNode *)malloc(sizeof(avlNode));
        new_node->data = data;
        new_node->left = new_node->right = NULL;
        new_node->height = 0;
        return new_node;
    }
    else if (data > root->data){
        root->right = avl_insert(root->right, data);
        if(avl_height(root->right) - avl_height(root->left) == 2){
            if(data > root->right->data){
                root = avl_oneLeftRotate(root);
            }
            else{
                root = avl_twoLeftRotate(root);
            }
        }
    }
    else if (data < root->data) {
        root->left = avl_insert(root->left, data);
        if(avl_height(root->left) - avl_height(root->right) == 2){
            if(data < root->left->data){
                root = avl_oneRightRotate(root);
            }
            else{
                root = avl_twoRightRotate(root);
            }
        }
    }

    /*
    // int h = 0;
    // int l = avl_height(root->left);
    // int r = avl_height(root->right);
    // if (l>r) h = l+1;
    // else h = r+1;
    //root->height = h; // UPDATING THE HEIGHT OF BRANCH
    */
    
    root->height = max_2num(avl_height(root->left), avl_height(root->right))+1; // UPDATING THE HEIGHT OF BRANCH
    return root;
}

// FUNCTIONS TO FIND THE MINIMUM ELEMENT IN THE TREE/BRANCH, RETURNS THE ADDRESS
avlNode *avl_findMin(avlNode *root){
    if(!(root)) return NULL;
    else if(!(root->left)) return root;
    else return avl_findMin(root->left);
}

// FUNCTIONS TO FIND THE MAXIMUM ELEMENT IN THE TREE/BRANCH, RETURNS THE ADDRESS
avlNode *avl_findMax(avlNode *root){
    if(!(root)) return NULL;
    else if(!(root->right)) return root;
    else return avl_findMin(root->right);
}

// FUNSTION TO REMOVE AN ELEMENT FROM THE TREE
avlNode *avl_remove(avlNode *root, int d){
    avlNode *temp = NULL;
    if (!(root)) return root;

    // FINDING ELEMENT
    else if (d < root->data){
        root->left = avl_remove(root->left, d);
    }
    else if (d > root->data){
        root->right = avl_remove(root->right, d);
    }
    // FOUND THEN,
    // IF TWO CHILDREN
    else if (root->left && root->right){
        temp = avl_findMin(root->right); // FINDING MINIMUM VALUE ELEMENT IN THE BRANCH
        root->data = temp->data;
        root->right = avl_remove(root->right, root->data);
    }
    // IF ONE CHILD OR NO CHILD PRESENT
    else {
        temp = root;
        if (!(root->left)){
            root = root->right;
        }
        else if (!(root->right)){
            root = root->left;
        }
        free(temp);
    }
    if(!(root)) return root;
    root->height = max_2num(avl_height(root->left), avl_height(root->right))+1; // UPDATE HEIGHT

    //
    // NOW CHECK FOR UNBALANCED TREE
    // 
    /* -------------------
    if (avl_height(root->left)-avl_height(root->right)==2){
        if(avl_height(root->left->left)-avl_height(root->left->right)==1){
            return avl_oneLeftRotate(root);
        }
        else{
            return avl_twoLeftRotate(root);
        }
    }
    else if(avl_height(root->right)-avl_height(root->left)==2){
        if(avl_height(root->right->right)-avl_height(root->right->left)==1){
            return avl_oneRightRotate(root);
        }
        else{
            return avl_twoRightRotate(root);
        }
    }
    // --------------------
    */
    int bal = avl_height(root->left)-avl_height(root->right);
    if (bal > 1){
        if (avl_height(root->left)>=avl_height(root->right)){
            return avl_oneRightRotate(root);
        }
        else{
            return avl_twoRightRotate(root);
        }
    }
    else if(bal <-1){
        if (avl_height(root->right)>=avl_height(root->left)){
            return avl_oneLeftRotate(root);
        }
        else {
            return avl_twoLeftRotate(root);
        }
    }
    return root;
}

// FUNTION TO GET THE BALANCE FACTOR OF THE NODE
int avl_getBalance(avlNode *root){
    if (!(root)) return 0;
    return avl_height(root->left)-avl_height(root->right);
}

// FUNCTION TO FIND IF AN ELEMENT IS PRESENT OR NOT
avlNode *avl_search(avlNode *root, int data){
    if (!(root)) return root;
    if (data == root->data) return root;
    else if (data < root->data) return avl_search(root->left, data);
    else if (data > root->data) return avl_search(root->right, data);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*
void display(avlNode *ptr, int level)
{
    int i;
    if(ptr != NULL)
    {
      display(ptr->right, level+1);
      for(i = 0; i<level; i++)
        printf("\t");
      printf("%d\n", ptr->data);
      display(ptr->left, level+1);
    }
}
*/

// %%%%%%%%%% TREE DISPLAY FUNCTION %%%%%%%%%%%%%%
int _avl_print_t(avlNode *tree, int is_left, int offset, int depth, char s[20][512])
{
    char b[20];
    // char s[20][255];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->data);

    int left  = _avl_print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _avl_print_t(tree->right, 0, offset + left + width, depth + 1, s);

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

void avl_print_t(avlNode *tree)
{
    int h = avl_height(tree)+6;
    char s[h][512];

    for (int i = 0; i < h; i++)
        sprintf(s[i], "%255s", " ");

    _avl_print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < h; i++)
        printf("%s\n", s[i]);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
