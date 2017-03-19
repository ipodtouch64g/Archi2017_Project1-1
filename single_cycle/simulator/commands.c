#include "commands.h"

//¡¹¡¸¡¹IMPLEMENT¡¹¡¸¡¹


void R_Command(char *op) {

	findRSRTRD();
	findSHAMT();
	findFUNC();
	if (strcmp(op, "add") == 0)
	{
		printf("0x%08x : add : $%d , $%d ,$%d\n",PC,rd,rs,rt);
		reg[rd] = reg[rs] + reg[rt];
		if (rd == 0)
		{
			detectWriteRegZero();
		}
		detectNumOverflow((int)reg[rs], (int)reg[rt], (int)reg[rd]);
	}

	else if (strcmp(op, "addu") == 0)
	{
		printf("0x%08x : addu : $%d , $%d ,$%d\n", PC, rd, rs, rt);
		reg[rd] = reg[rs] + reg[rt];
		if (rd == 0)
		{
			detectWriteRegZero();
		}
	}

	else if (strcmp(op, "sub") == 0)
	{
		printf("0x%08x : sub : $%d , $%d ,$%d\n", PC, rd, rs, rt);
		reg[rd] = reg[rs] - reg[rt];
		if (rd == 0)
		{
			detectWriteRegZero();
		}
		detectNumOverflow((int)reg[rs], (int)reg[rt], (int)reg[rd]);
	}

	else if (strcmp(op, "and") == 0)
	{
		printf("0x%08x : and : $%d , $%d ,$%d\n", PC, rd, rs, rt);
		reg[rd] = reg[rs] & reg[rt];
		if (rd == 0)
		{
			detectWriteRegZero();
		}
	}

	else if (strcmp(op, "or") == 0)
	{
		printf("0x%08x : or : $%d , $%d ,$%d\n", PC, rd, rs, rt);
		reg[rd] = reg[rs] | reg[rt];
		if (rd == 0)
		{
			detectWriteRegZero();
		}
	}

	else if (strcmp(op, "xor") == 0)
	{
		printf("0x%08x : xor : $%d , $%d ,$%d\n", PC, rd, rs, rt);
		reg[rd] = reg[rs] ^ reg[rt];
		if (rd == 0)
		{
			detectWriteRegZero();
		}
	}

	else if (strcmp(op, "nor") == 0)
	{
		printf("0x%08x : nor : $%d , $%d ,$%d\n", PC, rd, rs, rt);
		reg[rd] = ~(reg[rs] | reg[rt]);
		if (rd == 0)
		{
			detectWriteRegZero();
		}
	}

	else if (strcmp(op, "nand") == 0)
	{
		printf("0x%08x : nand : $%d , $%d ,$%d\n", PC, rd, rs, rt);
		reg[rd] = ~(reg[rs] & reg[rt]);
		if (rd == 0)
		{
			detectWriteRegZero();
		}
	}

	else if (strcmp(op, "slt") == 0)
	{
		printf("0x%08x : slt : $%d , $%d ,$%d\n", PC, rd, rs, rt);
		reg[rd] = (reg[rs] < reg[rt]) ? 1 : 0;
		if (rd == 0)
		{
			detectWriteRegZero();
		}
	}

	else if (strcmp(op, "sll") == 0)
	{
		printf("0x%08x : sll : $%d , $%d ,$%d\n", PC, rd, rt, shamt);
		reg[rd] = reg[rt] << shamt;
		if (rt != 0 || shamt != 0)
		{
			if (rd == 0)
				detectWriteRegZero();
		}
	}

	else if (strcmp(op, "srl") == 0)
	{
		printf("0x%08x : srl : $%d , $%d ,$%d\n", PC, rd, rt, shamt);
		reg[rd] = reg[rt] >> shamt;
		if (rd == 0)
		{
			detectWriteRegZero();
		}
	}

	else if (strcmp(op, "sra") == 0)
	{
		printf("0x%08x : sra : $%d , $%d ,$%d\n", PC, rd, rt, shamt);
		reg[rd] = (int)reg[rt] >> shamt;
		if (rd == 0)
		{
			detectWriteRegZero();
		}
	}

	else if (strcmp(op, "jr") == 0)
	{
		printf("0x%08x : jr : $%d\n", PC, rs);
		PC = reg[rs];
		return;     //DONT need to PC+=4
	}

	else if (strcmp(op, "mult") == 0)
	{
		printf("0x%08x : mult : $%d , $%d\n", PC, rs, rt);
		int64_t rs_64 = reg[rs];
		int64_t rt_64 = reg[rt];
		int64_t ans = rs_64*rt_64;
		/*if (rs_64 != 0 && ans / rs_64 != rt_64)
			detectNumOverflow();	*/													//overflowed ?????
		uint64_t u_ans = (uint64_t)ans;
		LO = u_ans << 32 >>32;
		HI = u_ans >> 32;
		detectHILOWrite("mult");
	}

	else if (strcmp(op, "multu") == 0)
	{
		printf("0x%08x : multu : $%d , $%d\n", PC, rs, rt);
		uint64_t rs_64 = reg[rs];
		uint64_t rt_64 = reg[rt];
		uint64_t ans = rs_64*rt_64;										
		LO = ans << 32 >> 32;
		HI = ans >> 32;
		detectHILOWrite("mult");
	}

	else if (strcmp(op, "mfhi") == 0)
	{
		printf("0x%08x : mfhi : $%d\n", PC, rd);
		reg[rd] = HI;
		if (rd == 0)
			detectWriteRegZero();
		detectHILOWrite("hilo");
	}

	else if (strcmp(op, "mflo") == 0)
	{
		printf("0x%08x : mflo : $%d\n", PC, rd);
		reg[rd] = HI;
		if (rd == 0)
			detectWriteRegZero();
		detectHILOWrite("hilo");
	}

	else
	{
		halt = 1;
	}

	PC += 4;    //go forward a word
}


