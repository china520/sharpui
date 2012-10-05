// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// Button.cpp

#include <sui/Button.h>
#include <suicore/drawing/uirender.h>
#include <suicore/hwndhelper.h>

namespace ui
{

//////////////////////////////////////////////////////////////////////////////
// ButtonBase

ButtonBase::ButtonBase()
{
    SetMinHeight(4);
    SetMinWidth(4);

    // 支持鼠标传递绘制
    WriteFlag(CoreFlags::IsSupportMouseOver, true);
    SetFocusable(true);
}

ButtonBase::~ButtonBase()
{
}

suic::Size ButtonBase::MeasureOverride(const suic::Size& size)
{
    suic::Size ret = __super::MeasureOverride(size);

    if (ret.cx <= 0 || ret.cy <= 0)
    {
        if (GetStyle())
        {
            suic::TriggerPtr setter(suic::UIRender::GetTriggerByStatus(this, GetStyle()));

            //
            // 计算背景图像的内容区域大小
            //
            if (setter.get())
            {
                return suic::UIRender::MeasureImageSize(setter);
            }
        }
    }

    return ret;
}

void ButtonBase::OnRender(suic::DrawingContext * drawing)
{
    suic::Control::OnRender(drawing);
}

void ButtonBase::OnMouseEnter(suic::MouseEventArg& e)
{
    __super::OnMouseEnter(e);
}

void ButtonBase::OnMouseMove(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseMove(e);
}

void ButtonBase::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);

    e.Handled(true);
}

void ButtonBase::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    suic::Control::OnMouseLeftButtonDown(e);
}

void ButtonBase::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    suic::Control::OnMouseLeftButtonUp(e);

    //
    // 只有鼠标位于元素上才出发Click事件
    //
    if (IsMouseOver())
    {
        suic::RoutedEventArg re(e.GetOriginalSource());

        OnClick(re);
    }
}

void ButtonBase::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    OnMouseLeftButtonDown(e);
}

void ButtonBase::OnGotFocus(suic::FocusEventArg& e)
{
    InvalidateVisual();

    __super::OnGotFocus(e);
    e.Handled(true);
}

void ButtonBase::OnLostFocus(suic::FocusEventArg& e)
{
    InvalidateVisual();
    __super::OnGotFocus(e);
}

void ButtonBase::OnClick(suic::RoutedEventArg& e)
{
    if (NULL != Click)
    {
        Click(this);
    }
}

//////////////////////////////////////////////////////////////////////////////
// Button

Button::Button()
    : nOffset(0)
{
    SetClassName(_T("Button"));
}

Button::~Button()
{
}

void Button::OnInitialized()
{
    // 调用基类

    ButtonBase::OnInitialized();
}

void Button::OnRender(suic::DrawingContext * drawing)
{
    Control::OnRender(drawing);
}

void Button::OnKeyDown(suic::KeyEventArg& e)
{
    //
    // 压下键盘空格则触发OnClick
    //
    if (e.IsSpacePress())
    {
        if (IsFocused())
        {
            suic::RoutedEventArg re(this);

            OnClick(re);
        }
    }

    e.Handled(true);
}

//-------------------------------------------
SystemMinButton::SystemMinButton()
{
    SetClassName(_T("SystemMinButton"));
    SetToolTip(new suic::UString(_T("最小化")));
}

SystemMinButton::~SystemMinButton()
{
    ;
}

void SystemMinButton::OnClick(suic::RoutedEventArg& e)
{
    suic::HwndHelper::MinimizeWindow(this);
}

//-------------------------------------------
SystemMaxButton::SystemMaxButton()
{
    SetClassName(_T("SystemMaxButton"));
}

SystemMaxButton::~SystemMaxButton()
{
    ;
}

void SystemMaxButton::OnLoaded(suic::LoadedEventArg& e)
{
    __super::OnLoaded(e);
}

void SystemMaxButton::OnClick(suic::RoutedEventArg& e)
{
    if (suic::HwndHelper::IsWindowMaximize(this))
    {
        SetToolTip(new suic::UString(_T("最大化")));
        suic::HwndHelper::RestoreWindow(this);
    }
    else
    {
        SetToolTip(new suic::UString(_T("向下还原")));
        suic::HwndHelper::MaximizeWindow(this);
    }
}

suic::Size SystemMaxButton::MeasureOverride(const suic::Size& size)
{
    suic::Size ret;
    suic::TriggerPtr& trg = GetStyle()->GetTrigger();

    if (trg.get())
    {
        suic::ImageBrushPtr bkgnd(trg->GetValue(_T("Restore")));

        if (bkgnd)
        {
            suic::Rect rectBk;

            rectBk = bkgnd->GetContentBrounds();       
            ret.cx += rectBk.Width() + 4;
            ret.cy += rectBk.Height();
        }
    }

    return ret;
}

void SystemMaxButton::OnRender(suic::DrawingContext * drawing)
{
    suic::String strName;

    if (suic::HwndHelper::IsWindowMaximize(this))
    {
        strName = _T("Restore");
        SetToolTip(new suic::UString(_T("向下还原")));
    }
    else
    {
        strName = _T("Max");
        SetToolTip(new suic::UString(_T("最大化")));
    }

    suic::Rect drawrect(0, 0, RenderSize().cx, RenderSize().cy);
    suic::TriggerPtr trigger(suic::UIRender::GetTriggerByStatus(this, GetStyle()));
    suic::BrushPtr bkgnd(trigger->GetValue(strName));

    if (bkgnd)
    {
        bkgnd->Draw(drawing, &drawrect);
    }
}

//-------------------------------------------
SystemCloseButton::SystemCloseButton()
{
    SetClassName(_T("SystemCloseButton"));
    SetToolTip(new suic::UString(_T("关闭")));
}

SystemCloseButton::~SystemCloseButton()
{
    ;
}

void SystemCloseButton::OnClick(suic::RoutedEventArg& e)
{
    suic::HwndHelper::CloseWindow(this);
}

};
