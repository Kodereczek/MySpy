// Filename: class.register.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Register::C_Register()
{
	// Public fields

	// Private fields

	// Initialization
	//RegOpenKeyEx(HKEY_CURRENT_USER, _nameKey.c_str(), 0, KEY_READ, &hKey);
}

C_Register::~C_Register()
{
	RegCloseKey(hKey);
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
string C_Register::ReadValue(string _nameValue, DWORD _typeValue)
{
	RegQueryValueEx(hKey, _nameValue.c_str(), 0, &_typeValue, (LPBYTE)bufferChar, &bufferSize);

	return string(bufferChar);
}

////////////////////////////////////////////////////////////////////////////////////////////////// Private methods