// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// ImageBox.cpp

#include "stdafx.h"

#include <sui/ImageBox.h>
#include <suic/render/uirender.h>

namespace ui
{

//////////////////////////////////////////////////////////////////////////////
// ImageBox

ImplementTypeofInfo(ImageBox, suic::FrameworkElement)

ImageBox::ImageBox()
{
    SetClassName(_T("ImageBox"));
    _source = suic::SystemHelper::GetImage();
}

ImageBox::ImageBox(suic::String source)
{
    this->ImageBox::ImageBox();
    _source->Load(source);
}

ImageBox::~ImageBox()
{
}

bool ImageBox::SetSource(suic::String source)
{
    if (_source->Load(source))
    {
        InvalidateMeasure();
        return true;
    }
    else
    {
        return false;
    }
}

bool ImageBox::SetSourceFromMemory(const suic::Byte* pData, suic::Uint64 len)
{
    if (_source->Load(pData, len))
    {
        InvalidateMeasure();
        return true;
    }
    else
    {
        return false;
    }
}

suic::ImagePtr ImageBox::GetSource() const
{
    return _source;
}

bool ImageBox::IsValid() const
{
    return (_source->Width() > 0 && _source->Height() > 0);
}

suic::Size ImageBox::MeasureOverride(const suic::Size& availableSize)
{
    if (_source)
    {
        return suic::Size(_source->Width(), _source->Height());
    }
    else
    {
        return suic::Size(GetWidth(), GetHeight());
    }
}

suic::Size ImageBox::ArrangeOverride(const suic::Size& size)
{
    return __super::ArrangeOverride(size);
}

void ImageBox::OnInitialized()
{
    __super::OnInitialized();

    suic::ObjectPtr obj = GetSetters()->GetValue(_T("Source"));
    suic::ImagePtr img(obj);

    if (img)
    {
    }
    else if (obj)
    {
        SetSource(obj->ToString());
    }
}

void ImageBox::OnLoaded(suic::LoadedEventArg& e)
{
    __super::OnLoaded(e);
}

void ImageBox::OnRender(suic::DrawingContext * drawing)
{
    if (_source)
    {
        int iWid = _source->Width();
        int iHei = _source->Height();

        suic::Rect elemrect;
        suic::Rect rcImg(0, 0, iWid, iHei);

        if (RenderSize().cx > iWid)
        {
            elemrect.left = (RenderSize().cx - _source->Width()) / 2;
            elemrect.right = elemrect.left + iWid;
        }
        else
        {
            elemrect.right = RenderSize().cx;
        }

        if (RenderSize().cy > iHei)
        {
            elemrect.top = (RenderSize().cy - _source->Height()) / 2;
            elemrect.bottom = elemrect.top + RenderSize().cy;
        }
        else
        {
            elemrect.bottom = RenderSize().cy;
        }

        drawing->DrawImage(_source, &elemrect, &rcImg, GetOpacity() * 255);
    }
}

}
