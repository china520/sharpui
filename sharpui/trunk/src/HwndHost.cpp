// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// HwndHost.cpp

#include <sui/HwndHost.h>

namespace ui
{

//////////////////////////////////////////////////////////////
// HwndHost
//
HwndHost::HwndHost()
    : _handle(0)
{
    SetClassName(_T("HwndHost"));
}

HwndHost::~HwndHost()
{
}

void HwndHost::OnInitialized()
{
    __super::OnInitialized();
}

void HwndHost::OnRender(suic::DrawingContext * drawing)
{
    //__super::OnRender(drawing);
}

suic::Size HwndHost::MeasureOverride(const suic::Size& size)
{
    HWND hwnd = HandleToHwnd(_handle);

    if (::IsWindow(hwnd))
    {
        suic::Rect rect;

        ::GetWindowRect(hwnd, &rect);
        return suic::Size(rect.Width(), rect.Height());
    }
    else
    {
        return suic::Size(0, 0);
    }
}

suic::Size HwndHost::ArrangeOverride(const suic::Size& size)
{
    HWND hwnd = HandleToHwnd(_handle);
    HWND host = HandleToHwnd(suic::HwndHelper::GetHandle(this));

    if (::IsWindow(hwnd) && ::IsWindow(host))
    {
        suic::Rect rect;
        suic::Point pt;
        
        ::GetWindowRect(host, &rect);
        pt = PointToScreen(pt);

        rect.left = pt.x;
        rect.top = pt.y;

        ::MoveWindow(hwnd, rect.left, rect.top, size.cx, size.cy, TRUE);
    }

    return size;
}

};