void I_Command(char *op) {
	findRSRTRD();

	//ADDI
	if (strcmp(op, "addi") == 0)
	{
		findSignedIMMEDIATE();
		printf("0x%08x : addi : $%d , $%d , $0x%02x", PC, rt, rs, immediate);
		if (rt == 0)
			detectWriteRegZero();
		int s_rt;
		int s_rs = (int)reg[rs];
		int s_imme = (int)immediate;
		s_rt = s_rs + s_imme;
		detectNumOverflow( s_rs, s_imme,s_rt );
		reg[rt] = reg[rs] + immediate;
		if (numOverflow == 1)
			reg[rt] = 0;
	}

	//ADDIU
	//Very strange because addiu and addi both use signed immediate.
	//only difference is whether we need to check if overflow , WTF.
	else if (strcmp(op, "addiu") == 0)
	{												
		findSignedIMMEDIATE();						
		printf("0x%08x : addiu : $%d , $%d , $0x%02x", PC, rt, rs, immediate);
		reg[rt] = reg[rs] + immediate;
		if (rt == 1)
			detectWriteRegZero();
	}

	//LW
	else if (strcmp(op, "lw") == 0)
	{
		findSignedIMMEDIATE();
		printf("0x%08x : lw : $%d , 0x%02xC($%d)", PC, rt,immediate, rs);
		dPos = reg[rs] + immediate;

		if (!detectMemOverflow(3) && !detectDataMisaligned(3))
		{
			reg[rt] = (dMemory[dPos] << 24) | (dMemory[dPos + 1] << 16) | (dMemory[dPos + 2] << 8) | (dMemory[dPos + 3]);
		}

		if (rt == 0)
			detectWriteRegZero();

		//check ovf
		int s_imme = (int)immediate;
		int s_pos = (int)reg[rs];
		detectNumOverflow(s_imme, s_pos, s_pos);
	}	  

	else if (strcmp(op, "lh") == 0)
	{
		findSignedIMMEDIATE();
		printf("0x%08x : lh : $%d , 0x%02xC($%d)", PC, rt, immediate, rs);
		dPos = reg[rs] + immediate;
		if (!detectMemOverflow(1) && !detectDataMisaligned(1))
		{
			reg[rt] = (uint16_t)((dMemory[dPos])<<8 |(dMemory[dPos+1]));
		}
		if (rt == 0)
			detectWriteRegZero();

		//check ovf
		int s_imme = (int)immediate;
		int s_pos = (int)reg[rs];
		detectNumOverflow(s_imme, s_pos, s_pos);
	}
	else if (strcmp(op, "lhu") == 0)
	{
		findSignedIMMEDIATE();
		printf("0x%08x : lhu : $%d , 0x%02xC($%d)", PC, rt, immediate, rs);
		dPos = reg[rs] + immediate;
		if (!detectMemOverflow(1) && !detectDataMisaligned(1))
		{
			reg[rt] = ((dMemory[dPos]) << 8 | (dMemory[dPos]+1));
		}
		if (rt == 0)
			detectWriteRegZero();

		//check ovf
		int s_imme = (int)immediate;
		int s_pos = (int)reg[rs];
		detectNumOverflow(s_imme, s_pos, s_pos);
	}
	else if (strcmp(op, "lb") == 0)
	{
		findSignedIMMEDIATE();
		printf("0x%08x : lb : $%d , 0x%02xC($%d)", PC, rt, immediate, rs);
		dPos = reg[rs] + immediate;
		if (!detectMemOverflow(0) && !detectDataMisaligned(0))
		{
			reg[rt] = (uint8_t)(dMemory[dPos]);
		}
		if (rt == 0)
			detectWriteRegZero();

		//check ovf
		int s_imme = (int)immediate;
		int s_pos = (int)reg[rs];
		detectNumOverflow(s_imme, s_pos, s_pos);
	}
	else if (strcmp(op, "lbu") == 0)
	{
		findSignedIMMEDIATE();
		printf("0x%08x : lbu : $%d , 0x%02xC($%d)", PC, rt, immediate, rs);
		dPos = reg[rs] + immediate;
		if (!detectMemOverflow(0) && !detectDataMisaligned(0))
		{
			reg[rt] = (dMemory[dPos]);
		}
		if (rt == 0)
			detectWriteRegZero();

		//check ovf
		int s_imme = (int)immediate;
		int s_pos = (int)reg[rs];
		detectNumOverflow(s_imme, s_pos, s_pos);
	}
	else if (strcmp(op, "sw") == 0)
	{

	}
	else if (strcmp(op, "sh") == 0)
	{

	}
	else if (strcmp(op, "sb") == 0)
	{

	}
	else if (strcmp(op, "lui") == 0)
	{

	}
	else if (strcmp(op, "andi") == 0)
	{

	}
	else if (strcmp(op, "ori") == 0)
	{

	}
	else if (strcmp(op, "nori") == 0)
	{

	}
	else if (strcmp(op, "slti") == 0)
	{

	}
	else if (strcmp(op, "beq") == 0)
	{

	}
	else if (strcmp(op, "bne") == 0)
	{

	}
	else if (strcmp(op, "bgtz") == 0)
	{

	}
	else
	{
		halt = 1;
	}

}

