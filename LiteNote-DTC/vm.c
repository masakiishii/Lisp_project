#include "ilispvm.h"

int vm_run(bytecode_t *op, int *sp)
{
	bytecode_t *pc;

	while(1) {
		pc = op;

		switch (pc->op) {
		case SET:
			sp[pc->reg0] = pc->data1;
			break;

		case ADD:
			sp[pc->reg0] = sp[pc->reg1] + sp[pc->reg2];
			break;

		case SUB:
			sp[pc->reg0] = sp[pc->reg1] - sp[pc->reg2];
			break;

		case MULT:
			sp[pc->reg0] = sp[pc->reg1] * sp[pc->reg2];
			break;

		case DEV:
			sp[pc->reg0] = sp[pc->reg1] / sp[pc->reg2];
			break;

		case LESSTHAN:
			if(sp[pc->reg1] < sp[pc->reg2]) {
				sp[pc->reg0] = 1;
			}else{
				sp[pc->reg0] = 0;
			}
			break;

		case L_EQUAL:
			if(sp[pc->reg1] <= sp[pc->reg2]) {
				sp[pc->reg0] = 1;
			}else{
				sp[pc->reg0] = 0;
			}
			break;

		case GREATERTHAN:
			if(sp[pc->reg1] > sp[pc->reg2]) {
				sp[pc->reg0] = 1;
			}else{
				sp[pc->reg0] = 0;
			}
			break;

		case G_EQUAL:
			if(sp[pc->reg1] >= sp[pc->reg2]) {
				sp[pc->reg0] = 1;
			}else{
				sp[pc->reg0] = 0;
			}
			break;
		case IF:
			if(sp[pc->reg0] == 0) {
				op = pc->pc2;
				continue;
			}
			break;

		case JUMP:
				op = pc->pc2;
				continue;

		case MOV:
			sp[pc->reg0] = sp[pc->reg1];
			break;

		case CALL:
			sp[pc->reg0] = vm_run(pc->pc2, sp+pc->reg0);
			break;
				
		case RET:
			return sp[pc->reg0];

		default:
			abort();
		}
		op++;
	}
}
