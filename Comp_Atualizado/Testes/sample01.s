	.file "sample01.pas"
	.comm a,4,4
	.comm b,4,4
	.comm c,4,4
	.text
	.globl	main
	.type main,	@function
main:
	movl	$123,	%ebx
	movl	%ebx,	a(%rip)
	movl	$232,	%edx
	movl	%edx,	b(%rip)
	movl	a(%rip),	%eax
	movl	b(%rip),	%ebx
	addl	%eax,	%ebx
	movl	%ebx,	c(%rip)
