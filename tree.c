/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


/**
 *  A helper function that allocates a new tree node.
 *
 *  @param value The entry's value. It represents either an attribute or a filename.
 *  @return A pointer to the newly allocated node.
 *  (for now it returns NULL, so the compiler does not complain)
 */
struct TreeNode *allocate_node(const char *value) {
	// Allocates space in the heap for a tree node
	struct TreeNode *node = malloc(sizeof(struct TreeNode));
	// Allocates space in the heap for a string in a tree node
	node->value = malloc(strlen(value) + 1);
	// Copies the value argument into the allocated value in the allocated node
	strcpy(node->value, value);
	// By default, set sibling and child to NULL
	node->sibling = NULL;
	node->child = NULL;
	// Return the node
	return node;
}

/**
 * Returns the number of iterations until a sibling is found with the value of value.
 * If no value of any sibling equals the value, return -1.
**/
int found_sibling(struct TreeNode *root, char *value) {
	// Counts the number of siblings until value is the value of a sibling
	int count = 1;
	// If value is not the value of a sibling, found = -1
	int found = -1;
	// Loops until the sibling is NULL
	while(root->sibling != NULL) {
		// If the current root's sibling value is not that of value and it hasn't
		// been found yet, then increment count
		if(strcmp((root->sibling)->value, value) != 0 && found == -1) {
			count++;
		} else {
			// Set found to true (0)
			found = 0;
		}
		// Makes current root the sibling of current root
		root = root->sibling;
	}
	// If found is still -1, then return the found_sibling as -1
	if(found == -1) {
		count = -1;
	}
	// Returns the number of siblings until value is the value of a sibling.
	// If no value of any sibling equals value, return -1.
	return count;
}

/**
 * Creates nodes from root, values and level up to level 5. At level 5, file names
 * will be put into nodes.
 *
**/
void create_nodes(struct TreeNode *root, char **values, int level) {
	/** If a node or nodes still need to be created for attributes of the file **/
	if(level < 5) {
		// If the root has a value equal to that of the current attribute
		if(strcmp(root->value, values[level-2]) == 0) {
			/** EMPTY **/
		// If the a node of a sibling of root has a value equal to that of the current attribute
		} else if(found_sibling(root, values[level-2]) != -1) {
			int iterations = found_sibling(root, values[level-2]);
			for(int i = 0; i < iterations; i++) {
				root = root->sibling;
			}
		} else {
			/** PLEASE EXCUSE MY CODE; I HAVE MULTIPLE ATTEMPTS BELOW **/
			// Store variables
			struct TreeNode *with_val = allocate_node(values[level-2]);
			struct TreeNode *temp = root;
			struct TreeNode *keep = NULL;
			int count = 1;
			int done = -1;
			while(root->sibling != NULL) {
				root = root->sibling;
				count++;
			}
			root->sibling = allocate_node(root->value);
			(root->sibling)->child = root->child;
			root = temp;
			for(int i = 0; i < count; i++) {
				if(strcmp(with_val->value, root->value) < 0) {
					char *temp1 = root->value;
					temp = root->child;
					root->value = with_val->value;
					root->child = with_val->child;
					with_val->value = temp1;
					with_val->child = temp;
					if(done == -1) {
						keep = root;
					}
					done = 0;
				}
				root = root->sibling;
			}
			if(keep != NULL) {
				root = keep;
			} else {
				root->value = with_val->value;
				root->child = with_val->child;
			}
			/**
			UNUSED CODE:
			struct TreeNode *temp = root;
			if(strcmp(values[level-2], root->value) < 0) {
				root->value = values[level-2];
			} else {
				temp->value = allocate_node(values[level-2]);
			}

			while(root->sibling != NULL) {
				root = root->sibling;
			}
			root->sibling = allocate_node(values[level-2]);
			root = root->sibling;
			**/

			/**
			ALSO (ANOTHER ATEMPT):
						// If the root's value is lesser in value in alphabetical order than the value soon to be inserted
			if(strcmp(root->value, values[level-2]) < 0){
				// If the sibling is not null, then:
				if(root->sibling != NULL) {
					// Creates node from sibling value (recursion)
					create_nodes(root->sibling, values, level);
				} else {
					// Allocates space at the last sibling for the new value
					root->sibling = allocate_node(values[level-2]);
					(root->sibling)->child = allocate_node(values[level-1]);
					// Creates the child nodes of the allocated node
					create_nodes((root->sibling)->child, values, level+1);
				}
			// Else:
			} else {
				struct TreeNode *root_temp = allocate_node(root->value);
				root_temp->child = root->child;
				root_temp->sibling = root->sibling;
				root->value = values[level-2];
				// Sets the root node to the value of the allocated node
				root->child = allocate_node(values[level-1]);
				root->sibling = root_temp;
				create_nodes(root->child, values, level+1);
			}
			**/
		}
		// If the child is NULL, then allocate space for it
		if(root->child == NULL) {
			root->child = allocate_node(values[level-1]);
		}
		// Create node for the child
		create_nodes(root->child, values, level+1);
	/** If the file name just needs to be entered into a node **/
	} else {
		// If there are more sibling nodes for file names that need to be created, then:
		if(strcmp(root->value, values[3]) != 0) {
			// If the current node's value is alphabetically first than the file name, then:
			if(strcmp(root->value, values[3]) < 0) {
				// If the sibling is not null, then:
				if(root->sibling != NULL) {
					// Creates node from sibling value (recursion)
					create_nodes(root->sibling, values, level);
				} else {
					// Allocates space at the last sibling for the new value
					root->sibling = allocate_node(values[3]);
				}
			// Else:
			} else {
				// Stores the value of the current node's value
				char *root_node_val = root->value;
				// Makes the current node's value the file name from the values
				root->value = values[3];
				// Sets file name of values to back to previous node's file name
				values[3] = root_node_val;
				// Creates node from left over value (recursion)
				create_nodes(root, values, level);
			}
		}
	}
}

