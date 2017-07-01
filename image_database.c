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
        // Stores the number of tokens separated by DELIMITERS from standard input
        int num_tokens;
        // Loops until the user has initiated EOF and each iteration gets standard input to buf
        while(fgets(buf, BUFFER_SIZE, stdin) != NULL) {
                // Gets the number of tokens separated by DELIMITERS and also puts the tokens
                // in an array of char * (args)
                num_tokens = tokenize(buf, args);
                // If the user typed in "i" for initialize in the first token and with 5 tokens
                // in total, then do the following:
                if(args[0][0] == 'i' && num_tokens == 5) {
                        // Stores the attributes and file name in a char* array
                        char *atrs_and_filename[4] = {args[1], args[2], args[3], args[4]};
                        // Insert the attributes and file name in the database using tree_insert
                        tree_insert(root_ptr, atrs_and_filename);
                // If the user typed in "q" for query in the first token and with 4 tokens
                // in total, then do the following:
                } else if(args[0][0] == 'q' && num_tokens == 4) {
                        // Stores the attributes in a char* array
                        char *atrs[3] = {args[1], args[2], args[3]};
                        // Using attributes, find the file names in alphabetical order
                        // in the database using tree_search
                        tree_search(root_ptr, atrs);
                // If the user typed in "p" for print in the first token and with 1 token
                // in total, then do the following:
                } else if(args[0][0] == 'p' && num_tokens == 1) {
                        // Print all attributes and associated file names in each line in
                        // alphabetical order in the database using tree_print
                        tree_print(root_ptr);
                } else {
                        // Error has occured in the command provided; provide error message to
                        // standard error
                        fprintf(stderr, "Invalid command.\n");
                }
        }
        return 0;
}
