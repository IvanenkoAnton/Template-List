/*******************************************************************************
	Created by Anton Ivanenko,April 2017
	OOP Lab
*******************************************************************************/

#pragma once
#include <iostream>
class CppFile
{
	char* _filename;
	char* _creation_date;
	int _size;
	CppFile & operator = (CppFile &obj) {};//no copy
public:
	CppFile() :_filename(NULL), _creation_date(NULL), _size(0) {};
	CppFile(const char* filename,const char* _creation_date, int size);
	CppFile(const CppFile &obj);
	void SetFileName(const char *_newname);
	char* GetFileName();
	char* GetCreationDate();
	bool operator == (const CppFile &obj) { return (!strcmp(this->_filename, obj._filename) && !strcmp(this->_creation_date, obj._creation_date) && (this->_size == obj._size)); }
	bool operator != (const CppFile &obj) { return !(*this == obj); }
	friend std::ostream& operator << (std::ostream & stream, CppFile &obj);
	~CppFile();
};

