// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ListViewItem.cpp

#include <sui/ListViewItem.h>
#include <sui/TextBlock.h>
#include <sui/GridViewRow.h>

namespace ui
{

//////////////////////////////////////////////////////////////
// ListViewItem
//

ImplementTypeofInfo(ListViewItem, ListBoxItem)

ListViewItem::ListViewItem()
{
    SetClassName(_T("ListViewItem"));
}

ListViewItem::~ListViewItem()
{
}

suic::String ListViewItem::ToString()
{
    GridViewRowPtr row(GetContent());

    if (!row)
    {
        return GetText();
    }
    else
    {
        return row->ToString();
    }
}

suic::ElementPtr ListViewItem::GetColumn(int index)
{
    // 如果内容是GridViewRow
    // 直接取内容
    GridViewRowPtr row(GetContent());

    if (row)
    {
        return row->GetColumn(index);
    }
    else
    {
        return GetContent();
    }
}

void ListViewItem::AddColumn(suic::String text)
{
    GridViewRowPtr row(GetContent());

    if (row)
    {
        row->AddColumn(new ui::TextBlock(text));
    }
}

void ListViewItem::AddColumn(suic::Element* elem)
{
    GridViewRowPtr row(GetContent());

    if (row)
    {
        row->AddColumn(elem);
    }
}

void ListViewItem::SetColumn(int index, suic::String text)
{
    suic::FrameworkElementPtr col(GetColumn(index));

    if (col)
    {
        col->SetText(text);
    }
}

void ListViewItem::SetColumn(int index, suic::Element* elem)
{
    GridViewRowPtr row(GetContent());

    if (row)
    {
        row->SetColumn(index, elem);
    }
}

}
