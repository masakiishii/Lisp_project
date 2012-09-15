#include "ilisp.h"

char **treePointer = NULL;
int setq_flag = 0;
int defun_flag = OFF;
int defun_call = OFF;

ConsCell *new_ConsCell(void)
{
	ConsCell *Cell = (ConsCell *)malloc(sizeof(ConsCell));
	Cell->celltype = 0;
	Cell->car = NULL;
	Cell->ivalue = 0;
	Cell->svalue = NULL;
	Cell->cdr = NULL;
	return Cell;
}

Parser *new_Parser(void)
{
	Parser *p = (Parser *)imalloc(sizeof(Parser));
	p->parser = Parser_parser;
	p->delete = Parser_delete;
	p->dump   = Parser_Dump;
	return p;
}

void Parser_delete(Parser *p)
{
	free(p);
	p = NULL;
}

ConsCell *Parser_parser(char **token)
{
	if((*token) == NULL) {
		return NULL;
	}

	ConsCell *head = (ConsCell *)malloc(sizeof(ConsCell));

	switch(**token){
	
	case '(' :
		head->celltype = T_BEGIN;
		treePointer++;
		head->car = parse(treePointer);
		head->cdr = parse(treePointer);
		break;

	case ')' :
		head->celltype = T_END;
		treePointer++;
		break;
	   
	case '-' :
		if(isalnum(*(*token+1))) {
			head->celltype = T_NUMBER;
			head->ivalue = strtol(*token, NULL, 10);
			treePointer++;
			head->cdr = parse(treePointer);

		}else{
			head->celltype = T_SUB;
			treePointer++;
			head->cdr = parse(treePointer);
		}
		break;

	case '+' :
		head->celltype = T_ADD;
		treePointer++;
		head->cdr = parse(treePointer); 
		break;

	case '*' :
		head->celltype = T_MUL;
		treePointer++;
		head->cdr = parse(treePointer); 
		break;

	case '/' :
		head->celltype = T_DIV;
		treePointer++;
		head->cdr = parse(treePointer); 
		break;

	case '<' :
		head->celltype = T_LT;
		treePointer++;
		head->cdr = parse(treePointer);
		break;

	case '>' :
		head->celltype = T_GT;
		treePointer++;
		head->cdr = parse(treePointer);
		break;

	default :
		if(isdigit(**token)) {
			head->celltype = T_NUMBER;
			head->ivalue = strtol(*token, NULL, 10);
			treePointer++;
			head->cdr = parse(treePointer);
		}else if(isalpha(**token)) {
			if((strncmp(*token, "if", 3) == 0)) {
				head->celltype = T_IF;
				head->svalue = *token;
				treePointer++;
				head->cdr = parse(treePointer);
			}else if((strncmp(*token, "setq", 5) == 0)) {
				setq_flag = 1;
				head->celltype = T_SETQ;
				treePointer++;
				head->cdr = parse(treePointer);
			}else if((strncmp(*token, "defun", 6) == 0)) {
				head->celltype = T_DEFUN;
				defun_flag = ON;
				treePointer++;
				head->cdr = parse(treePointer);
			}else{
				if(((**(token-1) == '(') && (defun_flag != ON)) || (strncmp(*(token-1), "defun", 6) == 0)) {
					head->celltype = T_FUNC;				
					head->svalue = *token;
					defun_call = ON;
					treePointer++;
					head->cdr = parse(treePointer);
				}else if(((**(token-1) == '(') && (defun_call == OFF)) || ((defun_flag == ON) && (**(token-1) != '('))) {
					head->celltype = T_ARGUMENT;
					head->svalue = *token;
					treePointer++;
					head->cdr = parse(treePointer);
				}else{
					if(defun_flag == ON) {
						head->celltype = T_FUNC;				
						head->svalue = *token;
						treePointer++;
						head->cdr = parse(treePointer);
					}else{
						head->celltype = T_STRING;
						head->svalue = *token;
						treePointer++;
						head->cdr = parse(treePointer);
					}
				}
			}
		}
		break;
	}
	return head;
}

void Parser_Dump(ConsCell *root, int level)
{
	int i;

	if(root == NULL){
		fprintf(stderr,"error!\n");
	}else{

		switch(root->celltype){
		case T_BEGIN    :
			if(root->cdr != NULL) {
				Tree_Dump(root->cdr, level+1);
			}else if( (root->cdr == NULL) && (level != 0) ){
				Tree_Dump(root->cdr, level+1);
			}
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'('\n");
			Tree_Dump(root->car, level+1);
			break;
		case T_END :
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"')'\n");
			break;
		case T_ADD     :
			Tree_Dump(root->cdr, level+1);

			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'+'\n");
			break;

		case T_SUB     :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'-'\n");
			break;

		case T_MUL    :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'*'\n");
			break;

		case T_DIV     :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'/'\n");
			break;

		case T_LT    :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'<'\n");
			break;

		case T_GT    :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'>'\n");
			break;

		case T_NUMBER   :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"%d\n", root->ivalue);
			break;

		case T_IF       :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"if\n");
			break;

		case T_SETQ     :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"setq\n");
			break;

		case T_DEFUN    :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"defun\n");
			break;

		case T_FUNC   :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"F:%s\n", root->svalue);
			break;

		case T_STRING   :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"S:%s\n", root->svalue);
			break;


		case T_ARGUMENT :
			Tree_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"A:%s\n", root->svalue);
			break;
		}
	}

}
