#include "ilisp.h"

char **tokenize(void)
{
	char *p = (char *)readline(">>>");
  
n	char *p1 = p;
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
			token[i] = strndup(p2,p1-p2);
			token[i][p1-p2] = '\0';
			i+=1;
			p1+=1;
			p2=p1;
			break;

		case '(': 
			//token[i++] = (char *)malloc(sizeof(char));
			//**token = *p1;
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

//  token[i] = (char *)malloc(sizeof(char));
//  *token[i] = '\0';

//  print_test(token);

	return token;
}

void print_test(char **pt){
	int i = 0;
	while(pt[i] != NULL) {
		printf("%s\n", pt[i]);
		i++;
	}
}
//
//
//
//	int i;
//
//	for(i=0;i<n;i++)
//		printf("%s\n",pt[i]);
//
//}
/*("%c",*p++);
  
  printf("\n");
  }else if((*p != ' ') && (!isalnum(*p))){
  if(((*p == '-') || (*p == '+')) && (isdigit(*(p+1)) != 0)){
  pars[i++] = p;
  printf("%c",*p++);
  while(isdigit(*p))
  printf("%c",*p++);

  printf("\n");
  }else{
  pars[i++] = p;
  printf("%c\n",*p++);
  }
  }
*/
