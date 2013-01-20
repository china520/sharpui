// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// Slider.cpp

#include <sui/Slider.h>
#include <sui/Button.h>
#include <suic/render/uirender.h>

namespace ui
{

typedef delegate<void(DragDeltaEventArg&)> ThumbDragDeltaEventHandler;

class SliderButton : public Button
{
public:

    ThumbDragDeltaEventHandler ThumbDragDelta;

    SliderButton(Slider* slider)
        : _slider(slider)
        , _trackPos(0)
        , _trackStart(0)
    {
        SetClassName(_T("SliderButton"));
    }

    void OnMouseLeftButtonDown(suic::MouseEventArg& e)
    {
        __super::OnMouseLeftButtonDown(e);

        _prev = e.MousePoint();

        suic::Point ptSelf = PointToScreen(suic::Point());

        if (CoreFlags::Horizontal == _slider->GetOrientation())
        {
            _trackStart = GetVisualOffset().x;
        }
        else
        {
            _trackStart = GetVisualOffset().y;
        }

        _trackPos = _trackStart;
    }

    void OnMouseMove(suic::MouseEventArg& e)
    {
        if (IsMouseCaptured())
        {
            int iHorz = e.MousePoint().x - _prev.x;
            int iVert = e.MousePoint().y - _prev.y;

            int newPos = _trackStart;

            if (CoreFlags::Horizontal == _slider->GetOrientation())
            {
                newPos += iHorz;

                if (newPos < 0)
                {
                    newPos = 0;
                }

                if (newPos > _slider->RenderSize().cx - GetDesiredSize().cx)
                {
                    newPos = _slider->RenderSize().cx - GetDesiredSize().cx;
                }

                iHorz = newPos - _trackPos;
            }
            else
            {
                newPos += iVert;

                if (newPos < 0)
                {
                    newPos = 0;
                }

                if (newPos > _slider->RenderSize().cy - GetDesiredSize().cy)
                {
                    newPos = _slider->RenderSize().cy - GetDesiredSize().cy;
                }

                iVert = newPos - _trackPos;
            }

            if (ThumbDragDelta && newPos != _trackPos)
            {
                _trackPos = newPos;
   
                DragDeltaEventArg de(iHorz, iVert);

                ThumbDragDelta(de);
            }
        }
    }

protected:

