#include <ntddk.h>

void Disable_WriteProtect();
void Disable_SMAP_SMEP();

void HackIDT();
void RestoreIDT();
void HackSyscall();
void RestoreSyscall();

VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
    DbgPrint("Driver Unload Called\n");
    //RestoreIDT();
    RestoreSyscall();
    pDriverObject->DriverUnload = NULL;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
{
    driver_object->DriverUnload = DriverUnload;
    KdPrint(("Driver Loaded at RegistryPath: %wZ\n", registry_path));
    Disable_WriteProtect();
    KdPrint(("Write Protection Disabled\n"));
    Disable_SMAP_SMEP();
    KdPrint(("SMAP and SMEP Disabled\n"));
    //HackIDT();
    HackSyscall();
    KdPrint(("IDT Hacked\n"));
    return STATUS_SUCCESS;
}