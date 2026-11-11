# Windows NT NoKeigo Driver

A driver that hooks x64 Timer interrupts and detects japanese "keigo" partterns through RAX/RBX/RCX/RDX/etc memory pointer, and replace it to "NO KEIGO, US IS BEST" if possible.

This driver only modify userland memory.

User application might CRASH or behave unexpectedly.

Currently under PoC stage.

## DISCLAIMER

This driver is for **educational, research and game-effect-design purposes only**.

Do not use it in production environments.

Do not use it to do anything malicious or illegal.