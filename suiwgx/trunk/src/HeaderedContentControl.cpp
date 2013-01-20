// ======================================================================
//
// Copyright (c) 2008-2012 汪荣, Inc. All rights reserved.
//
// Sharpui库源码遵循CPL协议进行开源，任何个人或团体在此协议上可以自由使用。
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// HeaderedContentControl.cpp

#include <suic/render/uirender.h>

#include <sui/HeaderedContentControl.h>
#include <sui/textblock.h>
#include <sui/Selector.h>

#include <suic/tools/vector.h>

namespace ui
{

ImplementTypeofInfo(HeaderedContentControl, suic::ContentControl)

HeaderedContentControl::HeaderedContentControl()
    : _indent(20)
{
    SetClassName(_T("HeaderContentControl"));
}

HeaderedContentControl::~HeaderedContentControl()
{
}

suic::ElementPtr HeaderedContentControl::GetHeader()
{
    return _header;
}

void HeaderedContentControl::SetHeader(suic::ElementPtr val)
{
    if (_header != val)
    {
        OnHeaderChanged(_header, val);
    }
}

int HeaderedContentControl::AddChild(suic::ObjectPtr child)
{
    suic::ElementPtr pElem(child);

    if (pElem->GetWrapper().Equals(_T("Header")))
    {
        SetHeader(child);

        return 0;
    }
    else
    {
        return __super::AddChild(child);
    }
}

////////////////////////////////////////////////////////////////////////////
//
suic::Size HeaderedContentControl::MeasureOverride(const suic::Size& availableSize)
{
    suic::Size retSize(__super::MeasureOverride(availableSize));

    if (_header)
    {
        _header->Measure(availableSize);

        retSize.cy += _header->GetDesiredSize().cy;

        if (retSize.cx < _header->GetDesiredSize().cx)
        {
            retSize.cx = _header->GetDesiredSize().cx;
        }
    }

    return retSize;
}

suic::Size HeaderedContentControl::ArrangeOverride(const suic::Size& availableSize)
{
    ClearVisualChildren();
    suic::Rect finalRect(0, 0, availableSize.cx, availableSize.cy);

    if (_header)
    {
        finalRect.bottom = finalRect.top + _header->GetDesiredSize().cy;
        finalRect.left += _indent;
        finalRect.right = finalRect.left + _header->GetDesiredSize().cx;

        AddVisualChild(_header.get());
        _header->Arrange(finalRect);

        finalRect.left = 0;
        finalRect.top = finalRect.bottom;
        finalRect.bottom = availableSize.cy;
        finalRect.right = availableSize.cx;
    }

    if (_content && _content->IsVisible())
    {
        AddVisualChild(_content.get());
        _content->Arrange(finalRect);
    }

    return availableSize;
}

void HeaderedContentControl::
OnHeaderChanged(suic::Element* oldHeader, suic::Element* newHeader)
{
    _header = newHeader;
}

void HeaderedContentControl::OnHeaderClicked(suic::Element* header)
{
    ;
}

void HeaderedContentControl::OnInitialized()
{
    __super::OnInitialized();
}

void HeaderedContentControl::OnRender(suic::DrawingContext * drawing)
{
}

void HeaderedContentControl::OnTextInput(suic::KeyboardEventArg& e)
{
}

void HeaderedContentControl::OnKeyDown(suic::KeyboardEventArg& e)
{
}

void HeaderedContentControl::OnPreviewMouseLeftButtonDown(suic::MouseEventArg& e)
{
    if (GetHeader().get() == e.GetSource())
    {
        Selector::SelectItem(e.GetSource(), true);

        InvalidateVisual();
    }
}

};
