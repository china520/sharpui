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

#include <suic/render/uirender.h>

namespace ui
{

ImplementTypeofInfo(TabItem, Selector)

TabItem::TabItem()
{
    SetClassName(_T("TabItem"));
    SetMinWidth(16);

    SetHorizontalContentAlignment(HoriContentAlignment::Center);
    SetVerticalContentAlignment(VertContentAlignment::Center);
    SetVerticalAlignment(VertAlignment::Stretch);

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

int TabItem::AddChild(suic::ObjectPtr child)
{
    suic::ElementPtr pElem(child);

    if (pElem->GetWrapper().Equals(_T("TabContent")))
    {
        SetTabContent(child);

        return 0;
    }
    else
    {
        return __super::AddChild(child);
    }
}

void TabItem::OnInitialized()
{
    suic::Control::OnInitialized();
}

void TabItem::OnPropertyChanged(suic::PropertyChangedEventArg& e)
{
    if (e.GetName().Equals(_T("Header")))
    {
        SetText(e.GetSetter()->ToString());
    }
    else
    {
        __super::OnPropertyChanged(e);
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
    AddLogicalChild(elem);

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
    e.SetHandled(true);
}

void TabItem::OnMouseMove(suic::MouseEventArg& e)
{
    e.SetHandled(true);

    __super::OnMouseMove(e);
}

void TabItem::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);
    e.SetHandled(true);
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

    e.SetHandled(true);
}

void TabItem::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);
}

void TabItem::OnGotFocus(suic::FocusEventArg& e)
{
    __super::OnGotFocus(e);
}

};
