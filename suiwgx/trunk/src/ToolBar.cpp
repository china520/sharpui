// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ToolBar.cpp

#include "stdafx.h"

#include <sui/ToolBar.h>
#include <suic/render/uirender.h>

namespace ui
{

//////////////////////////////////////////////////////////////////////////////
// ToolBar

ImplementTypeofInfo(ToolBar, HeaderedItemsControl)

ToolBar::ToolBar()
{
    SetClassName(_T("ToolBar"));
}

ToolBar::~ToolBar()
{
}

void ToolBar::OnInitialized()
{
    __super::OnInitialized();
}

void ToolBar::OnRender(suic::DrawingContext * drawing)
{
}

}
