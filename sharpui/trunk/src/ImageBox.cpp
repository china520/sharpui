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
#include <suicore/drawing/uirender.h>

namespace ui
{

//////////////////////////////////////////////////////////////////////////////
// ImageBox

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
    return _source->Load(source);
}

suic::ImagePtr ImageBox::GetSource() const
{
    return _source;
}

suic::Size ImageBox::MeasureOverride(const suic::Size& availableSize)
{
    return suic::Size(GetWidth(), GetHeight());
}

void ImageBox::OnInitialized()
{
    __super::OnInitialized();

    if (GetStyle())
    {
        suic::ObjectPtr obj = GetStyle()->GetValue(_T("Source"));

        if (obj)
        {
            _source = suic::ImagePtr(obj);

            if (!_source)
            {
                _source = suic::SystemHelper::GetImage();
                _source->Load(obj->ToString());
            }

            SetWidth(_source->Width());
            SetHeight(_source->Height());
        }
    }
}

void ImageBox::OnLoaded(suic::LoadedEventArg& e)
{
    __super::OnLoaded(e);
}

void ImageBox::OnRender(suic::DrawingContext * drawing)
{
    suic::Rect elemrect(0, 0, RenderSize().cx, RenderSize().cy);

    if (_source)
    {
        suic::Rect rcImg(0, 0, _source->Width(), _source->Height());

        elemrect.left = (elemrect.Width() - _source->Width()) / 2;
        elemrect.top = (elemrect.Height() - _source->Height()) / 2;
        elemrect.right = elemrect.left + _source->Width();
        elemrect.bottom = elemrect.top + _source->Height();

        drawing->DrawImage(_source, &elemrect, &rcImg, GetOpacity() * 255);
    }
}

}
