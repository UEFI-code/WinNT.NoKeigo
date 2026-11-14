# WINNT.NOKEIGO

> **Enter Ring 0. Hijack the syscall gate. Delete keigo at the point of write.**

WINNT.NOKEIGO is a deliberately unreasonable Windows NT kernel PoC that edits userland text from inside the kernel. The latest build does not merely wait for a convenient interrupt: it takes over the x64 syscall entry point and watches `NtWriteFile` itself.

The current hacking line:

```text
user process
    │
    └── NtWriteFile
          │
          ▼
      MSR_LSTAR ──► mySYSCALL_Handler
                           │
                           ├── syscall #8? Continue to the real kernel
                           └── yes ─► steal user Buffer
                                      │
                                      ▼
                              NoKeigo_Patcher()
                                      │
                                      ▼
                         "ございます" → "NO KEIGO"
```

In other words: the text is intercepted on its way into the operating system, before the write gets to pretend it is polite.

If the stars align:

```text
"お早うございます"
        ↓  NtWriteFile
"お早うNO KEIGO"
```

If the stars do not align:

```text
SYSTEM_SERVICE_EXCEPTION
IRQL_NOT_LESS_OR_EQUAL
TRIPLE FAULT
the machine has become a debugger session
```

This is not anti-malware.
This is not production software.
This is not even emotionally stable software.

This is an experimental kernel-level text mutation engine with maximum NT energy.

---

## MANIFESTO

> "Human dignity is as equal as kernel threads under the scheduler."

That should already be a United Nations convention.

Yet the ancient protocol known as `敬語` still attempts to reconstruct hierarchical privilege stacks inside ordinary human conversation.

This driver rejects that architecture.

Running directly in Ring 0 — because Ring -1 hypervisor and Ring -2 SMM handler deployments currently require hardware debugging equipment that is financially incompatible with this project's emotional state — WINNT.NOKEIGO descends beneath the application layer and forcefully overwrites keigo patterns from the lowest reachable level of the operating system.

Not diplomacy.
Not middleware.
Not a user-mode hook.

**Syscall intervention.**

---

## FEATURES

- Hijacks the x64 syscall entry through `MSR_LSTAR`
- Intercepts syscall number `8` — `NtWriteFile` on the target build
- Extracts the user-supplied write Buffer directly from the syscall frame
- Patches the first matching keigo sequence before the real syscall continues
- Recognizes a few hardcoded UTF-8 / Shift-JIS patterns, including `ございます`
- Preserves the original syscall handler for pass-through and unload
- Still contains the older x64 timer-interrupt attack path, because one control plane was clearly not enough
- Generates rare Windows moments
- Scientifically optimized for "what could possibly go wrong"

### The new syscall path

`mySYSCALL_Handler` receives every syscall entering the machine. Most calls are immediately forwarded to the original handler. When the syscall number matches `NtWriteFile`, the handler saves the register state, reaches into the user stack to locate the write Buffer, calls `NoKeigo_Patcher`, restores the state, and jumps back into the real syscall dispatcher.

The patcher scans a small window, replaces only the first matching sequence, and then lets the original write proceed. The kernel does not translate, sanitize, or ask permission. It mutates the bytes and sends them on their way.

---

## REQUIREMENTS

### 1. Disable KVA Shadow

The hook directly manipulates kernel entry machinery and expects the relevant kernel virtual addresses to remain reachable while handling user-originated syscalls.

```bat
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v FeatureSettingsOverride /t REG_DWORD /d 3 /f

reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v FeatureSettingsOverrideMask /t REG_DWORD /d 3 /f
```

### 2. Enable Test Mode

Unsigned driver.
Unwise decisions.
You know the drill.

### 3. Attach WinDbg Kernel Debugger

You will eventually meet `int 3`.
Be ready.

---

## INSTALL

```bat
sc create Nt_NoKeigo type= kernel binPath= "C:\Nt_NoKeigo.sys"
```

## START

```bat
sc start Nt_NoKeigo
```

Every syscall now passes through the new gate. `NtWriteFile` gets the special treatment; everything else is supposed to continue to the original handler.

Heavy CPU usage processes are easier targets.
The scheduler yearns for chaos.

## STOP

```bat
sc stop Nt_NoKeigo
```

If it stops cleanly, buy a lottery ticket.

---

## WARNINGS

- `MSR_LSTAR` is global kernel territory: this is not a per-process hook
- Syscall numbers are build-dependent; `8` must match the target Windows build
- User pointers are inspected and written from kernel mode
- The patcher scans only a small buffer window and changes raw bytes in place
- Applications may crash
- Strings may mutate incorrectly
- Debuggers may become your primary UI
- Your machine may begin speaking fluent NT panic

Play stupid kernel games.
Win legendary kernel prizes.

## STATUS

The project has crossed the line from "scan some registers during an interrupt" to "stand in front of the syscall dispatcher and rewrite file output." That is a substantial increase in power, danger, and comedic value.

It is a PoC. It is build-sensitive. It is intentionally fragile. It is also now one `NtWriteFile` away from turning kernel text processing into performance art.

---

## DISCLAIMER

This driver does NOT contains reverse engineering of any Windows code. It does NOT contain any exploit. It use x64 CPU features directly.

For educational and experimental research purposes only.

Do not deploy this on production systems.
Do not use this for malicious or illegal activities.