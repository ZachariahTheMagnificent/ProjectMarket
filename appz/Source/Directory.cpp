#include "Directory.h"
/****************************************************************************/
/*!
\file Directory.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class that gives access to the content in a list of similar files located in the same folder
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
Default constructor
\param filepath
		the location of the folder the files would have
\param searchpattern
		the type of files to be searched for
\param innitDrawings
		a bool to whether or not to read and store the information from the files after finding them
*/
/****************************************************************************/
Directory::Directory(const wchar_t* filepath, const wchar_t* searchpattern, bool innitDrawings)
	:
filepath(filepath),
filetype(searchpattern)
{
	HANDLE hFind;
	WIN32_FIND_DATA FindData;
	searchpath.append(filepath);
	searchpath.append(searchpattern);
	hFind = FindFirstFile((searchpath.c_str()), &FindData);
	do
	{
		std::wstring buffer; //= filepath;
		buffer += FindData.cFileName;
		FileList.push_back(buffer);
	}while (FindNextFile(hFind, &FindData) > 0);
	if(innitDrawings)
	{
		InnitDrawings();
	}
}
/****************************************************************************/
/*!
\brief
Default destructor
*/
/****************************************************************************/
Directory::~Directory()
{
	if(drawings.size())
	{
		SaveDrawings();
	}
}
/****************************************************************************/
/*!
\brief
Stores the changes we have made to the files
*/
/****************************************************************************/
void Directory::SaveDrawings()
{
	 std::ofstream savedata;// file to write to
	 for(int i = 0; i < size();++i )
	 {
		savedata.open(getname(i));
		savedata.write(&drawings[i].front(), sizeof(char) * drawings[i].size());
		savedata.close();
	 }
}
/****************************************************************************/
/*!
\brief
Returns the number of file the directory has
*/
/****************************************************************************/
int Directory::size() const
{
	return FileList.size();
}
/****************************************************************************/
/*!
\brief
Updates the directory
*/
/****************************************************************************/
bool Directory::update()
{
	FileList.clear();

	HANDLE hFind;
	WIN32_FIND_DATA FindData;
	hFind = FindFirstFile((searchpath.c_str()), &FindData);
	do
	{
		std::wstring buffer = FindData.cFileName;
		FileList.push_back(buffer);
	}while (FindNextFile(hFind, &FindData) > 0);
	InnitDrawings();
	return true;
}
/****************************************************************************/
/*!
\brief
returns the path used to find the files
*/
/****************************************************************************/
std::wstring Directory::path() const
{
	return filepath;
}
/****************************************************************************/
/*!
\brief
An operator overload for retrieving the files teh directory has
*/
/****************************************************************************/
std::wstring Directory::operator[](int index)
{
	return FileList[index];
}
/****************************************************************************/
/*!
\brief
Returns the name of a file
\param index
		the index of the file in the array
*/
/****************************************************************************/
std::wstring Directory::getname(int index)
{
	std::wstring buffer = filepath + FileList[index];
	return buffer;
}
/****************************************************************************/
/*!
\brief
reads from the files found and stores their values
*/
/****************************************************************************/
void Directory::InnitDrawings()
{
	 std::ifstream drawdata;//get input/stuff from file
	 for(int i = 0; i < size();++i )
	 {
		 std::string buffer;
		 drawdata.open(getname(i));
		 while(!drawdata.eof())//EOF
		 {
			 buffer.push_back(drawdata.get());
		 }
		 drawdata.close();
		 //buffer.pop_back();// do this to pop the null ascii
		 drawings.push_back(buffer);
	 }
}
/****************************************************************************/
/*!
\brief
gets the information in a file with a specified name
\param filename
		the name of the file
*/
/****************************************************************************/
std::string* Directory::getstring(const wchar_t* filename)
{
	int index = 0;
	std::wstring extension = filetype;
	extension.erase(0, 1);
	std::wstring name = filename;
	name += extension;
	while(wcscmp(name.c_str(), FileList[index].c_str()))
	{
		index++;
	}
	return &drawings[index];
}