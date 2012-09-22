#include <ilisp.h>

VirtualMachine *new_VirtualMachine(void)
{
	VirtualMachine *vm = (VirtualMachine *)imalloc(sizeof(VirtualMachine));
	vm->DirectThreadedCode_Run = VirtualMachine_DirectThreadedCode_Run;
	vm->delete = VirtualMachine_delete;
	return vm;
}


void VirtualMachineByteCodeLine_remove(VirtualMachineByteCodeLine *line, int num)
{
	size_t i = 0;
	for (i = num; i < line->size+num+1; i++) {
		line->code[i] = line->code[i + 1];
	}

	line->size--;
}

void VirtualMachineByteCodeLine_delete(ByteCode *code)
{
	free(code);
	code = NULL;
}

void VirtualMachine_delete(VirtualMachine *vm)
{
	free(vm);
	vm = NULL;
}

VirtualMachineByteCodeLine *new_VirtualMachineByteCodeLine(void)
{
	VirtualMachineByteCodeLine *ret  = (VirtualMachineByteCodeLine *)imalloc(sizeof(VirtualMachineByteCodeLine));
	ret->code = (ByteCode *)imalloc(sizeof(ByteCode) * VIRTUALMAChINE_BYTECODE_SIZE);
	ret->index = 0;
	ret->size = 0;
	ret->cons = NULL;
	ret->remove = VirtualMachineByteCodeLine_remove;
	ret->delete = VirtualMachineByteCodeLine_delete;
	return ret;
}

void VirtualMachine_ByteCode_Dump(ByteCode *vmcode)
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
	case OPFASTCALL :
		DBG_P("OPFASTCALL :");
		break;
	case OPiSUBC:
		DBG_P("OPiSUBC :");
		break;
	case OPiLTC:
		DBG_P("OPiLTC :");
		break;
	case OPRET :
		DBG_P("OPRET :");
		break;
	}
}


#define OP_NEXT *VM_Instruction_Table[opcode->op]
#define Code_Dump(C)  VirtualMachine_ByteCode_Dump(C)

VirtualMachineByteCodeLine *local_cache_register = NULL;

int VirtualMachine_DirectThreadedCode_Run(VirtualMachineByteCodeLine *op, int *sp)
{
	DBG_P("=====<<<VirtualMachine_DirectThreadedCode_Run>>>=====");

	register ByteCode *opcode = op->code;
	//register ByteCode *op_pointer = opcode;
	register int *Reg = sp;

	static const void *VM_Instruction_Table[] = {
		&&OPLOAD, &&OPADD, &&OPSUB, &&OPMUL, &&OPDIV,
		&&OPLT,  &&OPGT, &&OPIF, &&OPJMP, &&OPMOV, 
		&&OPCALL, &&OPFASTCALL,&&OPiSUBC,&&OPiLTC, &&OPRET
	};

	//while(op_pointer->op != OPRET) {
	//	op_pointer->opnext = VM_Instruction_Table[op_pointer->op];
	//	op_pointer++;
	//}
	//op_pointer->opnext = &&OPRET;

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
	(Reg[opcode->reg0] == 0) ? (opcode = opcode->pc2) : (opcode++);
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
	VirtualMachineByteCodeLine *s_func = (VirtualMachineByteCodeLine *)fetch_from_virtualmachine_memory(opcode->name);
	local_cache_register = s_func;
	Reg[opcode->reg0] = VirtualMachine_DirectThreadedCode_Run(s_func, Reg+opcode->reg0);
	opcode++;
	goto OP_NEXT;

OPFASTCALL:
	Code_Dump(opcode);
	Reg[opcode->reg0] = VirtualMachine_DirectThreadedCode_Run(local_cache_register, Reg+opcode->reg0);
	opcode++;
	goto OP_NEXT;

OPiSUBC:
	Code_Dump(opcode);
	Reg[opcode->reg0] = Reg[opcode->reg1] - opcode->data2;
	opcode++;
	goto OP_NEXT;

OPiLTC:
	Code_Dump(opcode);
	(Reg[opcode->reg1] < opcode->data2) ? (Reg[opcode->reg0] = 1) : (Reg[opcode->reg0] = 0);
	opcode++;
	goto OP_NEXT;

OPRET:
	Code_Dump(opcode);
	return Reg[opcode->reg0];
}

