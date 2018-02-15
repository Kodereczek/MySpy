// Filename: class.curl.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// C_Curl::Constructor and destructor
C_Curl::C_Curl()
{
	// Public fields
	userAgent[1]  = "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/525.13 (KHTML, like Gecko) Chrome/0.2.149.29 Safari/525.13";
	userAgent[2]  = "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.1) Gecko/2008070208 Firefox/3.0.1";
	userAgent[3]  = "Mozilla/5.0 (Macintosh; U; PPC; ja-JP; rv:1.0.1) Gecko/20020823 Netscape/7.0";
	userAgent[4]  = "Mozilla/5.0 (Windows NT 6.2; WOW64; rv:21.0) Gecko/20100101 Firefox/21.0";
	userAgent[5]  = "Mozilla/5.0 (Windows NT 6.1; rv:5.0) Gecko/20100101 Firefox/5.0";
	userAgent[6]  = "Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)";
	userAgent[7]  = "Mozilla/4.0 (compatible; MSIE 5.15; Mac_PowerPC)";
	userAgent[8]  = "Opera/9.80 (Macintosh; Intel Mac OS X 10.8.2) Presto/2.12.388 Version/12.11";
	userAgent[9]  = "Opera/9.80 (X11; Linux i686; U; pl) Presto/2.7.62 Version/11.00";
	userAgent[10] = "Opera/9.80 (Windows NT 6.0) Presto/2.12.388 Version/12.11";
	
	sourcePage.clear();

	// Private fields
	handle = NULL;

	header = NULL;

	// Initialization
	curl_global_init(CURL_GLOBAL_ALL);
	handle = curl_easy_init();
}

C_Curl::~C_Curl()
{
	sourcePage.clear();

	curl_slist_free_all(header);
	curl_easy_cleanup(handle);
	curl_global_cleanup();
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
void C_Curl::Request(string _url, string _postData, string _proxy, int _timeOut, int _getHeader, int _postHeader)
{
	sourcePage.clear();
	
	curl_easy_setopt(handle, CURLOPT_URL          , _url.c_str());
	curl_easy_setopt(handle, CURLOPT_TIMEOUT      , _timeOut);
	curl_easy_setopt(handle, CURLOPT_HEADER       , _getHeader);
	curl_easy_setopt(handle, CURLOPT_COOKIEFILE   , "cookies.txt");
    curl_easy_setopt(handle, CURLOPT_COOKIEJAR    , "cookies.txt");
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, Writer);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA    , &sourcePage);

	if(_postData != "")
	{
		curl_easy_setopt(handle, CURLOPT_POST      , 1);
		curl_easy_setopt(handle, CURLOPT_POSTFIELDS, _postData.c_str());
	}
	else 
		curl_easy_setopt(handle, CURLOPT_HTTPGET, 1); 
	
	if(_proxy != "") curl_easy_setopt(handle, CURLOPT_PROXY, _proxy.c_str());
	else             curl_easy_setopt(handle, CURLOPT_PROXY, 0);

	if(_postHeader != 0) curl_easy_setopt(handle, CURLOPT_HTTPHEADER, header);
	else                 curl_easy_setopt(handle, CURLOPT_HTTPHEADER, 0);
	
	result = curl_easy_perform(handle);

	curl_slist_free_all(header);
	header = NULL;

	curl_easy_reset(handle);
}

void C_Curl::DownloadFile(string _url, string _pathFile, ios_base::openmode _mode)
{
	Request(_url);

	file.open(_pathFile.c_str(), _mode);
	file << GetSourcePage();
	file.close();
}

void C_Curl::AddHeader(string _header)
{
	header = curl_slist_append(header, _header.c_str());
}

void C_Curl::ClearCookies()
{
	fstream file;
	file.open("cookies.txt", ios::out | ios::trunc);
	file.close();
}

int C_Curl::Split(string _input, string _output[], string _delimiter)
{
	int
		counter  = 0,
		position = 0;

	_input.append(_delimiter);

	while((position = _input.find(_delimiter)) != string::npos)
	{
		if(position == 0) _input.erase(0, 1);
		else
		{
			_output[counter] = _input.substr(0, position);
			_input.erase(0, position + 1);
			counter++;
		}
	}

	return counter;
}

string C_Curl::Escape(string _data)
{
	bufferChar = curl_easy_escape(handle, _data.c_str(), _data.size());
	_data = string(bufferChar);
	curl_free(bufferChar);

	return _data;
}

string C_Curl::Unescape(string _data)
{
	bufferChar = curl_easy_unescape(handle, _data.c_str(), _data.size(), NULL);
	_data = string(bufferChar);
	curl_free(bufferChar);

	return _data;
}

string C_Curl::GetSourcePage(int _position1, int _position2)
{
	if(_position1 == _position2) return sourcePage;
	else                         return sourcePage.substr(_position1, _position2);
}

////////////////////////////////////////////////////////////////////////////////////////////////// Private methods
int C_Curl::Writer(char *_ptr, size_t _size, size_t _nmemb, string *_data)  
{ 
  int result = 0;

  if(_data != NULL)  
  { 
    _data->append(_ptr, _size * _nmemb); 
    result = _size * _nmemb;  
  } 

  return result;  
}