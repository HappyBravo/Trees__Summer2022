// #include "C/BST/bst_functions.c"
// #include "C/AVL/avl_functions.c"
#include "C/RBT/rbt_functions.c"
#include "C/utility/python_functions.c"
#include <math.h>
#include <time.h>
#include <unistd.h>


// btNode *bst_root = NULL;
// avlNode *avl_root = NULL;
rb_tree *rb_root = NULL;

double timetaken(clock_t start, clock_t end){
    return (double)(end-start)/CLOCKS_PER_SEC;
}

int reader(char location[], FILE *r){
    int num;
    FILE *f = fopen(location, "r");
    printf("ENTERED READER\n");
    if (f == NULL) {
        printf("ERROR LOADING FILE\n");
        return 0;
    }
    if (r == NULL){
        printf("ERROR LOADING RESULT FILE\n");
        return 0;
    }


    clock_t start, end;
    for(int i = 0; i<10; i++){ // TAKING 10 TIMES
        
        rb_root = NULL;

        start = clock();
        while(!feof(f)){
            fscanf(f, "%d, ", &num);
            // printf("\rINSERTING %04d IN BST ", num);
            rb_root = rb_insert(rb_root, num);  
        }
        end = clock();
        double time_taken = timetaken(start, end);
        printf("\n\tIT TOOK %f secs.\n", time_taken);
        fprintf(r, "%f\t", time_taken);
        rewind(f);
    }
    fclose(f);
    return 1;

}

int main(){
    // char filename[30];
    // int num;
    char testcase[8];
    char location[30] = "test_files/test_";
    char result_location[30] = "res_C_RBT.txt";
    FILE *res = fopen(result_location, "w");
    
    for(int i = 1; i<7 ; i++){
        strcat(location, itoa(pow(10, i) + 1e-8, testcase, 10)); // sometimes pow() has error of 10^-9, so (int)10^2 becomes 99 instead of 100.
        strcat(location, ".txt"); // adding extension
        printf("OPENING %s\n",location);
        fprintf(res, "\nTESTCASE : %s\n", testcase);
        // FILE *f = fopen(location, "r");
        if(!reader(location, res)) break;
        // fscanf(f, "%d, ", &num);
        // printf("%d, ", num);
        // fclose(f);
        printf("\n%s DONE\n", location);
        strcpy(location, "test_files/test_");
        // fflush(stdin);
        // char c;
        // scanf("%c", c);
        sleep(2);
    }
    fclose(res);
    return 1;
}
