	.file	"test-program.c"
	.text
	.section	.rodata
.LC0:
	.string	"Sum: %d\n"
	.text
	.globl	loop_function
	.type	loop_function, @function
loop_function:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L2
.L5:
	call	rand@PLT
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$31, %eax
	addl	%eax, %edx
	andl	$1, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	testl	%eax, %eax
	setne	%al
	movb	%al, -17(%rbp)
	movq	$0, -8(%rbp)
#APP
# 13 "test-program.c" 1
	mov %rax, %rip	

# 0 "" 2
#NO_APP
	movq	%rax, -8(%rbp)
	movl	-16(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L3
	movl	-16(%rbp), %eax
	addl	%eax, -12(%rbp)
	jmp	.L4
.L3:
	movl	-16(%rbp), %eax
	subl	%eax, -12(%rbp)
.L4:
	addl	$1, -16(%rbp)
.L2:
	cmpl	$99999, -16(%rbp)
	jle	.L5
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	loop_function, .-loop_function
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
	movl	$0, %eax
	call	loop_function
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
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
