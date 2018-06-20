#pragma once

#include "IncluderW.h"

class GraphicsManager
{
public:
    GraphicsManager();
    ~GraphicsManager();

    BOOL InitializeGraphicsSystem();
    VOID TerminateGraphicsSystem();

    BOOL Update();
};

