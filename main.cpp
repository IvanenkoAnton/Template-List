/*******************************************************************************
	Created by Anton Ivanenko,April 2017
	OOP Lab
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

#include "List.h"
#include "CppFile.h"

//CreateObject
List<CppFile>* DownloadFromFile(std::string Filename);
CppFile CreateFromString(std::string CurString);
void DeleteElemByDate(std::string date, List<CppFile> &catalog, List<CppFile> &bin);
void ChangeFileName(std::string name,std::string newname, List<CppFile> &catalog);
void DeleteFile(std::string name, List<CppFile> &catalog, List<CppFile> &bin);
void ReestablishFile(std::string name, List<CppFile> &catalog, List<CppFile> &bin);

int main() {

	List<CppFile> *Catalog, *Bin = new List<CppFile>();
	char *Menu[] = { "1.Show Catalog","2.Show Bin","3.Delete File","4.Reestablish File","5.Change File Name","6.Delete By Date","7.Exit" };

	Catalog = DownloadFromFile("infofiles.csv");


	while (true) {
		int num;
		for (int i = 0; i < 7; i++) {
			std::cout << Menu[i] << std::endl;
		}
		std::cout << "Choose: ";
		std::cin >> num;
		switch (num) {
		case 1: {
			std::cout << std::endl;
			std::cout <<"Number of Files: " << Catalog->size() << std::endl;
			Catalog->Print();
			break;
		}
		case 2: {
			std::cout << std::endl;
			std::cout << "Number of Files: " << Bin->size() << std::endl;
			Bin->Print();
			break;
		}
		case 3: {
			std::string Name;
			std::cout << "Enter File Name: ";
			std::cin >> Name;
			DeleteFile(Name, *Catalog, *Bin);
			break;
		}
		case 4: {
			std::string Name;
			std::cout << "Enter File Name: ";
			std::cin >> Name;
			ReestablishFile(Name, *Catalog, *Bin);
			break;
		}
		case 5: {
			std::string Name,NewName;
			std::cout << "Enter File Name: ";
			std::cin >> Name;
			std::cout << "Enter New File Name: ";
			std::cin >> NewName;
			ChangeFileName(Name,NewName, *Catalog);
			break;
		}
		case 6: {
			std::string Date;
			std::cout << "Enter Date YYYY/MM/DD: ";
			std::cin >> Date;
			DeleteElemByDate(Date,*Catalog, *Bin);
			break;
		}
		case 7: {
			exit(0);
		}
		}
	}
	system("pause");
	return 0;
}

List<CppFile>* DownloadFromFile(std::string Filename) {
	List<CppFile> *Temp = new List<CppFile>();
	std::ifstream Info(Filename);
	if (Info.is_open()) {
		while (!Info.eof()) {
			char buf[255];
			std::string *Buffer;
			Buffer = NULL;
			Info.getline(buf, 255);
			Buffer = new std::string(buf);
			if (!Buffer->empty())Temp->push_front(CreateFromString(*Buffer));
			delete Buffer;
		}
	}
	else {
		std::cout << "Cannot open file: " << Filename << std::endl;
	}
	return Temp;
}


CppFile CreateFromString(std::string CurString) {
	std::string Word, filename, creation_date;
	int k = 0, size;
	CppFile* Temp = NULL;

	if (!CurString.empty()) {
		for (int i = 0; i < CurString.size(); i++) {
			Word.clear();
			while ((i < CurString.size()) && (CurString[i] != ' ') && (CurString[i] != ';')) {
				Word.push_back(CurString[i]);
				i++;
			}

			if (!Word.empty()) {
				switch (k) {
				case 0: {
					filename = Word;
					break;
				}
				case 1: {
					creation_date = Word;
					break;
				}
				case 2: {
					size = atoi(Word.c_str());
					break;
				}
				default: {
					std::cout << "Error. Many parametrs" << std::endl;
					system("pause");
					exit(1);
				}
				}
				k++;
			}
			else {
				std::cout << "Error intizialisation!" << std::endl;
				system("pause");
				exit(1);
			}
		}
	}
	return *(new CppFile(filename.c_str(), creation_date.c_str() , size));
}

void DeleteFile(std::string name, List<CppFile> &catalog, List<CppFile> &bin) {
	List<CppFile>::iterator iter = catalog.begin();
	while (iter != catalog.end()) {
		if (!strcmp((*iter).data.GetFileName(), name.c_str())) {
			catalog.splice(iter, bin);
			return;
		}
		iter++;
	}
	std::cout << "File not found" << std::endl;
}

void ReestablishFile(std::string name, List<CppFile> &catalog, List<CppFile> &bin) {
	List<CppFile>::iterator iter = bin.begin();
	while (iter != bin.end()) {
		if (!strcmp((*iter).data.GetFileName(), name.c_str())) {
			bin.splice(iter, catalog);
			return;
		}
		iter++;
	}
	std::cout << "File not found" << std::endl;
}

void ChangeFileName(std::string name,std::string newname, List<CppFile> &catalog) {
	List<CppFile>::iterator iter = catalog.begin();
	while (iter != catalog.end()) {
		if (!strcmp((*iter).data.GetFileName(), name.c_str())) {
			(*iter).data.SetFileName(newname.c_str());
			return;
		}
		iter++;
	}
	std::cout << "File not found" << std::endl;
}

void DeleteElemByDate(std::string date, List<CppFile> &catalog, List<CppFile> &bin) {
	List<CppFile>::iterator iter = catalog.begin(),tmp;
	while (iter != catalog.end()) {
		if (strcmp(date.c_str(), (*iter).data.GetCreationDate()) > 0){
			tmp = iter;
			tmp++;
			catalog.splice(iter, bin);
			iter = tmp;

		}
		else {
			iter++;
		}
	}
}



