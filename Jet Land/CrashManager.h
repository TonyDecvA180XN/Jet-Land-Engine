#pragma once

#include "IncluderW.h"
#include "IncluderSTD.h"

class CrashManager
{
public:
    static VOID CrashMessage(LPCTSTR error_type, LPCTSTR error_message);
    static VOID CrashLog(LPCTSTR filename, std::wstringstream &log);
    static VOID CrashLog(LPCTSTR filename, std::wstring &log);
};

