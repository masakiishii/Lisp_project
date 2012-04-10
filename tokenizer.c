#include "ilisp.h"


char **token(void)
{

  char *p = (char *)readline(">>>");
  
  char *p1 = p;
  char *p2 = p;
  char **token = (char **)malloc(sizeof(char *)*1024);    
  int i=0;

  while(*p1 != '\0'){

	switch(*p1){
	case '(': 
	case ')': 
	  token[i++] = (char *)malloc(sizeof(char));
	  **token = *p1;
	  p1++;
	  break;

	case ' ': case '\n': 
	  token[i] = (char *)malloc(sizeof(char)*(p1-p2));
	  memcpy(token[i],p2,p1-p2);
	  p1++;
	  p2 = p1;
	  i++;
	  break;


	default : p1++;
	}
  }
  return token;
}

/*    if(*p == ' '){
      p++;
    }else if(isalnum(*p)){
	  pars[i++] = p;
	  while(isalnum(*p))
			printf("%c",*p++);
  
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
