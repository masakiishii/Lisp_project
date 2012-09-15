#include "ilisp.h"

#define OP_NEXT *VM_Instruction_Table[opcode->op]

void VirtualMachine_ByteCode_Dump(ByteCode_t *vmcode)
{
	DBG_P("=====<<<VirtualMachine_ByteCode_Dump>>>=====");
	switch(vmcode->op) {
	case OPLOAD:
		DBG_P("OPLOAD :");
		break;
	case OPADD:
		DBG_P("OPADD :");
		break;
	case OPSUB:
		DBG_P("OPSUB :");
		break;
	case OPMUL:
		DBG_P("OPMUL :");
		break;
	case OPDIV:
		DBG_P("OPDIV :");
		break;
	case OPLT :
		DBG_P("OPLT :");
		break;
	case OPGT :
		DBG_P("OPGT :");
		break;
	case OPIF :
		DBG_P("OPIF :");
		break;
	case OPJMP :
		DBG_P("OPJMP :");
		break;
	case OPMOV :
		DBG_P("OPMOV :");
		break;
	case OPCALL :
		DBG_P("OPCALL :");
		break;
	case OPRET :
		DBG_P("OPRET :");
		break;
	}
}

#define Code_Dump(C)  VirtualMachine_ByteCode_Dump(C)

int VirtualMachine_DirectThreadedCode_Run(ByteCode_t *op, int *sp)
{
	DBG_P("=====<<<VirtualMachine_DirectThreadedCode_Run>>>=====");

	register ByteCode_t *opcode = op;
	register int *Reg = sp;

	static const void *VM_Instruction_Table[] = {
		&&OPLOAD, &&OPADD, &&OPSUB, &&OPMUL, &&OPDIV,
		&&OPLT,  &&OPGT,
		&&OPIF, &&OPJMP, &&OPMOV, &&OPCALL, &&OPRET
	};

	goto OP_NEXT;

OPLOAD:
	Code_Dump(opcode);
	Reg[opcode->reg0] = opcode->data1;
	opcode++;
	goto OP_NEXT;

OPADD:
	Code_Dump(opcode);
	Reg[opcode->reg0] = Reg[opcode->reg1] + Reg[opcode->reg2];
	opcode++;
	goto OP_NEXT;

OPSUB:
	Code_Dump(opcode);
	Reg[opcode->reg0] = Reg[opcode->reg1] - Reg[opcode->reg2];
	opcode++;
	goto OP_NEXT;

OPMUL:
	Code_Dump(opcode);
	Reg[opcode->reg0] = Reg[opcode->reg1] * Reg[opcode->reg2];
	opcode++;
	goto OP_NEXT;

OPDIV:
	Code_Dump(opcode);
	Reg[opcode->reg0] = Reg[opcode->reg1] / Reg[opcode->reg2];
	opcode++;
	goto OP_NEXT;

OPLT:
	Code_Dump(opcode);
	(Reg[opcode->reg1] < Reg[opcode->reg2]) ? (Reg[opcode->reg0] = 1) : (Reg[opcode->reg0] = 0);
	opcode++;
	goto OP_NEXT;

OPGT:
	Code_Dump(opcode);
	(Reg[opcode->reg1] > Reg[opcode->reg2]) ? (Reg[opcode->reg0] = 1) : (Reg[opcode->reg0] = 0);
	opcode++;
	goto OP_NEXT;

OPIF:
	Code_Dump(opcode);
	if(Reg[opcode->reg0] == 0) {
		opcode = opcode->pc2;
	}else{
		opcode++;
	}
	goto OP_NEXT;

OPJMP:
	Code_Dump(opcode);
	opcode = opcode->pc2;
	goto OP_NEXT;

OPMOV:
	Code_Dump(opcode);
	Reg[opcode->reg0] = Reg[opcode->reg1];
	opcode++;
	goto OP_NEXT;

OPCALL:
	Code_Dump(opcode);
	Reg[opcode->reg0] = VirtualMachine_DirectThreadedCode_Run(opcode->pc2, Reg+opcode->reg0);
	opcode++;
	goto OP_NEXT;

OPRET:
	Code_Dump(opcode);
	return Reg[opcode->reg0];
}

