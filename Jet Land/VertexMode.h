/**
 * \file This file contains declarations of different types of vertices used in game.
*/

#pragma once

#include "IncluderW.h"
#include "IncluderDX.h"

enum VERTEX_FORMAT : UINT
{
    VERTEX_FORMAT_POSITION                  = 0b00001,
    VERTEX_FORMAT_POSITION_TEXCOORDS        = 0b00011,
    VERTEX_FORMAT_POSITION_TEXCOORDS_NORMAL = 0b00111,
    VERTEX_FORMAT_POSITION_NORMAL           = 0b00101,
    VERTEX_FORMAT_POSITION_COLOR            = 0b01001,
    VERTEX_FORMAT_POSITION_COLOR_NORMAL     = 0b01101
};

namespace VertexComponent
{
    using Position  = DirectX::XMFLOAT3;
    using Texcoords = DirectX::XMFLOAT2;
    using Normal    = DirectX::XMFLOAT3;
    using Color     = DirectX::XMFLOAT4;

    enum Check : UINT
    {
        HavePosition  = 0b00001,
        HaveTexcoords = 0b00010,
        HaveNormal    = 0b00100,
        HaveColor     = 0b01000
    };
}

struct Vertex_P
{
    VertexComponent::Position position;
};

struct Vertex_PT
{
    VertexComponent::Position position;
    VertexComponent::Texcoords texcoords;
};

struct Vertex_PTN
{
    VertexComponent::Position position;
    VertexComponent::Texcoords texcoords;
    VertexComponent::Normal normal;
};

struct Vertex_PN
{
    VertexComponent::Position position;
    VertexComponent::Normal normal;
};

struct Vertex_PC
{
    VertexComponent::Position position;
    VertexComponent::Color color;
};

struct Vertex_PCN
{
    VertexComponent::Position position;
    VertexComponent::Color color;
    VertexComponent::Normal normal;
};
