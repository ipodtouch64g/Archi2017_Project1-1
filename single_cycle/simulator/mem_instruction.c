#include "mem_instruction.h"

void MachineCodeToCommands()
{
	findOP();
	switch (op)
	{
	case 0:  //R 
		findFUNC();
		switch (func)
		{
		case 0x20:
			add();break;
		case 0x21:
			addu();break;
		case 0x22:
			sub();break;
		case 0x24:	
			and();break;
		case 0x25:
			or();break;
		case 0x26:
			xor();break;
		case 0x27:
			nor();break;
		case 0x28:
			nand();break;
		case 0x2A:
			slt();break;
		case 0x00:
			sll();break;
		case 0x02:
			srl();break;
		case 0x03:
			sra();break;
		case 0x08:
			jr();break;
		case 0x18:
			mult();break;
		case 0x19:
			multu();break;
		case 0x10:
			mfhi();break;
		case 0x12:
			mflo();break;
		default:
			break;
		}
		break;
	case 0x08:
		addi();break;
	case 0x09:
		addiu();break;
	case 0x23:
		lw();break;
	case 0x21:
		lh();break;
	case 0x25:
		lhu();break;
	case 0x20:
		lb();break;
	case 0x24:
		lbu();break;
	case 0x2b:
		sw();break;
	case 0x29:
		sh();break;
	case 0x28:
		sb();break;
	case 0x0f:
		lui();break;
	case 0x0c:
		andi();break;
	case 0x0d:
		ori();break;
	case 0x0e:
		nori();break;
	case 0x0a:
		slti();break;
	case 0x04:
		beq();break;
	case 0x05:
		bne();break;
	case 0x07:
		bgtz();break;
	case 0x02:
		j();break;
	case 0x03:
		jal();break;
	case 0x3f:
		halt=1;break;
	default:
		break;
	}

}

void findOP()
{
	op = iMemory[PC];
	op = op >> 2;  //0x000000??
}

void findRSRTRD()
{
	//RD 
	rd = iMemory[PC + 2];
	rd = rd >> 3;
	//RT
	rt = iMemory[PC + 1];
	rt = rt << 27 >> 27;
	//RS 
	rs = (iMemory[PC] << 30 >> 27) | (iMemory[PC+1] >> 5);
}

void findFUNC()
{
	func = iMemory[PC + 3];
	func = func << 26 >> 26;  //find 6 lsb
}

void findSHAMT()
{
	shamt = (iMemory[PC + 2] << 29 >> 27) | (iMemory[PC + 3] >> 6);
}

void findIMMEDIATE()
{
	immediate = (iMemory[PC + 2] << 8) | (iMemory[PC + 3]);
}

void findADDR()
{
	iAddr = (iMemory[PC + 3]) | (iMemory[PC + 2] << 8) | (iMemory[PC + 1] << 16) | (iMemory[PC] << 30 >> 6);
}
