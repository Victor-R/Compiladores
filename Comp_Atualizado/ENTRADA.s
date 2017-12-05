	.file ENTRADA.pas
	.comm x
	.comm y
main:
	movl	$2,	%ebx
	movl	%ebx,	x(%rip)
	movl	$-2,	%edx
	movl	%edx,	y(%rip)
.L1
	movl	y(%rip),	%eax
	movl	$-1,	%ebx
	cmpl %ebx, %eax
	jz .L2
	movl	y(%rip),	%eax
	movl	%eax,	x(%rip)
	movl	x(%rip),	%eax
	movl	y(%rip),	%esi
	cltd
	idivl	%esi
	movl	%eax,	x(%rip)
	movl	x(%rip),	%eax
	movl	$2,	%esi
	cltd
	idivl	%esi
	movl	%eax,	x(%rip)
	jmp .L1
.L2
	movl	x(%rip),	%eax
	movl	$3,	%esi
	cmpl %eax, %eax
	jz .L3
	movl	$2,	%ebx
	movl	y(%rip),	%edx
	imull	%edx,	%eax
	movl	$4,	%edx
	addl	%eax,	%edx
	movl	%edx,	x(%rip)
	movl	$7,	%edx
	movl	%edx,	y(%rip)
	jmp .L4
.L3
	movl	$5,	%ebx
	movl	%ebx,	y(%rip)
	movl	$4,	%edx
	movl	%edx,	x(%rip)
.L4
