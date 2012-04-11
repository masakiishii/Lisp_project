#include "ilisp.h"



char **tokenize(void)
{
  char *p = (char *)readline(">>>");
  
  char *p1 = p;
  char *p2 = p;
  char **token = (char **)malloc(sizeof(char *)*1024);    
  int i=0;

  while(*p1 != '\0'){

	switch(*p1){

	case ')':
	case ' ':
	case '\n':
		if(*p1 == ')'){
			token[i] = strndup(p2, p1-p2-1);
			i+=1;
			token[i] = strndup(p1,1);
			p1+=1;
			p2=p1;
		}else{
			token[i] = strndup(p2,p1-p2);
			i+=1;
			p1+=1;
			p2=p1;
		}
		break;

	case '(': 
	  //token[i++] = (char *)malloc(sizeof(char));
	  //**token = *p1;
          token[i] = strndup(p1, 1);
          i++;
		  p1++;
		  p2++;
		  break;

	default : p1++;
	}
  }
  token[i] = (char *)malloc(sizeof(char));
  *token[i] = '\0';
  return token;
}
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
