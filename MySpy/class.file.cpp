// Filename: class.file.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_File::C_File()
{
	// Private fields
	data.clear();
	line.clear();

	size = 0;
}

C_File::~C_File()
{
	Close();
}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
bool C_File::Open(string _pathFile, ios_base::openmode _mode)
{
	file.open(_pathFile.c_str(), _mode);
	if(file.good()) return true;
	else            return false;
}

void C_File::Close()
{
	data.clear();
	line.clear();

	size = 0;

	if(file.is_open()) file.close();
}

string C_File::GetData()
{
	data.clear();

	SetPointnerAt(ios::beg);

	while(!file.eof())
    {
        getline(file, line);
		data += line + "\n";
    }

	return data;
}

void C_File::GetData(string &_data)
{
	_data.clear();

	SetPointnerAt(ios::beg);

	while(!file.eof())
    {
        getline(file, line);
		_data += line + "\n";
    }
}

void C_File::GetDataToLine(string _data[], int &_amountLine, int _maxLine)
{
	_amountLine = 0;

	SetPointnerAt(ios::beg);

	while(!file.eof())
    {
		if(_maxLine != 0 && _amountLine == _maxLine) return;

        getline(file, line);
		_data[_amountLine] = line;

		_amountLine++;
    }
}

void C_File::Save()
{
	file.flush();
}

void C_File::SetPointnerAt(ios_base::seekdir _option, streamoff _offset)
{
	file.seekg(_offset, _option);
}

streampos C_File::ReturnPositionPointner()
{
	return file.tellg();
}

int C_File::Size()
{
	file.seekg(0, ios_base::end);
	size = (int)ReturnPositionPointner();
	file.seekg(0, ios_base::beg);

	return size;
}

bool C_File::IsEnd()
{
	if(!file.eof()) return false;
	else            return true;
}