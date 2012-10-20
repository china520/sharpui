// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// RepeatButton.cpp

#include <sui/RepeatButton.h>

namespace ui
{

RepeatButton::RepeatButton()
{
    int iTime = (int)::GetDoubleClickTime();

    _iDelay = iTime + iTime / 3;
    _iInterval = iTime / 6;
}

RepeatButton::~RepeatButton()
{
}

void RepeatButton::OnInitialized()
{
    // 
    // 调用基类进行事件分发处理
    //
    Element::OnInitialized();
}

void RepeatButton::OnUnloaded(suic::LoadedEventArg& e)
{
    __super::OnUnloaded(e);

    suic::SystemHelper::KillTimer(_iTimer300);
    suic::SystemHelper::KillTimer(_iTimer301);
}

void RepeatButton::OnRender(suic::DrawingContext * drawing)
{
    // 
    // 直接调用基类进行绘制
    //
    Button::OnRender(drawing);
}

void RepeatButton::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    suic::SystemHelper::KillTimer(_iTimer301);
    suic::SystemHelper::SetTimer(_iTimer300, this, _iDelay);

    __super::OnMouseLeftButtonDown(e);
}

void RepeatButton::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    suic::SystemHelper::KillTimer(_iTimer301);

    __super::OnMouseLeftButtonUp(e);
}

void RepeatButton::OnMouseEnter(suic::MouseEventArg& e)
{
    if (IsMouseDown())
    {
        suic::SystemHelper::KillTimer(_iTimer301);
        suic::SystemHelper::SetTimer(_iTimer301, this, _iInterval);
    }

    __super::OnMouseEnter(e);
}

void RepeatButton::OnMouseLeave(suic::MouseEventArg& e)
{
    suic::SystemHelper::KillTimer(_iTimer301);

    __super::OnMouseLeave(e);
}

void RepeatButton::OnClick(suic::RoutedEventArg& e)
{
    // 
    // 启动定时器，激发OnClick事件
    //
    __super::OnClick(e);
}

void RepeatButton::OnTimer(int id)
{
    if (_iTimer300 && id == _iTimer300->id)
    {
        suic::SystemHelper::KillTimer(_iTimer300);

        if (IsMouseDown())
        {
            suic::SystemHelper::SetTimer(_iTimer301, this, _iInterval);
        }
    }

    if (IsMouseDown())
    {
        suic::Point pt = suic::SystemHelper::CalcuCusorPoint(this);

        pt = PointFromScreen(pt);

        OnRepeated(VisualDescendantBounds().PointIn(pt));
    }
}

void RepeatButton::OnRepeated(bool bMouseIn)
{
    if (bMouseIn && MouseLButtonDown)
    {
        suic::Point pt;
        suic::MouseEventArg e(this, pt);

        MouseLButtonDown(this, e);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//

void RepeatButton::SetDelay(int iDelay)
{
    _iDelay = iDelay;
}

void RepeatButton::SetInterval(int iInterval)
{
    _iInterval = iInterval;
}

}

