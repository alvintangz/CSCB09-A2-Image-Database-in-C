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
	struct TreeNode *node = malloc(sizeof(struct TreeNode));
	node->value = malloc(sizeof(char *));
	strcpy(node->value, value);
	node->sibling = NULL;
	node->child = NULL;
	return node;
}

/**
 * Returns the number of iterations until the sibling is found with the value or return -1 if none is found.
**/
int found_sibling(struct TreeNode *root, char *value) {
	int count = 1;
	int found = -1;
	while(root->sibling != NULL) {
		if(strcmp((root->sibling)->value, value) != 0 && found == -1) {
			count++;
		} else {
			found = 1;
		}
		root = root->sibling;
	}
	if(found == -1) {
		count = -1;
	}
	return count;
}

void create_nodes(struct TreeNode *root, char **values, int level) {
	/** If a node or nodes still need to be created for attributes of the file **/
	if(level < 5) {
		/** If the root of the file has a value equal to that of the current attribute **/
		if(strcmp(root->value, values[level-2]) == 0) {
			/** EMPTY **/
		} else if(found_sibling(root, values[level-2]) != -1) {
			int iterations = found_sibling(root, values[level-2]);
			for(int i = 0; i < iterations; i++) {
				root = root->sibling;
			}
		} else {
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
		}
		if(root->child == NULL) {
			root->child = allocate_node(values[level-1]);
		}
		create_nodes(root->child, values, level+1);
	/** If the file name just needs to be entered into a node **/
	} else {
		if(strcmp(root->value, values[level-2]) != 0) {
			struct TreeNode *with_val = allocate_node(values[level-2]);
			struct TreeNode *temp = root;
			int count = 1;
			while(root->sibling != NULL) {
				root = root->sibling;
				count++;
			}
			root->sibling = allocate_node(root->value);
			root = temp;
			for(int i = 0; i < count; i++) {
				if(strcmp(with_val->value, root->value) < 0) {
					char *temp1 = root->value;
					root->value = with_val->value;
					with_val->value = temp1;
				}
				root = root->sibling;
			}
			/**
			while(root->sibling != NULL) {
				root = root->sibling;
			}
			root->sibling = allocate_node(values[level-2]);
			**/
		} else {
			/**
			while(root != NULL) {

			}
			**/
		}
	}
}

struct TreeNode *first_found(struct TreeNode *root, char **values, int level) {
	/** When the root's value is one of the searched values. **/
	if(strcmp(root->value, values[level-2]) == 0) {
		return first_found(root->child, values, level+1);
	/** When the root's sibling's value is one of the searched values. **/
	} else if(found_sibling(root, values[level-2]) != -1) {
		for(int i = 0; i < found_sibling(root, values[level-2]); i++) {
			root = root->sibling;
		}
		return first_found(root->child, values, level+1);
	/** When the root's child is a node containing the file name. **/
	} else if(level == 5) {
		return root;
	/** When the one of the searched values is not found. **/
	} else {
		return NULL;
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
	if(root->child == NULL) {
		root->child = allocate_node(values[0]);
	}
	create_nodes(root->child, values, 2);
}

/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values) {
	struct TreeNode *node_with_file = NULL;
	if(root->child != NULL) {
		node_with_file = first_found(root->child, values, 2);
	}
	if(node_with_file == NULL) {
		printf("(NULL)\n");
	} else {
		while(node_with_file != NULL) {
			printf("%s ", node_with_file->value);
			node_with_file = node_with_file->sibling;
		}
		printf("\n");
	}
}

void print_each(struct TreeNode *tree, char **values, int level, int yes) {
	if(level == 5) {
		values[3] = tree->value;
		for(int i = 0; i < 4; i++) {
			printf("%s ", values[i]);
		}
		printf("\n");
	} else {
		values[level-2] = tree->value;
		print_each(tree->child, values, level+1, 1);
	}
	if(yes == 1) {
		struct TreeNode *temp = tree;
		while(temp->sibling != NULL) {
			print_each(temp->sibling, values, level, 0);
			temp = temp->sibling;
		}
	}
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {
	char *values[4];
	if(tree->child == NULL) {
		printf("(NULL)\n");
	} else {
		print_each(tree->child, values, 2, 1);
	}
}