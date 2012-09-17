#include "ilisp.h"

char **Tokenizer_spliter(char *line)
{
	char *current_ptr = line;
	char *previous_ptr = line;
	char **token = (char **)malloc(sizeof(char *) * TOKENSIZE);
	int i = 0;

	while(*current_ptr != EOL) {

		switch(*current_ptr) {

		case ')':
			if((*(current_ptr - 1) != ' ') && (*(current_ptr - 1) != ')')) {
				token[i] = strndup(previous_ptr, current_ptr - previous_ptr);
				token[i][current_ptr - previous_ptr] = EOL;
				i++;
			}
			token[i] = strndup(current_ptr, 1);
			token[i][1] = EOL;
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
				token[i][current_ptr - previous_ptr] = EOL;
				i++;
				current_ptr++;
				previous_ptr = current_ptr;
				break;
			}

		case '(': 
			token[i] = strndup(current_ptr, 1);
			token[i][1] = EOL;
			i++;
			current_ptr++;
			previous_ptr++;
			break;
			
		default : current_ptr++;
		}
	}
	token[i] = NULL;
//	Dump_Token(token);

	return token;
}



void Tokenizer_dump(char **token)
{
	int i = 0;
	while(token[i] != NULL) {
		DBG_P("<<Token>> = %s\n", token[i]);
		i++;
	}
}
int freelist_token_stack = 0;
void Tokenizer_delete(char **token, Tokenizer *t)
{
	int i = 0;
	if(defun_flag == ON) {
		t->freelist[freelist_token_stack] = token;
		freelist_token_stack++;
	}else{
		if (token != NULL) {
			while (token[i] != EOL) {
				free(token[i]);
				i++;
			}
			free(token);
		}
	}
}


Tokenizer *new_Tokenizer(void)
{
	int i;
	Tokenizer *t = (Tokenizer *)imalloc(sizeof(Tokenizer));
	t->spliter = Tokenizer_spliter;
	t->delete = Tokenizer_delete;
	t->dump = Tokenizer_dump;
	for(i = 0;i < FREELIST;i++) {
		t->freelist[i] = NULL;
	}
	return t;
}


