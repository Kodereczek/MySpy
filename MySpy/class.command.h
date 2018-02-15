// Filename: class.command.h
// Author:   Patryk Po³eæ

#pragma once

class C_Command
{
	// Constructor and destructor
	public:
		C_Command(C_Base *_objBase);
		~C_Command();

	// Public methods
	public:
		int CheckCommand();

	// Private methods
	private:
		void DeleteApplication(string _command);
		void UpdateApplication(string _command);
		void ResetApplication();

	// Public fields
	public:

	// Private fields
	private:
		C_Base
			*objBase;

		C_Scrambler 
			*hashMD5;

		C_Curl 
			*curl;

		stringstream
			bufferStringStream;

		string
			random,
			command[3];
};