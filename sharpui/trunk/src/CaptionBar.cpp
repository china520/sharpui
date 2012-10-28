// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// CaptionBar.cpp

#include <sui/captionbar.h>

namespace ui
{

CaptionBar::CaptionBar()
{
    SetClassName(_T("CaptionBar"));

    _title = TextBlockPtr(new TextBlock());
    _title->SetFocusable(false);

}

CaptionBar::~CaptionBar()
{
}

void CaptionBar::HideMinBox(bool value)
{
    suic::ElementPtr element = FindName(_T("MinBox"));

    if (element)
    {
        element->SetVisible(value);
    }
}

void CaptionBar::HideMaxBox(bool value)
{
    suic::ElementPtr element = FindName(_T("MaxBox"));

    if (element)
    {
        element->SetVisible(value);
    }

    element = FindName(_T("RestoreBox"));

    if (element)
    {
        element->SetVisible(value);
    }
}

void CaptionBar::HideCloseBox(bool value)
{
    suic::ElementPtr element = FindName(_T("CloseBox"));

    if (element)
    {
        element->SetVisible(value);
    }
}

static void OnHitTestResult(suic::Element* pSender, suic::HitResultEventArg& e)
{
    e.GetHitResult()->HitTestCode(HTCAPTION);
}

void CaptionBar::OnInitialized()
{
    // 
    // 调用基类进行事件分发处理
    //
    __super::OnInitialized();

    SystemCloseButton* closePtr(new SystemCloseButton());
    SystemMinButton* minPtr(new SystemMinButton());
    SystemMaxButton* maxPtr(new SystemMaxButton());

    InsertChild(0, _title.get());
    AddChild(minPtr);
    AddChild(maxPtr);
    AddChild(closePtr);

    _title->SetStyle(FindResource(_T("TextBlock")));

    _title->BeginInit();
    _title->EndInit();

    minPtr->SetStyle(FindResource(minPtr->GetClassName()));
    maxPtr->SetStyle(FindResource(maxPtr->GetClassName()));
    closePtr->SetStyle(FindResource(closePtr->GetClassName()));

    minPtr->BeginInit();
    minPtr->EndInit();

    maxPtr->BeginInit();
    maxPtr->EndInit();

    closePtr->BeginInit();
    closePtr->EndInit();

    //_layout.InvalidateMeasure();

    _title->SetHorizontalAlignment(_T("Stretch"));
    _title->SetVerticalAlignment(_T("Stretch"));

    suic::ObjectPtr value = GetStyle()->GetValue(_T("HideMinBox"));

    if (value)
    {
        minPtr->SetVisible(!value->ToBool());
    }

    value = GetStyle()->GetValue(_T("HideMaxBox"));

    if (value)
    {
        maxPtr->SetVisible(!value->ToBool());
    }

    value = GetStyle()->GetValue(_T("HideCloseBox"));

    if (value)
    {
        closePtr->SetVisible(!value->ToBool());
    }

    _maxBtn = maxPtr;
}

void CaptionBar::OnRender(suic::DrawingContext * drawing)
{
    // 
    // 直接调用基类进行绘制
    //
    FrameworkElement::OnRender(drawing);

    suic::String strTitle = GetText();

    if (suic::VisualHelper::GetRootElement(this) && strTitle.Empty())
    {
        strTitle = suic::VisualHelper::GetRootElement(this)->GetText();
    }

    _title->SetText(strTitle);
}

void CaptionBar::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    Element::OnMouseLeftButtonDown(e);
    suic::WindowPtr winPtr(suic::WindowPtr::cast(suic::VisualHelper::GetRootElement(this)));
    winPtr->DragMove();
    e.Handled(true);
}

void CaptionBar::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    Element::OnMouseLeftButtonDbclk(e);
    e.Handled(true);

    if (_maxBtn->IsVisible())
    {
        bool bIsMax = suic::HwndHelper::IsWindowMaximize(this);

        if (bIsMax)
        {
            suic::HwndHelper::RestoreWindow(this);
        }
        else
        {
            suic::HwndHelper::MaximizeWindow(this);
        }
    }
}

void CaptionBar::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    Element::OnMouseLeftButtonUp(e);

    e.Handled(true);
}

void CaptionBar::OnMouseEnter(suic::MouseEventArg& e)
{
    __super::OnMouseEnter(e);
}

void CaptionBar::OnMouseMove(suic::MouseEventArg& e)
{
    suic::WindowPtr winPtr(suic::WindowPtr::cast(suic::VisualHelper::GetRootElement(this)));

    winPtr->DragMove();
    e.Handled(true);
}

void CaptionBar::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);
}

}

