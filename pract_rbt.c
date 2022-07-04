// #include "red_black_tree_functions.c"
#include "rbt_functions.c"
#include "python_functions.c"

int main(){
    rb_tree *root = NULL;
    char t;
    int arr[10] = {11, 2, 20, 45, 98, 22, 62, 64, 50, 84};
    for(int i = 0; i< 10; i++){
        printf("\nInserting %d\n", arr[i]);
        root = rb_insert(root, arr[i]);
        // rb_print_tree(root);
        // printf("\n\n");
        // scanf("%c", &t);
    }
    rb_print_tree(root);
    printf("\n<<< \tDELETING\t>>>\n");
    int temp;
    do{
        printf("Enter number to delete : ");
        scanf("%d", &temp);
        root = rb_remove(root, temp);
        rb_print_tree(root);
    }while(atoi(python_input("Delete again ? (1/0) : ")));
    
    return 0;
}
