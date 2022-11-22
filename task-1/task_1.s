	.file	"task_1.c"
	.text
	.section	.rodata
.LC0:
	.string	"Error in getpwuid()"
.LC1:
	.string	"%d "
	.text
	.globl	print_group_id
	.type	print_group_id, @function
print_group_id:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, %edi
	call	getpwuid@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L2
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L2:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	$0, -8(%rbp)
	jmp	.L3
.L7:
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	jmp	.L4
.L6:
	movq	-16(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L5
	movq	-8(%rbp), %rax
	movl	16(%rax), %eax
	movl	%eax, -40(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L5:
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	leaq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
.L4:
	cmpq	$0, -32(%rbp)
	jne	.L6
.L3:
	call	getgrent@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L7
	movl	$10, %edi
	call	putchar@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	print_group_id, .-print_group_id
	.section	.rodata
.LC2:
	.string	"-u"
.LC3:
	.string	"-g"
.LC4:
	.string	"-G"
.LC5:
	.string	"Incorrect flag"
	.text
	.globl	parse_args
	.type	parse_args, @function
parse_args:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	cmpl	$1, -4(%rbp)
	jg	.L9
	movq	-24(%rbp), %rax
	movl	$0, (%rax)
	movq	-24(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-24(%rbp), %rax
	movl	$0, 8(%rax)
	movl	$0, %eax
	jmp	.L10
.L9:
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L11
	movq	-24(%rbp), %rax
	movl	$1, (%rax)
	movq	-24(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-24(%rbp), %rax
	movl	$0, 8(%rax)
	movl	$0, %eax
	jmp	.L10
.L11:
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L12
	movq	-24(%rbp), %rax
	movl	$0, (%rax)
	movq	-24(%rbp), %rax
	movl	$1, 4(%rax)
	movq	-24(%rbp), %rax
	movl	$0, 8(%rax)
	movl	$0, %eax
	jmp	.L10
.L12:
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L13
	movq	-24(%rbp), %rax
	movl	$0, (%rax)
	movq	-24(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-24(%rbp), %rax
	movl	$1, 8(%rax)
	movl	$0, %eax
	jmp	.L10
.L13:
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	movq	-24(%rbp), %rax
	movl	$0, (%rax)
	movq	-24(%rbp), %rax
	movl	$0, 4(%rax)
	movq	-24(%rbp), %rax
	movl	$0, 8(%rax)
	movl	$0, %eax
.L10:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	parse_args, .-parse_args
	.section	.rodata
.LC6:
	.string	"uid=%d\n"
.LC7:
	.string	"gid=%d\n"
.LC8:
	.string	"Error in getgrgid()"
.LC9:
	.string	"uid=%d(%s) "
.LC10:
	.string	"gid=%d(%s) "
.LC11:
	.string	"%d(%s),"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movl	%edi, -84(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-20(%rbp), %rdx
	movq	-96(%rbp), %rcx
	movl	-84(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	parse_args
	call	getuid@PLT
	movl	%eax, -72(%rbp)
	call	getgid@PLT
	movl	%eax, -68(%rbp)
	movl	-20(%rbp), %eax
	cmpl	$1, %eax
	jne	.L15
	movl	-72(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	exit@PLT
.L15:
	movl	-16(%rbp), %eax
	cmpl	$1, %eax
	jne	.L16
	movl	-68(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	exit@PLT
.L16:
	movl	-12(%rbp), %eax
	cmpl	$1, %eax
	jne	.L17
	movl	-68(%rbp), %edx
	movl	-72(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	print_group_id
	movl	$0, %edi
	call	exit@PLT
.L17:
	movl	-72(%rbp), %eax
	movl	%eax, %edi
	call	getpwuid@PLT
	movq	%rax, -56(%rbp)
	cmpq	$0, -56(%rbp)
	jne	.L18
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L18:
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movl	-68(%rbp), %eax
	movl	%eax, %edi
	call	getgrgid@PLT
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L19
	leaq	.LC8(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L19:
	movq	-48(%rbp), %rdx
	movl	-72(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC9(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-48(%rbp), %rdx
	movl	-68(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC10(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	$0, -32(%rbp)
	jmp	.L20
.L24:
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	jmp	.L21
.L23:
	movq	-48(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L22
	movq	-32(%rbp), %rax
	movl	16(%rax), %eax
	movl	%eax, -68(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movl	-68(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC11(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L22:
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	leaq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, 24(%rax)
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
.L21:
	cmpq	$0, -64(%rbp)
	jne	.L23
.L20:
	call	getgrent@PLT
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L24
	movl	$10, %edi
	call	putchar@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L26
	call	__stack_chk_fail@PLT
.L26:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
