
extern original_syscall_handler: qword
extern mySYSCALL_cfunc: proc

.data

my_syscall_stack BYTE 1024 DUP(0)

.code

GetSyscallHandler PROC
    mov ecx, 0C0000082h
    rdmsr
    shl rdx, 32
    or  rax, rdx
    ret
GetSyscallHandler ENDP

SetSyscallHandler PROC
    mov ecx, 0C0000082h
    mov rdx, rax
    shr rdx, 32
    wrmsr
    ret
SetSyscallHandler ENDP

mySYSCALL_Handler PROC
    ; RAX = syscall number
    ; RCX = return address
    ; R10 = argument 0
    ; RDX = argument 1
    ; R8  = argument 2
    ; R9  = argument 3
    ; [rsp+28h] = argument 4
    ; [rsp+30h] = argument 5
    ; [rsp+38h] = argument 6
    ; [rsp+40h] = argument 7
    ; [rsp+48h] = argument 8
    ; We are only interested in NtWriteFile
    cmp ax, 8
    jne to_ker
    swapgs
    int 3
    mov qword ptr [my_syscall_stack + 1016h], rsp
    lea rsp, [my_syscall_stack + 1016h]
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    ; prepare call cfunc;
    mov rcx, rsp ; argv0
    push rbp ; the fucking call convention...
    mov rbp, rsp
    sub rsp, 0ffh ; Prepare stack for mySYSCALL_cfunc
    call mySYSCALL_cfunc
    add rsp, 0ffh
    pop rbp
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop rsp
    swapgs
    to_ker:
    jmp [original_syscall_handler]

mySYSCALL_Handler ENDP

END