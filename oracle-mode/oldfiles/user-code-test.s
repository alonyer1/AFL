	.file	"user-code-test.c"
	.text
.Ltext0:
	.file 0 "/home/alon/project4/AFL/oracle-mode" "user-code-test.c"
	.globl	func
	.type	func, @function
func:
.LVL0:
.LFB51:
	.file 1 "user-code-test.c"
	.loc 1 13 53 view -0
	.cfi_startproc
	.loc 1 13 53 is_stmt 0 view .LVU1
	endbr64
	.loc 1 14 5 is_stmt 1 view .LVU2
.LVL1:
.LBB2:
	.loc 1 16 10 view .LVU3
	.loc 1 16 5 view .LVU4
	.loc 1 17 9 view .LVU5
	.loc 1 17 12 is_stmt 0 view .LVU6
	cmpb	$102, (%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU7
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU8
.LVL2:
	.loc 1 16 5 view .LVU9
	.loc 1 17 9 view .LVU10
	.loc 1 17 12 is_stmt 0 view .LVU11
#NO_APP
	cmpb	$105, 1(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU12
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU13
.LVL3:
	.loc 1 16 5 view .LVU14
	.loc 1 17 9 view .LVU15
	.loc 1 17 12 is_stmt 0 view .LVU16
#NO_APP
	cmpb	$120, 2(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU17
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU18
.LVL4:
	.loc 1 16 5 view .LVU19
	.loc 1 17 9 view .LVU20
	.loc 1 17 12 is_stmt 0 view .LVU21
#NO_APP
	cmpb	$101, 3(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU22
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU23
.LVL5:
	.loc 1 16 5 view .LVU24
	.loc 1 17 9 view .LVU25
	.loc 1 17 12 is_stmt 0 view .LVU26
#NO_APP
	cmpb	$100, 4(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU27
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU28
.LVL6:
	.loc 1 16 5 view .LVU29
	.loc 1 17 9 view .LVU30
	.loc 1 17 12 is_stmt 0 view .LVU31
#NO_APP
	cmpb	$32, 5(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU32
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU33
.LVL7:
	.loc 1 16 5 view .LVU34
	.loc 1 17 9 view .LVU35
	.loc 1 17 12 is_stmt 0 view .LVU36
#NO_APP
	cmpb	$115, 6(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU37
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU38
.LVL8:
	.loc 1 16 5 view .LVU39
	.loc 1 17 9 view .LVU40
	.loc 1 17 12 is_stmt 0 view .LVU41
#NO_APP
	cmpb	$116, 7(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU42
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU43
.LVL9:
	.loc 1 16 5 view .LVU44
	.loc 1 17 9 view .LVU45
	.loc 1 17 12 is_stmt 0 view .LVU46
#NO_APP
	cmpb	$114, 8(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU47
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU48
.LVL10:
	.loc 1 16 5 view .LVU49
	.loc 1 17 9 view .LVU50
	.loc 1 17 12 is_stmt 0 view .LVU51
#NO_APP
	cmpb	$105, 9(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU52
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU53
.LVL11:
	.loc 1 16 5 view .LVU54
	.loc 1 17 9 view .LVU55
	.loc 1 17 12 is_stmt 0 view .LVU56
#NO_APP
	cmpb	$110, 10(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 view .LVU57
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 view .LVU58
.LVL12:
	.loc 1 16 5 view .LVU59
	.loc 1 17 9 view .LVU60
	.loc 1 17 12 is_stmt 0 view .LVU61
#NO_APP
	cmpb	$103, 11(%rdi)
	jne	.L2
	.loc 1 20 9 is_stmt 1 discriminator 2 view .LVU62
#APP
# 20 "user-code-test.c" 1
	cpuid
# 0 "" 2
	.loc 1 16 35 discriminator 2 view .LVU63
.LVL13:
	.loc 1 16 5 discriminator 2 view .LVU64
#NO_APP
.LBE2:
	.loc 1 26 12 is_stmt 0 discriminator 2 view .LVU65
	movl	$0, %eax
	ret
.LVL14:
.L2:
.LBB3:
	.loc 1 18 20 view .LVU66
	movl	$-1, %eax
.LBE3:
	.loc 1 27 1 view .LVU67
	ret #TAKEN
	.cfi_endproc
.LFE51:
	.size	func, .-func
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xeb
	.value	0x5
	.byte	0x1
	.byte	0x8
	.long	.Ldebug_abbrev0
	.uleb128 0x2
	.long	.LASF12
	.byte	0x1d
	.long	.LASF0
	.long	.LASF1
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x1
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.long	.LASF4
	.uleb128 0x1
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x1
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x1
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x1
	.byte	0x8
	.byte	0x5
	.long	.LASF8
	.uleb128 0x4
	.byte	0x8
	.long	0x6c
	.uleb128 0x1
	.byte	0x1
	.byte	0x6
	.long	.LASF9
	.uleb128 0x1
	.byte	0x8
	.byte	0x5
	.long	.LASF10
	.uleb128 0x1
	.byte	0x8
	.byte	0x7
	.long	.LASF11
	.uleb128 0x5
	.long	.LASF13
	.byte	0x1
	.byte	0xd
	.byte	0x1f
	.long	0x58
	.quad	.LFB51
	.quad	.LFE51-.LFB51
	.uleb128 0x1
	.byte	0x9c
	.long	0xdd
	.uleb128 0x6
	.long	.LASF14
	.byte	0x1
	.byte	0xd
	.byte	0x2a
	.long	0x66
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x7
	.long	.LASF15
	.byte	0x1
	.byte	0xe
	.byte	0xb
	.long	0x66
	.uleb128 0x6
	.byte	0xa0
	.long	.Ldebug_info0+221
	.sleb128 0
	.uleb128 0x8
	.long	.LLRL0
	.uleb128 0x9
	.string	"i"
	.byte	0x1
	.byte	0x10
	.byte	0xe
	.long	0x58
	.long	.LLST1
	.long	.LVUS1
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0x9e
	.uleb128 0xd
	.byte	0x66
	.byte	0x69
	.byte	0x78
	.byte	0x65
	.byte	0x64
	.byte	0x20
	.byte	0x73
	.byte	0x74
	.byte	0x72
	.byte	0x69
	.byte	0x6e
	.byte	0x67
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.uleb128 0x2137
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x36
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loclists,"",@progbits
	.long	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.value	0x5
	.byte	0x8
	.byte	0
	.long	0
.Ldebug_loc0:
.LVUS1:
	.uleb128 .LVU4
	.uleb128 .LVU9
	.uleb128 .LVU9
	.uleb128 .LVU14
	.uleb128 .LVU14
	.uleb128 .LVU19
	.uleb128 .LVU19
	.uleb128 .LVU24
	.uleb128 .LVU24
	.uleb128 .LVU29
	.uleb128 .LVU29
	.uleb128 .LVU34
	.uleb128 .LVU34
	.uleb128 .LVU39
	.uleb128 .LVU39
	.uleb128 .LVU44
	.uleb128 .LVU44
	.uleb128 .LVU49
	.uleb128 .LVU49
	.uleb128 .LVU54
	.uleb128 .LVU54
	.uleb128 .LVU59
	.uleb128 .LVU59
	.uleb128 .LVU64
	.uleb128 .LVU64
	.uleb128 .LVU66
.LLST1:
	.byte	0x4
	.uleb128 .LVL1-.Ltext0
	.uleb128 .LVL2-.Ltext0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL2-.Ltext0
	.uleb128 .LVL3-.Ltext0
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.Ltext0
	.uleb128 .LVL4-.Ltext0
	.uleb128 0x2
	.byte	0x32
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL4-.Ltext0
	.uleb128 .LVL5-.Ltext0
	.uleb128 0x2
	.byte	0x33
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.Ltext0
	.uleb128 .LVL6-.Ltext0
	.uleb128 0x2
	.byte	0x34
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL6-.Ltext0
	.uleb128 .LVL7-.Ltext0
	.uleb128 0x2
	.byte	0x35
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL7-.Ltext0
	.uleb128 .LVL8-.Ltext0
	.uleb128 0x2
	.byte	0x36
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL8-.Ltext0
	.uleb128 .LVL9-.Ltext0
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL9-.Ltext0
	.uleb128 .LVL10-.Ltext0
	.uleb128 0x2
	.byte	0x38
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL10-.Ltext0
	.uleb128 .LVL11-.Ltext0
	.uleb128 0x2
	.byte	0x39
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL11-.Ltext0
	.uleb128 .LVL12-.Ltext0
	.uleb128 0x2
	.byte	0x3a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL12-.Ltext0
	.uleb128 .LVL13-.Ltext0
	.uleb128 0x2
	.byte	0x3b
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL13-.Ltext0
	.uleb128 .LVL14-.Ltext0
	.uleb128 0x2
	.byte	0x3c
	.byte	0x9f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_rnglists,"",@progbits
.Ldebug_ranges0:
	.long	.Ldebug_ranges3-.Ldebug_ranges2
.Ldebug_ranges2:
	.value	0x5
	.byte	0x8
	.byte	0
	.long	0
.LLRL0:
	.byte	0x4
	.uleb128 .LBB2-.Ltext0
	.uleb128 .LBE2-.Ltext0
	.byte	0x4
	.uleb128 .LBB3-.Ltext0
	.uleb128 .LBE3-.Ltext0
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF10:
	.string	"long long int"
.LASF15:
	.string	"fixed_str"
.LASF2:
	.string	"long unsigned int"
.LASF11:
	.string	"long long unsigned int"
.LASF14:
	.string	"input_str"
.LASF4:
	.string	"unsigned char"
.LASF9:
	.string	"char"
.LASF8:
	.string	"long int"
.LASF12:
	.string	"GNU C17 12.2.0 -mtune=generic -march=x86-64 -g -O1 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection"
.LASF5:
	.string	"short unsigned int"
.LASF6:
	.string	"signed char"
.LASF13:
	.string	"func"
.LASF7:
	.string	"short int"
.LASF3:
	.string	"unsigned int"
	.section	.debug_line_str,"MS",@progbits,1
.LASF0:
	.string	"user-code-test.c"
.LASF1:
	.string	"/home/alon/project4/AFL/oracle-mode"
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
