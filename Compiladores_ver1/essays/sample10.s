	.file	"sample10.c"
	.comm	a,8,8
	.comm	b,8,8
	.comm	c,8,8
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
	movq	$312345678, a(%rip)
	movq	$412345678, b(%rip)
	movq	a(%rip), %rdx
	movq	b(%rip), %rax
	imulq	%rdx, %rax
	movq	%rax, c(%rip)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
