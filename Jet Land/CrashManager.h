#pragma once





class CrashManager
{
public:
    static VOID CrashMessage(LPCTSTR error_type, LPCTSTR error_message);
    static VOID CrashLog(LPCTSTR filename, std::wstringstream &log);
    static VOID CrashLog(LPCTSTR filename, std::wstring &log);
    static VOID CrashLog(LPCTSTR filename, LPCTSTR log);
    static VOID CrashLog(LPCTSTR filename, ID3D10Blob * log);
};

