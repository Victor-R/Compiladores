	.file "sample02.pas"
	.comm a,8,8
	.comm b,8,8
	.comm c,8,8
	.text
	.globl	main
	.type main,	@function
main:
	movl	$123,	%ebx
	movq	%rbx,	a(%rip)
	movl	$232,	%ecx
	movq	%rcx,	b(%rip)
	movq	a(%rip),	%rax
	addq	%rax,	%rax
	movq	b(%rip),	%rbx
	addq	%rax,	%rbx
	movq	%rbx,	c(%rip)
