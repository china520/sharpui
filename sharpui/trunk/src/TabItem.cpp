// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// TabItem.cpp

#include <sui/TabItem.h>
#include <sui/Selector.h>

#include <suicore/drawing/uirender.h>

namespace ui
{

TabItem::TabItem()
{
    SetClassName(_T("TabItem"));
    SetMinWidth(16);

    SetHorizontalContentAlignment(suic::CENTER);
    SetVerticalContentAlignment(suic::CENTER);
    SetVerticalAlignment(suic::STRETCH);

    SetFocusable(true);
}

TabItem::~TabItem()
{
}

suic::ElementPtr TabItem::FindName(const suic::String& strName)
{
    if (GetName().Equals(strName))
    {
        return this;
    }
    else if (GetTabContent())
    {
        return GetTabContent()->FindName(strName);
    }
    else
    {
        return suic::ElementPtr();
    }
}

void TabItem::AddLogicalChild(suic::Element* child)
{
    if (child->GetWrapper().Equals(_T("TabContent")))
    {
        SetTabContent(child);
    }
    else
    {
        __super::AddLogicalChild(child);
    }
}

void TabItem::OnInitialized()
{
    suic::Control::OnInitialized();
}

void TabItem::OnSetterChanged(suic::SetterChangedEventArg& e)
{
    if (e.GetName().Equals(_T("Header")))
    {
        SetText(e.GetSetter()->ToString());
    }
    else
    {
        __super::OnSetterChanged(e);
    }
}

void TabItem::OnTabContentChanged(suic::Element* oldVal, suic::Element* newVal)
{
    ;
}

void TabItem::SetTabContent(suic::ElementPtr elem)
{
    suic::Element* oldVal = _tabContent.get();

    _tabContent = elem;

    OnTabContentChanged(oldVal, elem.get());
}

void TabItem::OnRender(suic::DrawingContext * drawing)
{
    suic::Control::OnRender(drawing);
}

void TabItem::OnLoaded(suic::LoadedEventArg& e)
{
    __super::OnLoaded(e);

    suic::FrameworkElementPtr frame(GetTabContent());

    if (frame)
    {
        frame->UpdateLoaded(e.GetTarget());
    }
}

void TabItem::OnStyleUpdated()
{
    suic::FrameworkElementPtr frame(GetTabContent());

    if (frame)
    {
        frame->UpdateStyle();
    }
}

void TabItem::OnMouseEnter(suic::MouseEventArg& e)
{
    e.Handled(true);
}

void TabItem::OnMouseMove(suic::MouseEventArg& e)
{
    e.Handled(true);

    __super::OnMouseMove(e);
}

void TabItem::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);
    e.Handled(true);
}

void TabItem::OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnPreviewMouseLeftButtonDown(e);
}

void TabItem::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);

    // 选中
    Selector::SelectItem(this, true);

    e.Handled(true);
}

void TabItem::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);
}

void TabItem::OnGotFocus(suic::FocusEventArg& e)
{
    __super::OnGotFocus(e);

    InvalidateVisual();
}

};
