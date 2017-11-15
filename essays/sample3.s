	.file	"sample3.c"
	.comm	a,4,4
	.comm	b,4,4
	.comm	c,4,4
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
	movss	.LC0(%rip), %xmm0
	movss	%xmm0, a(%rip)
	movss	.LC1(%rip), %xmm0
	movss	%xmm0, b(%rip)
	movss	a(%rip), %xmm1
	movss	b(%rip), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, c(%rip)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1123418112
	.align 4
.LC1:
	.long	1130889216
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
