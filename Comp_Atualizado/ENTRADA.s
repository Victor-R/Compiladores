	.file "ENTRADA.pas"
	.comm x
	.comm y
	.text
	.globl	main
	.type main,	@function
main:
	movl	$2,	%ebx
	movl	%rax,	x(%rip)
	movl	$-2,	%ecx
	movl	%rbx,	y(%rip)
