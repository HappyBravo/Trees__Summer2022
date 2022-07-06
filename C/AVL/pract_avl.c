#include "avl_functions.c"
#include "../utility/python_functions.c" // FROM "https://github.com/HappyBravo/python_functions_in_C"
#include <unistd.h>
#include <time.h>

int main(){
    // char p;
    // avlNode *root1 = NULL;
    // // int ele[] = {100,55,50,45,47,70,80,78,77,79,82,81,83,150,140, 135,142,143,180,170,165,160,175,173,200,190,195,500,1000,1500,2000,3000,4000,5000,6000,7000,8000,9000};
    // int ele[] = {18, 20, 9, 27, 28, 43, 43, 41, 29, 14};
    // for(int i =0; i<sizeof(ele)/sizeof(ele[0]); i++){
    //     root1 = avl_insert(root1, ele[i]);
    //     printf("\n%d inserted\n", ele[i]);
    //     // avl_print_t(root1);
    //     // scanf("%c",&p);
    // }
    // avl_print_t(root1);


    printf("\n\t - - - - - inserting random numbers - - - - - - \n");
    srand(time(NULL));
    int n ;
    
    int upper = 100000;
    int lower = 0;

    int limit = atoi(python_input("\nENTER LIMIT : "));
    avlNode *root2 = NULL;
    clock_t start, end;
    start = clock();
    for(int i = 0;i<limit; i++){
        // n = rand()%100;
        n = (rand() % (upper - lower + 1)) + lower;
        // printf("\n\tINSERTING %d IN THE TREE.....\n\n", n);
        // sleep(2);
        root2 = avl_insert(root2, n);
        // avl_print_t(root2);
        // sleep(0.5);
    }
    end = clock();
    double time_taken = (double)(end-start)/CLOCKS_PER_SEC;

    printf("\rTO INSERT %d NUMBERS IN THE BST, IT TOOK %f sec.",limit, time_taken);

    // printf("\n<<<\tFINAL TREE\t>>>\n");
    // avl_print_t(root2);
  
    printf("\n\t - - - - - Deleting - - - - - - \n");
    while(atoi(python_input("Do you want to remove ? (1:YES 0: NO) : "))){
        int r = atoi(python_input("Enter data to delete : "));
        root2 = avl_remove(root2, r);
        // printf("\nRemoved %d\n", r);
        avl_print_t(root2);
    }

    return 0;
}
