#include "ilispvm.h"

#define OP_NEXT *VM_Instruction_Table[opcode->op]

int VirtualMachine_DirectThreadedCode_Run(ByteCode_t *op, int *sp)
{
	register ByteCode_t *opcode = op;
	register int *Reg = sp;

	static const void *VM_Instruction_Table[] = {
		&&SET, &&ADD, &&SUB, &&MULT, &&DEV,
		&&LESSTHAN, &&L_EQUAL, &&GREATERTHAN,
		&&G_EQUAL, &&IF, &&JUMP, &&DEFUN, &&MOV, &&CALL, &&RET
	};

	goto OP_NEXT;

SET:
	Reg[opcode->reg0] = opcode->data1;
	opcode++;
	goto OP_NEXT;

ADD:
	Reg[opcode->reg0] = Reg[opcode->reg1] + Reg[opcode->reg2];
	opcode++;
	goto OP_NEXT;

SUB:
	Reg[opcode->reg0] = Reg[opcode->reg1] - Reg[opcode->reg2];
	opcode++;
	goto OP_NEXT;

MULT:
	Reg[opcode->reg0] = Reg[opcode->reg1] * Reg[opcode->reg2];
	opcode++;
	goto OP_NEXT;

DEV:
	Reg[opcode->reg0] = Reg[opcode->reg1] / Reg[opcode->reg2];
	opcode++;
	goto OP_NEXT;

LESSTHAN:
	if(Reg[opcode->reg1] < Reg[opcode->reg2]) {
		Reg[opcode->reg0] = 1;
	}else{
		Reg[opcode->reg0] = 0;
	}
	opcode++;
	goto OP_NEXT;

L_EQUAL:
	if(Reg[opcode->reg1] <= Reg[opcode->reg2]) {
		Reg[opcode->reg0] = 1;
	}else{
		Reg[opcode->reg0] = 0;
	}
	opcode++;
	goto OP_NEXT;

GREATERTHAN:
	if(Reg[opcode->reg1] > Reg[opcode->reg2]) {
		Reg[opcode->reg0] = 1;
	}else{
		Reg[opcode->reg0] = 0;
	}
	opcode++;
	goto OP_NEXT;

G_EQUAL:
	if(Reg[opcode->reg1] >= Reg[opcode->reg2]) {
		Reg[opcode->reg0] = 1;
	}else{
		Reg[opcode->reg0] = 0;
	}
	opcode++;
	goto OP_NEXT;

IF:
	if(Reg[opcode->reg0] == 0) {
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
	Reg[opcode->reg0] = Reg[opcode->reg1];
	opcode++;
	goto OP_NEXT;

CALL:
	Reg[opcode->reg0] = VirtualMachine_DirectThreadedCode_Run(opcode->pc2, Reg+opcode->reg0);
	opcode++;
	goto OP_NEXT;

RET:
	return Reg[opcode->reg0];
}
