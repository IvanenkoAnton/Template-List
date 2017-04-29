/*******************************************************************************
	Created by Anton Ivanenko,April 2017
	OOP Lab
*******************************************************************************/


#include "CppFile.h"
#include <string.h>


CppFile::CppFile(const char* filename,const char* creation_date, int size){
	if (filename && creation_date) {
		_filename = new char[strlen(filename) + 1];
		strcpy(_filename, filename);
		_creation_date = new char[strlen(creation_date) + 1];
		strcpy(_creation_date, creation_date);
		_size = size;
	}
	else {
		abort();
	}
}

CppFile::CppFile(const CppFile &obj) {
	_filename = new char[strlen(obj._filename) + 1];
	strcpy(_filename, obj._filename);
	_creation_date = new char[strlen(obj._creation_date) + 1];
	strcpy(_creation_date, obj._creation_date);
	_size = obj._size;
}


CppFile::~CppFile(){
	if (_filename) delete[] _filename;
	if (_creation_date)delete[] _creation_date;
}

void CppFile::SetFileName(const char *_newname) {
	if (_newname) {
		delete _filename;
		_filename = new char[strlen(_newname) + 1];
		strcpy(_filename, _newname);
	}
	else {
		abort();
	}
}

char* CppFile::GetFileName() {
	char *tmp = new char[strlen(_filename) + 1];
	strcpy(tmp, _filename);
	return tmp;
}

char* CppFile::GetCreationDate() {
	char *tmp = new char[strlen(_creation_date) + 1];
	strcpy(tmp, _creation_date);
	return tmp;
}

std::ostream& operator << (std::ostream & stream, CppFile &obj) {
	std::cout << "Filename: " << obj._filename << std::endl;
	std::cout << "Creation date: " << obj._creation_date << std::endl;
	std::cout << "Size: " << obj._size << std::endl;

	return stream;
}
