/**
 * This file is precompiled header, so don't modify it if it doesn't need.
 */

#pragma once

 // ---------------------------------------------------------------------------
 // Definitions
 // ---------------------------------------------------------------------------

#define NULL nullptr // Because NULL == 0 is deprecated

// ---------------------------------------------------------------------------
// Includes
// ---------------------------------------------------------------------------

// STL headers
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>


// WinAPI headers
#include <Windows.h>

// DirectX 11 headers
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#define DIRECTINPUT_VERSION 0x800 // to disable compiler warnings
#include <dinput.h>