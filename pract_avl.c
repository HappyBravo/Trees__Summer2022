#include "avl_tree_functions.c"
#include "python_functions.c" // FROM "https://github.com/HappyBravo/python_functions_in_C"
#include <unistd.h>
#include <time.h>

int main(){
    char p;
    avlNode *root1 = NULL;
    int ele[10] = {17, 31,1,19, 22, 5, 6, 8, 7, 33};
    for(int i =0; i<10; i++){
        root1 = avl_insert(root1, ele[i]);
        printf("\n%d inserted\n", ele[i]);
        // avl_print_t(root1);
        // scanf("%c",&p);
    }
    avl_print_t(root1);


    /*
    printf("\n\t - - - - - Deleting - - - - - - \n");
    int r = atoi(python_input("Enter data to delete : "));
    root1 = avl_remove(root1, r);
    printf("\nRemoved %d\n", r);
    avl_print_t(root1);
    */
    printf("\n\t - - - - - inserting random numbers - - - - - - \n");
    srand(time(NULL));
    avlNode *root2 = NULL;
    for(int i = 0;i<20; i++){
        root2 = avl_insert(root2, rand()%100);
        avl_print_t(root2);
        sleep(2);
    }
    return 0;
}