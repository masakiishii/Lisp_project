#include "ilisp.h"

char **Tokenizer_spliter(char *line)
{
	char *current_ptr = line;
	char *previous_ptr = line;
	char **token = (char **)malloc(sizeof(char *) * TOKENSIZE);
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

Tokenizer *new_Tokenizer(void)
{
	Tokenizer *t = (Tokenizer *)imalloc(sizeof(Tokenizer));
	t->spliter = Tokenizer_spliter;
	t->delete = Tokenizer_delete;
	t->dump = Tokenizer_dump;
	return t;
}

void Tokenizer_delete(char **token)
{

}

