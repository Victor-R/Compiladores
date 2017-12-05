	.file "entrada_longint.pas"
	.comm x,8,8
	.comm y,8,8
	.text
	.globl	main
	.type main,	@function
main:
	movl	$2,	%ebx
	movq	%rbx,	x(%rip)
	movl	$-2,	%ecx
	movq	%rcx,	y(%rip)
.L1
	movq	y(%rip),	%rax
	movq	$-1,	%rcx
	cmpq	%rcx,	%rax
	jz		.L2
	movq	y(%rip),	%rax
	movq	%rax,	x(%rip)
	movq	x(%rip),	%rax
	addq	%rax,	%rax
	movq	y(%rip),	%rbx
	addq	%rax,	%rbx
	movq	%rbx,	x(%rip)
	movq	x(%rip),	%rax
	mulq	%rdx,	%rax
	movq	y(%rip),	%rdx
	mulq	%rdx,	%rax
	movq	%rax,	x(%rip)
	movq	x(%rip),	%rax
	cltd
	idivq	%rsi
	movl	y(%rip),	%rsi
	cltd
	idivq	%rsi
	movq	%rax,	x(%rip)
	movq	x(%rip),	%rax
	mulq	%rdx,	%rax
	movq	$2,	%rsi
	mull	%edx,	%eax
	movq	%rax,	x(%rip)
	jmp		.L1
.L2
	movq	x(%rip),	%rax
	movq	$3,	%rdx
	cmpq	%rdx,	%rax
	jz .L3
	movl	$2,	%edx
	mulq	%rdx,	%rax
	movq	y(%rip),	%rdx
	mulq	%rdx,	%rax
	addq	%rax,	%rax
	movl	$4,	%edx
	addl	%eax,	%edx
	movq	%rdx,	x(%rip)
	movl	$7,	%eax
	movq	%rax,	y(%rip)
	jmp		.L4
.L3
	movl	$5,	%ebx
	movq	%rbx,	y(%rip)
	movl	$4,	%ecx
	movq	%rcx,	x(%rip)
.L4
