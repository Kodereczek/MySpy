// Filename: class.process.h
// Author:   Patryk Po³eæ

#pragma once 

class C_Process
{
	// Constructor and destructor
	public:
		C_Process();
		~C_Process();

	// Public methods
	public:
		DWORD IsProcess(string _processName);
		 void KillProcess(DWORD _processID); 

	// Private methods
	private:
		
	// Public fields
	public:

	// Private fields
	private:
		HANDLE
			hSnapshot,
			hProcess;

		PROCESSENTRY32
			proc32Struct;
};