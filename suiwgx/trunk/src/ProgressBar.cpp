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
#include <suic/render/uirender.h>

namespace ui
{

ImplementTypeofInfo(ProgressBar, RangeBase)

ProgressBar::ProgressBar()
{
    SetClassName(_T("ProgressBar"));
    SetAutoDelete(false);

    SetHeight(24);
    SetWidth(60);

    SetSmallChange(0);
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

    if (dVal > GetMaximum())
    {
        deta = -1;
        dVal += deta;
    }
    else if (dVal <= GetSmallChange())
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

    if (GetBackground())
    {
        GetBackground()->Draw(drawing, &elemrect);
    }

    //
    // 绘制进度条状态
    //
    suic::ImageBrushPtr bkgnd;//(GetValue(_T("Thumb")));

    if (bkgnd)
    {
        suic::Rect rcdraw(elemrect);

        // 水平
        if (GetOrientation() == CoreFlags::Horizontal)
        {
            LONG iOff = (LONG)((GetValue() - GetMinimum()) * (double)(rcdraw.right - rcdraw.left) / (GetMaximum() - GetMinimum()));
            rcdraw.right = rcdraw.left + iOff;
        }
        else
        {
            LONG iOff = (LONG)((double)(rcdraw.bottom - rcdraw.top) * (GetValue() - GetMinimum()) / (GetMaximum() - GetMinimum()));
            rcdraw.top = rcdraw.bottom - iOff;
        }

        if (!rcdraw.Empty())
        {
            bkgnd->Draw(drawing, &rcdraw);
        }
    }

    //suic::Render::DrawText(drawing, this, GetText(), trg, &elemrect, true);
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

