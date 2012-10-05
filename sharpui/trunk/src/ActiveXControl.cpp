// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ActiveX.cpp

#include <sui/ActiveXControl.h>

namespace ui
{

ActiveX::ActiveX()
{
    SetClassName(_T("ActiveX"));
}

ActiveX::~ActiveX()
{
}

/////////////////////////////////////////////////////////////////
//
void ActiveX::OnInitialized()
{
    __super::OnInitialized();
}

void ActiveX::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void ActiveX::OnTextInput(suic::KeyEventArg& e)
{
}

void ActiveX::OnKeyDown(suic::KeyEventArg& e)
{
}

void ActiveX::OnGotFocus(suic::FocusEventArg& e)
{
}

void ActiveX::OnLostFocus(suic::FocusEventArg& e)
{
}

void ActiveX::OnSetCursor(suic::CursorEventArg& e)
{
}

void ActiveX::OnMouseEnter(suic::MouseEventArg& e)
{
    __super::OnMouseEnter(e);
}

void ActiveX::OnMouseMove(suic::MouseEventArg& e)
{
    __super::OnMouseMove(e);
}

void ActiveX::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);
}

void ActiveX::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);
}

void ActiveX::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDbclk(e);
}

void ActiveX::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);
}

}
