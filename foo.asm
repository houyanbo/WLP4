; begin prologue
.import print
.import init
.import new
.import delete
lis $4 ; new convention $4 always contains 4
.word 4
lis $10 ; $10 will always hold address for print
.word print
lis $11 ; $11 will always hold 1
.word 1
sub $29, $30, $4
sw $1 , -4($30) ; store variable a at $30 -4
sw $2 , -8($30) ; store variable b at $30 -8
sub $30, $30, $4
sub $30, $30, $4
;end prologue
sw $2, -4($30)
sub $30, $30, $4
add $2, $0, $0
sw $31, -4($30)
sub $30, $30, $4
lis $5
.word init
jalr $5
add $30, $30, $4
lw $31, -4($30)
lis $3
.word 42
sw $3, -4($30)
sub $30, $30, $4
sw $1, -4($30)
sub $30, $30, $4
lw $3, -8($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $29, -4($30)
sub $30, $30, $4
sw $31, -4($30)
sub $30, $30, $4
lis $3
.word 1
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 2
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 3
sw $3, -4($30)
sub $30, $30, $4
lw $3, -8($29)
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 5
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 6
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 7
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 8
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 9
sw $3, -4($30)
sub $30, $30, $4
lw $3, -4($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, 0($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, 0($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, 0($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, -8($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, 0($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, 0($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, 0($29)
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 0($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, 0($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, -4($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, -4($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, -4($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, -4($29)
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 2
sw $3, -4($30)
sub $30, $30, $4
lw $3, -4($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, -4($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, -8($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, -4($29)
sw $3, -4($30)
sub $30, $30, $4
lw $3, -4($29)
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 1
sw $3, -4($30)
sub $30, $30, $4
lis $3
.word 2
sw $3, -4($30)
sub $30, $30, $4
lis $5
.word Fmany
jalr $5
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $29, -4($30)
; begin epilogue
add $30, $30, $4
add $30, $30, $4
add $30, $30, $4
jr $31
Fmany:
sub $29, $30, $4
lis $3
.word 4
sw $3, -4($30)
sub $30, $30, $4
sw $1, -4($30)
sub $30, $30, $4
lw $3, 0($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
lw $3, 0($29)
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 52($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
sw $3, 0($29)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 128($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 124($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 120($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 116($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 112($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 108($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 104($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 100($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 96($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 92($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 88($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 84($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 80($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 76($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 72($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 68($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 64($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 60($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 56($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 52($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 48($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 44($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 40($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 36($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 32($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 28($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 24($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 20($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 16($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 12($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 8($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
sw $1, -4($30)
sub $30, $30, $4
lw $3, 4($29)
add $1, $3, $0
sw $31, -4($30)
sub $30, $30, $4
jalr $10
add $30, $30, $4
lw $31, -4($30)
add $30, $30, $4
lw $1, -4($30)
lw $3, 0($29)
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 128($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 124($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 120($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 116($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 112($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 108($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 104($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 100($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 96($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 92($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 88($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 84($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 80($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 76($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 72($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 68($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 64($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 60($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 56($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 52($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 48($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 44($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 40($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 36($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 32($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 28($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 24($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 20($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 16($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 12($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 8($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
mult $3, $4
mflo $3
sw $3, -4($30)
sub $30, $30, $4
lw $3, 4($29)
mult $3, $4
mflo $3
add $30, $30, $4
lw $5, -4($30)
add $3 ,$5 ,$3
div $3, $4
mflo $3
add $30, $29, $4
jr $31
many:
a1 -31
a10 -22
a11 -21
a12 -20
a13 -19
a14 -18
a15 -17
a16 -16
a17 -15
a18 -14
a19 -13
a2 -30
a20 -12
a21 -11
a22 -10
a23 -9
a24 -8
a25 -7
a26 -6
a27 -5
a28 -4
a29 -3
a3 -29
a30 -2
a31 -1
a32 0
a4 -28
a5 -27
a6 -26
a7 -25
a8 -24
a9 -23
v 1
wain:
a 1
b 2
var 3
