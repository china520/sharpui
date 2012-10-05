// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ProgressBar.cpp

#include <sui/ProgressBar.h>
#include <suicore/drawing/uirender.h>

namespace ui
{

ProgressBar::ProgressBar()
{
    SetClassName(_T("ProgressBar"));
    SetAutoDelete(false);

    SetHeight(24);
    SetWidth(60);

    SmallChange(0);
    SetValue(10);

    SetAutoDelete(true);
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::OnInitialized()
{
    __super::OnInitialized();

    //suic::SystemHelper::SetTimer(this, 50);
}

void ProgressBar::OnTimer(int id)
{
    static double deta = 1;

    double dVal = GetValue() + deta;

    if (dVal > Maximum())
    {
        deta = -1;
        dVal += deta;
    }
    else if (dVal <= SmallChange())
    {
        deta = 1;
        dVal += deta;
    }

    SetValue(dVal);
}

void ProgressBar::OnRender(suic::DrawingContext * drawing)
{
    // 先绘制背景
    suic::Rect elemrect(0, 0, RenderSize().cx, RenderSize().cy);

    suic::TriggerPtr trg(suic::UIRender::GetTriggerByStatus(this, GetStyle()));
    suic::UIRender::DrawBackground(drawing, trg, &elemrect);

    //
    // 绘制进度条状态
    //
    suic::ImageBrushPtr bkgnd(trg->GetValue(_T("Thumb")));

    if (bkgnd)
    {
        suic::Rect rcdraw(elemrect);

        // 水平
        if (GetOrientation() == CoreFlags::Horizontal)
        {
            LONG iOff = (LONG)((GetValue() - Minimum()) * (double)(rcdraw.right - rcdraw.left) / (Maximum() - Minimum()));
            rcdraw.right = rcdraw.left + iOff;
        }
        else
        {
            LONG iOff = (LONG)((double)(rcdraw.bottom - rcdraw.top) * (GetValue() - Minimum()) / (Maximum() - Minimum()));
            rcdraw.top = rcdraw.bottom - iOff;
        }

        if (!rcdraw.Empty())
        {
            bkgnd->Draw(drawing, &rcdraw);
        }
    }

    suic::UIRender::DrawText(drawing, GetText(), trg, &elemrect
        , GetHorizontalContentAlignment(), GetVerticalContentAlignment());
}

void ProgressBar::OnMaximumChanged(double oldMaximum, double newMaximum)
{
}

void ProgressBar::OnMinimumChanged(double oldMinimum, double newMinimum)
{
}

void ProgressBar::OnValueChanged(double oldValue, double newValue)
{
    InvalidateVisual();

    __super::OnValueChanged(oldValue, newValue);
}

};

