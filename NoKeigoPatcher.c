#include <ntddk.h>

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