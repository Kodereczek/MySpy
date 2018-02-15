// Filename: class.file.h
// Author:   Patryk Po³eæ

#pragma once

class C_File
{
	// Constructor and destructor
	public:
		C_File();
		~C_File();

	// Public methods
	public:
		bool Open(string _pathFile, ios_base::openmode _mode);
		void Close();

	  string GetData();
	    void GetData(string &_data);
		void GetDataToLine(string _data[], int &_amountLine, int _maxLine = 0);
	   
		void Save();

		void SetPointnerAt(ios_base::seekdir _option, streamoff _offset = 0);
   streampos ReturnPositionPointner();
         int Size();
	    bool IsEnd();

	// Private methods
	private:
		
	// Public fields
	public:
		fstream 
			file;

	// Private fields
	private:
		string
			data,
			line;

		int
			size;
};