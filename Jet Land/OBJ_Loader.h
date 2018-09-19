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
    enum LINE_TYPE;

    LINE_TYPE GetLineType(std::wstring * line);
}

VOID LoadMeshObjFromFile(std::wstring * filename, VERTEX_FORMAT * vertex_mode,
    VOID ** vertex_buffer_data, UINT * vertex_count, UINT * vertex_size,
    UINT ** index_buffer_data, UINT * index_count);


