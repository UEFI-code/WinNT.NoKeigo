#include <ntddk.h>

UINT64 original_D1_handler = 0;

UINT64 GetIDT_Item_Addr(UINT64 int_id); // asm toolget
void HackIDT_FireAndForget3(UINT64 int_id, void *func); // asm toolget

void myINTHandler_d1h(); // defined in tools.asm

void HackIDT()
{
    // trigger breakpoint
    DbgBreakPoint();
    original_D1_handler = GetIDT_Item_Addr(0xd1);
    HackIDT_FireAndForget3(0xd1, myINTHandler_d1h);
}

void RestoreIDT()
{
    HackIDT_FireAndForget3(0xd1, original_D1_handler);
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
    // x64 interrupt
    UINT8* RIP;
    UINT64 CS;
    UINT64 RFLAGS;
    UINT8* RSP;
    UINT64 SS;
} MY_GP_FRAME;

const char *keigo_pattern[] = {
    "TestKeigo",
    "\xe3\x81\x94\xe3\x81\x96\xe3\x81\x84\xe3\x81\xbe\xe3\x81\x99\x0", // ございます utf8
    "\x82\xb2\x82\xb4\x82\xa2\x82\xdc\x82\xb7\x0", // ございます sjis
};
#define KEIGO_PATTERN_COUNT (sizeof(keigo_pattern) / 8)

#define SCAN_SIZE 32
void NoKeigo_Patcher(UINT8 *addr)
{
    if (!MmIsAddressValid(addr))
        return;
    if (!MmIsAddressValid(addr + SCAN_SIZE))
        return;
    //DbgPrint("Scanning keigo buf at 0x%p ...\n", addr);
    for (UINT8 *p = addr; p < addr + SCAN_SIZE; p++)
    {
        for (int i = 0; i < KEIGO_PATTERN_COUNT; i++)
        {
            const char *pattern = keigo_pattern[i];
            size_t pattern_len = strlen(pattern); // here's a trick: Keigo has no 0 in the middle
            if (memcmp(p, pattern, pattern_len) == 0)
            {
                //DbgBreakPoint();
                DbgPrint("Found keigo pattern at 0x%p: %s\n", p, pattern);
                memcpy(p, "NO KEIGO, US IS BEST", pattern_len);
                return; // patch only the first occurrence
            }
        }
    }
}

// static UINT64 counter = 0;
void myD1Handler_cfunc(MY_GP_FRAME *frame)
{
    // counter = (counter + 1) % 256;
    // if (counter % 256 != 1)
    //     return;
    //DbgBreakPoint();
    //DbgPrint("Mem patch triggered\n");
    NoKeigo_Patcher(frame->RAX);
    NoKeigo_Patcher(frame->RBX);
    NoKeigo_Patcher(frame->RCX);
    NoKeigo_Patcher(frame->RDX);
    NoKeigo_Patcher(frame->RDI);
    NoKeigo_Patcher(frame->RSI);
    NoKeigo_Patcher(frame->RDI);
    NoKeigo_Patcher(frame->R8);
    NoKeigo_Patcher(frame->R9);
    NoKeigo_Patcher(frame->R10);
    NoKeigo_Patcher(frame->R11);
    NoKeigo_Patcher(frame->RSP);
}