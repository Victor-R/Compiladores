	.file	"teste.c"
	.comm	x,4,4
	.comm	y,4,4
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$2, x
	movl	$-2, y
	jmp	.L2
.L3:
	movl	y, %eax
	movl	%eax, x
	movl	x, %eax
	addl	$45, %eax
	movl	%eax, x
	movl	y, %eax
	addl	$1, %eax
	movl	%eax, y
	movl	x, %eax
	subl	$1, %eax
	movl	%eax, x
.L2:
	movl	y, %eax
	cmpl	$-1, %eax
	jl	.L3
	movl	x, %eax
	cmpl	$3, %eax
	jle	.L4
	movl	y, %eax
	addl	$2, %eax
	addl	%eax, %eax
	movl	%eax, x
	movl	$7, y
	jmp	.L5
.L4:
	movl	$5, y
	movl	$4, x
.L5:
	movl	$0, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 7.2.1 20170915 (Red Hat 7.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
