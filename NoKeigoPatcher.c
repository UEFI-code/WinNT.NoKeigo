#include <ntddk.h>

const char *keigo_pattern[] = {
    "TestKeigo",
    "\xe3\x81\x94\xe3\x81\x96\xe3\x81\x84\xe3\x81\xbe\xe3\x81\x99\x0", // ございます utf8
    "\x82\xb2\x82\xb4\x82\xa2\x82\xdc\x82\xb7\x0", // ございます sjis
    "\xe3\x81\xaa\xe3\x82\x8a\xe3\x81\xbe\xe3\x81\x99\x0", // なります utf8
    "\x82\xc8\x82\xe8\x82\xdc\x82\xb7\x0", // なります sjis
    "\xe9\xa0\x82\xe3\x81\x8d\xe3\x81\xbe\xe3\x81\x99\x0", // 頂きます utf8
    "\x92\xb8\x82\xab\x82\xdc\x82\xb7\x0", // 頂きます sjis
    "\xe3\x81\x84\xe3\x81\x9f\xe3\x81\xa0\xe3\x81\x8d\xe3\x81\xbe\xe3\x81\x97\xe3\x81\x9f\x0", // いただきました utf8
    "\x82\xa2\x82\xbd\x82\xbe\x82\xab\x82\xdc\x82\xb5\x82\xbd\x0", // いただきました sjis
};
#define KEIGO_PATTERN_COUNT (sizeof(keigo_pattern) / 8)

#define SCAN_SIZE 64
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
                memcpy(p, "NO KEIGO. US IS BEST. CALIFORNIA DREAM. ASIA SUCKS. ", pattern_len);
                return; // patch only the first occurrence
            }
        }
    }
}