#include "simulator.h"

// Open image files and output files
void OpenFile()
{

        unsigned len_iimage=0, len_dimage=0;

        error_dump = fopen("error_dump.rpt","w");
        snapshot = fopen("snapshot.rpt","w");
        iimage = fopen("iimage.bin","rb");
        dimage = fopen("dimage.bin","rb");


        fseek(iimage,0,SEEK_END);
        fseek(dimage,0,SEEK_END);

        len_iimage = (unsigned)ftell(iimage);
        len_dimage = (unsigned)ftell(dimage);

        rewind(iimage);
        rewind(dimage);

        iimageBuf = (char*)malloc(len_iimage*sizeof(char));
        dimageBuf = (char*)malloc(len_dimage*sizeof(char));

        //Finally read it into buffer
        fread(iimageBuf,1,len_iimage,iimage);
        fread(dimageBuf,1,len_dimage,dimage);

        fclose(iimage);
        fclose(dimage);
        iimageParser();
        dimageParser();
       //printParsed();
}
//Deal with iimage
void iimageParser()
{
        unsigned tmp=0,lineNum=0;

        //First 4 bytes is initial value of PC
        for(int i=0; i<4; i++)
                tmp = (tmp<<8) + (unsigned char)iimageBuf[i];
        PC = tmp;

        //Second 4 bytes is # of how many lines of instructions below
        for(int i=4; i<8; i++)
                lineNum = (lineNum<<8) + (unsigned char)iimageBuf[i];

        //Others are instructions,write them to iMemory
        for(int i=8; i<8+lineNum*4; i++)
                iMemory[tmp++] = iimageBuf[i];
}
//Deal with dimage
void dimageParser()
{
        unsigned tmp=0,lineNum=0,index=0;

        //First 4 bytes is initial value of SP
        for(int i=0; i<4; i++)
                tmp = (tmp<<8) + (unsigned char)dimageBuf[i];
        reg[29] = tmp;

        //Second 4 bytes is # of how many lines of instructions below
        for(int i=4; i<8; i++)
                lineNum = (lineNum<<8) + (unsigned char)dimageBuf[i];

        //Others are instructions,write them to dMemory
        for(int i=8; i<8+lineNum*4; i++)
                dMemory[index++] = dimageBuf[i];
}

//Debug
void printParsed()
{
        printf("PC: 0x%08X\n", PC);
        printf("HI: 0x%08X\n", HI);
        printf("LO: 0x%08X\n", LO);
        for(int i=0; i<1024; i+=4)
                printf("iMemory at 0x%08X : 0x%02X%02X%02X%02X\n",i,iMemory[i],iMemory[i+1],iMemory[i+2],iMemory[i+3]);
        for(int i=0; i<1024; i+=4)
                printf("dMemory at 0x%08X : 0x%02X%02X%02X%02X\n",i,dMemory[i],dMemory[i+1],dMemory[i+2],dMemory[i+3]);
}
//Dump errors
void errorDump()
{
        if (writeRegZero == 1)
        {
                fprintf(error_dump, "In cycle %d: Write $0 Error\n", cycle);
                //printf("In cycle %d: Write $0 Error\n", cycle);
        }


        if (numOverflow == 1)
        {
                fprintf(error_dump, "In cycle %d: Number Overflow\n", cycle);
                //printf("In cycle %d: Number Overflow\n", cycle);
        }


        if (HILOOverWrite == 1)
        {
                fprintf(error_dump, "In cycle %d: Overwrite HI-LO registers\n", cycle);
                //printf("In cycle %d: Overwrite HI-LO registers\n", cycle);
        }


        if(memOverflow==1)
        {
                fprintf(error_dump, "In cycle %d: Address Overflow\n", cycle);
                //printf("In cycle %d: Address Overflow\n", cycle);
                halt=1;
        }

        if(dataMisaligned==1)
        {
                fprintf(error_dump, "In cycle %d: Misalignment Error\n", cycle);
                //printf("In cycle %d: Misalignment Error\n", cycle);
                halt=1;
        }

}

void snapShot()
{
        fprintf(snapshot, "cycle %d\n", cycle);
        //printf("cycle %d\n", cycle);
        if(cycle==0)
        {
                for(int i=0; i<32; i++)
                {
                        fprintf(snapshot, "$%02d: 0x", i);
                        fprintf(snapshot, "%08X\n", reg[i]);
                        //printf("$%02d: 0x", i);
                        //printf("%08X\n", reg[i]);
                }
                fprintf(snapshot, "$HI: 0x%08X\n",HI);
                fprintf(snapshot, "$LO: 0x%08X\n",LO);
                fprintf(snapshot, "PC: 0x%08X\n\n\n",PC);
                //printf("$HI: 0x%08X\n", HI);
                //printf("$LO: 0x%08X\n", LO);
                //printf("PC: 0x%08X\n\n\n", PC);
        }

        else
        {
                for(int i=0; i<32; i++)
                {
                        if (lastReg[i] != reg[i])
                        {
                                fprintf(snapshot, "$%02d: 0x", i);
                                fprintf(snapshot, "%08X\n", reg[i]);
                                //printf("$%02d: 0x", i);
                                //printf("%08X\n", reg[i]);
                        }
                        lastReg[i] = reg[i];
                }
                if (lastHI != HI)
                {
                        fprintf(snapshot, "$HI: 0x%08X\n", HI);
                        //printf("$HI: 0x%08X\n", HI);
                }
                if (lastLO != LO)
                {
                        fprintf(snapshot, "$LO: 0x%08X\n", LO);
                        //printf("$LO: 0x%08X\n", LO);
                }

                if (lastPC != PC)
                {
                        fprintf(snapshot, "PC: 0x%08X\n\n\n", PC);
                        //printf( "PC: 0x%08X\n\n\n", PC);
                }


                lastHI = HI;
                lastLO = LO;
                lastPC = PC;
        }
        cycle++;
}