void J_Command(char *op) {
	if (strcmp(op, "j") == 0)
	{

	}
	else if (strcmp(op, "jal") == 0)
	{

	}
	else
	{
		halt = 1;
	}
}





//detect error
void detectWriteRegZero()
{
	writeRegZero = 1;
	reg[0] = 0;
}

void detectNumOverflow(int a,int b,int c)
{
	if(a>0&&b>0&&c<0 || a<0&&b<0&&c>0)
		numOverflow = 1;
}

void detectHILOWrite(char* op)
{
	if (strcmp(op, "mult") == 0)
	{
		if (toggledMULT == 1 && toggledHILO==1)  //NO HILO error , turn off HILO toggle now
		{
			toggledHILO = 0;
		}
		else if (toggledMULT == 1 && toggledHILO == 0) //HILO error!!
		{
			HILOOverWrite = 1;
		}
		else            //first MULT in a row,turn on MULT toggle now
		{
			toggledMULT = 1;
		}
	}
	else  //op == hi lo
	{
		toggledHILO = 1;
	}
}

int detectMemOverflow(int len_byte)
{
	if (dPos + len_byte >= MEM_MAX_SIZE || dPos >= MEM_MAX_SIZE)
	{
		memOverflow = 1;
		halt = 1;
		return 1;
	}
	else
		return 0;
}

int detectDataMisaligned(int len_byte)
{
	if (dPos % (len_byte + 1) != 0)
	{
		dataMisaligned = 1;
		halt = 1;
		return 1;
	}
	else
		return 0;
}


// find 
void findOP()
{
	op = iMemory[PC];
	op = op >> 2 << 26 >> 26;  //0x000000??
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
	rs = (iMemory[PC] << 30 >> 27) | (iMemory[PC + 1] << 24 >> 29);
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

void findUnsignedIMMEDIATE()
{
	immediate = (iMemory[PC + 2] << 8) | (iMemory[PC + 3]);
}

//Tricky part to get 16bit immediate SIGN EXTENSION to 32bit immediate
void findSignedIMMEDIATE()
{
	immediate = (int16_t)((iMemory[PC + 2] << 8) | (iMemory[PC + 3])); 
}

void findADDR()
{
	address = (iMemory[PC + 3]) | (iMemory[PC + 2] << 8) | (iMemory[PC + 1] << 16) | (iMemory[PC] << 30 >> 6);
}
