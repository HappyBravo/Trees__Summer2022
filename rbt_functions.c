#include <stdio.h>
#include <stdlib.h>

/*
 Red-black tree is a kind of self balancing BST
 which balances itself on the basis of colour of its node.
 In a Red-Black "balanced" tree, each path has same number of Black coloured nodes. (not **STRICTLY** balanced though...)
*/

#define RBT_BLACK 0
#define RBT_RED 1

struct rb_element{ // DEFINING THE ELEMENT STRUCTURE FOR AVL TREE
    int data;
    struct rb_element *left;
    struct rb_element *right;
    struct rb_element *parent; // WE WILL NEED IT
    int color;
};
typedef struct rb_element rbNode;

struct rb_tree
{
    rbNode *root; // THE ROOT OF THE TREE
    rbNode *nil; // THE NULL ELEMENTS
};
typedef struct rb_tree rb_tree;

static rbNode *rb_new_node(rb_tree *tree, int data){
    // printf("making new node");
    rbNode *t = NULL;
    // printf("\nmaking space allocating");
    // printf("\n\t Size of rbNode : %u", sizeof(rbNode));
    t = (rbNode *)malloc(sizeof(rbNode));
    // printf("\nspace allocated");
    t->data = data;
    t->parent = tree->nil;
    t->left = tree->nil;
    t->right = tree->nil;
    t->color = RBT_RED;
    // printf("\nnew node made");
    return t;
}

static rbNode *rb_uncle(rb_tree *tree, rbNode *node){
    rbNode *grandparent;
    if (node->parent == tree->nil || node->parent->parent == tree->nil){
        return tree->nil;
    }
    grandparent = node->parent->parent;

    if (grandparent->left == node->parent) return grandparent->right;
    else return grandparent->left;
}

static void rb_rotate(rb_tree *tree, rbNode *node, int left_or_right){
     // left_or_right : 0 - ROTATE LEFT
     //                 1 - ROTATE RIGHT

     rbNode *new_node = (left_or_right) ? node->right : node->left;

     if (left_or_right){
        //  printf("\nright");
         node->right = new_node->left;
         if(node->right != tree->nil){
             node->right->parent = node;
         }
         new_node->left = node;
     }
     else{
        //  printf("\nleftt");
         node->left = new_node->right;
         if(node->left != tree->nil){
             node->left->parent = node;
         }
         new_node->right = node;
     }

     new_node->parent = node->parent;
     node->parent = new_node;
     if(new_node->parent == tree->nil){
         tree->root = new_node;
     }
     else if (new_node->parent->left == node){
         new_node->parent->left = new_node;
     }
     else{
         new_node->parent->right = new_node;
     }
}

static void rb_insert_fixup(rb_tree *tree, rbNode *node){
    rbNode *grandparent = node->parent->parent;
    rbNode *uncle = rb_uncle(tree, node);

    // CASE 1 : UNCLE IS RED
    while(node->parent->color == RBT_RED && uncle->color == RBT_RED){
        grandparent->color = RBT_RED;
        uncle->color = RBT_BLACK;
        node->parent->color = RBT_BLACK;
        node = grandparent; // taking pointer up
        uncle = rb_uncle(tree, node);
    }
    if (node->parent->color == RBT_BLACK){
        if (node == tree->root) node->color = RBT_BLACK;
        return;
    }

    // CASE 2 : NODE IS CLOSE TO UNCLE
    // FOR EXAMPLE :-
    //            (gp)
    //           /    \
    //     (uncle)   (parent)
    //      /   \     /    \
    //              [node]
    //
    if ( (node->parent->left == node) == (grandparent->left == uncle) ){
        rbNode *new_n = node->parent;
        rb_rotate(tree, new_n, new_n->right == node);
        node = new_n;
    }
    
    // CASE 3 : NODE IS FAR FROM UNCLE
    // FOR EXAMPLE :-
    //            (gp)
    //           /    \
    //     (uncle)   (parent)
    //      /   \     /    \
    //                    [node]
    //
    node->parent->color = RBT_BLACK;
    grandparent->color = RBT_RED;
    rb_rotate(tree, grandparent, grandparent->left == uncle);
    tree->root->color = RBT_BLACK;
    // return tree;
}

rb_tree *rb_insert(rb_tree *tree, int data){
    
    if (tree == NULL){
        printf("\n>>> TREE DOES NOT EXIST!!!\n>>> MAKING NEW TREE\n");
        tree = (rb_tree *)malloc(sizeof(rb_tree));
        tree->nil = (rbNode *)malloc(sizeof(rbNode));
        tree->nil->color = 0;
        tree->nil->left = tree->nil;
        tree->nil->right = tree->nil;
        tree->nil->parent = tree->nil;
        tree->root = tree->nil; 
        printf("\n>>> TREE MADE!!!\n");
    }
    rbNode *new_node;
    rbNode *parent = tree->nil;
    rbNode *temp = tree->root;

    while(temp != tree->nil){
        // printf("inisde loop");
        parent = temp;
        if (data < temp->data) temp = temp->left;
        else if (data > temp->data) temp = temp->right;
        else{
            printf("\n>>> %d IS ALREADY PRESENT !!!\n", data);
            return NULL;
        }
    }

    new_node = rb_new_node(tree, data);

    if (new_node == NULL) return 0;
    new_node->parent = parent;

    if (parent == tree->nil) tree->root = new_node;
    else if(data < parent->data) parent->left = new_node;
    else parent->right = new_node;

    rb_insert_fixup(tree, new_node);

    return tree;
}


// %%%%%%%%%% TREE DISPLAY FUNCTION %%%%%%%%%%%%%%
int rb_height(rb_tree *T, rbNode *root){
  int left = 1;
  int right = 1;
  
  if(root == T->nil) return 0;

  if (root->left){
    left = 1 + rb_height(T, root->left);
  }
  if (root->right){
    right = 1 + rb_height(T, root->right);
  }
  return (right>left) ? right : left;
}

int _rb_print_t(rb_tree *T, rbNode *tree, int is_left, int offset, int depth, char s[20][512])
{
    char b[20];
    // char s[20][255];
    int width = 7;

    // if (tree == NULL) return 0;

    if (tree == T->nil){
        sprintf(b, "(NIL,0)");
        return 0;
    }
    else{
        sprintf(b, "(%03d,%d)", tree->data, tree->color);
    }

    int left  = _rb_print_t(T, tree->left,  1, offset,                depth + 1, s);
    int right = _rb_print_t(T, tree->right, 0, offset + left + width, depth + 1, s);

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

void rb_print_t(rb_tree *tree, rbNode *node)
{
    int h = rb_height(tree, node)*2;
    printf("\nHeight = %d\n", h);

    char s[h][512];

    for (int i = 0; i < h; i++)
        sprintf(s[i], "%255s", " ");

    _rb_print_t(tree, node, 0, 0, 0, s);

    for (int i = 0; i < h; i++)
        printf("%s\n", s[i]);
}

void rb_print_tree(rb_tree *tree){
    // printf("\n\t>>> Printing Tree\n");
    rb_print_t(tree, tree->root);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
