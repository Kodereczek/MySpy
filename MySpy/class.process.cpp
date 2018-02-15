// Filename: class.process.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Process::C_Process()
{
	// Private fields
	hSnapshot = NULL;
	hProcess  = NULL;

	proc32Struct.dwSize = sizeof(PROCESSENTRY32);
}

C_Process::~C_Process()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
DWORD C_Process::IsProcess(string _processName)
{
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    while(Process32Next(hSnapshot, &proc32Struct)) if(proc32Struct.szExeFile == _processName) return proc32Struct.th32ProcessID;

	CloseHandle(hSnapshot);

	return 0;
}

void C_Process::KillProcess(DWORD _processID)
{
	hProcess = OpenProcess(PROCESS_TERMINATE, false, _processID);
	TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);
}