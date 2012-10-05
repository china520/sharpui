// =============================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// =============================================================

////////////////////////////////////////////////////////////////
// GridViewColumn.cpp

#include <sui/GridViewColumn.h>

namespace ui
{

////////////////////////////////////////////////////////////////
// GridViewColumn
//
GridViewColumn::GridViewColumn()
    : _actualIndex(0)
    , _columnWidth(20)
    , _columnDesired(20)
{
    _header = new GridViewColumnHeader();
    _header->HeaderGripper()->DragDelta += DragDeltaHandler(this, &GridViewColumn::OnColumnHeaderResize);
}

GridViewColumn::~GridViewColumn()
{
}

void GridViewColumn::
OnColumnHeaderGripperDragStarted(suic::ObjectPtr sender, DragStartedEventArg& e)
{

}

void GridViewColumn::
OnColumnHeaderResize(suic::ObjectPtr sender, DragDeltaEventArg& e)
{
    _columnWidth += e.HorizontalChange();

    if (_columnWidth < 10)
    {
        _columnWidth = 10;
    }

    suic::Size size = ColumnHeader()->GetDesiredSize();

    size.cx = GetColumnWidth();
    ColumnHeader()->SetDesiredSize(size);

    if (DragDelta)
    {
        DragDelta(this, e);
    }
}

void GridViewColumn::
OnColumnHeaderGripperDragCompleted(suic::ObjectPtr sender, DragCompletedEventArg& e)
{

}

GridViewColumnHeader* GridViewColumn::ColumnHeader()
{
    return _header.get();
}

int GridViewColumn::GetActualIndex() const
{
    return _actualIndex;
}

void GridViewColumn::SetActualIndex(int index)
{
    _actualIndex = index;
}

//===========================================================
//
ColumnHeaderCollection::ColumnHeaderCollection()
{
}

void ColumnHeaderCollection::Add(GridViewColumn* pColumn, int wid)
{
    pColumn->SetActualIndex(_colomns.size());
    pColumn->SetColumnWidth(wid);

    _colomns.push_back(pColumn);

    if (ColumnHeaderChanged)
    {
        ColumnHeaderChanged(pColumn, 1);
    }
}

void ColumnHeaderCollection::Add(suic::String text, int wid)
{
    GridViewColumn * pColumn = new GridViewColumn();

    pColumn->ColumnHeader()->SetText(text);
    Add(pColumn, wid);
}

void ColumnHeaderCollection::Remove(GridViewColumn* pColumn)
{
    for (int i = 0; i < GetCount(); ++i)
    {
        if (_colomns[i].get() == pColumn)
        {
            _colomns.erase(_colomns.begin() + i);
            break;
        }
    }
}

int ColumnHeaderCollection::GetCount() const
{
    return (int)_colomns.size();
}

GridViewColumn* ColumnHeaderCollection::GetColumn(int index)
{
    return _colomns[index].get();
}

void ColumnHeaderCollection::Clear()
{
    _colomns.clear();
}

};
