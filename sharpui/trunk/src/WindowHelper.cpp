// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// WindowHelper.cpp

#include <sui/WindowHelper.h>
#include <suicore/carethelper.h>

namespace ui
{

//////////////////////////////////////////////////////////////////////////////
// WndHelper
// 
WndHelper::WndHelper(suic::ElementPtr p) 
    : ePtr(p)
{
}

WndHelper::~WndHelper()
{
}

bool WndHelper::OpenClipboard()
{
    suic::VisualHostPtr pHost = suic::HwndHelper::GetVisualHost(ePtr);

    if (!pHost)
    {
        return false;
    }

    HWND realwnd = HandleToHwnd(pHost->GetHandle());

    if (::IsWindow(realwnd))
    {
        if (::OpenClipboard(realwnd))
        {
            return true;
        }
    }

#ifdef _DEBUG
    LPVOID lpMsgBuf;
    ::FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        ::GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL
        );
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, _T("Info"), MB_OK | MB_ICONINFORMATION );
    ::LocalFree( lpMsgBuf );
#endif

    return false;
}

void WndHelper::CloseClipboard()
{
    ::CloseClipboard();
}

int WndHelper::PasteText(suic::String & text)
{
    // 首先打开我们自己定义的数据格式
    suic::String UI_EDIT_CFMSDEVCOLSEL(_T("UI_EDIT_BINARY"));
    CLIPFORMAT uCF_MSDEVColumnSelect = (CLIPFORMAT)::RegisterClipboardFormat(UI_EDIT_CFMSDEVCOLSEL.c_str());
    HANDLE hMem_TextBlok = ::GetClipboardData(uCF_MSDEVColumnSelect);
    if (hMem_TextBlok)
    {
        int nSize = (int)::GlobalSize(hMem_TextBlok);
        BYTE * arColBlk = (BYTE*)::GlobalLock(hMem_TextBlok);
    }

    HideCaret();

    HGLOBAL hmem = NULL;
    if (::IsClipboardFormatAvailable(CF_UNICODETEXT))
    {
        hmem = ::GetClipboardData(CF_UNICODETEXT);
    }

    if (hmem)
    {
        suic::Char * pClipData = (suic::Char *)::GlobalLock(hmem);
        DWORD dwLen = (DWORD)::GlobalSize(hmem);

        text = suic::String(pClipData, (dwLen / 2) - 1);

#ifdef _DEBUG
        _CrtCheckMemory();
#endif
        ::GlobalUnlock(hmem);
    }

    return 0;
}

int WndHelper::CutText(suic::String & text)
{
    int nRet = CopyText(text);
    if (0 == nRet)
    {
        ::EmptyClipboard();
    }
    return nRet;
}

int WndHelper::CopyText(const suic::String & text)
{
    ::EmptyClipboard();

    // 采用unicode编码来存储字符
    suic::Uint32 dataSize = (suic::Uint32)text.Length() * sizeof(suic::Char);

    HGLOBAL hmem = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, dataSize + sizeof(TCHAR));
    LPVOID lpClipData = (LPVOID)::GlobalLock(hmem);

    if (NULL != lpClipData)
    {
        memcpy(lpClipData, text.c_str(), dataSize);
        ::ZeroMemory(((BYTE *)lpClipData + dataSize), sizeof(TCHAR));
    }

    int uCodePage = 0;

    // 计算需要的字节数
    int nLen  = ::WideCharToMultiByte(uCodePage, 0, (LPWSTR)lpClipData, -1, NULL, 0, NULL, NULL);

    HGLOBAL hMBCSMem = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, (dataSize + 2));
    LPSTR lpMBCSSource = (LPSTR)::GlobalLock(hMBCSMem);

    int nBytes = ::WideCharToMultiByte(uCodePage, 0, (LPWSTR)lpClipData, -1, lpMBCSSource, nLen, NULL, NULL);

    assert(nBytes <= (int)nLen);

    lpMBCSSource[nBytes] = _T('\0');

    ::GlobalUnlock(hmem);
    ::GlobalUnlock(hMBCSMem);

    // 我们存储是unicode文本
    ::SetClipboardData(CF_UNICODETEXT, hmem);
    ::SetClipboardData(CF_TEXT, hMBCSMem);
    ::SetClipboardData(CF_OEMTEXT, hMBCSMem);

    return 0;
}

bool WndHelper::CreateSolidCaret(int w, int h)
{
    return suic::CaretHelper::CreateCaret(ePtr.get(), w, h);
}

bool WndHelper::DestroyCaret()
{
    return ::DestroyCaret() ? true : false;
}

void WndHelper::ShowCaret()
{
    suic::CaretHelper::ShowCaret(ePtr.get());
}

void WndHelper::HideCaret()
{
    suic::CaretHelper::HideCaret(ePtr.get());
}

void WndHelper::SetCaretPos(int x, int y)
{
    suic::CaretHelper::SetCaretPos(ePtr.get(), x, y);
}

bool WndHelper::GetCaretPos(suic::Point & pt)
{
    return ::GetCaretPos(&pt) ? true : false;
}

};