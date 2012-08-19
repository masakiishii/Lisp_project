#include "ilispvm.h"

int VirtualMachine_DirectThreadedCode_Run(bytecode_t *op, int *sp)
{
	bytecode_t *opcode = op;

	static void *VM_Instruction_Table[] = {
		&&SET, &&ADD, &&SUB, &&MULT, &&DEV,
		&&LESSTHAN, &&L_EQUAL, &&GREATERTHAN,
		&&G_EQUAL, &&IF, &&JUMP, &&DEFUN, &&MOV, &&CALL, &&RET
	};

	goto *VM_Instruction_Table[opcode->op];

SET:
	sp[opcode->reg0] = opcode->data1;
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

ADD:
	sp[opcode->reg0] = sp[opcode->reg1] + sp[opcode->reg2];
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

SUB:
	sp[opcode->reg0] = sp[opcode->reg1] - sp[opcode->reg2];
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

MULT:
	sp[opcode->reg0] = sp[opcode->reg1] * sp[opcode->reg2];
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

DEV:
	sp[opcode->reg0] = sp[opcode->reg1] / sp[opcode->reg2];
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

LESSTHAN:
	if(sp[opcode->reg1] < sp[opcode->reg2]) {
		sp[opcode->reg0] = 1;
	}else{
		sp[opcode->reg0] = 0;
	}
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

L_EQUAL:
	if(sp[opcode->reg1] <= sp[opcode->reg2]) {
		sp[opcode->reg0] = 1;
	}else{
		sp[opcode->reg0] = 0;
	}
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

GREATERTHAN:
	if(sp[opcode->reg1] > sp[opcode->reg2]) {
		sp[opcode->reg0] = 1;
	}else{
		sp[opcode->reg0] = 0;
	}
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

G_EQUAL:
	if(sp[opcode->reg1] >= sp[opcode->reg2]) {
		sp[opcode->reg0] = 1;
	}else{
		sp[opcode->reg0] = 0;
	}
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

IF:
	if(sp[opcode->reg0] == 0) {
		opcode = opcode->pc2;
	}else{
		opcode++;
	}
	goto *VM_Instruction_Table[opcode->op];

JUMP:
	opcode = opcode->pc2;
	goto *VM_Instruction_Table[opcode->op];

DEFUN:

MOV:
	sp[opcode->reg0] = sp[opcode->reg1];
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

CALL:
	sp[opcode->reg0] = VirtualMachine_DirectThreadedCode_Run(opcode->pc2, sp+opcode->reg0);
	opcode++;
	goto *VM_Instruction_Table[opcode->op];

RET:
	return sp[opcode->reg0];
}
