	.file "sample03.pas"
	.comm a,4,4
	.comm b,4,4
	.comm c,4,4
	.text
	.globl	main
	.type main,	@function
main:
	movl	$123,	%ebx
	movss	%xmm0, a(%rip)
	movl	$232,	%ecx
	movss	%xmm0, b(%rip)
	movss	a(%rip),	%xmm0
	addss	%xmm0,	%xmm1
	movss	b(%rip),	%xmm1
	addss	%xmm0,	%xmm2
	movss	%xmm2, c(%rip)
