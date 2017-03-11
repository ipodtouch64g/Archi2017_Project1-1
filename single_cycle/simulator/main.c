#include "simulator.h"

int main()
{
  //Read iimage and dimage
  OpenFile();
  iimageParser();
  dimageParser();

  //Start initializing
  halt = 0;
  cycle = 0;
  //Start simulation
  while(halt!=1)
  {
    writeRegZero=0;
    numOverflow=0;
    regOverflow=0;
    memOverflow=0;
    dataMisaligned=0;
    snapShot();
    MachineCodeToCommands();

  }

  return 0;
}
