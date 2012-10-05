// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// GridViewRow.cpp

#include <sui/GridViewRow.h>
#include <sui/TextBlock.h>

namespace ui
{

//////////////////////////////////////////////////////////////
// GridViewRow
//
GridViewRow::GridViewRow(ColumnHeaderCollectionPtr& colomns)
{
    SetClassName(_T("GridViewRow"));

    _colomns = colomns;
}

GridViewRow::~GridViewRow()
{
}

void GridViewRow::AddColumn(suic::ObjectPtr item)
{
    suic::ElementPtr pElem(item);

    if (!pElem)
    {
        pElem = new ui::TextBlock(item->ToString());
    }

    if (IsInitialized())
    {
        pElem->BeginInit();
        pElem->EndInit();
    }

    _cells.push_back(item);
}

void GridViewRow::SetColumn(int index, suic::ObjectPtr item)
{
    _cells[index] = item;
}

suic::ObjectPtr GridViewRow::GetColumn(int index)
{
    return _cells[index];
}

suic::Element* GridViewRow::GetLogicalChild(int index)
{
    return _cells[index].get();
}

suic::Int32 GridViewRow::GetLogicalChildrenCount()
{
    return (suic::Int32)_cells.size();
}

suic::Size GridViewRow::MeasureOverride(const suic::Size& availableSize)
{
    int iColumnHei = 0;

    for (int i = 0; i < (int)_cells.size(); ++i)
    {
        _cells[i]->Measure(availableSize);

        if (_cells[i]->GetDesiredSize().cy > iColumnHei)
        {
            iColumnHei = _cells[i]->GetDesiredSize().cy;
        }
    }

    return suic::Size(0, iColumnHei);
}

suic::Size GridViewRow::ArrangeOverride(const suic::Size& size)
{
    ClearVisualChildren();

    suic::Rect finalRect(0, 0, size.cx, size.cy);

    for (int i = 0; i < (int)_cells.size(); ++i)
    {
        GridViewColumn* pColumn = _colomns->GetColumn(i);

        finalRect.right = finalRect.left + pColumn->GetColumnWidth();

        AddVisualChild(_cells[i].get());
        _cells[i]->Arrange(finalRect);

        finalRect.left = finalRect.right + pColumn->ColumnHeader()->HeaderGripper()->GetDesiredSize().cx;
    }

    return size;
}

void GridViewRow::OnInitialized()
{
    __super::OnInitialized();

    for (int i = 0; i < (int)_cells.size(); ++i)
    {
        _cells[i]->BeginInit();
        _cells[i]->EndInit();
    }
}

void GridViewRow::OnRender(suic::DrawingContext * drawing)
{
    //__super::OnRender(drawing);
}

}
