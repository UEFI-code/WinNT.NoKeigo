# WINNT.NOKEIGO

> "Enter ring0. Reject politeness. Embrace unstable technology."

A chaotic Windows NT kernel toy that hooks x64 timer interrupts, sniffs register-linked userland memory, searches for a few hardcoded Japanese keigo patterns, and partially overwrites matched suffixes with raw bootleg energy.

If the stars align:

```text
"お早うございます"
        ↓
"お早うNO KEIGO"
```

Right now it mostly detects suffix-style patterns like `ございます` and overwrites only the matched tail section.

If the stars do not align:

```text
SYSTEM_SERVICE_EXCEPTION
IRQL_NOT_LESS_OR_EQUAL
mysterious silence
```

(

Actual testing revealed that the driver is far more stable than originally expected.

Mostly because it has already survived enough **Double Faults and Triple Faults** to psychologically transcend the concept of uptime.

)

This is not anti-malware.
This is not production software.
This is not even emotionally stable software.

Current state: experimental PoC with maximum NT energy.

---

## MANIFESTO

> "Human dignity is as equal as kernel threads under the scheduler."

That should already be a United Nations convention.

Yet the ancient protocol known as `敬語` still attempts to reconstruct hierarchical privilege stacks inside ordinary human conversation.

This driver rejects that architecture.

Running directly in Ring 0 — because Ring -1 hypervisor and Ring -2 SMM handler deployments currently require hardware debugging equipment that is financially incompatible with this project's emotional state — WINNT.NOKEIGO descends beneath the application layer and forcefully overwrites keigo patterns from the lowest reachable level of the operating system.

Not diplomacy.
Not middleware.
Kernel intervention.

---

## FEATURES

- Hooks x64 timer interrupts like it owns the machine
- Reads userland memory through live register context
- Detects a few hardcoded UTF-8 / Shift-JIS keigo suffix patterns
- Generates rare Windows moments
- Scientifically optimized for "what could possibly go wrong"

---

## REQUIREMENTS

### 1. Disable KVA Shadow

Some kernel VA becomes inaccessible while timer interrupts fire in ring3.

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

Heavy CPU usage processes are easier targets.
The scheduler yearns for chaos.

## STOP

```bat
sc stop Nt_NoKeigo
```

If it stops cleanly, buy a lottery ticket.

---

## WARNINGS

- Applications may crash
- Strings may mutate incorrectly
- Debuggers may become your primary UI
- Your machine may begin speaking fluent NT panic

Play stupid kernel games.
Win legendary kernel prizes.

---

## DISCLAIMER

For educational and experimental research purposes only.

Do not deploy this on production systems.
Do not use this for malicious or illegal activities.