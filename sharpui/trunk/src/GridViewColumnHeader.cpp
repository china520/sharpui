// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ColumnHeader.cpp

#include <sui/GridViewColumnHeader.h>

namespace ui
{

GridSplitter::GridSplitter()
{
    SetClassName(_T("GridHeaderGripper"));
}

void GridSplitter::OnRender(suic::DrawingContext * drawing)
{
    suic::TriggerPtr trg(GetStyle()->GetTrigger());
    suic::ImageBrushPtr bkgnd(trg->GetValue(suic::BACKGROUND));

    if (bkgnd)
    {
        suic::Rect rectBk = bkgnd->GetContentBrounds();
        suic::Rect drawrect(0, 0, RenderSize.cx, RenderSize.cy);

        drawrect.left = (RenderSize.cx - rectBk.Width()) / 2;
        drawrect.right = drawrect.left + rectBk.Width();
        drawrect.top = (RenderSize.cy - rectBk.Height()) / 2;
        drawrect.bottom = drawrect.top + rectBk.Height();

        bkgnd->Draw(drawing, &drawrect);
    }
    else
    {
        __super::OnRender(drawing);
    }
}

void GridSplitter::OnMouseMove(suic::MouseEventArg& e)
{
    if (IsMouseCaptured())
    {
        __super::OnMouseMove(e);
    }

    e.Handled(true);
}

void GridSplitter::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);

    SetCaptureMouse();

    e.Handled(true);
}

void GridSplitter::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonUp(e);

    ReleaseCaptureMouse();

    e.Handled(true);
}

//////////////////////////////////////////////////////////////
// GridViewColumnHeader
//
GridViewColumnHeader::GridViewColumnHeader()
{
    SetClassName(_T("GridViewColumnHeader"));

    _headerGripper.SetAutoDelete(false);
    _headerGripper.SetMinWidth(1);
}

GridViewColumnHeader::~GridViewColumnHeader()
{
}

void GridViewColumnHeader::OnInitialized()
{
    __super::OnInitialized();

    _headerGripper.SetStyle(FindResource(_headerGripper.GetClassName()));

    _headerGripper.BeginInit();
    _headerGripper.EndInit();
}

void GridViewColumnHeader::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

suic::Size GridViewColumnHeader::MeasureOverride(const suic::Size& size)
{
    suic::Size ret;

    _headerGripper.Measure(size);
    __super::MeasureOverride(size);

    ret = GetDesiredSize();
    ret.cx += _headerGripper.GetDesiredSize().cx;

    return ret;
}

suic::Size GridViewColumnHeader::ArrangeOverride(const suic::Size& size)
{
    return __super::ArrangeOverride(size);
}

}
