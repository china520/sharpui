// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ToolBarItem.cpp

#include "stdafx.h"

#include <sui/ToolBarItem.h>
#include <suic/render/uirender.h>

namespace ui
{

//////////////////////////////////////////////////////////////////////////////
// ToolBarItem

ImplementTypeofInfo(ToolBarItem, ButtonBase)

ToolBarItem::ToolBarItem()
{
    SetClassName(_T("ToolBarItem"));
}

ToolBarItem::~ToolBarItem()
{
}

bool ToolBarItem::IsChecked() const
{
    return IsSelected();
}

void ToolBarItem::SetChecked(bool val)
{
    SetSelected(val);
}

void ToolBarItem::OnClick(suic::RoutedEventArg& e)
{
    __super::OnClick(e);
}

void ToolBarItem::OnInitialized()
{
    __super::OnInitialized();
}

void ToolBarItem::OnRender(suic::DrawingContext * drawing)
{
    suic::Render::RenderBackground(drawing, this);

    // 绘制图标
    suic::ImageBrushPtr brPtr(suic::Render::GetProperty(this, GetStyle().get(), _T("Glyph")));

    if (brPtr)
    {
        suic::Rect rcBounds(brPtr->GetContentBrounds());
        suic::Rect rect;

        rect.left = (RenderSize().cx - rcBounds.Width()) / 2;
        rect.top = (RenderSize().cy - rcBounds.Height()) / 2;
        rect.right = rect.left + rcBounds.Width();
        rect.bottom = rect.top + rcBounds.Height();

        brPtr->Draw(drawing, &rect);
    }
}

}
