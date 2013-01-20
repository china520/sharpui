// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// CheckButton.cpp

#include <sui/CheckButton.h>
#include <suic/render/uirender.h>

namespace ui
{

ImplementTypeofInfo(CheckButton, ButtonBase)

CheckButton::CheckButton() 
    : _bChecked(false)
    , _bAutoSize(true)
    , _bAdjusted(false)
{
    SetClassName(_T("CheckButton"));
    SetHorizontalContentAlignment(HoriAlignment::Left);
    SetPadding(suic::Rect(2,0,0,0));
}

CheckButton::~CheckButton()
{
}

void CheckButton::OnInitialized()
{
    // 
    // 调用基类进行事件分发处理
    //
    ButtonBase::OnInitialized();

    _bAdjusted = false;
}

void CheckButton::OnPropertyChanged(suic::PropertyChangedEventArg& e)
{
    //
    // 初始化控件本身资源
    //
    if (e.GetName().Equals(_T("AutoSize")))
    {
        if (e.GetSetter()->ToString().Equals(_T("False")))
        {
            SetAutoSize(false);
        }
    }
    else
    {
        //
        // 必须调用基类初始化基本数据
        //
        __super::OnPropertyChanged(e);
    }
}

void CheckButton::SetAutoSize(bool val)
{
    _bAutoSize = val;
}

bool CheckButton::GetAutoSize() const
{
    return _bAutoSize;
}

bool CheckButton::IsChecked() const
{
    return _bChecked;
}

void CheckButton::SetCheck(bool val)
{
    if (val != _bChecked)
    {
        _bChecked = val;
        CheckedEventArg evt(_bChecked);
    
        if (val && NULL != Checked)
        {
            //TriggerEvent(Checked, evt);
        }
    }
}

void CheckButton::AutoCalcSize()
{
}

suic::Size CheckButton::MeasureOverride(const suic::Size& size)
{
    suic::Size ret;

    if (GetStyle())
    {
        suic::SetterCollectionPtr& setPtr = GetStyle()->Setters();
        suic::ImageBrushPtr bkgnd(setPtr->GetValue(InternalBackgrount()));

        if (bkgnd)
        {
            suic::Size sizeImg;
            suic::Rect rectBk;

            rectBk = bkgnd->GetContentBrounds();       
            ret = suic::Render::MeasureTextSize(GetText(), GetFont());

            ret.cx += rectBk.Width() + 4;
            ret.cy += rectBk.Height();
        }
    }

    return ret;
}

//////////////////////////////////////////////////////////////////////////////
// CheckButton

suic::String CheckButton::InternalBackgrount()
{
    if (_bChecked)
    {
        return _T("Checked");
    }
    else
    {
        return _T("Unchecked");
    }
}

void CheckButton::OnRender(suic::DrawingContext * drawing)
{
    if (GetStyle())
    {
        // 
        // 先绘制背景
        //
        suic::Rect drawrect(0, 0, RenderSize().cx, RenderSize().cy);
        suic::ImageBrushPtr bkgnd(suic::Render::GetProperty(this, GetStyle().get(), InternalBackgrount()));

        if (bkgnd)
        {
            suic::Rect rectBk = bkgnd->GetContentBrounds();

            drawrect.right = drawrect.left + rectBk.Width();
            drawrect.top += (drawrect.Height() - rectBk.Height()) / 2;
            drawrect.bottom = drawrect.top + rectBk.Height();

            bkgnd->Draw(drawing, &drawrect);
        }

        //
        // 绘制文字
        //
        drawrect.top = 0;
        drawrect.bottom = RenderSize().cy;
        drawrect.left = drawrect.right + GetPadding().left;
        drawrect.right = RenderSize().cx;

        suic::Render::RenderText(drawing, this, GetText(), &drawrect, true);
    }
}

void CheckButton::OnKeyDown(suic::KeyboardEventArg& e)
{
    if (e.IsSpacePress())
    {
        if (IsFocused())
        {
            SetCheck(!_bChecked);
            e.SetHandled(true);
        }
    }
}

void CheckButton::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    if (IsMouseOver())
    {
        // 触发选中事件
        SetCheck(!_bChecked);
    }

    __super::OnMouseLeftButtonUp(e);
}

void CheckButton::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    OnMouseLeftButtonDown(e);
}

void CheckButton::OnGotFocus(suic::FocusEventArg& e)
{
    __super::OnGotFocus(e);
    e.SetHandled(true);
}

void CheckButton::OnLostFocus(suic::FocusEventArg& e)
{
}

}
