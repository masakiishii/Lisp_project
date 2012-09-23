#include <ilisp.h>

char **treePointer = NULL;
int setq_flag = 0;
int defun_flag = OFF;
int defun_call = OFF;

ConsCell *new_ConsCell(void)
{
	ConsCell *Cell = (ConsCell *)imalloc(sizeof(ConsCell));
	Cell->celltype = 0;
	Cell->car = NULL;
	Cell->ivalue = 0;
	Cell->svalue = NULL;
	Cell->cdr = NULL;
	return Cell;
}

Parser *new_Parser(void)
{
	int i;
	Parser *p = (Parser *)imalloc(sizeof(Parser));
	p->parser = Parser_parser;
	p->delete = Parser_delete;
	p->dump   = Parser_Dump;
	for(i = 0;i < FREELIST;i++) {
		p->freelist[i] = NULL;
	}
	return p;
}

int freelist_cell_stack = 0;
void Parser_delete(ConsCell *root, Parser *p)
{
	if(defun_flag == ON) {
		p->freelist[freelist_cell_stack] = root;
		freelist_cell_stack++;
	}else{
		if(root != NULL) {
			switch(root->celltype) {
			case T_BEGIN:
				if(root->cdr != NULL) {
					Parser_delete(root->cdr, p);
				}
				Parser_delete(root->car, p);
				free(root);
				root = NULL;
				break;
			case T_END:
				free(root);
				root = NULL;
				break;
			default :
				Parser_delete(root->cdr, p);
				free(root);
				root = NULL;
				break;
			}
		}
	}
}

ConsCell *Parser_parser(char **token)
{
	if((*token) == NULL) {
		return NULL;
	}

	ConsCell *head = new_ConsCell();
	ConsCell *path = head;
	ConsCell *branch[BRANCHSIZE] = {NULL};
	int branch_count = 0;

	while(*token != NULL) {
		switch(**token){
		case '(' :
			path->cdr = new_ConsCell();
			path = path->cdr;
			path->celltype = T_BEGIN;
			branch[branch_count++] = path;
			break;

		case ')' :
			path->cdr = new_ConsCell();
			path = path->cdr;
			path->celltype = T_END;
			path = branch[--branch_count];
			break;
	   
		case '-' :
			if(isalnum(*(*token+1))) {
				path->cdr = new_ConsCell();
				path = path->cdr;
				path->celltype = T_NUMBER;
				path->ivalue = strtol(*token, NULL, 10);
			}else{
				path->car = new_ConsCell();
				path = path->car;
				path->celltype = T_SUB;
			}
			break;

		case '+' :
			path->car = new_ConsCell();
			path = path->car;
			path->celltype = T_ADD;
			break;

		case '*' :
			path->car = new_ConsCell();
			path = path->car;
			path->celltype = T_MUL;
			break;

		case '/' :
			path->car = new_ConsCell();
			path = path->car;
			path->celltype = T_DIV;
			break;

		case '<' :
			path->car = new_ConsCell();
			path = path->car;
			path->celltype = T_LT;
			break;

		case '>' :
			path->car = new_ConsCell();
			path = path->car;
			path->celltype = T_GT;
			break;

		default :
			if(isdigit(**token)) {
				path->cdr = new_ConsCell();
				path = path->cdr;
				path->celltype = T_NUMBER;
				path->ivalue = strtol(*token, NULL, 10);
			}else if(isalpha(**token)) {
				if((strncmp(*token, "if", 3) == 0)) {
					path->car = new_ConsCell();
					path = path->car;
					path->celltype = T_IF;
					path->svalue = *token;
				}else if((strncmp(*token, "setq", 5) == 0)) {
					setq_flag = ON;
					path->car = new_ConsCell();
					path = path->car;
					path->celltype = T_SETQ;
				}else if((strncmp(*token, "defun", 6) == 0)) {
					defun_flag = ON;
					path->car = new_ConsCell();
					path = path->car;
					path->celltype = T_DEFUN;
				}else{
					if((strncmp(*(token-1), "defun", 6) == 0)) {
						path->cdr = new_ConsCell();
						path = path->cdr;
						path->celltype = T_FUNC;
						path->svalue = *token;
						defun_call = ON;
					}else if(((**(token-1) == '(') && (defun_flag == OFF))) {
						path->car = new_ConsCell();
						path = path->car;
						path->celltype = T_FUNC;
						path->svalue = *token;
					}else if(((**(token-1) == '(') && (defun_call == OFF)) || ((defun_flag == ON) && (**(token-1) != '('))) {
						path->cdr = new_ConsCell();
						path = path->cdr;
						path->celltype = T_ARGUMENT;
						path->svalue = *token;
					}else{
						if(defun_flag == ON) {
							path->car = new_ConsCell();
							path = path->car;
							path->celltype = T_FUNC;
							path->svalue = *token;
						}else{
							path->cdr = new_ConsCell();
							path = path->cdr;
							path->celltype = T_STRING;
							path->svalue = *token;
						}
					}
				}
			}
			break;
		}
		token++;
	}
	return head;
}

