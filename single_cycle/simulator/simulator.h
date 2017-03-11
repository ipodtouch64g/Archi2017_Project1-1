#ifndef simulator_h
#define simulator_h
#include <stdio.h>
#include <stdlib.h>
#include "reg.h"
#include "mem_data.h"
#include "mem_instruction.h"

char *iimageBuf,*dimageBuf;
FILE *iimage, *dimage, *error_dump, *snapshot;

int writeRegZero,numOverflow,regOverflow,halt;
int memOverflow,dataMisaligned;

unsigned cycle;

void OpenFile();
void iimageParser();
void dimageParser();
void errorDump();
void snapShot();

#endif
