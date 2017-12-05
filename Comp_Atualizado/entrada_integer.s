	.file "entrada_integer.pas"
	.comm x,4,4
	.comm y,4,4
	.text
	.globl	main
	.type main,	@function
main:
	movl	$2,	%ebx
	movl	%ebx,	x(%rip)
	movl	$-2,	%edx
	movl	%edx,	y(%rip)
.L1
	movl	y(%rip),	%eax
	movl	$-1,	%ecx
	cmpl	%ecx,	%eax
	jz		.L2
	movl	y(%rip),	%eax
	movl	%eax,	x(%rip)
	movl	x(%rip),	%eax
	movl	y(%rip),	%ebx
	addl	%eax,	%ebx
	movl	%ebx,	x(%rip)
	movl	x(%rip),	%eax
	mull	%edx,	%eax
	movl	y(%rip),	%edx
	mull	%edx,	%eax
	movl	%eax,	x(%rip)
	movl	x(%rip),	%eax
	cltd
	idivl	%esi
	movl	y(%rip),	%esi
	cltd
	idivl	%esi
	movl	%eax,	x(%rip)
	movl	x(%rip),	%eax
	mull	%edx,	%eax
	movl	$2,	%esi
	mull	%edx,	%eax
	movl	%eax,	x(%rip)
	jmp		.L1
.L2
	movl	x(%rip),	%eax
	movl	$3,	%edx
	cmpl	%edx,	%eax
	jz .L3
	mull	%edx,	%eax
	movl	y(%rip),	%edx
	mull	%edx,	%eax
	movl	$4,	%edx
	addl	%eax,	%edx
	movl	%edx,	x(%rip)
	mull	%edx,	%eax
	movl	y(%rip),	%edx
	mull	%edx,	%eax
	movl	$4,	%edx
	addl	%eax,	%edx
	movl	%edx,	x(%rip)
	movl	%edx,	y(%rip)
	jmp		.L4
.L3
	movl	%edx,	y(%rip)
	movl	%edx,	x(%rip)
.L4
