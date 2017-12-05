	.file "sample09.pas"
	.comm a
	.comm b
	.comm c
main:
	movl	$312345678,	%ebx
	movl	%ebx,	a(%rip)
	movl	$412345678,	%edx
	movl	%edx,	b(%rip)
	movl	a(%rip),	%eax
	movl	b(%rip),	%edx
	imull	%edx,	%eax
	movl	%eax,	c(%rip)
