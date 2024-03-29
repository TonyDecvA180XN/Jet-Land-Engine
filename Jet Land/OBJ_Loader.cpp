#include "OBJ_Loader.h"

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
	LINE_TYPE GetLineType(std::string * line)
	{
		if (line->_Starts_with("#"))
		{
			return LINE_TYPE_COMMENT;
		}
		if (line->_Starts_with("v "))
		{
			return LINE_TYPE_VERTEX_POSITION;
		}
		if (line->_Starts_with("vt"))
		{
			return LINE_TYPE_VERTEX_TEXCOORDS;
		}
		if (line->_Starts_with("vn"))
		{
			return LINE_TYPE_VERTEX_NORMAL;
		}
		if (line->_Starts_with("f"))
		{
			return LINE_TYPE_FACE;
		}
		if (line->_Starts_with("o"))
		{
			return LINE_TYPE_OBJECT;
		}
		if (line->_Starts_with("g"))
		{
			return LINE_TYPE_GROUP;
		}
		if (line->_Starts_with("s"))
		{
			return LINE_TYPE_SMOOTHGROUP;
		}
		else
		{
			return LINE_TYPE_OTHER;
		}
	}
}



//VOID LoadMeshObjFromFile(std::string * filename, VFORMAT * vertex_mode,
//    VOID ** vertex_buffer_data, UINT * vertex_count, UINT * vertex_size,
//    UINT ** index_buffer_data, UINT * index_count)
//{
//    std::wfstream file_reader;
//
//    file_reader.open(*filename, std::wfstream::in);
//    if (file_reader.fail())
//    {
//        return;
//    }
//    // first stage
//    // create counts for components
//    UINT positionsCount = 0,
//        texcoordsCount = 0,
//        normalsCount = 0,
//        faceCount = 0;
//    while (!file_reader.eof())
//    {
//        std::wstring line;
//        std::getline(file_reader, line);
//        switch (OBJ::GetLineType(&line))
//        {
//        case OBJ::LINE_TYPE_COMMENT:
//        {
//            break;
//        }
//        case OBJ::LINE_TYPE_VERTEX_POSITION:
//        {
//            positionsCount++;
//            break;
//        }
//        case OBJ::LINE_TYPE_VERTEX_TEXCOORDS:
//        {
//            texcoordsCount++;
//            break;
//        }
//        case OBJ::LINE_TYPE_VERTEX_NORMAL:
//        {
//            normalsCount++;
//            break;
//        }
//        case OBJ::LINE_TYPE_FACE:
//            faceCount++;
//            break;
//        // ignore all the rest
//        default:
//            break;
//        }
//    }
//    file_reader.close();
//    // second stage
//    // destingush the type of Vertex Mode
//    if (texcoordsCount > 0 && normalsCount > 0)
//    {
//        *vertex_mode = VERTEX_FORMAT_POSITION_TEXCOORDS_NORMAL;
//    }
//    else if (texcoordsCount > 0)
//    {
//        *vertex_mode = VERTEX_FORMAT_POSITION_TEXCOORDS;
//    }
//    else if (normalsCount > 0)
//    {
//        *vertex_mode = VERTEX_FORMAT_POSITION_NORMAL;
//    }
//    else
//    {
//        *vertex_mode = VERTEX_FORMAT_POSITION;
//    }
//
//    // create temp sample stores
//    VertexComponent::Position                * positions;
//    VertexComponent::Texcoords               * texcoords;
//    VertexComponent::Normal                  * normals;
//    struct Face { UINT p[3], t[3], n[3]; }   *faces;
//
//    positions = new VertexComponent::Position[positionsCount];
//    //if (*vertex_mode & VertexComponent::HaveTexcoords)
//    texcoords = new VertexComponent::Texcoords[texcoordsCount];
//    //if (*vertex_mode & VertexComponent::HaveNormal)
//    normals = new VertexComponent::Normal[normalsCount];
//    faces = new Face[faceCount];
//
//    UINT iPosition = 0;
//    UINT iTexcoords = 0;
//    UINT iNormal = 0;
//    UINT iFace = 0;
//
//    //read data from file
//    file_reader.open(*filename, std::wfstream::in);
//    if (file_reader.fail())
//    {
//        return;
//    }
//    while (!file_reader.eof())
//    {
//        std::wstring line;
//        std::getline(file_reader, line);
//        wchar_t padding;
//        switch (OBJ::GetLineType(&line))
//        {
//        case OBJ::LINE_TYPE_VERTEX_POSITION:
//        {
//            std::wstringstream lineStream(line);
//            lineStream >> padding >> positions[iPosition].x >> positions[iPosition].y >> positions[iPosition].z;
//            iPosition++;
//            break;
//        }
//        case OBJ::LINE_TYPE_VERTEX_TEXCOORDS:
//        {
//            std::wstringstream lineStream(line);
//            lineStream >> padding >> padding >> texcoords[iTexcoords].x >> texcoords[iTexcoords].y;
//            iTexcoords++;
//            break;
//        }
//        case OBJ::LINE_TYPE_VERTEX_NORMAL:
//        {
//            std::wstringstream lineStream(line);
//            lineStream >> padding >> padding >> normals[iNormal].x >> normals[iNormal].y >> normals[iNormal].z;
//            iNormal++;
//            break;
//        }
//        case OBJ::LINE_TYPE_FACE:
//        {
//            std::wstringstream lineStream(line);
//            lineStream >> padding;
//
//            for (UINT i = 0; i < 3; i++)
//            {
//                lineStream >> faces[iFace].p[i];
//                if (*vertex_mode && VertexComponent::HaveTexcoords && VertexComponent::HaveNormal)
//                    lineStream >> padding >> faces[iFace].t[i] >> padding >> faces[iFace].n[i];
//                else if (*vertex_mode && VertexComponent::HaveTexcoords)
//                    lineStream >> padding >> faces[iFace].t[i];
//                else if (*vertex_mode && VertexComponent::HaveNormal)
//                    lineStream >> padding >> padding >> faces[iFace].n[i];
//            }
//
//            iFace++;
//            break;
//        }
//        // ignore all the rest
//        default:
//            break;
//        }
//    }
//    file_reader.close();
//    // third stage
//
//    VOID * vertex_buffer = NULL;
//    UINT * index_buffer = NULL;
//
//    index_buffer = new UINT[faceCount * 3];
//    *index_count = faceCount * 3;
//    for (UINT iI = 0; iI < faceCount * 3; iI++)
//    {
//        index_buffer[iI] = iI;
//    }
//    switch (*vertex_mode)
//    {
//    case VERTEX_FORMAT_POSITION:
//    {
//        vertex_buffer = new Vertex_P[faceCount * 3];
//        *vertex_count = faceCount * 3;
//        *vertex_size = sizeof Vertex_P;
//        for (UINT iF = 0; iF < faceCount; iF++)
//        {
//            for (UINT iV = 0; iV < 3; iV++)
//            {
//                ((Vertex_P *)vertex_buffer)[iF * 3 + iV].position.x = positions[faces[iF].p[2 - iV] - 1].x;
//                ((Vertex_P *)vertex_buffer)[iF * 3 + iV].position.y = positions[faces[iF].p[2 - iV] - 1].y;
//                ((Vertex_P *)vertex_buffer)[iF * 3 + iV].position.z = -positions[faces[iF].p[2 - iV] - 1].z;
//            }
//        }
//        break;
//    }
//    case VERTEX_FORMAT_POSITION_TEXCOORDS:
//    {
//        vertex_buffer = new Vertex_PT[faceCount * 3];
//        *vertex_count = faceCount * 3;
//        *vertex_size = sizeof Vertex_PT;
//        for (UINT iF = 0; iF < faceCount; iF++)
//        {
//            for (UINT iV = 0; iV < 3; iV++)
//            {
//                ((Vertex_PT *)vertex_buffer)[iF * 3 + iV].position.x = positions[faces[iF].p[2 - iV] - 1].x;
//                ((Vertex_PT *)vertex_buffer)[iF * 3 + iV].position.y = positions[faces[iF].p[2 - iV] - 1].y;
//                ((Vertex_PT *)vertex_buffer)[iF * 3 + iV].position.z = -positions[faces[iF].p[2 - iV] - 1].z;
//
//                ((Vertex_PT *)vertex_buffer)[iF * 3 + iV].texcoords.x = texcoords[faces[iF].t[2 - iV] - 1].x;
//                ((Vertex_PT *)vertex_buffer)[iF * 3 + iV].texcoords.y = 1.0f - texcoords[faces[iF].t[2 - iV] - 1].y;
//            }
//        }
//        break;
//    }
//    case VERTEX_FORMAT_POSITION_NORMAL:
//    {
//        vertex_buffer = new Vertex_PN[faceCount * 3];
//        *vertex_count = faceCount * 3;
//        *vertex_size = sizeof Vertex_PN;
//        for (UINT iF = 0; iF < faceCount; iF++)
//        {
//            for (UINT iV = 0; iV < 3; iV++)
//            {
//                ((Vertex_PN *)vertex_buffer)[iF * 3 + iV].position.x = positions[faces[iF].p[2 - iV] - 1].x;
//                ((Vertex_PN *)vertex_buffer)[iF * 3 + iV].position.y = positions[faces[iF].p[2 - iV] - 1].y;
//                ((Vertex_PN *)vertex_buffer)[iF * 3 + iV].position.z = -positions[faces[iF].p[2 - iV] - 1].z;
//
//                ((Vertex_PN *)vertex_buffer)[iF * 3 + iV].normal.x = normals[faces[iF].n[2 - iV] - 1].x;
//                ((Vertex_PN *)vertex_buffer)[iF * 3 + iV].normal.y = normals[faces[iF].n[2 - iV] - 1].y;
//                ((Vertex_PN *)vertex_buffer)[iF * 3 + iV].normal.z = normals[faces[iF].n[2 - iV] - 1].z;
//            }
//        }
//        break;
//    }
//    case VERTEX_FORMAT_POSITION_TEXCOORDS_NORMAL:
//    {
//        vertex_buffer = new Vertex_PTN[faceCount * 3];
//        *vertex_count = faceCount * 3;
//        *vertex_size = sizeof Vertex_PTN;
//        for (UINT iF = 0; iF < faceCount; iF++)
//        {
//            for (UINT iV = 0; iV < 3; iV++)
//            {
//                ((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].position.x = positions[faces[iF].p[2 - iV] - 1].x;
//                ((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].position.y = positions[faces[iF].p[2 - iV] - 1].y;
//                ((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].position.z = -positions[faces[iF].p[2 - iV] - 1].z;
//
//                ((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].texcoords.x = texcoords[faces[iF].t[2 - iV] - 1].x;
//                ((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].texcoords.y = 1.0f - texcoords[faces[iF].t[2 - iV] - 1].y;
//
//                ((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].normal.x = normals[faces[iF].n[2 - iV] - 1].x;
//                ((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].normal.y = normals[faces[iF].n[2 - iV] - 1].y;
//                ((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].normal.z = -normals[faces[iF].n[2 - iV] - 1].z;
//            }
//        }
//        break;
//    }
//    default:
//        break;
//    }
//
//    // cleanup
//    delete[] positions;
//    delete[] texcoords;
//    delete[] normals;
//    delete[] faces;
//    positions = NULL;
//    texcoords = NULL;
//    normals = NULL;
//    faces = NULL;
//
//    // return
//    *vertex_buffer_data = vertex_buffer;
//    *index_buffer_data = index_buffer;
//}

