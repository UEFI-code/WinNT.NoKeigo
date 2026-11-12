# Windows NT NoKeigo Driver

A driver that hooks x64 Timer interrupts and detects japanese "keigo" partterns through RAX/RBX/RCX/RDX/etc memory pointer, and replace it to "NO KEIGO, US IS BEST" if possible.

This driver only modify userland memory.

User application might CRASH or behave unexpectedly.

Currently under PoC stage.

## Prerequisites

Disable KVA shadow because some kernel VA is inaccessible when timer-interrupts on ring3

```
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v FeatureSettingsOverride /t REG_DWORD /d 3 /f

reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v FeatureSettingsOverrideMask /t REG_DWORD /d 3 /f
```

Must Enable `Test Mode` to allow unsigned drivers & disable patch guard

Must Attach WinDbg Kernel Debugger to capture `int 3` in kernel

Remember: 

- Play STUPID game, win STUPID prizes
- Play NT game, win NT prizes
- Play Intel game, win Intel prizes
- Play AMD game, win AMD prizes

## Play

1. Install:

```
sc create Nt_NoKeigo type= kernel binPath= "C:\Nt_NoKeigo.sys"
```

2. Start the service:

```
sc start Nt_NoKeigo
```

3. Stop the service:

```
sc stop Nt_NoKeigo
```

## DISCLAIMER

This driver is for **educational, research and game-effect-design purposes only**.

Do not use it in production environments.

Do not use it to do anything malicious or illegal.