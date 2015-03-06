#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <vector>
#include <map>
#include "Vertex.h"
#include "Vector3.h"
#include "Directory.h"
/****************************************************************************/
/*!
\file LoadObj.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to load OBJs
*/
/****************************************************************************/

/****************************************************************************/
/*!
Class ObjLoader:
\brief
used to load OBJs
*/
/****************************************************************************/
class ObjLoader
{
public:
	static bool LoadOBJ(
		std::wstring file_path,
		std::vector<Vertex>& out_vertices
	);
};

#endif