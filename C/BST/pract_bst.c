#include "bst_functions.c"
#include "../utility/python_functions.c"
#include <unistd.h>
#include <time.h>

int main(){
    btNode *root = NULL;
    srand(time(NULL)); // INITIALIZE RANDOM NUMBER

    int n;
    int i = 0;
    
    int upper = 100;//000;
    int lower = 0;

    int limit = atoi(python_input("ENTER LIMIT : "));

    // while (atoi(python_input("WANT TO INSERT ? (1/0) : ")))
    clock_t start, end;
    start = clock();
    while (i<limit)
    {
        // n = rand()%100;
        // printf("%d \t \t \t ", i);
        n = (rand() % (upper - lower + 1)) + lower;
        // printf("\nINSERTING %d IN THE BST", n);
        root = bst_insert_iter(root, n);
        // print_t(root);
        i++;
    }
    end = clock();
    double time_taken = (double)(end-start)/CLOCKS_PER_SEC;

    printf("\rTO INSERT %d NUMBERS IN THE BST, IT TOOK %f sec.",limit, time_taken);

    printf("\n");
    print_t(root);

    printf("\n\nDELETE\n");

    // while (i<limit)
    while (atoi(python_input("WANT TO DELETE ? (1/0) : ")))
    {
        // n = rand()%100;
        // printf("%d \t \t \t ", i);
        n = atoi(python_input("TO DELETE : "));
        printf("\nDELETING %d FROM THE BST\n", n);
        root = bst_delete(root, n);
        print_t(root);
        i++;
    }
    printf("\n");
    print_t(root);
  
    return 0;
}
