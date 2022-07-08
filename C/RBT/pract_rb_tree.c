#include "rbt_functions.c"
// #include "red_black_tree_functions.c"
#include "../utility/python_functions.c" // FROM "https://github.com/HappyBravo/python_functions_in_C"
#include <unistd.h>
#include <time.h>

int main(){
    rb_tree *root = NULL;
    char t;
    
    int arr[10] = {31, 70, 7, 33, 8, 0, 62, 94, 50, 82};
    
    // printf("\n\t - - - - - Inserting random numbers - - - - - - \n");
    int n;
    srand(time(NULL));

    // while (atoi(python_input("INSERT NUMBER ? (1/0) : "))){
    for(int i = 0; i<10; i++){
        n = rand()%100;
        // printf("ENTER NUMBER : ");
        // scanf("%d", &n);
        // printf("\n\tINSERTING %d IN THE TREE.....\n\n", n);
        // sleep(2);
        root = rb_insert(root, arr[i]);


        // printf("\nInserting %d\n", arr[i]);
        // root = rb_insert(root, arr[i]);
        
        // rb_print_tree(root);
        // printf("\n\n");
        // scanf("%c", &t);
    }
    printf("\n\t<<<\tFINAL TREE\t>>>\n\n");
    rb_print_tree(root);

    printf("\n<<<\tDELETING\t>>>\n");
    
    int temp;
    do{
        printf("Enter number to delete : ");
        scanf("%d", &temp);
        root = rb_remove(root, temp);
        rb_print_tree(root);
    }while(atoi(python_input("Delete again ? (1/0) : ")));
    
    return 0;
}