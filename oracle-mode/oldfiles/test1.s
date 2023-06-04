	.file	"test-program.c"
	.text
	.globl	generateRandomString
	.type	generateRandomString, @function
generateRandomString:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$10000, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L2
.L3:
	call	rand@PLT
	movslq	%eax, %rcx
	movq	%rcx, %rax
	shrq	%rax
	movabsq	$-8925843906633654007, %rdx
	mulq	%rdx
	shrq	$4, %rdx
	movq	%rdx, %rax
	salq	$5, %rax
	subq	%rdx, %rax
	addq	%rax, %rax
	subq	%rax, %rcx
	movq	%rcx, %rdx
	movl	%edx, -12(%rbp)
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	cltq
	leaq	charset.0(%rip), %rcx
	movzbl	(%rax,%rcx), %eax
	movb	%al, (%rdx)
	addl	$1, -16(%rbp)
.L2:
	cmpl	$9999, -16(%rbp)
	jle	.L3
	movq	-8(%rbp), %rax
	addq	$10000, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	generateRandomString, .-generateRandomString
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, %eax
	call	generateRandomString
	movq	%rax, -8(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L6
.L8:
	movl	-12(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-12(%rbp), %eax
	movslq	%eax, %rcx
	movq	-8(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	jne	.L7
	addl	$1, -16(%rbp)
.L7:
	addl	$1, -12(%rbp)
.L6:
	cmpl	$9999, -12(%rbp)
	setle	%al
	testb	%al, %al
	jne	.L8
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	-16(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.section	.rodata
	.align 32
	.type	charset.0, @object
	.size	charset.0, 63
charset.0:
	.string	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	.ident	"GCC: (Ubuntu 12.2.0-3ubuntu1) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
