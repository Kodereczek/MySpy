// Filename: class.scrambler.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Scrambler::C_Scrambler()
{
	// Private fields
	data = NULL;
	hash = NULL;
}

C_Scrambler::~C_Scrambler()
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
string C_Scrambler::Random()
{
	srand((int)time(0));
	bufferStringStream.str("");
	bufferStringStream << (rand() % 99999) + 10000;
	
	return Hash(bufferStringStream.str(), MD5);
}

string C_Scrambler::Hash(string _data, DWORD _hashType)
{
	bufferStringStream.str("");
	
	CryptAcquireContext(&hCryptProv, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
	CryptCreateHash(hCryptProv, _hashType, 0, 0, &phHash);
	data = new BYTE[_data.size() + 1];
	memcpy(data, _data.c_str(), _data.size() + 1);
	CryptHashData(phHash, data, _data.size(), 0);
	CryptGetHashParam(phHash, HP_HASHSIZE, (BYTE*)&pbData, &pbwDataLen, 0);
	hash = new BYTE[pbData];
	CryptGetHashParam(phHash, HP_HASHVAL, hash, &pbData, 0);
	
	for(int a = 0; a < 16; a++)
	{
		bufferStringStream << hex << setfill('0') << setw(2) << (int)hash[a];
	}

	delete[] data;
	delete[] hash;

	CryptDestroyHash(phHash);
	CryptReleaseContext(hCryptProv, 0);

	return bufferStringStream.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////// Private methods