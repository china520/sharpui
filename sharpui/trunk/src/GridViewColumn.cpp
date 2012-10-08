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
    , _prevWidth(0)
{
    _header = new GridViewColumnHeader();

    _header->HeaderGripper()->MouseLButtonDown += suic::MouseEventHandler(this, &GridViewColumn::OnHeaderGripperStarted);
    _header->HeaderGripper()->MouseMove += suic::MouseEventHandler(this, &GridViewColumn::OnHeaderGripperResize);
    _header->HeaderGripper()->MouseLButtonUp += suic::MouseEventHandler(this, &GridViewColumn::OnHeaderGripperCompleted);
}

GridViewColumn::~GridViewColumn()
{
}

void GridViewColumn::OnHeaderGripperStarted(suic::Element* sender, suic::MouseEventArg& e)
{
    _point = e.MousePoint();
    _prevWidth = _columnWidth;
}

void GridViewColumn::OnHeaderGripperResize(suic::Element* sender, suic::MouseEventArg& e)
{
    int iWid = _prevWidth + e.MousePoint().x - _point.x;

    if (iWid < 10)
    {
        iWid = 10;
    }

    if (iWid != GetColumnWidth())
    {
        int iDelta = iWid - GetColumnWidth();

        SetColumnWidth(iWid);

        suic::Size size = ColumnHeader()->GetDesiredSize();

        size.cx = GetColumnWidth();
        ColumnHeader()->SetDesiredSize(size);

        if (DragDelta)
        {
            DragDeltaEventArg edd(iDelta, 0);

            DragDelta(this, edd);
        }

        if (GetColumnWidth() != iWid)
        {
            //_prevWidth = GetColumnWidth();
        }
    }
}

void GridViewColumn::OnHeaderGripperCompleted(suic::Element* sender, suic::MouseEventArg& e)
{
    ;
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
