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
    : m_iTimer300(0)
    , m_iTimer301(0)
{
    int iTime = (int)::GetDoubleClickTime();

    m_iDelay = iTime + iTime / 3;
    m_iInterval = iTime / 6;
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

    suic::SystemHelper::KillTimer(this, m_iTimer300);
    suic::SystemHelper::KillTimer(this, m_iTimer301);
    m_iTimer300 = 0;
    m_iTimer301 = 0;
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
    suic::SystemHelper::KillTimer(this, m_iTimer301);
    m_iTimer300 = suic::SystemHelper::SetTimer(this, m_iDelay);

    __super::OnMouseLeftButtonDown(e);
}

void RepeatButton::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    suic::SystemHelper::KillTimer(this, m_iTimer301);
    m_iTimer301 = 0;

    __super::OnMouseLeftButtonUp(e);
}

void RepeatButton::OnMouseEnter(suic::MouseEventArg& e)
{
    if (IsMouseDown())
    {
        suic::SystemHelper::KillTimer(this, m_iTimer301);
        m_iTimer301 = suic::SystemHelper::SetTimer(this, m_iInterval);
    }

    __super::OnMouseEnter(e);
}

void RepeatButton::OnMouseLeave(suic::MouseEventArg& e)
{
    suic::SystemHelper::KillTimer(this, m_iTimer301);
    m_iTimer301 = 0;

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
    if (id == m_iTimer300)
    {
        suic::SystemHelper::KillTimer(this, m_iTimer300);
        m_iTimer300 = 0;

        if (IsMouseDown())
        {
            m_iTimer301 = suic::SystemHelper::SetTimer(this, m_iInterval);
        }
    }

    if (IsMouseDown())
    {
        suic::Point pt = UI_CalcuCusorPoint(this);

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
    m_iDelay = iDelay;
}

void RepeatButton::SetInterval(int iInterval)
{
    m_iInterval = iInterval;
}

}

