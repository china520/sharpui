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
#include <suic/render/uirender.h>
#include <suic/tools/hwndhelper.h>

namespace ui
{

//////////////////////////////////////////////////////////////////////////////
// ButtonBase

ImplementTypeofInfo(ButtonBase, suic::ContentControl)

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
        //
        // 计算背景图像的内容区域大小
        //
        return suic::Render::MeasureImageSize(GetBackground());
    }

    return ret;
}

void ButtonBase::OnRender(suic::DrawingContext * drawing)
{
    suic::Control::OnRender(drawing);
}

void ButtonBase::OnMouseMove(suic::MouseEventArg& e)
{
    e.SetHandled(true);
    __super::OnMouseMove(e);
}

void ButtonBase::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    e.SetHandled(true);
    SetCaptureMouse();
    __super::OnMouseLeftButtonDown(e);
}

void ButtonBase::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    e.SetHandled(true);
    ReleaseCaptureMouse();

    //
    // 只有鼠标位于元素上才出发Click事件
    //
    if (IsMouseOver())
    {
        suic::RoutedEventArg re(e.GetOriginalSource());

        OnClick(re);
    }

    __super::OnMouseLeftButtonUp(e);
}

void ButtonBase::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    OnMouseLeftButtonDown(e);
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

ImplementTypeofInfo(Button, ButtonBase)

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
    ButtonBase::OnRender(drawing);
}

void Button::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);
    SetFocus();
}

void Button::OnKeyDown(suic::KeyboardEventArg& e)
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

    e.SetHandled(true);
}

ImplementTypeofInfo(SystemMinButton, Button)
ImplementTypeofInfo(SystemMaxButton, Button)
ImplementTypeofInfo(SystemCloseButton, Button)

//-------------------------------------------
SystemMinButton::SystemMinButton()
{
    SetClassName(_T("SystemMinButton"));
    SetToolTip(new suic::OString(_T("最小化")));
    SetFocusable(false);
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
    SetFocusable(false);
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
        SetToolTip(new suic::OString(_T("最大化")));
        suic::HwndHelper::RestoreWindow(this);
    }
    else
    {
        SetToolTip(new suic::OString(_T("向下还原")));
        suic::HwndHelper::MaximizeWindow(this);
    }
}

suic::Size SystemMaxButton::MeasureOverride(const suic::Size& size)
{
    suic::Size ret;
    suic::ImageBrushPtr bkgnd;

    if (GetStyle()->Setters())
    {
        bkgnd = GetStyle()->Setters()->GetValue(_T("Restore"));
    }
    
    if (!bkgnd)
    {
        bkgnd = GetSetters()->GetValue(_T("Restore"));
    }

    if (bkgnd)
    {
        suic::Rect rectBk;

        rectBk = bkgnd->GetContentBrounds();       
        ret.cx += rectBk.Width() + 4;
        ret.cy += rectBk.Height();
    }

    return ret;
}

void SystemMaxButton::OnRender(suic::DrawingContext * drawing)
{
    suic::String strName;

    if (suic::HwndHelper::IsWindowMaximize(this))
    {
        strName = _T("Restore");
        SetToolTip(new suic::OString(_T("向下还原")));
    }
    else
    {
        strName = _T("Max");
        SetToolTip(new suic::OString(_T("最大化")));
    }

    suic::Rect drawrect(0, 0, RenderSize().cx, RenderSize().cy);
    suic::BrushPtr bkgnd(suic::Render::GetProperty(this, GetStyle().get(), strName));

    if (bkgnd)
    {
        bkgnd->Draw(drawing, &drawrect);
    }
}

//-------------------------------------------
SystemCloseButton::SystemCloseButton()
{
    SetClassName(_T("SystemCloseButton"));
    SetToolTip(new suic::OString(_T("关闭")));
    SetFocusable(false);
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