VOID LoadMeshOBJFromFile(std::string filename, VFORMAT * vertex_mode,
	VOID ** vertex_buffer_data, UINT * vertex_count, UINT * vertex_size,
	UINT ** index_buffer_data, UINT * index_count)
{
	std::fstream file(filename, std::fstream::in);
	// first stage
	// create counts for components
	UINT positionsCount = 0,
		texcoordsCount = 0,
		normalsCount = 0,
		faceCount = 0;
	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		switch (OBJ::GetLineType(&line))
		{
		case OBJ::LINE_TYPE_COMMENT:
		{
			break;
		}
		case OBJ::LINE_TYPE_VERTEX_POSITION:
		{
			positionsCount++;
			break;
		}
		case OBJ::LINE_TYPE_VERTEX_TEXCOORDS:
		{
			texcoordsCount++;
			break;
		}
		case OBJ::LINE_TYPE_VERTEX_NORMAL:
		{
			normalsCount++;
			break;
		}
		case OBJ::LINE_TYPE_FACE:
			faceCount++;
			break;
			// ignore all the rest
		default:
			break;
		}
	}
	// second stage
	// destingush the type of Vertex Mode
	*vertex_mode = 0;
	if (positionsCount > 0)
	{
		*vertex_mode |= PositionMask;
	}
	if (texcoordsCount > 0)
	{
		*vertex_mode |= TexcoordsMask;
	}
	if (normalsCount > 0)
	{
		*vertex_mode |= NormalsMask;
	}


	// create temp sample stores
	struct Position { FLOAT x; FLOAT y; FLOAT z; } *positions;
	struct Texcoords { FLOAT x; FLOAT y; }         *texcoords;
	struct Normal { FLOAT x; FLOAT y; FLOAT z; }   *normals;
	struct Face { UINT p[3], t[3], n[3]; }         *faces;

	positions = new Position[positionsCount];
	//if (*vertex_mode & VertexComponent::HaveTexcoords)
	texcoords = new Texcoords[texcoordsCount];
	//if (*vertex_mode & VertexComponent::HaveNormal)
	normals = new Normal[normalsCount];
	faces = new Face[faceCount];

	UINT iPosition = 0;
	UINT iTexcoords = 0;
	UINT iNormal = 0;
	UINT iFace = 0;

	//read data from file
	file.clear(); // reset eof flag to access the stream again
	file.seekg(0, std::ios::beg); // go back to the beginning

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		char padding;
		switch (OBJ::GetLineType(&line))
		{
		case OBJ::LINE_TYPE_VERTEX_POSITION:
		{
			std::stringstream lineStream(line);
			lineStream >> padding >> positions[iPosition].x >> positions[iPosition].y >> positions[iPosition].z;
			iPosition++;
			break;
		}
		case OBJ::LINE_TYPE_VERTEX_TEXCOORDS:
		{
			std::stringstream lineStream(line);
			lineStream >> padding >> padding >> texcoords[iTexcoords].x >> texcoords[iTexcoords].y;
			iTexcoords++;
			break;
		}
		case OBJ::LINE_TYPE_VERTEX_NORMAL:
		{
			std::stringstream lineStream(line);
			lineStream >> padding >> padding >> normals[iNormal].x >> normals[iNormal].y >> normals[iNormal].z;
			iNormal++;
			break;
		}
		case OBJ::LINE_TYPE_FACE:
		{
			std::stringstream lineStream(line);
			lineStream >> padding;

			for (UINT i = 0; i < 3; i++)
			{
				lineStream >> faces[iFace].p[i];
				if (*vertex_mode & (TexcoordsMask | NormalsMask))
					lineStream >> padding >> faces[iFace].t[i] >> padding >> faces[iFace].n[i];
				else if (*vertex_mode & TexcoordsMask)
					lineStream >> padding >> faces[iFace].t[i];
				else if (*vertex_mode & NormalsMask)
					lineStream >> padding >> padding >> faces[iFace].n[i];
			}

			iFace++;
			break;
		}
		// ignore all the rest
		default:
			break;
		}
	}
	// third stage

	VOID * vertex_buffer = NULL;
	UINT * index_buffer = NULL;

	index_buffer = new UINT[faceCount * 3];
	*index_count = faceCount * 3;
	for (UINT iI = 0; iI < faceCount * 3; iI++)
	{
		index_buffer[iI] = iI;
	}

	*vertex_size = 12 * bool(PositionMask & *vertex_mode)
		+ 16 * bool(ColorMask & *vertex_mode)
		+ 8 * bool(TexcoordsMask & *vertex_mode)
		+ 12 * bool(NormalsMask & *vertex_mode);
	*vertex_count = faceCount * 3;
	vertex_buffer = new BYTE[*vertex_size * *vertex_count];
	if (!vertex_buffer) { return; }
	FLOAT * iB = (FLOAT *)vertex_buffer;
	for (UINT iF = 0; iF < faceCount; ++iF)
	{
		for (UINT iV = 0; iV < 3; iV++)
		{
			if (*vertex_mode & PositionMask)
			{
				*iB = positions[faces[iF].p[2 - iV] - 1].x;  ++iB;
				*iB = positions[faces[iF].p[2 - iV] - 1].y;  ++iB;
				*iB = -positions[faces[iF].p[2 - iV] - 1].z; ++iB;
			}
			if (*vertex_mode & TexcoordsMask)
			{
				*iB = texcoords[faces[iF].t[2 - iV] - 1].x;         ++iB;
				*iB = 1.0f - texcoords[faces[iF].t[2 - iV] - 1].y;  ++iB;
			}
			if (*vertex_mode & NormalsMask)
			{
				*iB = normals[faces[iF].n[2 - iV] - 1].x;  ++iB;
				*iB = normals[faces[iF].n[2 - iV] - 1].y;  ++iB;
				*iB = -normals[faces[iF].n[2 - iV] - 1].z; ++iB;
			}
		}
	}

	/*switch (*vertex_mode)
	{
	case VERTEX_FORMAT_POSITION_TEXCOORDS_NORMAL:
	{
		vertex_buffer = new Vertex_PTN[faceCount * 3];
		*vertex_count = faceCount * 3;
		*vertex_size = sizeof VertexPTN;
		for (UINT iF = 0; iF < faceCount; iF++)
		{
			for (UINT iV = 0; iV < 3; iV++)
			{
				((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].position.x = positions[faces[iF].p[2 - iV] - 1].x;
				((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].position.y = positions[faces[iF].p[2 - iV] - 1].y;
				((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].position.z = -positions[faces[iF].p[2 - iV] - 1].z;

				((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].texcoords.x = texcoords[faces[iF].t[2 - iV] - 1].x;
				((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].texcoords.y = 1.0f - texcoords[faces[iF].t[2 - iV] - 1].y;

				((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].normal.x = normals[faces[iF].n[2 - iV] - 1].x;
				((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].normal.y = normals[faces[iF].n[2 - iV] - 1].y;
				((Vertex_PTN *)vertex_buffer)[iF * 3 + iV].normal.z = -normals[faces[iF].n[2 - iV] - 1].z;
			}
		}
		break;
	}
	case VERTEX_FORMAT_POSITION_TEXCOORDS:
	{
		vertex_buffer = new Vertex_PT[faceCount * 3];
		*vertex_count = faceCount * 3;
		*vertex_size = sizeof Vertex_PT;
		for (UINT iF = 0; iF < faceCount; iF++)
		{
			for (UINT iV = 0; iV < 3; iV++)
			{
				((Vertex_PT *)vertex_buffer)[iF * 3 + iV].position.x = positions[faces[iF].p[2 - iV] - 1].x;
				((Vertex_PT *)vertex_buffer)[iF * 3 + iV].position.y = positions[faces[iF].p[2 - iV] - 1].y;
				((Vertex_PT *)vertex_buffer)[iF * 3 + iV].position.z = -positions[faces[iF].p[2 - iV] - 1].z;

				((Vertex_PT *)vertex_buffer)[iF * 3 + iV].texcoords.x = texcoords[faces[iF].t[2 - iV] - 1].x;
				((Vertex_PT *)vertex_buffer)[iF * 3 + iV].texcoords.y = 1.0f - texcoords[faces[iF].t[2 - iV] - 1].y;
			}
		}
		break;
	}
	case VERTEX_FORMAT_POSITION_NORMAL:
	{
		vertex_buffer = new Vertex_PN[faceCount * 3];
		*vertex_count = faceCount * 3;
		*vertex_size = sizeof Vertex_PN;
		for (UINT iF = 0; iF < faceCount; iF++)
		{
			for (UINT iV = 0; iV < 3; iV++)
			{
				((Vertex_PN *)vertex_buffer)[iF * 3 + iV].position.x = positions[faces[iF].p[2 - iV] - 1].x;
				((Vertex_PN *)vertex_buffer)[iF * 3 + iV].position.y = positions[faces[iF].p[2 - iV] - 1].y;
				((Vertex_PN *)vertex_buffer)[iF * 3 + iV].position.z = -positions[faces[iF].p[2 - iV] - 1].z;

				((Vertex_PN *)vertex_buffer)[iF * 3 + iV].normal.x = normals[faces[iF].n[2 - iV] - 1].x;
				((Vertex_PN *)vertex_buffer)[iF * 3 + iV].normal.y = normals[faces[iF].n[2 - iV] - 1].y;
				((Vertex_PN *)vertex_buffer)[iF * 3 + iV].normal.z = normals[faces[iF].n[2 - iV] - 1].z;
			}
		}
		break;
	}
	case VERTEX_FORMAT_POSITION:
	{
		vertex_buffer = new Vertex_P[faceCount * 3];
		*vertex_count = faceCount * 3;
		*vertex_size = sizeof Vertex_P;
		for (UINT iF = 0; iF < faceCount; iF++)
		{
			for (UINT iV = 0; iV < 3; iV++)
			{
				((Vertex_P *)vertex_buffer)[iF * 3 + iV].position.x = positions[faces[iF].p[2 - iV] - 1].x;
				((Vertex_P *)vertex_buffer)[iF * 3 + iV].position.y = positions[faces[iF].p[2 - iV] - 1].y;
				((Vertex_P *)vertex_buffer)[iF * 3 + iV].position.z = -positions[faces[iF].p[2 - iV] - 1].z;
			}
		}
		break;
	}



	default:
		break;
	}*/

	// cleanup
	delete[] positions;
	delete[] texcoords;
	delete[] normals;
	delete[] faces;
	positions = NULL;
	texcoords = NULL;
	normals = NULL;
	faces = NULL;

	// return
	*vertex_buffer_data = vertex_buffer;
	*index_buffer_data = index_buffer;
}