// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// RepeatedButton.cpp

#include <sui/RepeatedButton.h>

namespace ui
{

RepeatedButton::RepeatedButton()
{
    int iTime = (int)::GetDoubleClickTime();

    _iDelay = iTime + iTime / 3;
    _iInterval = iTime / 6;
}

RepeatedButton::~RepeatedButton()
{
}

void RepeatedButton::OnInitialized()
{
    // 
    // 调用基类进行事件分发处理
    //
    Element::OnInitialized();
}

void RepeatedButton::OnUnloaded(suic::LoadedEventArg& e)
{
    __super::OnUnloaded(e);

    suic::SystemHelper::suiKillTimer(_iTimer300);
    suic::SystemHelper::suiKillTimer(_iTimer301);
}

void RepeatedButton::OnRender(suic::DrawingContext * drawing)
{
    // 
    // 直接调用基类进行绘制
    //
    Button::OnRender(drawing);
}

void RepeatedButton::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    suic::SystemHelper::suiKillTimer(_iTimer301);
    suic::SystemHelper::suiSetTimer(_iTimer300, this, _iDelay);

    __super::OnMouseLeftButtonDown(e);
}

void RepeatedButton::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    suic::SystemHelper::suiKillTimer(_iTimer301);

    __super::OnMouseLeftButtonUp(e);
}

void RepeatedButton::OnMouseEnter(suic::MouseEventArg& e)
{
    if (IsMouseDown())
    {
        suic::SystemHelper::suiKillTimer(_iTimer301);
        suic::SystemHelper::suiSetTimer(_iTimer301, this, _iInterval);
    }

    __super::OnMouseEnter(e);
}

void RepeatedButton::OnMouseLeave(suic::MouseEventArg& e)
{
    suic::SystemHelper::suiKillTimer(_iTimer301);

    __super::OnMouseLeave(e);
}

void RepeatedButton::OnClick(suic::RoutedEventArg& e)
{
    // 
    // 启动定时器，激发OnClick事件
    //
    __super::OnClick(e);
}

void RepeatedButton::OnTimer(int id)
{
    if (_iTimer300 && id == _iTimer300->id)
    {
        suic::SystemHelper::suiKillTimer(_iTimer300);

        if (IsMouseDown())
        {
            suic::SystemHelper::suiSetTimer(_iTimer301, this, _iInterval);
        }
    }

    if (IsMouseDown())
    {
        suic::Point pt = suic::SystemHelper::CalcuCusorPoint(this);

        pt = PointFromScreen(pt);

        OnRepeated(VisualDescendantBounds().PointIn(pt));
    }
}

void RepeatedButton::OnRepeated(bool bMouseIn)
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

void RepeatedButton::SetDelay(int iDelay)
{
    _iDelay = iDelay;
}

void RepeatedButton::SetInterval(int iInterval)
{
    _iInterval = iInterval;
}

}

