#ifndef mem_instruction_h
#define mem_instruction_h

unsigned char iMemory[1024];
unsigned iAddr,iPos;
unsigned op,rs,rt,rd,func,shamt,immediate;

void MachineCodeToCommands();




#endif
