	.file	"test2.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB51:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rsi, %rbp
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol@PLT
	movq	%rax, %rbx
	movq	16(%rbp), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol@PLT
	cmpl	%ebx, %eax
	je	.L3
	leal	1(%rbx), %ecx
	leal	1(%rax), %esi
	je	.L4
	leal	2(%rax), %edx
	cmpl	%edx, %ebx
	je	.L5
	cmpl	%ecx, %eax
	je	.L6
	cmpl	%esi, %ebx
	je	.L7
	cmpl	%edx, %ecx
	sete	%al
	movzbl	%al, %eax
	addl	$1, %eax
.L1:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L3:
	.cfi_restore_state
	movl	$2, %eax
	jmp	.L1
.L4:
	movl	$2, %eax
	jmp	.L1
.L5:
	movl	$2, %eax
	jmp	.L1
.L6:
	movl	$2, %eax
	jmp	.L1
.L7:
	movl	$2, %eax
	jmp	.L1
	.cfi_endproc
.LFE51:
	.size	main, .-main
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
