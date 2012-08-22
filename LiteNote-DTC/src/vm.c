#include "ilispvm.h"

#define OP_NEXT *VM_Instruction_Table[opcode->op]

int VirtualMachine_DirectThreadedCode_Run(bytecode_t *op, int *sp)
{
	bytecode_t *opcode = op;

	static void *VM_Instruction_Table[] = {
		&&SET, &&ADD, &&SUB, &&MULT, &&DEV,
		&&LESSTHAN, &&L_EQUAL, &&GREATERTHAN,
		&&G_EQUAL, &&IF, &&JUMP, &&DEFUN, &&MOV, &&CALL, &&RET
	};

	goto OP_NEXT;

SET:
	sp[opcode->reg0] = opcode->data1;
	opcode++;
	goto OP_NEXT;

ADD:
	sp[opcode->reg0] = sp[opcode->reg1] + sp[opcode->reg2];
	opcode++;
	goto OP_NEXT;

SUB:
	sp[opcode->reg0] = sp[opcode->reg1] - sp[opcode->reg2];
	opcode++;
	goto OP_NEXT;

MULT:
	sp[opcode->reg0] = sp[opcode->reg1] * sp[opcode->reg2];
	opcode++;
	goto OP_NEXT;

DEV:
	sp[opcode->reg0] = sp[opcode->reg1] / sp[opcode->reg2];
	opcode++;
	goto OP_NEXT;

LESSTHAN:
	if(sp[opcode->reg1] < sp[opcode->reg2]) {
		sp[opcode->reg0] = 1;
	}else{
		sp[opcode->reg0] = 0;
	}
	opcode++;
	goto OP_NEXT;

L_EQUAL:
	if(sp[opcode->reg1] <= sp[opcode->reg2]) {
		sp[opcode->reg0] = 1;
	}else{
		sp[opcode->reg0] = 0;
	}
	opcode++;
	goto OP_NEXT;

GREATERTHAN:
	if(sp[opcode->reg1] > sp[opcode->reg2]) {
		sp[opcode->reg0] = 1;
	}else{
		sp[opcode->reg0] = 0;
	}
	opcode++;
	goto OP_NEXT;

G_EQUAL:
	if(sp[opcode->reg1] >= sp[opcode->reg2]) {
		sp[opcode->reg0] = 1;
	}else{
		sp[opcode->reg0] = 0;
	}
	opcode++;
	goto OP_NEXT;

IF:
	if(sp[opcode->reg0] == 0) {
		opcode = opcode->pc2;
	}else{
		opcode++;
	}
	goto OP_NEXT;

JUMP:
	opcode = opcode->pc2;
	goto OP_NEXT;

DEFUN:

MOV:
	sp[opcode->reg0] = sp[opcode->reg1];
	opcode++;
	goto OP_NEXT;

CALL:
	sp[opcode->reg0] = VirtualMachine_DirectThreadedCode_Run(opcode->pc2, sp+opcode->reg0);
	opcode++;
	goto OP_NEXT;

RET:
	return sp[opcode->reg0];
}
