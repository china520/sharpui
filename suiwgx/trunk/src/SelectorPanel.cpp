// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// SelectorPanel.cpp

#include "stdafx.h"

#include <sui/SelectorPanel.h>
#include <suic/render/uirender.h>

namespace ui
{

//////////////////////////////////////////////////////////////////////////////
// SelectorPanel

ImplementTypeofInfo(SelectorPanel, suic::Panel)

SelectorPanel::SelectorPanel()
{
    SetClassName(_T("SelectorPanel"));
}

SelectorPanel::~SelectorPanel()
{
}

void SelectorPanel::OnInitialized()
{
    __super::OnInitialized();
}

void SelectorPanel::OnRender(suic::DrawingContext * drawing)
{
}

}
