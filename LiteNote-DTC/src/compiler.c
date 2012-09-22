#include <ilisp.h>

int defun_flag;

Compiler *new_Compiler(void)
{
	Compiler *c = (Compiler *)imalloc(sizeof(Compiler));
	c->compile = Compiler_compile;
	c->compileToFastCode = Compiler_compileToFastCode;
	c->delete = Compiler_delete;
	return c;
}

void Compiler_delete(Compiler *c)
{
	free(c);
	c = NULL;
}

void Compiler_compile(ConsCell *root, VirtualMachineByteCodeLine *func, int r)
{
	ConsCell *eval_pointer = NULL;
	int if_index;
	int jump_index;
	ConsCell *arg_ptr;

	switch(root->celltype){
	case T_BEGIN:
		DBG_P("=====<<<T_BEGIN>>>=====");
		root = root->car;
		eval_pointer = root->cdr;
//		if(root->celltype == T_OPERATOR){
		Compiler_compile(root, func, r);
//		}
		break;

	case T_END :
		DBG_P("=====<<<T_END>>>=====");
		break;

	case T_ADD :
		DBG_P("=====<<<OPADD>>>=====");
		eval_pointer = root->cdr;
		Compiler_compile(eval_pointer, func, r);
		while((eval_pointer->cdr->celltype != T_END)){
			Compiler_compile(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = OPADD;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			eval_pointer = eval_pointer->cdr;
		}
		break;

	case T_SUB :
		DBG_P("=====<<<OPSUB>>>=====");
		eval_pointer = root->cdr;
		Compiler_compile(eval_pointer, func, r);
		while((eval_pointer->cdr->celltype != T_END)){
			Compiler_compile(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = OPSUB;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			eval_pointer = eval_pointer->cdr;
		}
		break;

	case T_MUL :
		DBG_P("=====<<<OPMUL>>>=====");
		eval_pointer = root->cdr;
		Compiler_compile(eval_pointer, func, r);
		while((eval_pointer->cdr->celltype != T_END)){
			Compiler_compile(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = OPMUL;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			eval_pointer = eval_pointer->cdr;
		}
		break;

	case T_DIV :
		DBG_P("=====<<<OPDIV>>>=====");
		eval_pointer = root->cdr;
		Compiler_compile(eval_pointer, func, r);
		while((eval_pointer->cdr->celltype != T_END)){
			Compiler_compile(eval_pointer->cdr, func, r+1);
			func->code[func->index].op = OPDIV;
			func->code[func->index].reg0 = r;
			func->code[func->index].reg1 = r;
			func->code[func->index].reg2 = r+1;
			func->index++;
			eval_pointer = eval_pointer->cdr;
		}
		break;
	case T_LT :
		DBG_P("=====<<<OPLT>>>=====");
		eval_pointer = root->cdr;
		Compiler_compile(eval_pointer, func, r);
		Compiler_compile(eval_pointer->cdr, func, r+1);
		func->code[func->index].op = OPLT;
		func->code[func->index].reg0 = r;
		func->code[func->index].reg1 = r;
		func->code[func->index].reg2 = r+1;
		func->index++;
		break;
	case T_GT :
		DBG_P("=====<<<OPGT>>>=====");
		eval_pointer = root->cdr;
		Compiler_compile(eval_pointer, func, r);
		Compiler_compile(eval_pointer->cdr, func, r+1);
		func->code[func->index].op = OPGT;
		func->code[func->index].reg0 = r;
		func->code[func->index].reg1 = r;
		func->code[func->index].reg2 = r+1;
		func->index++;
		break;

	case T_IF :
		DBG_P("=====<<<T_IF>>>=====");
		eval_pointer = root->cdr;
		Compiler_compile(eval_pointer, func, r);
		func->code[func->index].op = OPIF;
		func->code[func->index].reg0 = r;
		if_index = func->index;
		func->index++;
		Compiler_compile(eval_pointer->cdr, func, r);
		func->code[func->index].op = OPJMP;
		func->code[func->index].reg0 = 0;
		jump_index = func->index;
		func->index++;
		func->code[if_index].pc2 = &func->code[func->index];
		Compiler_compile(eval_pointer->cdr->cdr, func, r);
		func->code[jump_index].pc2 = &func->code[func->index];
		break;

	case T_DEFUN :
		DBG_P("=====<<<defun>>>=====");
		eval_pointer = root->cdr;
		int counter = 0;
		ConsCell *arg = root->cdr->cdr->car;
		while(arg->celltype != T_END) {
			counter++;
			arg = arg->cdr;
		}
		VirtualMachineByteCodeLine *newfunc;
		newfunc = new_VirtualMachineByteCodeLine();
		//hash_put(root->cdr->svalue, newfunc);
		Map *map = new_Map(root->cdr->svalue, (void *)newfunc);
		store_to_virtualmachine_memory(map);
		newfunc->index = 0;
		newfunc->cons = root;
		Compiler_compile(eval_pointer->cdr->cdr, newfunc, counter);
		newfunc->code[newfunc->index].op = OPRET;
		newfunc->code[newfunc->index].reg0 = counter;
		newfunc->size = newfunc->index - 1;
		Compiler_compileToFastCode(newfunc);
		break;

	case T_FUNC:{
		//VirtualMachineByteCodeLine *s_func;
		int counter = 0;
		eval_pointer = root;
		//s_func = search_func_hash(root->svalue);
		//s_func = (VirtualMachineByteCodeLine *)fetch_from_virtualmachine_memory(root->svalue);
		while(root->cdr->celltype != T_END){
			Compiler_compile(root->cdr, func, r + counter);
			root = root->cdr;
			counter++;
		}
		func->code[func->index].op = OPCALL;
		func->code[func->index].reg0 = r;
		func->code[func->index].name = eval_pointer->svalue;
		//func->code[func->index].pc2 = &s_func->code[0];
		func->index++;
		break;
	}
	case  T_NUMBER:
		DBG_P("=====<<<T_NUMBER>>>=====");
		func->code[func->index].op = OPLOAD;
		func->code[func->index].reg0 = r;
		func->code[func->index].data1 = root->ivalue;
		func->index++;
		break;

	case T_ARGUMENT:
	case T_STRING:{
		DBG_P("=====<<<OPMOV>>>=====");
		int counter = 0;
		arg_ptr = func->cons->cdr->cdr->car;
		while(arg_ptr->celltype != T_END) {
			if(strcmp(arg_ptr->svalue, root->svalue) == 0) {
				func->code[func->index].op = OPMOV;
				func->code[func->index].reg0 = r;
				func->code[func->index].reg1 = counter;
				func->index++;	
			}
			arg_ptr = arg_ptr->cdr;
			counter++;
		}
		break;
	}
	default :
		break;
	}
}


void Compiler_compileToFastCode(VirtualMachineByteCodeLine *vmcode)
{
	int i;
	ByteCode *code = vmcode->code;
	static int remove_counter = 0;
	static int jmp_index = 0;


	for(i = 0; code[i].op != OPRET; i++) {
		switch(code[i].op) {
		case OPCALL:
			code[i].op = OPFASTCALL;
			break;
		case OPSUB:
			if(code[i - 1].op == OPLOAD && code[i - 2].op == OPMOV) {
				code[i].op = OPiSUBC;
				code[i].data2 = code[i - 1].data1;
				code[i].reg1 = code[i - 2].reg1;
				vmcode->remove(vmcode, i - 1);
				vmcode->remove(vmcode, i - 2);
				i -= 2;
				remove_counter += 2;
			}
			break;

		case OPLT :
			if(code[i - 1].op == OPLOAD && code[i - 2].op == OPMOV) {
				code[i].op = OPiLTC;
				code[i].data2 = code[i - 1].data1;
				code[i].reg1 = code[i - 2].reg1;
				vmcode->remove(vmcode, i - 1);
				vmcode->remove(vmcode, i - 2);
				i -= 2;
				remove_counter += 2;
			}
			break;

		case OPJMP:
			jmp_index = i;
			break;

		case OPIF :
			code[i].pc2 -= remove_counter;
			break;

		default:
			break;
		}
	}
	code[jmp_index].pc2 -= remove_counter;
}
