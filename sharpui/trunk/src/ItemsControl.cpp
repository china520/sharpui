// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ItemsControl.cpp

#include <suicore/drawing/uirender.h>
#include <sui/ItemsControl.h>
#include <sui/textblock.h>
#include <util/vector.h>

namespace ui
{

/// <summary>
///  ItemContainer，Item的容器
/// </summary>
ItemCollection::ItemCollection(suic::Element* itemControl)
    : _itemControl(itemControl)
{
}

ItemCollection::~ItemCollection()
{
}

int ItemCollection::GetCount()
{
    return (int)_items.size();
}

suic::ObjectPtr ItemCollection::GetItem(int iIndex) const
{
    suic::ObjectPtr obj = _items[iIndex];

    return obj;
}

suic::String ItemCollection::GetItemText(int iIndex) const
{
    return _items[iIndex]->ToString();
}

void ItemCollection::HandleItem(suic::ObjectPtr& obj)
{
    suic::ElementPtr item(obj);

    if (item)
    {
        _itemControl->AddLogicalChild(item.get());

        if (!item->IsInitialized())
        {
            if (_itemControl->ReadFlag(CoreFlags::IsInitPending))
            {
                item->BeginInit();
            }
            else if (_itemControl->ReadFlag(CoreFlags::IsInitialized))
            {
                item->BeginInit();
                item->EndInit();
            }
        }

        if (_itemControl->ReadFlag(CoreFlags::IsLoaded))
        {
            if (!item->ReadFlag(CoreFlags::IsLoaded))
            {
                suic::HwndHelper::LoadedElement(item.get());
            }
        }
    }

    if (ContainerChanged)
    {
        suic::NotifyCollectionChangedArg e(suic::NotifyCollectionChangedAction::Add);

        e.AddNewItem(obj);

        ContainerChanged(_itemControl, e);
    }
}

int ItemCollection::InsertItem(int index, suic::ObjectPtr item)
{
    _items.insert(_items.begin() + index, item);

    HandleItem(item);

    return index;
}

int ItemCollection::AddItem(suic::ObjectPtr item)
{
    int index = _items.size();

    _items.push_back(item);
    HandleItem(item);

    return index;
}

void ItemCollection::Clear()
{
    _items.clear();
}

bool ItemCollection::Contains(suic::ObjectPtr item)
{
    return (IndexOf(item) >= 0);
}

int ItemCollection::IndexOf(suic::ObjectPtr item) const
{
    for (int i = 0; i < (int)_items.size(); ++i)
    {
        if (_items[i].get() == item.get())
        {
            return i;
        }
    }

    return -1;
}

void ItemCollection::Remove(suic::ObjectPtr item)
{
    for (int i = 0; i < (int)_items.size(); ++i)
    {
        if (_items[i].get() == item.get())
        {
            RemoveAt(i);

            break;
        }
    }
}

void ItemCollection::RemoveAt(int index)
{
    suic::ObjectPtr itemPtr = _items[index];

    _items.erase(_items.begin() + index);

    if (ContainerChanged)
    {
        suic::NotifyCollectionChangedArg e(suic::NotifyCollectionChangedAction::Remove);

        e.AddOldItem(itemPtr);

        ContainerChanged(_itemControl, e);
    }
}

void ItemCollection::RemoveRange(int index, int count)
{
    _items.erase(_items.begin() + index, _items.begin() + index + count);
}

/// <summary>
///  ItemsControl，Item的基类
/// </summary>
ItemsControl::ItemsControl()
{
    SetClassName(_T(""));

    _items = new ItemCollection(this);
    _items->ContainerChanged.Add(this, &ItemsControl::OnNotifyCollectionChanged);

    InitializeScrollView();
}

ItemsControl::~ItemsControl()
{
}

void ItemsControl::InitializeScrollView()
{
    _itemsHost = new VisualizePanel(_items);
    _scrollHost = new ScrollViewer();

    _scrollHost->SetContent(_itemsHost);
}

bool ItemsControl::HasItems() const
{
    return (GetItems()->GetCount() > 0);
}

bool ItemsControl::IsGrouping() const
{
    return false;
}

ItemCollectionPtr ItemsControl::GetItems() const
{
    return _items;
}

void ItemsControl::CheckAddingItem(suic::ObjectPtr& itemObj)
{
    ;
}

int ItemsControl::GetItemsCount() const
{
    return GetItems()->GetCount();
}

int ItemsControl::AddChild(suic::ObjectPtr value)
{
    CheckAddingItem(value);

    return GetItems()->AddItem(value);
}

int ItemsControl::InsertChild(int index, suic::ObjectPtr value)
{
    CheckAddingItem(value);

    return GetItems()->InsertItem(index, value);
}

int ItemsControl::AddText(const suic::String& text)
{
    return 0;
}

void ItemsControl::RemoveAt(int iIndex)
{
    if (iIndex < GetItems()->GetCount() && iIndex >= 0)
    {        
        GetItems()->RemoveAt(iIndex);
        InvalidateArrange();
    }
}

void ItemsControl::RemoveChild(suic::ObjectPtr ePtr)
{
    GetItems()->Remove(ePtr);
    InvalidateArrange();
}

void ItemsControl::ClearChildren()
{
    GetItems()->Clear();

    InvalidateArrange();
}

suic::ObjectPtr ItemsControl::GetItem(int iIndex) const
{
    return GetItems()->GetItem(iIndex);
}

suic::String ItemsControl::GetItemText(int iIndex) const
{
    return GetItems()->GetItemText(iIndex);
}

/////////////////////////////////////////////////////////////////
// ItemsControl
//
suic::Size ItemsControl::MeasureOverride(const suic::Size& availableSize)
{
    _scrollHost->Measure(availableSize);

    return _scrollHost->GetDesiredSize();
}

suic::Size ItemsControl::ArrangeOverride(const suic::Size& availableSize)
{
    suic::Rect finalRect(0, 0, availableSize.cx, availableSize.cy);

    finalRect.Deflate(GetBorderThickness());

    _scrollHost->Arrange(finalRect);

    return availableSize;
}

void ItemsControl::OnUnloaded(suic::LoadedEventArg& e)
{
    __super::OnUnloaded(e);

    //_scrollView->OnUnloaded(e);
}

void ItemsControl::OnInitialized()
{
    __super::OnInitialized();

    // 加入可视树
    AddVisualChild(_scrollHost.get());
    AddLogicalChild(_scrollHost.get());

    _itemsHost->WriteFlag(CoreFlags::IsComposition, true);
    _scrollHost->WriteFlag(CoreFlags::IsComposition, true);

    _scrollHost->BeginInit();
    _scrollHost->EndInit();

    _scrollHost->SetHorizontalAlignment(suic::STRETCH);
    _scrollHost->SetVerticalAlignment(suic::STRETCH);

    _scrollHost->SetMargin(GetMargin());
    _scrollHost->SetFocusable(false);

    _itemsHost->SetFocusable(false);
}

suic::Element* ItemsControl::GetChild(int index)
{
    return dynamic_cast<suic::Element*>(GetItems()->GetItem(index).get());
}

suic::Int32 ItemsControl::GetChildrenCount()
{
    return GetItems()->GetCount();
}

void ItemsControl::OnNotifyCollectionChanged(suic::ObjectPtr sender, suic::NotifyCollectionChangedArg& e)
{
    OnItemsChanged(e);
}

void ItemsControl::OnItemsChanged(suic::NotifyCollectionChangedArg& e)
{
    WriteFlag(CoreFlags::IsMeasureDirty, true);

    if (e.NewItems()->GetCount() > 0)
    {
        suic::Size availableSize;

        if (e.GetAction() == suic::NotifyCollectionChangedAction::Add)
        {
        }
    }

    if (e.OldItems()->GetCount() > 0)
    {
        if (e.GetAction() == suic::NotifyCollectionChangedAction::Remove)
        {
        }
    }
}

void ItemsControl::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void ItemsControl::OnTextInput(suic::KeyEventArg& e)
{
    _scrollHost->OnKeyDown(e);
}

void ItemsControl::OnKeyDown(suic::KeyEventArg& e)
{
    _scrollHost->OnKeyDown(e);

    if (!e.Handled())
    {
        ;
    }
}

void ItemsControl::OnMouseEnter(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseEnter(e);
}

void ItemsControl::OnMouseMove(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseMove(e);
}

void ItemsControl::OnMouseLeave(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseLeave(e);
}

void ItemsControl::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseLeftButtonDown(e);
}

void ItemsControl::OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e)
{
    //e.Handled(true);
}

void ItemsControl::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseLeftButtonDbclk(e);
}

void ItemsControl::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    e.Handled(true);
    __super::OnMouseLeftButtonUp(e);
}

void ItemsControl::OnMouseWheel(suic::MouseWheelEventArg& e)
{
    e.Handled(true);
}

};
