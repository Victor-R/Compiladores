	movl	$2,	%eax
	movl	%eax,	x(%rip)
	movl	$-2,	%ebx
	movl	%ebx,	y(%rip)
.L1
	movl y(%rip),%eax
	movl	%ecx,	x(%rip)
	movl x(%rip),%eax
	movl (%rsp), %ebx
	movl %rax, %eax
	addl %eax, (%esp)
	movsd %xmm0, %rax
	addq $8,%rsp
	movl	$45,	%edx
	movl (%rsp), %ebx
	movl %rax, %eax
	addl %eax, (%esp)
	movsd %xmm0, %rax
	addq $8,%rsp
	movl	%edx,	x(%rip)
	movl y(%rip),%eax
	movl (%rsp), %ebx
	movl %rax, %eax
	addl %eax, (%esp)
	movsd %xmm0, %rax
	addq $8,%rsp
	movl	$1,	%eax
	movl (%rsp), %ebx
	movl %rax, %eax
	addl %eax, (%esp)
	movsd %xmm0, %rax
	addq $8,%rsp
	movl	%eax,	y(%rip)
	movl y(%rip),%eax
	movl	$-1,	%ebx
	cmpl %ebx, %eax
	jz .L2
	jmp .L1
.L2
	movl x(%rip),%eax
	movl	$3,	%ebx
	cmpl %ebx, %eax
	jz .L3
	movl	$2,	%ebx
	movl y(%rip),%eax
	movl (%rsp), %ebx
	movl %rax, %eax
	imull %esp, %eax
	movsd %xmm0, %rax
	addq $8,%rsp
	movl (%rsp), %ebx
	movl %rax, %eax
	addl %eax, (%esp)
	movsd %xmm0, %rax
	addq $8,%rsp
	movl	$4,	%ebx
	movl (%rsp), %ebx
	movl %rax, %eax
	addl %eax, (%esp)
	movsd %xmm0, %rax
	addq $8,%rsp
	movl	%ebx,	x(%rip)
	movl	$7,	%ecx
	movl	%ecx,	y(%rip)
	jmp .L4
.L3
	movl	$5,	%edx
	movl	%edx,	y(%rip)
	movl	$4,	%eax
	movl	%eax,	x(%rip)
.L4
