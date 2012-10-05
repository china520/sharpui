// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// TabPanel.cpp

#include <sui/TabPanel.h>

namespace ui
{

//////////////////////////////////////////////////////////////
// TabLayout
//
TabPanel::TabPanel()
{
    SetClassName(_T("TabLayout"));
}

TabPanel::~TabPanel()
{
}

void TabPanel::OnInitialized()
{
    __super::OnInitialized();
}

void TabPanel::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

void TabPanel::OnGotFocus(suic::FocusEventArg& e)
{

}

};
