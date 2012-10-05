// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// TextBlock.cpp

#include "stdafx.h"

#include <sui/TextBlock.h>
#include <suicore/drawing/uirender.h>

namespace ui
{

/////////////////////////////////////////////////////////
// TextBlock

TextBlock::TextBlock()
{
    SetClassName(_T("TextBlock"));

    SetVerticalContentAlignment(suic::CENTER);
    SetHorizontalContentAlignment(suic::LEFT);
}

TextBlock::TextBlock(suic::String text)
{
    this->TextBlock::TextBlock();
    SetText(text);
}

TextBlock::~TextBlock()
{
}

suic::Size TextBlock::MeasureOverride(const suic::Size& availableSize)
{
    suic::TriggerPtr setter(suic::UIRender::GetTriggerByStatus(this, GetStyle()));

    if (setter.get())
    {
        suic::Size ret = suic::UIRender::MeasureTextSize(GetText(), setter);

        ret.cx += 2;
        MeasureCheck(ret);

        return ret;
    }
    else
    {
        return __super::MeasureOverride(availableSize);
    }
}

void TextBlock::OnInitialized()
{
    __super::OnInitialized();
}

void TextBlock::OnRender(suic::DrawingContext * drawing)
{
    suic::Rect elemrect(0, 0, RenderSize().cx, RenderSize().cy);

    // 绘制背景
    //suic::UIRender::DrawBackground(drawing, GetStyle()->GetTrigger(), &elemrect);

    elemrect.Deflate(GetPadding());

    suic::UIRender::DrawText(drawing, GetText()
        , GetStyle()->GetTrigger(), &elemrect
        , GetHorizontalContentAlignment(), GetVerticalContentAlignment());

    //
    // 如果拥有焦点则绘制焦点虚线
    //
    if (IsFocused())
    {
        suic::Rect rect(0, 0, RenderSize().cx, RenderSize().cy);

        rect.Deflate(GetBorderThickness());
        drawing->DrawFocused(&rect);
    }
}

void TextBlock::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    Element::OnMouseLeftButtonDown(e);
}

void TextBlock::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
    Element::OnMouseLeftButtonUp(e);
}

void TextBlock::OnMouseEnter(suic::MouseEventArg& e)
{
}

void TextBlock::OnMouseMove(suic::MouseEventArg& e)
{
}

void TextBlock::OnMouseLeave(suic::MouseEventArg& e)
{
}

bool TextBlock::HandleFocus() const
{
    return false;
}

};
