|   PC = 0x00000008 																		#check if initial PC ok
|#test largest positive - second smallest negative OVF
|	lw $1,0x0000($0)                                                                        #pc=0x13C
|	lw $2,0x0010($0)                                                                        #pc=0x140
|	sub $1,$1,$2                                                                            #pc=0x144
|#test addi largest ovf
|	lw $1,0x0000($0)																		#pc=0x148
|	addi $1,$1,0x7FFF                                                                       #pc=0x14C
|#test addi smallest ovf
|	lw $1,0x0008($0)																		#pc=0x150
|   addi $1,$1,0x8000                                                                       #pc=0x154
|#test largest positive sub smallest negative overflow
|   lw $1,0x0000($0)                                 										#pc=0x158
|   lw $2,0x0008($0)                                 										#pc=0x15C
|   sub $1,$1,$2                                     										#pc=0x160
|#test largest positive sub overflow
|   lw $1,0x0000($0)                                 										#pc=0x164
|   lw $2,0x0000($0)                                 										#pc=0x168
|   sub $1,$1,$2                                                                            #pc=0x16C
|#test smallest negative sub overflow
|   lw $1,0x0008($0)                                                                        #pc=0x170
|   lw $2,0x0008($0)                                                                        #pc=0x174
|   sub $1,$1,$2                                                                            #pc=0x178
|#test smallest negative add overflow
|   lw $1,0x0008($0)                                                                        #pc=0x17C
|   lw $2,0x0008($0)                                                                        #pc=0x180
|   add $1,$1,$2                                                                            #pc=0x184
|#test biggest positive add overflow
|   lw $1,0($0)                                                                             #pc=0x188
|   lw $2,0($0)                                                                             #pc=0x18C
|   add $1,$1,$2                                                                            #pc=0x190
|#test smallest negative sub largest positive overflow
|   lui $1, 0x8000                                                                          #pc=0x194
|   sub $2,$1,$2                                                                            #pc=0x198
|#test addi overflow
|   addi $2,$1,0x8000                                                                       #pc=0x19C
|#test only no write $0 error
|   sll $0,$0,0 																			#pc=0x1A0
|   sll $0,$1,0																				#pc=0x1A4
|#test shift right arithmetic
|   sra $1,$1,31 																			#pc=0x1A8
|#test signed comparison
|   srl $2,$2,1																				#pc=0x1AC
|   slt $3,$1,$2 																			#pc=0x1B0
|#test load half word
|   lh $3,4($0)  																			#pc=0x1B4
|   lhu $3,4($0)  																			#pc=0x1B8
|#test load byte
|   lb $3,3($0)  																			#pc=0x1BC
|   lbu $3,3($0) 																			#pc=0x1C0
|#test save word
|   lw $4,0($0) 																			#pc=0x1C4
|   sw $0,0xff01($3) 																		#pc=0x1C8
|   lw $4,0($0)                                                                             #pc=0x1CC
|#test save halfword
|   sh $1,0xff01($3)                                                                        #pc=0x1D0
|   lw $4,0($0)                                                                             #pc=0x1D8
|#test save byte
|   sb $0,0xff02($3)                                                                        #pc=0x1DC
|   lw $4,0($0)                                                                             #pc=0x1E0
|#test unsigned I-command
|   andi $2,$1,0xffff                                                                       #pc=0x1E4
|   ori $2,$2,0xffff                                                                        #pc=0x1E8
|   nori $2,$2,0xffff                                                                       #pc=0x1EC
|#test signed comparison
|   slti $2,$1,0xffff                                                                       #pc=0x1F0
|   slti $2,$1,0x8000                                                                       #pc=0x1F4
|   slti $2,$0,0xffff                                                                       #pc=0x1F8
|   slti $2,$0,0x1fff                                                                       #pc=0x1FC
|
|   #jump to boundary then jump back to execute next instruction
|---jal 0x100                               												#pc=0x200 command = 0x0c0000ff jump to PC=0x3fc(1020)
|   lw $4,0x0010($0)                        												#pc=0x204 load 0x0210
|   jr $4                                   												#pc=0x208 jump to 0x210
|   halt                                    												#pc=0x20C
|   halt                                    												#pc=0x210
|	#test every writeto0
|   add $0,$0,$0
|   addu $0,$0,$0
|   sub $0,$0,$0
|   and $0,$0,$0
|   or $0,$0,$0
|   xor $0,$0,$0
|   nor $0,$0,$0
|	nand $0,$0,$0
|	slt $0,$0,$0
|	srl $0,$0,0X0000
|	sra $0,$0,0X0000
|	mult $1,$1
|	multu $1,$1
|	mfhi $0																					
|	mult $1,$1
|	addi  $0,$1,0xffff
|	addiu  $0,$1,0xffff
|	lw   $0,0x0000($0)
|	lh    $0,0x0000($0)
|	lhu   $0,0x0000($0)
|	lb    $0,0x0000($0)
|	lbu	  $0,0x0000($0)
| lui   $0,0x0000
|	andi   $0,$1,0xffff
|	ori    $0,$1,0xffff
|	nori   $0,$1,0xffff
|	slti    $0,$1,0xffff
|	#test branch
|   addi $2,$0,0x0000                                                                       #pc=0x280
||<-beq  $2,$0,0x0001                                                                       #pc=0x284
||   halt                                                                                   #pc=0x288
||<->bne  $1,$0,0x0001                                                                      #pc=0x28C
||	halt																					#pc=0x290
||->bgtz $1,0xFFFF                                                                          #pc=0x294
||<-bgtz $4,0X0009                                                                          #pc=0x298
||	halt																					#pc=0x29C
|||>lw $4,0x8($0)                                                                           #pc=0x2A0
|||	lh $3,0x(-1)($4) #####test misalign,numovf,addovf END#####                              #pc=0x2A4
||| halt                                                                                    #pc=0x2A8
|||	halt                                                                                    #pc=0x2AC
||<->bgtz $4,0Xfffb                                                                        	#pc=0x2B0
||| halt                                                                                    #pc=0x2B4
||<->bne $1,$0,0xfffd                                                                       #pc=0x2B8
|||	halt                                                                                    #pc=0x2BC
||<->beq $2,$0,0xfffd																		#pc=0x2C0
|
.
.
.
|
|------ j 0x200  #pc=0x3fc command = 0x08000080 jump to PC=0x200							#pc=0x3FC
