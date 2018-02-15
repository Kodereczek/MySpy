// Filename: class.z.h
// Author:   Patryk Po³eæ

#pragma once

enum HashType
{
    MD2 = CALG_MD2,
    MD5 = CALG_MD5,
    SHA = CALG_SHA
};

class C_Scrambler
{
	// Constructor and destructor
	public:
		C_Scrambler();
		~C_Scrambler();

	// Public methods
	public:
		string Random();
		string Hash(string _data, DWORD _hashType);

	// Private methods
	private:

	// Public fields
	public:

	// Private fields
	private:
		HCRYPTPROV 
			hCryptProv;

		HCRYPTHASH 
			phHash;

		DWORD
			pbData,
			pbwDataLen;

		BYTE
			*data,
			*hash;

		stringstream
			bufferStringStream;

		int
			random;
};