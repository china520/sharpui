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

ImplementTypeofInfo(WebBrowser, ActiveXHost)

WebBrowser::WebBrowser()
{
    SetClassName(_T("WebBrowser"));
    _webHost = new WebWrapper();
}

WebBrowser::~WebBrowser()
{
}

bool WebBrowser::CanGoBack() const
{
    return false;
}

bool WebBrowser::CanGoForward() const
{
    return false;
}

void WebBrowser::GoBack()
{
}

void WebBrowser::GoForward()
{
}

suic::ObjectPtr WebBrowser::InvokeScript(suic::String scriptName)
{
    return suic::ObjectPtr();
}

void WebBrowser::Navigate(const suic::String& uri)
{
    WebWrapper* pWeb = (WebWrapper*)_webHost;

    pWeb->OpenURL(uri.c_str());
}

void WebBrowser::Refresh()
{
}

//============================================================
//
suic::Size WebBrowser::ArrangeOverride(const suic::Size& size)
{
    suic::Size finalRect = __super::ArrangeOverride(size);

    suic::Point point = PointToScreen(suic::Point());
    suic::Rect rect(point.x, point.y, size.cx, size.cy);

    WebWrapper* pWeb = (WebWrapper*)_webHost;

    if (_webHost)
    {
        pWeb->SetWebRect(&rect);
        pWeb->OpenWebBrowser();
    }

    return finalRect;
}

void WebBrowser::OnInitialized()
{
    __super::OnInitialized();
}

void WebBrowser::OnLoaded(suic::LoadedEventArg& e)
{
    suic::FrameworkElement::OnLoaded(e);

    WebWrapper* pWeb = (WebWrapper*)_webHost;
    suic::VisualHostPtr pHost(e.GetTarget());

    if (_webHost)
    {
        pWeb->SetHandle(pHost->GetHandle());
    }
}

void WebBrowser::OnVisibilityChanged(bool visible)
{
    suic::Point point = PointToScreen(suic::Point());
    suic::Rect rect(point.x, point.y, RenderSize().cx, RenderSize().cy);

    WebWrapper* pWeb = (WebWrapper*)_webHost;

    if (visible)
    {
        pWeb->SetWebRect(&rect);
    }
    else
    {
        suic::Rect rc;

        pWeb->SetWebRect(&rc);
    }
}

void WebBrowser::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void WebBrowser::OnTextInput(suic::KeyboardEventArg& e)
{
}

void WebBrowser::OnKeyDown(suic::KeyboardEventArg& e)
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

}
