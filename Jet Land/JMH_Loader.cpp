#include "JMH_Loader.h"

VOID LoadMeshJMHFromFile(std::string * filename, VFORMAT * vertex_mode,
	VOID ** vertex_buffer_data, UINT * vertex_count, UINT * vertex_size,
	UINT ** index_buffer_data, UINT * index_count)
{
	std::fstream input(*filename, std::fstream::in | std::fstream::binary);
	if (input.fail()) { return; }

	char header[5] = {'\0', '\0', '\0', '\0', '\0'};
	input.read(header, 4);
	if (strcmp(header, "JMH0") != 0) { return; }

	input.read((char *)vertex_count, sizeof UINT);

	BYTE componentChecker = 0;
	input.read((char *)&componentChecker, 1);
	if (componentChecker)
	{
		*vertex_mode |= PositionMask;
		*vertex_size += 3 * sizeof FLOAT;
	}
	input.read((char *)&componentChecker, 1);
	if (componentChecker)
	{
		*vertex_mode |= ColorMask;
		*vertex_size += 4 * sizeof FLOAT;
	}
	input.read((char *)&componentChecker, 1);
	if (componentChecker)
	{
		*vertex_mode |= TexcoordsMask;
		*vertex_size += 2 * sizeof FLOAT;
	}
	input.read((char *)&componentChecker, 1);
	if (componentChecker)
	{
		*vertex_mode |= NormalsMask;
		*vertex_size += 3 * sizeof FLOAT;
	}

	*vertex_buffer_data = new BYTE[*vertex_size * *vertex_count];
	input.read((char *)*vertex_buffer_data, *vertex_size * *vertex_count);

	input.read((char *)index_count, sizeof UINT);

	*index_buffer_data = new UINT[*index_count];
	input.read((char *)*index_buffer_data, *index_count * sizeof UINT);

	input.close();

	return;
}