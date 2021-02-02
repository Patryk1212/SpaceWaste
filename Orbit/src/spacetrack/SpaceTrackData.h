#pragma once

#include <afxwin.h>    // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxinet.h>

class CSpaceTrackDownload : public CObject
{
public:
    CSpaceTrackDownload();
    CSpaceTrackDownload(LPCTSTR pszUrl, LPCTSTR pszUserName, LPCTSTR pszPassword);
    ~CSpaceTrackDownload();

    BOOL Authenticate(LPCTSTR pszUrl, LPCTSTR pszUserName, LPCTSTR pszPassword);
    CString Query(LPCTSTR pszQuery);

private:
    DWORD  m_dwFlags;
    CHttpConnection* m_pHttpConnection;
    CInternetSession  m_cInternetSession;
};