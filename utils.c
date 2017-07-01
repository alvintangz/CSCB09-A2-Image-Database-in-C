/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <string.h>

#include "utils.h"


/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */
int tokenize(char *cmd, char **cmd_argv) {
	// A pointer to the current token
	char *token;
	// Stores the current index at cmd_argv which token will be stored
	int current_tok = 0;
	// Gets the first token, which would be a command
	token = strtok(cmd, DELIMITERS);
	// Loop until there are no more valid tokens
	while(token != NULL) {
		// Stores the current token in cmd_argv
		cmd_argv[current_tok] = token;
		// Get the next token
		token = strtok(NULL, DELIMITERS);
		// Increment the index at which a token will be stored in cmd_argv
		current_tok++;
	}
	// Returns the amount of tokens there are
	return current_tok;
}
