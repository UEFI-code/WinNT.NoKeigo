#include <ntddk.h>

void Disable_SMAP_SMEP();
void HackIDT();

VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
    DbgPrint("Driver Unload Called\n");
    pDriverObject->DriverUnload = NULL;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
{
    driver_object->DriverUnload = DriverUnload;
    KdPrint(("Driver Loaded at RegistryPath: %wZ\n", registry_path));
    Disable_SMAP_SMEP();
    KdPrint(("SMAP and SMEP Disabled\n"));
    HackIDT();
    KdPrint(("IDT Hacked\n"));
    return STATUS_SUCCESS;
}