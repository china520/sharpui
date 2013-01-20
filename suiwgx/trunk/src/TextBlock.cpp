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
#include <suic/render/uirender.h>

namespace ui
{

/////////////////////////////////////////////////////////
// TextBlock

ImplementTypeofInfo(TextBlock, suic::FrameworkElement)

TextBlock::TextBlock()
    : _single(true)
{
    SetClassName(_T("TextBlock"));

    SetVerticalContentAlignment(VertContentAlignment::Center);
    SetHorizontalContentAlignment(HoriContentAlignment::Left);
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
    suic::Size ret = suic::Render::MeasureTextSize(GetText(), GetFont());

    ret.cx += 2;
    MeasureCheck(ret);

    return ret;
}

void TextBlock::OnInitialized()
{
    __super::OnInitialized();
}

void TextBlock::OnRender(suic::DrawingContext * drawing)
{
    // 绘制背景
    suic::Render::RenderBackground(drawing, this);
    suic::Render::RenderText(drawing, this, GetText(), _single);

    //
    // 如果拥有焦点则绘制焦点虚线
    //
    if (IsFocused())
    {
        suic::Rect rect(0, 0, RenderSize().cx, RenderSize().cy);

        rect.Deflate(GetBorderThickness());
        drawing->DrawFocusedRectangle(&rect);
    }
}

void TextBlock::OnPropertyChanged(suic::PropertyChangedEventArg& e)
{
    if (e.GetName().Equals(_T("TextWrapper")))
    {
        SetSingle(e.GetSetter()->ToBool());
    }
    else
    {
        //
        // 必须调用基类初始化基本数据
        //
        __super::OnPropertyChanged(e);
    }
}

}
