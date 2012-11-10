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
    : _single(true)
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
    suic::TriggerPtr setter(suic::Render::GetTriggerByStatus(this, GetStyle()));

    if (setter.get())
    {
        suic::Size ret = suic::Render::MeasureTextSize(GetText(), setter);

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
    // 绘制背景
    suic::Render::DrawBackground(drawing, this);
    suic::Render::DrawText(drawing, this, GetText(), _single);

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

void TextBlock::OnSetterChanged(suic::SetterChangedEventArg& e)
{
    if (e.GetName().Equals(_T("IsSingle")))
    {
        SetSingle(e.GetSetter()->ToBool());
    }
    else
    {
        //
        // 必须调用基类初始化基本数据
        //
        __super::OnSetterChanged(e);
    }
}

}
