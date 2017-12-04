	.file	"sample16.c"
	.comm	a,8,8
	.comm	b,8,8
	.comm	c,8,8
	.comm	d,8,8
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
	movsd	a(%rip), %xmm0
	movsd	b(%rip), %xmm1
	divsd	%xmm1, %xmm0
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
	.long	3901001285
	.long	1074330838
	.align 8
.LC1:
	.long	1950500642
	.long	1074822763
	.ident	"GCC: (GNU) 6.3.1 20161221 (Red Hat 6.3.1-1)"
	.section	.note.GNU-stack,"",@progbits
