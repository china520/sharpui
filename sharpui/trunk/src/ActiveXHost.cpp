// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ActiveXHost.cpp

#include <sui/ActiveXHost.h>

namespace ui
{

ActiveXHost::ActiveXHost()
{
    SetClassName(_T("ActiveXHost"));
}

ActiveXHost::~ActiveXHost()
{
}

bool ActiveXHost::DoVerb(int verb)
{ 
    /*int hr = _axOleObject.DoVerb(verb,
        IntPtr.Zero,
        this.ActiveXSite,
        0, 
        this.ParentHandle.Handle,
        _bounds); 

    return hr == S_OK;*/ 

    return false;
}

/////////////////////////////////////////////////////////////////
//
void ActiveXHost::OnInitialized()
{
    __super::OnInitialized();
}

void ActiveXHost::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void ActiveXHost::OnTextInput(suic::KeyEventArg& e)
{
}

void ActiveXHost::OnKeyDown(suic::KeyEventArg& e)
{
}

void ActiveXHost::OnGotFocus(suic::FocusEventArg& e)
{
}

void ActiveXHost::OnLostFocus(suic::FocusEventArg& e)
{
}

void ActiveXHost::OnSetCursor(suic::CursorEventArg& e)
{
}

void ActiveXHost::OnMouseEnter(suic::MouseEventArg& e)
{
    __super::OnMouseEnter(e);
}

void ActiveXHost::OnMouseMove(suic::MouseEventArg& e)
{
    __super::OnMouseMove(e);
}

void ActiveXHost::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);
}

void ActiveXHost::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);
}

void ActiveXHost::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDbclk(e);
}

void ActiveXHost::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);
}

}
