.global func, func2, func3
.section .text

func:
endbr64
cmpb   $0x66,(%rdi)
je     func_1
mov    $0xffffffff,%eax
ret
func_1:
cmpb   $0x69,0x1(%rdi)
je     func_2
mov    $0xffffffff,%eax
ret
func_2:
cmpb   $0x78,0x2(%rdi)
je     func_3
mov    $0xffffffff,%eax
ret
func_3:
cmpb   $0x65,0x3(%rdi)
je     func_4
mov    $0xffffffff,%eax
ret
func_4:
cmpb   $0x64,0x4(%rdi)
je     func_5
mov    $0xffffffff,%eax
ret
func_5:
cmpb   $0x20,0x5(%rdi)
je     func_6
mov    $0xffffffff,%eax
ret
func_6:
cmpb   $0x73,0x6(%rdi)
je     func_7
mov    $0xffffffff,%eax
ret
func_7:
cmpb   $0x74,0x7(%rdi)
je     func_8
mov    $0xffffffff,%eax
ret
func_8:
cmpb   $0x72,0x8(%rdi)
je     func_9
mov    $0xffffffff,%eax
ret
func_9:
cmpb   $0x69,0x9(%rdi)
je     func_10
mov    $0xffffffff,%eax
ret
func_10:
cmpb   $0x6e,0xa(%rdi)
je     func_11
mov    $0xffffffff,%eax
ret
func_11:
cmpb   $0x67,0xb(%rdi)
je     func_12
mov    $0xffffffff,%eax
ret
func_12:
mov    $0x0, %eax
ret

func2:
endbr64
cmpb   $0x66,(%rdi)
jne    func2_bad
cmpb   $0x69,0x40(%rdi)
jne    func2_bad
cmpb   $0x78,0x80(%rdi)
jne    func2_bad
cmpb   $0x65,0xc0(%rdi)
jne    func2_bad
cmpb   $0x64,0x100(%rdi)
jne    func2_bad
cmpb   $0x20,0x140(%rdi)
jne    func2_bad
cmpb   $0x73,0x180(%rdi)
jne    func2_bad
cmpb   $0x74,0x1c0(%rdi)
jne    func2_bad
cmpb   $0x72,0x200(%rdi)
jne    func2_bad
cmpb   $0x69,0x240(%rdi)
jne    func2_bad
cmpb   $0x6e,0x280(%rdi)
jne    func2_bad
cmpb   $0x67,0x2c0(%rdi)
setne  %al
movzbl %al,%eax
neg    %eax
ret
func2_bad:
mov    $0xffffffff,%eax
ret

func3:
endbr64
cmpb   $0x66,(%rdi)
jne    func3_bad
cmpb   $0x69,0x1040(%rdi)
jne    func3_bad
cmpb   $0x78,0x20c0(%rdi)
jne    func3_bad
cmpb   $0x65,0x3180(%rdi)
jne    func3_bad
cmpb   $0x64,0x41c0(%rdi)
jne    func3_bad
cmpb   $0x20,0x5280(%rdi)
jne    func3_bad
cmpb   $0x73,0x6380(%rdi)
jne    func3_bad
cmpb   $0x74,0x7500(%rdi)
jne    func3_bad
cmpb   $0x72,0x8580(%rdi)
jne    func3_bad
cmpb   $0x69,0x9700(%rdi)
jne    func3_bad
cmpb   $0x6e,0xa7c0(%rdi)
jne    func3_bad
cmpb   $0x67,0xbbc0(%rdi)
setne  %al
movzbl %al,%eax
neg    %eax
ret
func3_bad:
mov    $0xffffffff,%eax
ret
