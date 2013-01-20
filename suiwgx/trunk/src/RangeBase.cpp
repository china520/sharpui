// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// RangeBase.cpp

#include <sui/RangeBase.h>

namespace ui
{

ImplementTypeofInfo(RangeBase, suic::Control)

RangeBase::RangeBase()
    : _iMinimum(0)
    , _iMaximum(100)
    , _iValue(0)
{
    SetClassName(_T("RangeBase"));
}

RangeBase::~RangeBase()
{
}

void RangeBase::OnRender(suic::DrawingContext * drawing)
{
    __super::OnRender(drawing);
}

double RangeBase::GetLargeChange() const
{
    return 0.0;
}

void RangeBase::SetLargeChange(double val)
{
}

double RangeBase::GetMaximum() const
{
    return _iMaximum;
}

void RangeBase::SetMaximum(double val)
{
    if (_iValue != val)
    {
        double _iOldValue = _iValue;
        _iMaximum = val;

        OnMaximumChanged(_iOldValue, val);
    }
}

double RangeBase::GetMinimum() const
{
    return _iMinimum;
}

void RangeBase::SetMinimum(double val)
{
    if (_iValue != val)
    {
        double _iOldValue = _iValue;
        _iMinimum = val;

        OnMinimumChanged(_iOldValue, val);
    }
}

double RangeBase::GetSmallChange() const
{
    return _iSmallChange;
}

void RangeBase::SetSmallChange(double val)
{
    _iSmallChange = val;
}

double RangeBase::GetValue() const
{
    return _iValue;
}

void RangeBase::SetValue(double val)
{
    if (val < GetSmallChange())
    {
        val = GetSmallChange();
    }

    if (_iValue != val)
    {
        double _iOldValue = _iValue;
        _iValue = val;

        OnValueChanged(_iOldValue, val);
    }
}

void RangeBase::OnMaximumChanged(double oldMaximum, double newMaximum)
{
}

void RangeBase::OnMinimumChanged(double oldMinimum, double newMinimum)
{
}

void RangeBase::OnValueChanged(double oldValue, double newValue)
{
    if (ValueChanged)
    {
        ValueChanged(this, oldValue, newValue);
    }
}

void RangeBase::OnGotFocus(suic::FocusEventArg& e)
{
    ;
}

};

