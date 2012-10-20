// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ItemContainer.cpp

#include <sui/ItemContainer.h>
#include <sui/textblock.h>
#include <util/vector.h>
#include <suicore/drawing/uirender.h>
#include <sui/Selector.h>

namespace ui
{

//ItemContent::~ItemContent()
//{
//}
//
//ItemContent::ItemContent()
//{
//    SetClassName(_T("ContentItem"));
//    SetHorizontalContentAlignment(suic::LEFT);
//
//    WriteFlag(CoreFlags::IsSupportMouseOver, true);
//
//    SetMinHeight(ITEM_MINHEIGHT);
//}
//
//bool ItemContent::IsValidName(suic::String name)
//{
//    return true;
//}
//
//bool ItemContent::IsSelected() const
//{
//    return ReadFlag(CoreFlags::IsSelected);
//}
//
//void ItemContent::Select()
//{
//    if (!ReadFlag(CoreFlags::IsSelected))
//    {
//        Selector::SelectItem(this, true);
//    }
//}
//
//void ItemContent::Unselect()
//{
//    if (ReadFlag(CoreFlags::IsSelected))
//    {
//        Selector::SelectItem(this, false);
//    }
//}
//
//void ItemContent::OnMouseEnter(suic::MouseEventArg& e)
//{
//    e.Handled(true);
//
//    __super::OnMouseEnter(e);
//}
//
//suic::Size ItemContent::MeasureOverride(const suic::Size& availableSize)
//{
//    if (GetLogicalChildrenCount() == 0)
//    {
//        suic::Size size = Element::MeasureOverride(availableSize);
//
//        if (size.cx <= 0 || size.cy <= 0)
//        {
//            suic::StylePtr sty(GetStyle());
//
//            if (sty)
//            {
//                suic::TriggerPtr setter;
//
//                if (IsSelected() || IsMouseDown())
//                {
//                    setter = sty->GetTrigger(suic::FOCUSED);
//                }
//
//                if (!setter)
//                {
//                    setter = suic::UIRender::GetSettersByStatus(this, sty);
//                }
//
//                size = suic::UIRender::MeasureTextSize(GetText(), setter);
//            }
//        }
//
//        size.cx += GetPadding().left + GetPadding().right;
//        size.cy += GetPadding().top + GetPadding().bottom;
//
//        return size;
//    }
//    else
//    {
//        return __super::MeasureOverride(availableSize);
//    }
//}
//
//void ItemContent::OnInitialized()
//{
//    __super::OnInitialized();
//}
//
//void ItemContent::OnRender(suic::DrawingContext * drawing)
//{
//    if (GetStyle())
//    {
//        if (IsEnabled() && IsSelected())
//        {
//            suic::TriggerPtr setter = GetStyle()->GetTrigger(suic::FOCUSED);
//
//            if (!setter)
//            {
//                setter = GetStyle()->GetTrigger();
//            }
//
//            if (setter)
//            {
//                suic::UIRender::Draw(drawing, this, setter);
//            }
//        }
//        else
//        {
//            suic::Control::OnRender(drawing);
//        }
//    }
//}
//
//void ItemContent::OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e)
//{
//    //if (!ReadFlag(suic::IsSelected))
//    {
//        Selector::SelectItem(this, true);
//
//        InvalidateVisual();
//    }
//}
//
//void ItemContent::OnMouseLeftButtonDown(suic::MouseEventArg& e)
//{
//    suic::Element::OnMouseLeftButtonDown(e);
//
//    if (!e.Handled())
//    {
//        //e.Handled(true);
//
//        //if (!ReadFlag(suic::IsSelected))
//        {
//            Selector::SelectItem(this, true);
//
//            InvalidateVisual();
//        }
//    }
//}
//
//void ItemContent::OnMouseLeftButtonUp(suic::MouseEventArg& e)
//{
//    suic::Control::OnMouseLeftButtonUp(e);
//
//    InvalidateVisual();
//}

ItemContentList::ItemContentList()
{
    _items = suic::CreateEnumerator();
}

ItemContentList::~ItemContentList()
{
}

suic::Int32 ItemContentList::GetCount()
{
    return _items->GetCount();
}

suic::ObjectPtr ItemContentList::GetAt(suic::Int32 index)
{
    return _items->GetAt(index);
}

void ItemContentList::Add(suic::ObjectPtr item)
{
    _items->Add(item);
}

bool ItemContentList::Remove(suic::ObjectPtr item)
{
    return _items->Remove(item);
}

suic::ObjectPtr ItemContentList::RemoveAt(suic::Int32 index)
{
    return _items->RemoveAt(index);
}

void ItemContentList::Reset()
{
    _items->Reset();
}

NotifyContainerChangedArg::NotifyContainerChangedArg(int ac)
    : _action(ac)
    , suic::RoutedEventArg(suic::ObjectPtr())
{
}

void NotifyContainerChangedArg::AddNewItem(suic::ObjectPtr item)
{
    _newItems.Add(item);
}

void NotifyContainerChangedArg::AddOldItem(suic::ObjectPtr item)
{
    _oldItems.Add(item);
}

ItemContentList* NotifyContainerChangedArg::NewItems()
{
    return &_newItems;
}

ItemContentList* NotifyContainerChangedArg::OldItems()
{
    return &_oldItems;
}

};
