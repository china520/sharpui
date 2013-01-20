// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// RichTextBox.cpp

#include <sui/RichTextBox.h>

namespace ui
{

ImplementTypeofInfo(RichTextBox, suic::Control)

RichTextBox::RichTextBox()
{
    SetClassName(_T("RichTextBox"));
}

RichTextBox::~RichTextBox()
{
}

////////////////////////////////////////////////////////////////////////////////////////////

void RichTextBox::OnInitialized()
{
    __super::OnInitialized();
}

void RichTextBox::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void RichTextBox::OnTextInput(suic::KeyboardEventArg& e)
{
}

void RichTextBox::OnKeyDown(suic::KeyboardEventArg& e)
{
}

void RichTextBox::OnGotFocus(suic::FocusEventArg& e)
{
}

void RichTextBox::OnLostFocus(suic::FocusEventArg& e)
{
}

void RichTextBox::OnSetCursor(suic::CursorEventArg& e)
{
}

void RichTextBox::OnMouseEnter(suic::MouseEventArg& e)
{
    __super::OnMouseEnter(e);
}

void RichTextBox::OnMouseMove(suic::MouseEventArg& e)
{
    __super::OnMouseMove(e);
}

void RichTextBox::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);
}

void RichTextBox::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);
}

void RichTextBox::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDbclk(e);
}

void RichTextBox::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);
}

};
