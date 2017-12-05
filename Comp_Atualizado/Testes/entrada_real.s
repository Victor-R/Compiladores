	.file "entrada_real.pas"
	.comm x,4,4
	.comm y,4,4
	.text
	.globl	main
	.type main,	@function
main:
	movss	$-1075681152(%rip),	%xmm(null)
	movss	%xmm1, x(%rip)
	movl	$2,	%ebx
	movss	%xmm1, y(%rip)
.L1
	movss	y(%rip),	%xmm0
	movl	$-1,	%ecx
	cmpl	%ecx,	%eax
	jz		.L2
	movss	y(%rip),	%xmm0
	movss	%xmm3, x(%rip)
	movss	x(%rip),	%xmm0
	addss	%xmm0,	%xmm4
	movss	y(%rip),	%xmm1
	addss	%xmm0,	%xmm5
	movss	%xmm5, x(%rip)
	movss	x(%rip),	%xmm0
	mulss	%xmm0,	%xmm1
	movss	y(%rip),	%xmm1
	mulss	%xmm0,	%xmm1
	movss	%xmm1, x(%rip)
	movss	x(%rip),	%xmm0
	idivss	%xmm1,	%xmm0
	movss	y(%rip),	%xmm1
	idivss	%xmm1,	%xmm0
	movss	%xmm2, x(%rip)
	movss	x(%rip),	%xmm0
	mulss	%xmm0,	%xmm1
	movl	$2,	%esi
	mull	%edx,	%eax
	movss	%xmm1, x(%rip)
	jmp		.L1
.L2
	movss	x(%rip),	%xmm0
	movl	$3,	%edx
	cmpl	%edx,	%eax
	jz .L3
	movl	$2,	%edx
	mulss	%xmm0,	%xmm1
	movss	y(%rip),	%xmm1
	mulss	%xmm0,	%xmm1
	addss	%xmm0,	%xmm1
	movl	$4,	%edx
	addl	%eax,	%edx
	movss	%xmm1, x(%rip)
	movl	$7,	%eax
	movss	%xmm1, y(%rip)
	jmp		.L4
.L3
	movl	$5,	%ebx
	movss	%xmm1, y(%rip)
	movl	$4,	%ecx
	movss	%xmm1, x(%rip)
.L4
