// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// GridView.cpp

#include <sui/GridView.h>

namespace ui
{

//////////////////////////////////////////////////////////////
// GridView
//
GridView::GridView()
{
    SetClassName(_T("GridView"));
}

GridView::~GridView()
{
}

void GridView::OnInitialized()
{
    __super::OnInitialized();
}

void GridView::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

};
