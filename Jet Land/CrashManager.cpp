#include "CrashManager.h"



VOID CrashManager::CrashMessage(LPCTSTR error_type, LPCTSTR error_message)
{
    MessageBox(NULL, error_message, error_type, MB_ICONERROR);
}

VOID CrashManager::CrashLog(LPCTSTR filename, std::wstringstream &log)
{
    std::wofstream output;
    output.open(filename, std::wofstream::app);
    output << log.str();
    output.close();
}

VOID CrashManager::CrashLog(LPCTSTR filename, std::wstring &log)
{
    std::wofstream output;
    output.open(filename, std::wofstream::app);
    output << log;
    output.close();
}

VOID CrashManager::CrashLog(LPCTSTR filename, LPCTSTR log)
{
    std::wofstream output;
    output.open(filename, std::wofstream::app);
    output << log;
    output.close();
}

VOID CrashManager::CrashLog(LPCTSTR filename, ID3D10Blob * log)
{
    std::ofstream output;
    output.open(filename, std::ofstream::app);
    output << LPSTR(log->GetBufferPointer());
    output.close();
}