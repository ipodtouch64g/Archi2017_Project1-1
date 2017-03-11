#ifndef simulator_h
#define simulator_h
#include <stdio.h>
#include <stdlib.h>



char *iimageBuf,*dimageBuf;
FILE *iimage, *dimage, *error_dump, *snapshot;

int writeRegZero,numOverflow,regOverflow,halt;
int memOverflow,dataMisaligned;

unsigned char iMemory[1024];
unsigned iAddr, iPos;
unsigned op, rs, rt, rd, func, shamt, immediate;

unsigned char dMemory[1024];
unsigned dAddr, dPos;

unsigned reg[32], PC, HI, LO;
unsigned regChanged[32], PCChanged, HIChanged, LOChanged;

unsigned cycle;

void OpenFile();
void iimageParser();
void dimageParser();
void errorDump();
void snapShot();
void printParsed();
#endif
