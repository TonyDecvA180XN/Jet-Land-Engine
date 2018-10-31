#pragma once
#include <Windows.h>

#define VFORMAT BYTE
//              00000000
//              ||||
//       position|||
//           color||
//        texcoords|
//                 normal

#define PositionMask      0b10000000
#define ColorMask         0b01000000
#define TexcoordsMask     0b00100000
#define NormalsMask       0b00010000