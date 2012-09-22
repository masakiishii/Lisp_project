#include <ilisp.h>

char **Tokenizer_spliter(char *line)
{
	char *current = line;
	char *previous = line;
	char **token = (char **)imalloc(sizeof(char *) * TOKENSIZE);
	int i = 0;

	while(*current != EOL) {

		switch(*current) {

		case ')':
			if((*(current - 1) != ' ') && (*(current - 1) != ')')) {
				token[i] = strndup(previous, current - previous);
				token[i][current - previous] = EOL;
				i++;
			}
			token[i] = strndup(current, 1);
			token[i][1] = EOL;
			i++;
			current++;
			previous = current;
			break;

		case ' ':
		case '\n':
			if(current == previous) {
				current++;
				previous = current;
				break;
			}else{
				token[i] = strndup(previous, current - previous);
				token[i][current - previous] = EOL;
				i++;
				current++;
				previous = current;
				break;
			}

		case '(': 
			token[i] = strndup(current, 1);
			token[i][1] = EOL;
			i++;
			current++;
			previous++;
			break;
			
		default : current++;
		}
	}
	token[i] = NULL;

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


