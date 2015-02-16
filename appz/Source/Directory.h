#ifndef _DIRECTORY_H
#define _DIRECTORY_H

#include <windows.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

class Directory
{
private:
	std::vector<std::wstring> FileList;
	std::vector<std::string> drawings;
	const std::wstring filepath;
	const std::wstring filetype;
	std::wstring searchpath;
	void InnitDrawings();
	std::wstring getname(int index);
public:
	std::string* getstring(const wchar_t* filename);
	Directory(const wchar_t* filepath, const wchar_t* searchpattern, bool innitDrawings = false);
	~Directory();
	int size() const;
	bool update();
	std::wstring path() const;
	std::wstring operator[](int index);
	void SaveDrawings();
};

#endif