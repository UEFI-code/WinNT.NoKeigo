#include <ntddk.h>

UINT64 original_syscall_handler = 0;

UINT64 GetSyscallHandler(void); // defined in tools2.asm
void SetSyscallHandler(void* func); // defined in tools2.asm

void mySYSCALL_Handler(void); // defined in tools2.asm

void HackSyscall()
{
    DbgBreakPoint();
    original_syscall_handler = GetSyscallHandler();
    DbgPrint("Original Syscall Handler: %llx\n", original_syscall_handler);
    SetSyscallHandler(mySYSCALL_Handler);
    DbgPrint("Hacked Syscall Handler: %llx\n", mySYSCALL_Handler);
}

void RestoreSyscall()
{
    SetSyscallHandler(original_syscall_handler);
}

typedef struct {
    UINT64 R11;
    UINT64 R10;
    UINT64 R9;
    UINT64 R8;
    UINT64 RDI;
    UINT64 RSI;
    UINT64 RDX;
    UINT64 RCX;
    UINT64 RBX;
    UINT64 RAX;
    UINT8* RSP;
} MY_SYSCALL_FRAME;

void mySYSCALL_cfunc(MY_SYSCALL_FRAME *frame)
{
    DbgBreakPoint();
    DbgPrint("Entered mySYSCALL_cfunc\n");
    DbgPrint("Return Address: %llx\n", frame->RCX);
}