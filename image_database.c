/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "utils.h"

int main(void) {

        // char array to hold a line of input
	char buf[BUFFER_SIZE] = {'\0'};

        // char* array to hold the pointers to tokens
	char *args[INPUT_ARG_MAX_NUM];

        // the root of the tree
        struct TreeNode root;
        root.value = "";
        root.child = NULL;
        root.sibling = NULL;

	struct TreeNode *root_ptr = &root;

        // Add your code below:
        int num_tokens;
        while(fgets(buf, BUFFER_SIZE, stdin) != NULL) {
                num_tokens = tokenize(buf, args);
                if(args[0][0] == 'i' && num_tokens == 5) {
                        char *atrs_and_filename[4] = {args[1], args[2], args[3], args[4]};
                        tree_insert(root_ptr, atrs_and_filename);
                } else if(args[0][0] == 'q' && num_tokens == 4) {
                        char *atrs[3] = {args[1], args[2], args[3]};
                        tree_search(root_ptr, atrs);
                } else if(args[0][0] == 'p' && num_tokens == 1) {
                        tree_print(root_ptr);
                } else {
                        fprintf(stderr, "Invalid command.\n");
                }

        }

        return 0;
}
