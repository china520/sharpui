//////////////////////////////////////////////////////////////////////////////
// Separator.cpp

#include <sui/Separator.h>
#include <suicore/drawing/uirender.h>

namespace ui
{

const int SEPARATOR_DEFAULT_HEIGHT = 10;

Separator::Separator()
{
    SetClassName(_T("Separator"));
    SetHeight(SEPARATOR_DEFAULT_HEIGHT);
}

Separator::~Separator()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
// Separator
//

suic::Size Separator::MeasureOverride(const suic::Size& size)
{
    suic::Size availableSize;

    availableSize.cy = GetHeight();

    return availableSize;
}

void Separator::OnRender(suic::DrawingContext * drawing)
{
    suic::Rect rect(0, 0, RenderSize.cx, RenderSize.cy);

    rect.top += (rect.Height() / 2);
    rect.bottom = rect.top + 1;

    drawing->FillRectangle(rect, ARGB(255,125,125,125));
}

void Separator::OnMouseEnter(suic::MouseEventArg& e)
{
}

void Separator::OnMouseMove(suic::MouseEventArg& e)
{
}

void Separator::OnMouseLeave(suic::MouseEventArg& e)
{
}

void Separator::OnMouseLeftButtonDown(suic::MouseEventArg& e)
{
}

void Separator::OnMouseLeftButtonDbclk(suic::MouseEventArg& e)
{
}

void Separator::OnMouseLeftButtonUp(suic::MouseEventArg& e)
{
}

void Separator::OnGotFocus(suic::FocusEventArg& e)
{
    ;
}

};
