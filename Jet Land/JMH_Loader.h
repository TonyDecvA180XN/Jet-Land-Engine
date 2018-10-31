#pragma once

#include "VFormat.h"

VOID LoadMeshJMHFromFile(std::string * filename, VFORMAT * vertex_mode,
	VOID ** vertex_buffer_data, UINT * vertex_count, UINT * vertex_size,
	UINT ** index_buffer_data, UINT * index_count);
