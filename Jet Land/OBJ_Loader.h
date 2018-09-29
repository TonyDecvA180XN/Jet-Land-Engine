/**
 * \file This file contains functions used for managing .obj files on game.
*/

#pragma once


#include <fstream>
#include <string>
#include <sstream>
#include "VertexMode.h"


namespace OBJ
{
	enum LINE_TYPE
	{
		LINE_TYPE_COMMENT,
		LINE_TYPE_VERTEX_POSITION,
		LINE_TYPE_VERTEX_TEXCOORDS,
		LINE_TYPE_VERTEX_NORMAL,
		LINE_TYPE_FACE,
		LINE_TYPE_OBJECT,
		LINE_TYPE_GROUP,
		LINE_TYPE_SMOOTHGROUP,
		LINE_TYPE_OTHER
	};
    LINE_TYPE GetLineType(std::wstring * line);
}

VOID LoadMeshObjFromFile(std::string * filename, VERTEX_FORMAT * vertex_mode,
    VOID ** vertex_buffer_data, UINT * vertex_count, UINT * vertex_size,
    UINT ** index_buffer_data, UINT * index_count);


