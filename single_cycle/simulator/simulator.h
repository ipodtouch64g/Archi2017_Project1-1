#ifndef simulator_h
#define simulator_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MEM_MAX_SIZE 1024

char *iimageBuf,*dimageBuf;
FILE *iimage, *dimage, *error_dump, *snapshot;

int writeRegZero,numOverflow,HILOOverWrite,halt;
int memOverflow,dataMisaligned;

int toggledHILO, toggledMULT;

unsigned char iMemory[1024];
unsigned iPos,address;
unsigned op, rs, rt, rd, func, shamt, immediate;

unsigned char dMemory[1024];
unsigned dAddr, dPos;

unsigned reg[32], PC, HI, LO;
unsigned lastReg[32], lastPC, lastHI, lastLO;

unsigned cycle;

void OpenFile();
void iimageParser();
void dimageParser();
void errorDump();
void snapShot();
void printParsed();
#endif
