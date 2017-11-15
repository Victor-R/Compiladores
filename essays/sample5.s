	.file	"sample5.c"
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
	movsd	.LC0(%rip), %xmm0
	movsd	%xmm0, a(%rip)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, b(%rip)
	movsd	a(%rip), %xmm1
	movsd	b(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, c(%rip)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1079951360
	.align 8
.LC1:
	.long	0
	.long	1080885248
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
