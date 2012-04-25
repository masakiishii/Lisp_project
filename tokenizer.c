#include "ilisp.h"

char **tokenize(char *line)
{
	char *p;

	if(line == NULL) {
		p = (char *)readline(">>>");
		add_history(p);
	}else{
		p = line;
	}

	char str_bye[] = "(bye)";
	char str_exit[] = "(exit)";

	if((strcmp(str_bye, p) == 0) || (strcmp(str_exit, p) == 0)) {
		return NULL;
	} else {

		char *current_ptr = p;
		char *previous_ptr = p;
		char **token = (char **)malloc(sizeof(char *) * HEAP_SIZE);
		int i = 0;

		while(*current_ptr != '\0') {

			switch(*current_ptr) {

			case ')':
				if((*(current_ptr - 1) != ' ') && (*(current_ptr - 1) != ')')) {
					token[i] = strndup(previous_ptr, current_ptr - previous_ptr);
					token[i][current_ptr - previous_ptr] = '\0';
					i++;
				}
				token[i] = strndup(current_ptr, 1);
				token[i][1] = '\0';
				i++;
				current_ptr++;
				previous_ptr = current_ptr;
				break;

		case ' ':
		case '\n':
			if(current_ptr == previous_ptr) {
				current_ptr++;
				previous_ptr = current_ptr;
				break;
			}else{
				token[i] = strndup(previous_ptr, current_ptr - previous_ptr);
				token[i][current_ptr - previous_ptr] = '\0';
				i++;
				current_ptr++;
				previous_ptr = current_ptr;
				break;
			}

		case '(': 
			token[i] = strndup(current_ptr, 1);
			token[i][1] = '\0';
			i++;
			current_ptr++;
			previous_ptr++;
			break;
			
		default : current_ptr++;
		}
	}
	token[i] = NULL;

//	print_test(token);

	return token;
	}
}

void print_test(char **pt)
{
	int i = 0;
	while(pt[i] != NULL) {
		printf("%s\n", pt[i]);
		i++;
	}
}
