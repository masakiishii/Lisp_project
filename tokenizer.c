#include "ilisp.h"

char **tokenize(void)
{
	char *p = (char *)readline(">>>");
	add_history(p);
	char str_bye[] = "(bye)";
	char str_exit[] = "(exit)";

	if( (strcmp(str_bye, p) == 0) || (strcmp(str_exit, p) == 0) ){
		return NULL;
	}else{
  
	char *p1 = p;
	char *p2 = p;
	char **token = (char **)malloc(sizeof(char *)*1024);    
	int i=0;

	while(*p1 != '\0'){

		switch(*p1){

		case ')':
			if( *(p1-1) != ' '){
				token[i] = strndup(p2,p1-p2);
				token[i][p1-p2] = '\0';
				i+=1;
				token[i] = strndup(p1,1);
				token[i][1] = '\0';
				i+=1;
				p1+=1;
				p2=p1;
			}else{
				token[i] = strndup(p1,1);
				token[i][1] = '\n';
				i+=1;
			}
			break;

		case ' ':
		case '\n':
			if(p1 == p2){
				p1++;
				p2 = p1;
				break;
			}else{
				token[i] = strndup(p2,p1-p2);
				token[i][p1-p2] = '\0';
				i+=1;
				p1+=1;
				p2=p1;
				break;
			}

		case '(': 
			token[i] = strndup(p1, 1);
			token[i][1] = '\0';
			i++;
			p1++;
			p2++;
			break;

		default : p1++;
		}
	}
	token[i] = NULL;

	print_test(token);

	return token;
	}
}

void print_test(char **pt){
	int i = 0;
	while(pt[i] != NULL) {
		printf("%s\n", pt[i]);
		i++;
	}
}
