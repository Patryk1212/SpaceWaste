#include "pch.h"
#include "SpaceTrackData.h"

CSpaceTrackDownload::CSpaceTrackDownload() : CObject()
{
    m_dwFlags = 0;
    m_pHttpConnection = (CHttpConnection*)NULL;
}
CSpaceTrackDownload::CSpaceTrackDownload(LPCTSTR pszUrl, LPCTSTR pszUserName, LPCTSTR pszPassword) : CObject()
{
    Authenticate(pszUrl, pszUserName, pszPassword);
}

CSpaceTrackDownload::~CSpaceTrackDownload()
{
    if (m_pHttpConnection != (CHttpConnection*)NULL)
    {
        m_pHttpConnection->Close();
        delete m_pHttpConnection;
    }
}

BOOL CSpaceTrackDownload::Authenticate(LPCTSTR pszUrl, LPCTSTR pszUserName, LPCTSTR pszPassword)
{
    UINT  cbData;
    DWORD  dwType;
    LPSTR  pszData;
    CString  szPath;
    CString  szReply;
    CString  szServer;
    CString  szCredentials;
    CHttpFile* pHttpFile;
    INTERNET_PORT  nPort;
    BYTE  nData[1024];

    for (pHttpFile = (CHttpFile*)NULL, pszData = (LPSTR)NULL; AfxParseURL(pszUrl, dwType, szServer, szPath, nPort); )
    {
        try
        {
            if ((m_pHttpConnection = m_cInternetSession.GetHttpConnection(szServer, (m_dwFlags = (nPort == INTERNET_DEFAULT_HTTPS_PORT) ? INTERNET_FLAG_SECURE : 0), nPort)))
            {
                if ((pHttpFile = m_pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, szPath, (LPCTSTR)NULL, 1, (LPCTSTR*)NULL, (LPCTSTR)NULL, m_dwFlags)))
                {
                    for (szCredentials.Format(STRING(IDS_SPACETRACK_CREDENTIALSFORMAT) /* identity=%s&password=%s */, pszUserName, pszPassword); (pszData = (LPSTR)GlobalAlloc(GPTR, (szCredentials.GetLength() + 1) * sizeof(CHAR))); )
                    {
#ifndef UNICODE
                        strcpy_s(pszData, szCredentials.GetLength() + 1, szCredentials);
#else
                        WideCharToMultiByte(CP_ACP, 0, szCredentials, -1, pszData, szCredentials.GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
                        for (pHttpFile->SendRequest(STRING(IDS_SPACETRACK_HTTPCONTENTTYPEHEADER) /* Content-Type: application/x-www-form-urlencoded */, lstrlen(STRING(IDS_SPACETRACK_HTTPCONTENTTYPEHEADER)), pszData, (DWORD)strlen(pszData)), ZeroMemory(nData, sizeof(nData) / sizeof(BYTE)); (cbData = pHttpFile->Read(nData, sizeof(nData) / sizeof(BYTE))) > 0; )
                        {
#ifndef UNICODE
                            szReply = (LPCSTR)nData;
#else
                            MultiByteToWideChar(CP_ACP, 0, (LPCSTR)nData, -1, szReply.GetBufferSetLength(cbData), cbData + 1);
                            szReply.ReleaseBuffer();
#endif
                            if (szReply == STRING(IDS_SPACETRACK_LOGINSUCCESS)) /* "" i.e. returns two double-quotes on successful login */
                            {
                                pHttpFile->Close();
                                GlobalFree(pszData);
                                delete pHttpFile;
                                return TRUE;
                            }
                            break;
                        }
                        GlobalFree(pszData);
                        break;
                    }
                    pHttpFile->Close();
                    delete pHttpFile;
                }
                m_pHttpConnection->Close();
                delete m_pHttpConnection;
            }
            break;
        }
        catch (...)
        {
            if (pszData != (LPSTR)NULL) GlobalFree(pszData);
            if (pHttpFile != (CHttpFile*)NULL)
            {
                pHttpFile->Close();
                delete pHttpFile;
            }
            if (m_pHttpConnection != (CHttpConnection*)NULL)
            {
                m_pHttpConnection->Close();
                delete m_pHttpConnection;
            }
            break;
        }
    }
    m_dwFlags = 0;
    m_pHttpConnection = (CHttpConnection*)NULL;
    return FALSE;
}   // END Authenticate()

CString CSpaceTrackDownload::Query(LPCTSTR pszQuery)
{
    UINT  cbData;
    CString  szResult[2];
    CHttpFile* pHttpFile;
    BYTE  nData[65536];

    for (pHttpFile = (CHttpFile*)NULL; m_pHttpConnection != (CHttpConnection*)NULL; )
    {
        try
        {
            if ((pHttpFile = m_pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, pszQuery, (LPCTSTR)NULL, 1, (LPCTSTR*)NULL, (LPCTSTR)NULL, m_dwFlags)))
            {
                for (pHttpFile->SendRequest(), ZeroMemory(nData, sizeof(nData) / sizeof(BYTE)); (cbData = pHttpFile->Read(nData, sizeof(nData) / sizeof(BYTE) - 1)) > 0; ZeroMemory(nData, sizeof(nData) / sizeof(BYTE)))
                {
#ifndef UNICODE
                    szResult[0] += (LPCSTR)nData;
#else
                    MultiByteToWideChar(CP_ACP, 0, (LPCSTR)nData, cbData, szResult[1].GetBufferSetLength(cbData), cbData + 1);
                    szResult[1].ReleaseBuffer();
                    szResult[0] += szResult[1];
#endif
                }
                pHttpFile->Close();
                delete pHttpFile;
            }
            break;
        }
        catch (...)
        {
            if (pHttpFile != (CHttpFile*)NULL)
            {
                pHttpFile->Close();
                delete pHttpFile;
            }
            szResult[0].Empty();
            break;
        }
    }
    return szResult[0];
}   // END Query()