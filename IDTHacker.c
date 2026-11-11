UINT64 original_D1_addr = 0;

UINT64 GetIDT_Item_Addr(UINT64 int_id); // asm toolget
void HackIDT_FireAndForget2(UINT64 int_id, void *func); // asm toolget

void myINTHandler_d1h(); // defined in tools.asm

void HackIDT()
{
    // trigger breakpoint
    DbgBreakPoint();
    original_D1_addr = GetIDT_Item_Addr(0xd1);
    HackIDT_FireAndForget2(0xd1, myINTHandler_d1h);
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

void myD1Handler_cfunc(MY_GP_FRAME *frame)
{
    DbgBreakPoint();
    DbgPrint("We are in myD1Handler_cfunc, arg = %p\n", frame);
    DbgPrint("Usr RIP = %p\n", frame->RIP);
}