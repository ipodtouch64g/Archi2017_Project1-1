#include "simulator.h"

int main()
{
	//initializing
	halt = 0;
	cycle = 0;
	memset(lastReg,0,128);
	PC = 0;
	HI = 0;
	LO = 0;
	lastPC = 0;
	lastHI = 0;
	lastLO = 0;
	toggledHILO = 0;toggledMULT = 0;
  //Read iimage and dimage
	OpenFile();
	lastReg[29] = reg[29];			//stupid $sp...
  //Start simulation
  while(halt!=1)
  {
    writeRegZero=0;
    numOverflow=0;
    HILOOverWrite=0;
    memOverflow=0;
    dataMisaligned=0;
    snapShot();
    MachineCodeToCommands();
	errorDump();
  }
  fclose(snapshot);
  fclose(error_dump);
  return 0;
}
