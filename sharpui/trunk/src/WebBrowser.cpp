// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// WebBrowser.cpp

#include <sui/WebBrowser.h>
#include "WebWrapper.h"

namespace ui
{

WebBrowser::WebBrowser()
{
    SetClassName(_T("WebBrowser"));
    _webHost = new WebWrapper();
}

WebBrowser::~WebBrowser()
{
}

bool WebBrowser::OpenUri(const suic::String& uri)
{
    WebWrapper* pWeb = (WebWrapper*)_webHost;

    pWeb->OpenURL(uri.c_str());

    return true;
}

//============================================================
//
suic::Size WebBrowser::ArrangeOverride(const suic::Size& size)
{
    suic::Size finalRect = __super::ArrangeOverride(size);
    suic::Point point = PointToScreen(suic::Point());
    suic::Rect rect(point.x, point.y, size.cx, size.cy);

    WebWrapper* pWeb = (WebWrapper*)_webHost;

    if (_webHost && !pWeb->GetHandle())
    {
        pWeb->SetWebRect(&rect);

        pWeb->SetHandle(suic::HwndHelper::GetHandle(this));
        pWeb->OpenWebBrowser();

        OpenUri(_T("http://www.baidu.com"));
    }

    return finalRect;
}

void WebBrowser::OnInitialized()
{
    __super::OnInitialized();
}

void WebBrowser::OnLoaded(suic::LoadedEventArg& e)
{
    __super::OnLoaded(e);
}

void WebBrowser::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void WebBrowser::OnTextInput(suic::KeyEventArg& e)
{
}

void WebBrowser::OnKeyDown(suic::KeyEventArg& e)
{
}

void WebBrowser::OnGotFocus(suic::FocusEventArg& e)
{
}

void WebBrowser::OnLostFocus(suic::FocusEventArg& e)
{
}

void WebBrowser::OnSetCursor(suic::CursorEventArg& e)
{
}

void WebBrowser::OnMouseEnter(suic::MouseEventArg& e)
{
    __super::OnMouseEnter(e);
}

void WebBrowser::OnMouseMove(suic::MouseEventArg& e)
{
    __super::OnMouseMove(e);
}

void WebBrowser::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);
}

void WebBrowser::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);
}

void WebBrowser::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDbclk(e);
}

void WebBrowser::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);
}

};
