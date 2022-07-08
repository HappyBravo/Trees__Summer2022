#include "binary_tree_functions.c" // FROM "https://github.com/HappyBravo/BinaryTree_Functions"

// CHECKING IF THE PASSES ELEMENT IS PRESENT IN THE TREE OR NOT
int bst_isPresent(btNode *root, int d){
    if (!(root)) return 0;
    if (root->data == d) return 1;
    else if (root->data > d) return bst_isPresent(root->left, d);
    else if (root->data < d) return bst_isPresent(root->right, d);
}

// INSERTING AN ELEMENT IN THE BST
btNode *bst_insert_main(btNode *root, int d){
    if (!(root)) return createNode(d);
    else{
        if (d < root->data) root->left = bst_insert_main(root->left, d);
        else if (d > root->data) root->right = bst_insert_main(root->right, d);
    }
    return root;
}

btNode *bst_insert(btNode *root, int d){
    if (isPresent(root, d)) {
        printf("\n>>> %d is already presesnt !\n");
        return root;
    }
    return bst_insert_main(root, d);
}

/* 
 * THIS IS SIMPLE BUT WRONG
 * THERE MAY BE A BIGGER/SMALLER NUMBER IN RIGHT/LEFT BRANCH THAN THE ROOT IN LOWER LEVELS - THIS CASE IS MISSED WHEN WE CHECK WITH THIS SIMPLE METHOD  
 */
// int isBST(btNode *root){
//     if(!(root)) return 1;
//     if (root->left){
//         if (root->left->data > root->data) return 0;
//     }
//     if (root->right){
//         if (root->right->data < root->data) return 0;
//     }
//     if ( !(isBST(root->left)) + !(isBST(root->right)) ) return 0;
//     return 1;
// }

// CHECKING IF THE GIVEN TREE IS A BST OR NOT
int isBST_main(btNode *root, btNode *l, btNode *r){
    if (!(root)) return 1;
    if (l != NULL && root->data <= l->data){
        return 0;
    }
    if (r != NULL && root->data >= r->data){
        return 0;
    }
    if (!(isBST_main(root->left, l, root)) + !(isBST_main(root->right, root, r))){
        return 0;
    }
    return 1;
}

int isBST(btNode *root){
    return isBST_main(root, NULL, NULL);
}

// FINDING THE MAXIMUM ELEMENT IN THE BST, RETURNS THE ADDRESS OF THE MAXIMUM ELEMENT
btNode *bst_findMax(btNode *root){
    if (!(root)) return root;
    if (!(root->right)) return root;
    else bst_findMax(root->right);
}

// FINDING THE MINIMUM ELEMENT IN THE BST, RETURNS THE ADDRESS OF THE MINIMUM ELEMENT
btNode *bst_findMin(btNode *root){
    if (!(root)) return root;
    if (!(root->left)) return root;
    else bst_findMin(root->left);
}

btNode *bst_inorderSuccessor(btNode *root, int d){
    if (!(root)) return root; //NULL;
    if (root->data == d) {
        // AFTER LOCATING THE DESIRED ELEMENT,
        // WE FIND ITS INORDER-SUCCESSOR...
        if(root->right) { // CHECK IF IT HAS RIGHT CHILD/BRANCH
        return bst_findMin(root->right);
        }
        return root;
    }
    else if (d < root->data) {
        return bst_inorderSuccessor(root->left, d);
    }
    else if (d > root->data) {
        return bst_inorderSuccessor(root->right, d);
    }
}

btNode *bst_inorderPredecessor(btNode *root, int d){
    if (!(root)) return root; //NULL;
    if (root->data == d) {
        // AFTER LOCATING THE DESIRED ELEMENT,
        // WE FIND ITS INORDER-PREDECESSOR...
        if(root->left){ // CHECK IF IT HAS RIGHT CHILD/BRANCH
            return bst_findMax(root->left);
        }
        return root;
    }
    if (d < root->data) {
        return bst_inorderPredecessor(root->left, d);
    }
    else if (d > root->data) {
        return bst_inorderPredecessor(root->right, d);
    }
}

/*
NOW bst_findMin() HANDLES THIS TASK
btNode *bst_minValAddress(btNode *root){
    btNode *temp = NULL;
    temp = root;
    while(temp->left){
        temp = temp->left;
    }
    return temp;
}
*/

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
    if (!(isPresent(root, d))) {
        printf("\n>>> %d is NOT presesnt !\n");
        return root;
    }
    return bst_delete_main(root, d); 
}
