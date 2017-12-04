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
	movl	$45,	%edx
	addl	%eax,	%edx
	movl	%edx,	x(%rip)
	movl	y(%rip),	%eax
	movl	$1,	%ebx
	addl	%eax,	%ebx
	movl	%ebx,	y(%rip)
	movl	x(%rip),	%eax
	movl	$1,	%edx
	subl	%eax,	%edx
	movl	%edx,	x(%rip)
	jmp .L1
.L2
	movl	x(%rip),	%eax
	movl	$3,	%ebx
	cmpl %ebx, %eax
	jz .L3
	movl	$2,	%ecx
	movl	y(%rip),	%eax
	movl (%rsp), %ebx
	movl %rax, %eax
	imull %esp, %eax
	movsd %xmm0, %rax
	addq $8,%rsp
	movl	$4,	%edx
	addl	%eax,	%edx
	movl	%edx,	x(%rip)
	movl	$7,	%ebx
	movl	%ebx,	y(%rip)
	jmp .L4
.L3
	movl	$5,	%edx
	movl	%edx,	y(%rip)
	movl	$4,	%ebx
	movl	%ebx,	x(%rip)
.L4
