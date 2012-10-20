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
#include <suicore/drawing/uirender.h>

namespace ui
{

/////////////////////////////////////////////////////////
// Label

Label::Label()
{
    SetClassName(_T("Label"));

    SetVerticalContentAlignment(suic::CENTER);
    SetHorizontalContentAlignment(suic::LEFT);
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
    suic::Render::DrawBackground(drawing, GetStyle()->GetTrigger(), &drawrect);
}

}
