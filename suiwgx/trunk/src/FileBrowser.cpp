// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// FileBrowser.cpp

#include "stdafx.h"
#include "commdlg.h"
#include <sui/FileBrowser.h>

namespace ui
{

//////////////////////////////////////////////////////////////////////////////
// FileBrowser

FileBrowser::FileBrowser(bool bDel)
{
    SetClassName(_T("FileBrowser"));
    SetAutoDelete(bDel);
}

FileBrowser::~FileBrowser()
{
}

void FileBrowser::OnRender(suic::DrawingContext * drawing)
{
}

bool FileBrowser::InternalOpen(bool bOpen, const suic::String& filter)
{
    suic::VisualHostPtr pHost = suic::HwndHelper::GetVisualHost(GetOwner());

    OPENFILENAME ofn;       // common dialog box structure
    TCHAR szFile[260] = {0};       // buffer for file name
    HWND hwnd = NULL;              // owner window

    if (pHost)
    {
        hwnd = HandleToHwnd(pHost->GetHandle());
    }

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;

    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = _T('\0');
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter.c_str();
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST/* | OFN_FILEMUSTEXIST*/;

    // Display the Open dialog box. 

    BOOL bRet = FALSE;

    if (bOpen)
    {
        bRet = GetOpenFileName(&ofn);
    }
    else
    {
        bRet = GetSaveFileName(&ofn);
    }

    if (bRet) 
    {
        _path = szFile;

        return true;
    }
    else
    {
        return false;
    }
}

bool FileBrowser::Open(const suic::String& filter)
{
    return InternalOpen(true, filter);
}

bool FileBrowser::Save(const suic::String& filter)
{
    return InternalOpen(true, filter);
}

suic::String FileBrowser::GetFilePath() const
{
    return _path;
}

};
