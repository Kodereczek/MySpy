// Filename: class.curl.h
// Author:   Patryk Po³eæ

#pragma once

class C_Curl
{
	// Constructor and destructor
	public:
		C_Curl();
		~C_Curl();

	// Public methods
	public:
		void Request(string _url, string _postData = "", string _proxy = "", int _timeOut = 0, int _getHeader = 0, int _postHeader = 0);

		void DownloadFile(string _url, string _pathFile, ios_base::openmode _mode = ios::app | ios::binary); 

		void AddHeader(string _header);

		void ClearCookies();

         int Split(string _input, string _output[], string _delimiter = ":");

	  string Escape(string _data);
	  string Unescape(string _data);

	  string GetSourcePage(int _position1 = 0, int _position2 = 0);

	// Private methods
	private:
		static int Writer(char *_ptr, size_t _size, size_t _nmemb, string *_data);

	// Public fields
	public:
		CURLcode 
			result;

		string 
			userAgent[11],
			sourcePage;

	// Private fields
	private:
		CURL 
			*handle;

		struct curl_slist 
			*header;

		fstream 
			file;

		char
			*bufferChar;
};