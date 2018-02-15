// Filename: class.register.h
// Author:   Patryk Po³eæ

#pragma once

class C_Register
{
	// Constructor and destructor
	public:
		C_Register();
		~C_Register();

	// Public methods
	public:

	// Private methods
	private:

	// Public fields
	public:
		string ReadValue(string _nameValue, DWORD _typeValue);

	// Private fields
	private:
		HKEY 
			hKey;
		
		CHAR 
			bufferChar[256];

		DWORD 
			bufferSize,
			typeValue;
};