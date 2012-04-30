#include "ilisp.h"


char *skip_space(char *buf)
{
	while (*buf != NULL) {
		char c = *buf;
		switch (c) {
		case ' '  :
			buf++;
			continue;
		default :
			break;
		}
		break;
	}
	return buf;
}
token_t *tokenize(char *buf)
{
	token_t *tokens = (token_t *)malloc(sizeof(token_t) * 1024);
	token_t *pointer;
	token_t *head = tokens;

	while (*buf != '\n') {
		buf = skip_space(buf);
		char c = *buf;
		switch (c) {
		case '(' :
			*tokens = parse_begin(buf);
			tokens++;
			break;
		case ')' :
			*tokens = parse_end(buf);
			tokens++;
			break;
		case '+' :
		case '-' :
			if(isalnum(*(buf+1)))
				goto number;

		case '*' :
		case '/' :
		case '=' :
		case '<' :
		case '>' :
			*tokens = parse_operater(buf);
			tokens++;
			break;
		case '0' :
		case '1' :
		case '2' :
		case '3' :
		case '4' :
		case '5' :
		case '6' :
		case '7' :
		case '8' :
		case '9' :
number:     *tokens = parse_number(buf);
			tokens++;
			break;
		default:
			*tokens = parse_symbol(buf);
			tokens++;
			break;
		}
		buf++;
	}
	return head;
}


token_t parse_begin(char *buf)
{
	token_t parse_bgn;
	parse_bgn.type = T_BEGIN;
	parse_bgn.str = strndup(buf, 1);
	return parse_bgn;
}


token_t parse_end(char *buf)
{
	token_t parse_ed;
	parse_ed.type = T_END;
	parse_ed.str = strndup(buf, 1);
	return parse_ed;
}

token_t parse_operater(char *buf)
{
	token_t parse_op;
	parse_op.type = T_OPERATOR;
	parse_op.str = strndup(buf, 1);
	return parse_op;
}


token_t parse_number(char *buf)
{
	char *buf_current = buf;
	token_t parse_num;

	while(isalnum(*buf_current)){
		buf_current++;
	}
	parse_num.str = strndup(buf, buf_current - buf);
	parse_num.type = T_NUMBER;
	buf = buf_current;
	return parse_num;
}

token_t parse_symbol(char *buf)
{
	char *buf_current = buf;
	token_t parse_num;

	while(*buf_current != ' '){
		buf_current++;
	}
	parse_num.str = strndup(buf, buf_current - buf);
	parse_num.type = T_STRING;
	buf = buf_current;
	return parse_num;

}
