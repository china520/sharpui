// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// Selector.cpp

#include <sui/Selector.h>

namespace ui
{

SelectionChangedEventArg::SelectionChangedEventArg()
: suic::RoutedEventArg(suic::ObjectPtr())
{
}

void SelectionChangedEventArg::AddItem(suic::ObjectPtr item, bool bAdd)
{
    if (bAdd)
    {
        _addItems.Add(item);
    }
    else
    {
        _removeItems.Add(item);
    }
}

ItemContentList* SelectionChangedEventArg::AddedItems()
{
    return &_addItems;
}

ItemContentList* SelectionChangedEventArg::RemovedItems()
{
    return &_removeItems;
}
// ============================================================================
// Selector，Item的基类。
// ============================================================================

Selector::Selector()
    : _selectMode(SelectionMode::Single)
    , _focusItem(NULL)
{
}

Selector::~Selector()
{
}

Selector* Selector::SelectorFromItem(suic::Element* pElem)
{
    suic::Element* pParent = pElem->LogicalParent();

    while (pParent)
    {
        Selector* pRet = dynamic_cast<Selector*>(pParent);

        if (pRet)
        {
            return pRet;
        }

        pParent = pParent->LogicalParent();
    }

    return NULL;
}

void Selector::SelectItem(suic::ObjectPtr item, bool selected)
{
    suic::ElementPtr pElem(item);
    Selector* pSelector = Selector::SelectorFromItem(pElem.get());

    if (!pElem || !pSelector)
    {
        ;
    }
    else
    {
        ItemSelectionEventArg es(selected, 0);

        pElem->WriteFlag(CoreFlags::IsSelected, selected);
        pSelector->OnItemSelected(item, es);
    }
}

int Selector::SelectedIndex()
{
    return -1;
}

void Selector::SelectedIndex(int iIndex)
{
    suic::ElementPtr viewPtr(GetItems()->GetItem(iIndex));

    SelectItem(viewPtr.get(), true);
}

suic::ObjectPtr Selector::SelectedItem()
{
    suic::ObjectPtr ret;

    if (_selectedItems.GetCount() > 0)
    {
        ret = _selectedItems.GetAt(0);
    }
    
    return ret;
}

void Selector::SelectedItem(suic::ObjectPtr obj)
{
    int index = GetItems()->IndexOf(obj);

    if (index >= 0)
    {
        SelectedIndex(index);
    }
}

void Selector::UnselectAllItems()
{
    for (int i = 0; i < _selectedItems.GetCount(); ++i)
    {
        suic::ElementPtr item(_selectedItems.GetAt(i));

        item->WriteFlag(CoreFlags::IsSelected, false);
    }

    _selectedItems.Reset();

    if (_focusItem)
    {
        _focusItem->WriteFlag(CoreFlags::IsSelected, false);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
void Selector::OnItemSelected(suic::ObjectPtr item, ItemSelectionEventArg& e)
{
    suic::Element* oldFocus = _focusItem;
    SelectionChangedEventArg ec;
    suic::Element* pItem = dynamic_cast<suic::Element*>(item.get());

    if (e.IsSelected())
    {
        if (_focusItem != pItem)
        {
            _focusItem = pItem;
        }

        if (ItemSelected)
        {
            ItemSelected(pItem);
        }
    }
    else
    {
        if (_focusItem == pItem)
        {
            _focusItem = NULL;
        }

        if (ItemUnselected)
        {
            ItemUnselected(pItem);
        }
    }

    ec.AddItem(item, e.IsSelected());
    OnSelectionChanged(ec);

    if (_focusItem && _focusItem != oldFocus)
    {
        _focusItem->Focus();
    }
}

void Selector::OnSelectionChanged(SelectionChangedEventArg& e)
{
    if (e.RemovedItems()->GetCount() > 0)
    {
        for (int i = 0; i < e.RemovedItems()->GetCount(); ++i)
        {
            _selectedItems.Remove(e.RemovedItems()->GetAt(i));
        }
    }

    if (e.AddedItems()->GetCount() > 0)
    {
        if (_selectMode == SelectionMode::Single)
        {
            if (_selectedItems.GetCount() > 0
                && _selectedItems.GetAt(0) != e.AddedItems()->GetAt(0))
            {
                suic::ElementPtr pElem(_selectedItems.GetAt(0));

                Selector::SelectItem(_selectedItems.GetAt(0), false);

                pElem->InvalidateVisual();
            }

            _selectedItems.Reset();
        }

        for (int i = 0; i < e.AddedItems()->GetCount(); ++i)
        {
            suic::ObjectPtr itemPtr = e.AddedItems()->GetAt(i);

            _selectedItems.Add(itemPtr);
        }
    }

    if (SelectionChanged)
    {
        SelectionChanged(this, e);
    }
}

void Selector::OnInitialized()
{
    __super::OnInitialized();

    for (int i = 0; i < GetItems()->GetCount(); ++i)
    {
        suic::FrameworkElementPtr itemPtr(GetItems()->GetItem(i));
        suic::ObjectPtr obj = itemPtr->GetStyle()->GetValue(_T("IsSelected"));

        if (obj && obj->ToBool())
        {
            SelectedIndex(i);
        }
    }
}

void Selector::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void Selector::OnTextInput(suic::KeyEventArg& e)
{
    __super::OnTextInput(e);
}

void Selector::OnKeyDown(suic::KeyEventArg& e)
{
    if (e.IsLeftArrow())
    {
        _scrollView->LineLeft();
    }
    else if (e.IsRightArrow())
    {
        _scrollView->LineRight();
    }
    else if (e.IsUpArrow())
    {
        ;
    }
    else if (e.IsDownArrow())
    {
        ;
    }
    else if (e.IsPageup())
    {
        ;
    }
    else if (e.IsPagedown())
    {
        ;
    }
    else if (e.IsHomeKey())
    {
        ;
    }
    else if (e.IsEndKey())
    {
        ;
    }
    else
    {
        __super::OnKeyDown(e);
        return;
    }

    e.Handled(true);
}

void Selector::OnMouseEnter(suic::MouseEventArg& e)
{
    __super::OnMouseEnter(e);

    e.Handled(true);
}

void Selector::OnMouseMove(suic::MouseEventArg& e)
{
    __super::OnMouseMove(e);
}

void Selector::OnMouseLeave(suic::MouseEventArg& e)
{
    __super::OnMouseLeave(e);

    e.Handled(true);
}

void Selector::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);
}

void Selector::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDbclk(e);
}

void Selector::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);
}

void Selector::OnItemsChanged(NotifyContainerChangedArg& e)
{
    __super::OnItemsChanged(e);
}

};
