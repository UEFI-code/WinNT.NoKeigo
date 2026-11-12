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

## DISCLAIMER

This driver is for **educational, research and game-effect-design purposes only**.

Do not use it in production environments.

Do not use it to do anything malicious or illegal.