//ConsCell *Parser_parser(char **token)
//{
//	if((*token) == NULL) {
//		return NULL;
//	}
//
//	ConsCell *head = (ConsCell *)imalloc(sizeof(ConsCell));
//
//	switch(**token){
//	
//	case '(' :
//		head->celltype = T_BEGIN;
//		treePointer++;
//		head->car = Parser_parser(treePointer);
//		head->cdr = Parser_parser(treePointer);
//		break;
//
//	case ')' :
//		head->celltype = T_END;
//		treePointer++;
//		break;
//	   
//	case '-' :
//		if(isalnum(*(*token+1))) {
//			head->celltype = T_NUMBER;
//			head->ivalue = strtol(*token, NULL, 10);
//			treePointer++;
//			head->cdr = Parser_parser(treePointer);
//
//		}else{
//			head->celltype = T_SUB;
//			treePointer++;
//			head->cdr = Parser_parser(treePointer);
//		}
//		break;
//
//	case '+' :
//		head->celltype = T_ADD;
//		treePointer++;
//		head->cdr = Parser_parser(treePointer); 
//		break;
//
//	case '*' :
//		head->celltype = T_MUL;
//		treePointer++;
//		head->cdr = Parser_parser(treePointer); 
//		break;
//
//	case '/' :
//		head->celltype = T_DIV;
//		treePointer++;
//		head->cdr = Parser_parser(treePointer); 
//		break;
//
//	case '<' :
//		head->celltype = T_LT;
//		treePointer++;
//		head->cdr = Parser_parser(treePointer);
//		break;
//
//	case '>' :
//		head->celltype = T_GT;
//		treePointer++;
//		head->cdr = Parser_parser(treePointer);
//		break;
//
//	default :
//		if(isdigit(**token)) {
//			head->celltype = T_NUMBER;
//			head->ivalue = strtol(*token, NULL, 10);
//			treePointer++;
//			head->cdr = Parser_parser(treePointer);
//		}else if(isalpha(**token)) {
//			if((strncmp(*token, "if", 3) == 0)) {
//				head->celltype = T_IF;
//				head->svalue = *token;
//				treePointer++;
//				head->cdr = Parser_parser(treePointer);
//			}else if((strncmp(*token, "setq", 5) == 0)) {
//				setq_flag = 1;
//				head->celltype = T_SETQ;
//				treePointer++;
//				head->cdr = Parser_parser(treePointer);
//			}else if((strncmp(*token, "defun", 6) == 0)) {
//				head->celltype = T_DEFUN;
//				defun_flag = ON;
//				treePointer++;
//				head->cdr = Parser_parser(treePointer);
//			}else{
//				if(((**(token-1) == '(') && (defun_flag != ON)) || (strncmp(*(token-1), "defun", 6) == 0)) {
//					head->celltype = T_FUNC;				
//					head->svalue = *token;
//					defun_call = ON;
//					treePointer++;
//					head->cdr = Parser_parser(treePointer);
//				}else if(((**(token-1) == '(') && (defun_call == OFF)) || ((defun_flag == ON) && (**(token-1) != '('))) {
//					head->celltype = T_ARGUMENT;
//					head->svalue = *token;
//					treePointer++;
//					head->cdr = Parser_parser(treePointer);
//				}else{
//					if(defun_flag == ON) {
//						head->celltype = T_FUNC;				
//						head->svalue = *token;
//						treePointer++;
//						head->cdr = Parser_parser(treePointer);
//					}else{
//						head->celltype = T_STRING;
//						head->svalue = *token;
//						treePointer++;
//						head->cdr = Parser_parser(treePointer);
//					}
//				}
//			}
//		}
//		break;
//	}
//	return head;
//}

void Parser_Dump(ConsCell *root, int level)
{
	int i;

	if(root == NULL){
		fprintf(stderr,"error!\n");
	}else{
		switch(root->celltype){
		case T_BEGIN    :
			if(root->cdr != NULL) {
				Parser_Dump(root->cdr, level+1);
			}else if( (root->cdr == NULL) && (level != 0) ){
				Parser_Dump(root->cdr, level+1);
			}
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'('\n");
			Parser_Dump(root->car, level+1);
			break;
		case T_END :
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"')'\n");
			break;
		case T_ADD     :
			Parser_Dump(root->cdr, level+1);

			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'+'\n");
			break;

		case T_SUB     :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'-'\n");
			break;

		case T_MUL    :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'*'\n");
			break;

		case T_DIV     :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'/'\n");
			break;

		case T_LT    :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'<'\n");
			break;

		case T_GT    :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"'>'\n");
			break;

		case T_NUMBER   :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"%d\n", root->ivalue);
			break;

		case T_IF       :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"if\n");
			break;

		case T_SETQ     :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"setq\n");
			break;

		case T_DEFUN    :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"defun\n");
			break;

		case T_FUNC   :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"F:%s\n", root->svalue);
			break;

		case T_STRING   :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"S:%s\n", root->svalue);
			break;


		case T_ARGUMENT :
			Parser_Dump(root->cdr, level+1);
			for(i=0;i<level;i++)
				fprintf(stderr,"  ");
			fprintf(stderr,"A:%s\n", root->svalue);
			break;
		}
	}

}
