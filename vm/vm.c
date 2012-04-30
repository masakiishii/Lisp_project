#include "ilispvm.h"

int vm_run(bytecode_t *op)
{
	bytecode_t *pc;
	int regs[128];
	while(1) {
		pc = op;
		switch (pc->op) {
		case SET:
			regs[pc->reg0] = pc->data1;
			break;
		case ADD:
			regs[pc->reg0] = regs[pc->reg1] + regs[pc->reg2];
			break;
		case SUB:
			regs[pc->reg0] = regs[pc->reg1] - regs[pc->reg2];
			break;
		case MULT:
			regs[pc->reg0] = regs[pc->reg1] * regs[pc->reg2];
			break;
		case DEV:
			regs[pc->reg0] = regs[pc->reg1] / regs[pc->reg2];
			break;
		case LESSTHAN:
			if(regs[pc->reg1] < regs[pc->reg2]) {
				regs[pc->reg0] = 1;
			}else{
				regs[pc->reg0] = 0;
			}
			break;
		case L_EQUAL:
			if(regs[pc->reg1] <= regs[pc->reg2]) {
				regs[pc->reg0] = 1;
			}else{
				regs[pc->reg0] = 0;
			}
			break;
		case GREATERTHAN:
			if(regs[pc->reg1] > regs[pc->reg2]) {
				regs[pc->reg0] = 1;
			}else{
				regs[pc->reg0] = 0;
			}
			break;
		case G_EQUAL:
			if(regs[pc->reg1] >= regs[pc->reg2]) {
				regs[pc->reg0] = 1;
			}else{
				regs[pc->reg0] = 0;
			}
			break;
		case RET:
			return regs[pc->reg0];
			/* case IF: */
			/* 	if (regs[pc->reg0]) { */
			/* 		op =  pc->pc1; */
			/* 		continue; */
				
			break;

		}
		op++;
	}
}



/* 	bytecode_t *ops = malloc(sizeof(*ops) * 1024); */
/* 	/\* */
/* 	 *  L_0: set reg1 10 */
/* 	 *  L_1: set reg2 20 */
/* 	 *  L_2: if (reg1) goto L_5; */
/* 	 *  L_3: add reg0 reg1 reg2 */
/* 	 *  L_4: add reg0 reg1 reg2 */
/* 	 *  L_5: ret reg0 */
/* 	 *\/ */
/* 	ops[0].op = SET; */
/* 	ops[0].reg0 = 1; */
/* 	ops[0].data1 = 10; */

/* 	ops[1].op = SET; */
/* 	ops[1].reg0 = 2; */
/* 	ops[1].data1 = 20; */

/* 	ops[2].op = IF; */
/* 	ops[2].reg0 = 1; */
/* 	ops[2].pc1  = &ops[5]; */

/* 	ops[3].op = ADD; */
/* 	ops[3].reg0 = 0; */
/* 	ops[3].reg1 = 1; */
/* 	ops[3].reg2 = 2; */

/* 	ops[4].op = ADD; */
/* 	ops[4].reg0 = 0; */
/* 	ops[4].reg1 = 1; */
/* 	ops[4].reg2 = 2; */

/*  ops[5].op = RET; */
/* 	ops[5].reg0 = 0; */
/* 	fprintf(stderr, "%d\n", vm_run(ops)); */
/* 	return 0; */
/* } */

