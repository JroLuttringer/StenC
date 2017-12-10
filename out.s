.data
__const_6:	.word 6
rows__:	.word 0
__const_1:	.word 1
coef__:	.word 0
space__:	.word 0
i__:	.word 0
k__:	.word 0
__const_0:	.word 0
__temp_0:	.word 0
__string_1:	.asciiz "  "
__temp_6:	.word 0
__temp_7:	.word 0
__temp_8:	.word 0
__temp_9:	.word 0
__string_13:	.asciiz "   "
__string_17:	.asciiz "\n"
ERRDIVZERO:	.asciiz "Error : division by zero"

.text
main:
	lw $t0, __const_6
	sw $t0, rows__
	lw $t0, __const_1
	sw $t0, coef__
	lw $t0, __const_0
	sw $t0, i__
	__label_20:
	lw $t0, i__
	lw $t1, rows__
	blt $t0, $t1, __label_18
	j __label_19
	__label_18:
	lw $t0, __const_1
	sw $t0, space__
	__label_4:
	lw $t0, rows__
	lw $t1, i__
	subu $t2,$t0,$t1
	sw $t2, __temp_0
	lw $t0, space__
	lw $t1, __temp_0
	ble $t0, $t1, __label_2
	j __label_3
	__label_2:
	la $a0, __string_1
	li $v0, 4
	syscall
	lw $t0, space__
	lw $t1, __const_1
	addu $t2,$t0,$t1
	sw $t2, space__
	j __label_4
	__label_3:
	lw $t0, __const_0
	sw $t0, k__
	__label_16:
	lw $t0, k__
	lw $t1, i__
	ble $t0, $t1, __label_14
	j __label_15
	__label_14:
	lw $t0, k__
	lw $t1, __const_0
	beq $t0, $t1, __label_10
	j __label_5
	__label_5:
	lw $t0, i__
	lw $t1, __const_0
	beq $t0, $t1, __label_10
	j __label_11
	__label_10:
	lw $t0, __const_1
	sw $t0, coef__
	j __label_12
	__label_11:
	lw $t0, i__
	lw $t1, k__
	subu $t2,$t0,$t1
	sw $t2, __temp_6
	lw $t0, __temp_6
	lw $t1, __const_1
	addu $t2,$t0,$t1
	sw $t2, __temp_7
	lw $t0, coef__
	lw $t1, __temp_7
	mul $t2,$t0,$t1
	sw $t2, __temp_8
	lw $t0, __temp_8
	lw $t1, k__
	div $t2,$t0,$t1
	sw $t2, __temp_9
	lw $t0, __temp_9
	sw $t0, coef__
	__label_12:
	lw $a0, coef__
	li $v0, 1
	syscall
	la $a0, __string_13
	li $v0, 4
	syscall
	lw $t0, k__
	lw $t1, __const_1
	addu $t2,$t0,$t1
	sw $t2, k__
	j __label_16
	__label_15:
	la $a0, __string_17
	li $v0, 4
	syscall
	lw $t0, i__
	lw $t1, __const_1
	addu $t2,$t0,$t1
	sw $t2, i__
	j __label_20
	__label_19:
	lw $v0, __const_0
	jr $ra
