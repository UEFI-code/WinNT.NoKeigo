#include <ntddk.h>

UINT64 original_syscall_handler = 0;

UINT64 GetSyscallHandler(void); // defined in tools2.asm
void SetSyscallHandler(void* func); // defined in tools2.asm

void mySYSCALL_Handler(void); // defined in tools2.asm

void NoKeigo_Patcher(UINT8 *addr);

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
    // DbgBreakPoint();
    // for NtWriteFile, we only interested in the Buffer, which is in user RSP
    // DbgPrint("User RSP: %llx\n", frame->RSP);
    if (!MmIsAddressValid(frame->RSP))
    {
        DbgPrint("Invalid User RSP Address\n");
        return;
    }
    UINT64 UsrBuf = *(UINT64*)(frame->RSP + 0x28);
    // DbgPrint("NtWriteFile Buffer Address: %llx\n", UsrBuf);
    NoKeigo_Patcher(UsrBuf);
}