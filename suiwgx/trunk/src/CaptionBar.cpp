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

ImplementTypeofInfo(CaptionBar, StackLayout)

CaptionBar::CaptionBar()
{
    SetClassName(_T("CaptionBar"));

    _title = new Label();
    _title->SetFocusable(false);

    suic::SetterPtr setPtr(new suic::Setter());

    setPtr->Property = _T("AsControl");
    setPtr->Value = new suic::OString(_T("True"));
    GetSetters()->SetSetter(setPtr);
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
    e.GetHitResult().HitTestCode(HTCAPTION);
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

    _title->SetStyle(GetStyle()->GetStylePart(_T("Label")));

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

    _title->SetHorizontalAlignment(HoriAlignment::Stretch);
    _title->SetVerticalAlignment(VertAlignment::Stretch);

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
    __super::OnRender(drawing);

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
    e.SetHandled(true);
}

void CaptionBar::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    Element::OnMouseLeftButtonDbclk(e);
    e.SetHandled(true);

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

    e.SetHandled(true);
}

void CaptionBar::OnMouseEnter(suic::MouseEventArg& e)
{
    __super::OnMouseEnter(e);
}

void CaptionBar::OnMouseMove(suic::MouseEventArg& e)
{
    suic::WindowPtr winPtr(suic::WindowPtr::cast(suic::VisualHelper::GetRootElement(this)));

    winPtr->DragMove();
    e.SetHandled(true);
}

void CaptionBar::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);
}

}

