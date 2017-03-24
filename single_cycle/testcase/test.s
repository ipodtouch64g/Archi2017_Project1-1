PC = 0x00000008 #check if initial PC ok

lw $1,0($0)
lw $2,0($0)
add $1,$1,$2  #test biggest positive add overflow

lui $1, 0x8000
sub $2,$1,$2  #test smallest negative sub largest positive overflow

addi $2,$1,0x8000 #test addi overflow


sll $0,$0,0 #test only no write $0 error
sll $0,$1,0

sra $1,$1,31 #test shift right arithmetic

srl $2,$2,1
slt $3,$1,$2 #test signed comparison

lh $3,4($0)  #100001_00000_00011_0000_0000_0000_0100
lhu $3,4($0)  #100101_00000_00011_0000_0000_0000_0100
