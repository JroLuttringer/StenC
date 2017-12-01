	.file	"simple_arithm.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$5, -4(%rbp)
	movl	$7, -8(%rbp)
	cmpl	$7, -4(%rbp)
	jle	.L2
	movl	$4, -8(%rbp)
	jmp	.L3
.L2:
	cmpl	$6, -4(%rbp)
	jg	.L3
	movl	$8, -8(%rbp)
.L3:
	cmpl	$99, -4(%rbp)
	jle	.L4
	cmpl	$200, -4(%rbp)
	jle	.L5
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jne	.L5
.L4:
	movl	$1, %eax
	jmp	.L7
.L5:
	movl	$0, %eax
.L7:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-8ubuntu3) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
