// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

#include <suic/animation/DoubleAnimation.h>

namespace ui
{

DoubleAnimation::DoubleAnimation(suic::DpPropertyEntity property, bool bRelayout)
    : _dFrom(0)
    , _dTo(1)
    , _bReverse(false)
    , suic::PropertyAnimation(property)
{
    SetRelayout(bRelayout);
}

DoubleAnimation::DoubleAnimation(suic::DpPropertyEntity property, double dFrom, double dTo, bool bRelayout)
    : _dFrom(dFrom)
    , _dTo(dTo)
    , _bReverse(false)
    , suic::PropertyAnimation(property)
{
    SetRelayout(bRelayout);
}

DoubleAnimation::~DoubleAnimation()
{

}

void DoubleAnimation::OnMeasure(suic::FrameworkElement* pElem)
{
    if (_isEndOf)
    {
        return;
    }

    double dValue = GetCurrentValue();

    pElem->SetValue(_property, new suic::ODouble(dValue));

    if (GetRelayout())
    {
        if (pElem->GetParent())
        {
            pElem->GetParent()->UpdateLayout();
        }
        else
        {
            pElem->UpdateLayout();
        }
    }
    else
    {
        pElem->InvalidateVisual();
    }
}

double DoubleAnimation::GetCurrentValue()
{
    if (_isEndOf)
    {
        return 0;
    }

    double dDiff = (_dTo - _dFrom) * GetSpeedRatio() / GetDuration();

    if (_bReverse)
    {
        _dCurrent -= dDiff;

        if ((dDiff > 0 && _dCurrent <= _dFrom) 
            || (dDiff < 0 && _dCurrent >= _dFrom))
        {
            _dCurrent = _dFrom;
            _isEndOf = true;
        }
    }
    else
    {
        _dCurrent += dDiff;

        if ((dDiff > 0 && _dCurrent >= _dTo) 
            || (dDiff < 0 && _dCurrent <= _dTo))
        {
            _dCurrent = _dTo;

            if (GetAutoReverse())
            {
                _bReverse = true;
            }
            else
            {
                _isEndOf = true;
            }
        }
    }

    return _dCurrent;
}

void DoubleAnimation::OnStart(suic::FrameworkElement* pElem)
{
    __super::OnStart(pElem);

    _bReverse = false;
    _dCurrent = _dFrom + (_dTo - _dFrom) * GetSpeedRatio() / GetDuration();
    pElem->SetValue(_property, new suic::ODouble(_dFrom));

    if (pElem->GetParent() && GetRelayout())
    {
        pElem->GetParent()->UpdateLayout();
    }
    else
    {
        pElem->InvalidateVisual();
    }
}

void DoubleAnimation::OnFinish(suic::FrameworkElement* pElem)
{
    __super::OnFinish(pElem);

    if (!_bReverse)
    {
        pElem->SetValue(_property, new suic::OString(_dTo));
    }
    else
    {
        pElem->SetValue(_property, new suic::OString(_dFrom));
    }

    pElem->SetValue(_property, new suic::OString(_dTo));

    if (pElem->GetParent() && GetRelayout())
    {
        pElem->GetParent()->UpdateLayout();
    }
    else
    {
        pElem->InvalidateVisual();
    }
}

double DoubleAnimation::GetFrom() const
{
    return _dFrom;
}

void DoubleAnimation::SetFrom(double val)
{
    _dFrom = val;
}

double DoubleAnimation::GetTo() const
{
    return _dTo;
}

void DoubleAnimation::SetTo(double val)
{
    _dTo = val;
}

}
