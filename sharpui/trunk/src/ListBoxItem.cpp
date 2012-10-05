// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ListBox.cpp

#include <sui/listboxitem.h>
#include <suicore/uimousedriver.h>
#include <suicore/drawing/uirender.h>
#include <sui/listbox.h>

namespace ui
{

ListBoxItem::ListBoxItem()
{
    SetClassName(_T("ListBoxItem"));
    SetMinHeight(16);
    SetHorizontalContentAlignment(suic::LEFT);
}

ListBoxItem::~ListBoxItem()
{
}

void ListBoxItem::OnSetterChanged(suic::SetterChangedEventArg& e)
{
    __super::OnSetterChanged(e);
}

void ListBoxItem::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    suic::Element::OnMouseLeftButtonDown(e);

    if (!e.Handled())
    {
        Selector::SelectItem(this, true);

        InvalidateVisual();
    }
}

void ListBoxItem::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    suic::Control::OnMouseLeftButtonUp(e);

    ListBox* pParent = dynamic_cast<ListBox*>(LogicalParent());

    if (pParent)
    {
        pParent->OnMouseLeftButtonUp(e);
    }
}

void ListBoxItem::OnRender(suic::DrawingContext * drawing)
{
    if (IsEnabled() && IsSelected())
    {
        suic::TriggerPtr setter = GetStyle()->GetTrigger(suic::FOCUSED);

        if (!setter)
        {
            setter = GetStyle()->GetTrigger();
        }

        if (setter)
        {
            suic::UIRender::Draw(drawing, this, setter);
        }
    }
    else
    {
        suic::Control::OnRender(drawing);
    }
}

}
