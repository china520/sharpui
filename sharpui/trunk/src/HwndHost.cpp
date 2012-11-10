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
    //if (!PrintWindow(HandleRef hWnd, HandleRef hDC, 0))
    // {SendMessage(_hwnd.Handle, WindowMessage.WM_PRINT, hdcBitmap.Handle, (IntPtr) (NativeMethods.PRF_CHILDREN | NativeMethods.PRF_CLIENT | NativeMethods.PRF_ERASEBKGND | NativeMethods.PRF_NONCLIENT));
    //}
    // elseRedrawWindow(_hwnd, IntPtr.Zero, IntPtr.Zero, NativeMethods.RDW_INVALIDATE | NativeMethods.RDW_ALLCHILDREN);
}

/*
void OnWindowPositionChanged(Rect rcBoundingBox)
        { 
            if (_isDisposed)
            {
                return;
            } 

            UnsafeNativeMethods.SetWindowPos(_hwnd, 
                                           new HandleRef(null, IntPtr.Zero), 
                                           (int)rcBoundingBox.X,
                                           (int)rcBoundingBox.Y, 
                                           (int)rcBoundingBox.Width,
                                           (int)rcBoundingBox.Height,
                                           NativeMethods.SWP_ASYNCWINDOWPOS
                                           | NativeMethods.SWP_NOZORDER 
                                           | NativeMethods.SWP_NOCOPYBITS
                                           | NativeMethods.SWP_NOACTIVATE); 
        } 

*/

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