/**
 * Returns the TreeNode of the first found file name with the attributes provided in
 * values. Returns NULL if the searched result is not found.
**/
struct TreeNode *first_found(struct TreeNode *root, char **values, int level) {
	struct TreeNode *ret_val;
	// When the root's value is one of the searched values
	if(strcmp(root->value, values[level-2]) == 0) {
		// Uses recursion to find the file name with the attributes provided
		ret_val = first_found(root->child, values, level+1);
	// When the root's sibling's value is one of the searched values
	} else if(found_sibling(root, values[level-2]) != -1) {
		// Loops until a root is found that has a value that matches the value
		// being search with
		for(int i = 0; i < found_sibling(root, values[level-2]); i++) {
			root = root->sibling;
		}
		// Uses recursion to find the file name with the attributes provided
		ret_val = first_found(root->child, values, level+1);
	// When the root's child is a node containing the file name
	} else if(level == 5) {
		ret_val = root;
	// When the one of the searched values is not found.
	} else {
		ret_val = NULL;
	}
	// Return return value
	return ret_val;
}

/**
 * Prints the database in alphabetical order. Each file with attributes holds up
 * each line.
 * values stores the values to be printed on level 5 and only_once allows a line
 * to be only printed once
**/
void print_database(struct TreeNode *tree, char **values, int level, int only_once) {
	// If the level is at 5, then:
	if(level == 5) {
		// Gets the file name of all the attributes collected
		values[3] = tree->value;
		// Loops through each attribute and file name collected and prints them
		for(int i = 0; i < 4; i++) {
			printf("%s ", values[i]);
		}
		// New line
		printf("\n");
	// Else:
	} else {
		// Grab the value of the current tree and store it into values to be used
		// later when print_database hits level 5
		values[level-2] = tree->value;
		// Use print_database with the a value gained in last line and the child of
		// the current node
		print_database(tree->child, values, level+1, 1);
	}

	// Ensures the recursion allows for each file and its attributes to printed only
	// once
	if(only_once == 1) {
		// Loops through until the sibling is NULL
		while(tree->sibling != NULL) {
			// Prints the file and its attributes from each case of a sibling
			print_database(tree->sibling, values, level, 0);
			// Sets tree to its sibling
			tree = tree->sibling;
		}
	}
}

/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for 
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values) {
	// If the child of the first empty root is NULL, then allocate space for a node
	// with the first attribute in values
	if(root->child == NULL) {
		root->child = allocate_node(values[0]);
	}
	// Use create_nodes to create each single node for each insert
	create_nodes(root->child, values, 2);
}

/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values) {
	// Stores the first node with the desired query values
	struct TreeNode *node_with_file = NULL;
	// If the child of the root is not NULL, then use first_found
	// to find the first node with the desired query values
	if(root->child != NULL) {
		node_with_file = first_found(root->child, values, 2);
	}

	// If node_with_file is still NULL, then print null message.
	if(node_with_file == NULL) {
		printf("(NULL)\n");
	// Else:
	} else {
		// Loop through each node with the file names and print them out
		while(node_with_file != NULL) {
			printf("%s ", node_with_file->value);
			node_with_file = node_with_file->sibling;
		}
		// New line
		printf("\n");
	}
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {
	// Empty array of char* to be used in print_database
	char *values[4];
	// If the child of the first node is NULL, then the who
	// database is NULL so print NULL
	if(tree->child == NULL) {
		printf("(NULL)\n");
	} else {
		// Else, use print_database to print each line of
		// a file name and its corresponding attributes
		print_database(tree->child, values, 2, 1);
	}
}