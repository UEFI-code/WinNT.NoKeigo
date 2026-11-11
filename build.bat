del *.obj
del *.sys

set "KIT=C:\Program Files (x86)\Windows Kits\10"
set "WDKVER=10.0.26100.0"
set "INC=%KIT%\Include\%WDKVER%"
set "LIB=%KIT%\Lib\%WDKVER%\km\x64"

cl.exe /nologo /c /kernel /GS /W4 /Zi /Od ^
    /D_AMD64_ ^
    /I"%INC%\km" ^
    /I"%INC%\shared" ^
    /I"%INC%\ucrt" ^
    main.c /Fo:main.obj

cl.exe /nologo /c /kernel /GS /W4 /Zi /Od ^
    /D_AMD64_ ^
    /I"%INC%\km" ^
    /I"%INC%\shared" ^
    /I"%INC%\ucrt" ^
    IDTHacker.c /Fo:IDTHacker.obj

ml64.exe /nologo /c /Zi tools.asm /Fo:tools.obj

link.exe /nologo ^
    /DRIVER ^
    /SUBSYSTEM:NATIVE ^
    /ENTRY:DriverEntry ^
    /MACHINE:X64 ^
    /NODEFAULTLIB ^
    /DEBUG ^
    /OUT:Nt_NoKeigo.sys ^
    /LIBPATH:"%LIB%" ^
    main.obj ^
    IDTHacker.obj ^
    tools.obj ^
    ntoskrnl.lib ^
    hal.lib ^
    BufferOverflowK.lib

