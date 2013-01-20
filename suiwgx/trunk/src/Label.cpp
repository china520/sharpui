// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// Label.cpp

#include "stdafx.h"

#include <sui/Label.h>
#include <suic/render/uirender.h>

namespace ui
{

/////////////////////////////////////////////////////////
// Label

ImplementTypeofInfo(Label, suic::ContentControl)

Label::Label()
{
    SetClassName(_T("Label"));

    SetVerticalContentAlignment(VertContentAlignment::Center);
    SetHorizontalContentAlignment(HoriContentAlignment::Left);
}

Label::Label(suic::String text)
{
    this->Label::Label();
    SetText(text);
}

Label::~Label()
{
}

suic::Size Label::MeasureOverride(const suic::Size& availableSize)
{
    return __super::MeasureOverride(availableSize);
}

void Label::OnInitialized()
{
    __super::OnInitialized();
}

void Label::OnRender(suic::DrawingContext * drawing)
{
    suic::Rect drawrect(0, 0, RenderSize().cx, RenderSize().cy);

    // 
    // 先绘制背景
    //
    suic::Render::RenderBackground(drawing, this, &drawrect);
    suic::Render::RenderText(drawing, this, GetText(), true);
}

}