    suic::Point _prev;
    Slider* _slider;
    int _trackPos;
    int _trackStart;
};

ImplementTypeofInfo(Slider, RangeBase)

Slider::Slider()
{
    SetClassName(_T("Slider"));

    SetMinHeight(10);
    SetMinWidth(50);

    SetHorizontalContentAlignment(HoriContentAlignment::Left);
    SetHorizontalAlignment(HoriAlignment::Left);

    SetVerticalContentAlignment(VertContentAlignment::Top);
    SetVerticalAlignment(VertAlignment::Top);

    SliderButton* pSliderBtn = new SliderButton(this);
    _thumbBtn = pSliderBtn;

    pSliderBtn->ThumbDragDelta += ThumbDragDeltaEventHandler(this, &Slider::OnThumbDragDelta);
}

Slider::~Slider()
{
}

suic::Size Slider::MeasureOverride(const suic::Size& size)
{
    suic::Size availableSize;

    _thumbBtn->Measure(size);
    availableSize.cy = _thumbBtn->GetDesiredSize().cy;

    return availableSize;
}

suic::Size Slider::ArrangeOverride(const suic::Size& size)
{
    suic::Rect rcdraw(0, 0, size.cx, size.cy);
    const suic::Size& thumbSize = _thumbBtn->GetDesiredSize();

    // 水平
    if (GetOrientation() == CoreFlags::Horizontal)
    {
        int len = rcdraw.right - rcdraw.left - thumbSize.cx;

        rcdraw.left = rcdraw.left 
            + (LONG)(len * (GetValue() - GetMinimum()) / (GetMaximum() - GetMinimum()));
        rcdraw.right = rcdraw.left + thumbSize.cx;
    }
    else
    {
        int len = rcdraw.bottom - rcdraw.top - thumbSize.cy;

        rcdraw.top = rcdraw.bottom - thumbSize.cy 
            - (LONG)(len * (GetValue() - GetMinimum()) / (GetMaximum() - GetMinimum()));
        rcdraw.bottom = rcdraw.top + thumbSize.cy;
    }
   
    _thumbBtn->Arrange(rcdraw);

    return size;
}

void Slider::OnInitialized()
{
    __super::OnInitialized();

     AddVisualChild(_thumbBtn.get());
     AddLogicalChild(_thumbBtn.get());

    _thumbBtn->SetClassName(_T("Slider.Thumb"));

    _thumbBtn->BeginInit();
    _thumbBtn->EndInit();
}

void Slider::OnRender(suic::DrawingContext * drawing)
{
    // 先绘制背景
    suic::Rect rcdraw(0, 0, RenderSize().cx, RenderSize().cy);
    suic::ImageBrushPtr bkgnd(GetBackground());

    if (!bkgnd)
    {
        if (GetOrientation() == CoreFlags::Horizontal)
        {
            rcdraw.top = (RenderSize().cy - GetDesiredSize().cy) / 2;
            rcdraw.bottom = rcdraw.top + GetDesiredSize().cy;
        }
        else
        {
            rcdraw.left = (RenderSize().cx - GetDesiredSize().cx) / 2;
            rcdraw.right = rcdraw.left + GetDesiredSize().cx;
        }

        suic::Render::RenderBackground(drawing, this, &rcdraw);
    }
    else
    {
        suic::Rect rect = bkgnd->GetContentBrounds();

        if (GetOrientation() == CoreFlags::Horizontal)
        {
            rcdraw.top = (RenderSize().cy - rect.Height()) / 2;
            rcdraw.bottom = rcdraw.top + rect.Height();
        }
        else
        {
            rcdraw.left = (RenderSize().cx - rect.Width()) / 2;
            rcdraw.right = rcdraw.left + rect.Width();
        }

        bkgnd->Draw(drawing, &rcdraw);
    }
}

double Slider::GetInterval() const
{
    return 0.0;
}

void Slider::SetInterval(double val)
{
}

double Slider::GetSelectionEnd() const
{
    return 0.0;
}

void Slider::SetSelectionEnd(double val)
{
}

double Slider::GetSelectionStart() const
{
    return 0.0;
}

void Slider::SetSelectionStart(double val)
{
}

void Slider::OnMaximizeValue()
{
}

void Slider::OnMaximumChanged(double oldMaximum, double newMaximum)
{
}

void Slider::OnMinimizeValue()
{
}

void Slider::OnMinimumChanged(double oldMinimum, double newMinimum)
{
}

void Slider::OnValueChanged(double oldValue, double newValue)
{
    InvalidateArrange();
    InvalidateVisual();

    __super::OnValueChanged(oldValue, newValue);
}

void Slider::OnThumbDragCompleted(DragCompletedEventArg& e)
{
}

void Slider::HandleHorizontal(int pos)
{
    suic::Rect rcItem(0, 0, RenderSize().cx, RenderSize().cy);
    const suic::Size& thumbSize = _thumbBtn->GetDesiredSize();

    if (pos >= rcItem.right - thumbSize.cx) 
    {
        SetValue(GetMaximum());
    }
    else if (pos <= rcItem.left) 
    {
        SetValue(GetMinimum());
    }
    else 
    {
        SetValue(GetMinimum() + (GetMaximum() - GetMinimum()) * (double)(pos) / (double)(rcItem.Width() - thumbSize.cx));
    }
}

void Slider::HandleVertical(int pos)
{
    suic::Rect rcItem(0, 0, RenderSize().cx, RenderSize().cy);
    const suic::Size& thumbSize = _thumbBtn->GetDesiredSize();

    if (pos <= rcItem.top ) 
    {
        SetValue(GetMinimum());
    }
    else if (pos >= rcItem.bottom - thumbSize.cy) 
    {
        SetValue(GetMaximum());
    }
    else 
    {
        SetValue(GetMinimum() + (GetMaximum() - GetMinimum()) * (double)(pos) / (double)(rcItem.Height() - thumbSize.cy));
    }
}

void Slider::OnThumbDragDelta(DragDeltaEventArg& e)
{
    if (GetOrientation() == CoreFlags::Horizontal) 
    {
        int pos = _thumbBtn->GetVisualOffset().x + e.HorizontalChange();

        HandleHorizontal(pos);
    }
    else 
    {
        int pos = _thumbBtn->GetVisualOffset().y + e.VerticalChange();

        HandleVertical(pos);
    }
}

void Slider::OnThumbDragStarted(DragStartedEventArg& e)
{
}

void Slider::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
    __super::OnMouseLeftButtonDown(e);

    const suic::Size& thumbSize = _thumbBtn->GetDesiredSize();
    suic::Point ptSelf = PointToScreen(suic::Point());

    if (GetOrientation() == CoreFlags::Horizontal) 
    {
        double pos = e.MousePoint().x - ptSelf.x - thumbSize.cx / 2;

        HandleHorizontal(pos);
    }
    else
    {
        double pos = e.MousePoint().y - ptSelf.y - thumbSize.cy / 2;

        HandleVertical(pos);
    }
}

void Slider::OnKeyDown(suic::KeyboardEventArg& e)
{
    if (GetOrientation() == CoreFlags::Horizontal) 
    {
        if (e.IsLeftArrow())
        {
            if (GetValue() > GetMinimum())
            {
                SetValue((int)GetValue() - 1);
            }
        }
        else if (e.IsRightArrow())
        {
            if (GetValue() < GetMaximum())
            {
                SetValue((int)GetValue() + 1);
            }
        }
    }
    else
    {
        if (e.IsUpArrow())
        {
            if (GetValue() > GetMinimum())
            {
                SetValue((int)GetValue() - 1);
            }
        }
        else if (e.IsDownArrow())
        {
            if (GetValue() < GetMaximum())
            {
                SetValue((int)GetValue() + 1);
            }
        }
    }
}

};
