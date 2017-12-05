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
	flds	.LC0
	fstps	x
	flds	.LC1
	fstps	y
	jmp	.L2
.L3:
	flds	y
	fstps	x
	flds	x
	flds	y
	fdivrp	%st, %st(1)
	fstps	x
	flds	x
	flds	.LC0
	fdivrp	%st, %st(1)
	fstps	x
.L2:
	flds	y
	fld1
	fchs
	fucomip	%st(1), %st
	fstp	%st(0)
	ja	.L3
	flds	.LC3
	flds	x
	fucomip	%st(1), %st
	fstp	%st(0)
	jbe	.L9
	flds	y
	fld	%st(0)
	faddp	%st, %st(1)
	flds	.LC4
	faddp	%st, %st(1)
	fstps	x
	flds	.LC5
	fstps	y
	jmp	.L6
.L9:
	flds	.LC6
	fstps	y
	flds	.LC4
	fstps	x
.L6:
	movl	$0, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1073741824
	.align 4
.LC1:
	.long	-1073741824
	.align 4
.LC3:
	.long	1077936128
	.align 4
.LC4:
	.long	1082130432
	.align 4
.LC5:
	.long	1088421888
	.align 4
.LC6:
	.long	1084227584
	.ident	"GCC: (GNU) 7.2.1 20170915 (Red Hat 7.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
