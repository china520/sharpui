// 华勤科技版权所有 2010-2011
// 
// 文件名：GridViewColumnHeader.h
// 功  能：实现GridViewColumnHeader
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIGRIDVIEWCOLUMNHEADER_H_
# define _UIGRIDVIEWCOLUMNHEADER_H_

#include <sui/sharpuiconfig.h>
#include <sui/Button.h>
#include <sui/DragEvent.h>

namespace ui
{

class GridSplitter : public suic::FrameworkElement
{
public:

    DragStartedHandler DragStarted;
    DragDeltaHandler DragDelta;
    DragCompletedHandler DragCompleted;

    GridSplitter();

    void OnRender(suic::DrawingContext * drawing);

    void OnMouseMove(suic::MouseEventArg& e);

    void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonUp(suic::MouseEventArg& e);

protected:

    suic::Point _ptPrev;
};

// ===========================================================
// GridViewColumnHeader。
// ===========================================================
class SHARPUI_API GridViewColumnHeader : public ui::ButtonBase
{
public:

    GridViewColumnHeader();
    virtual ~GridViewColumnHeader();

    GridSplitter* HeaderGripper();

protected:

    void OnInitialized();

    void OnRender(suic::DrawingContext * drawing);

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

protected:

    GridSplitter _headerGripper;
    double _originalWidth;
};

typedef suic::shared<GridViewColumnHeader> GridViewColumnHeaderPtr;

inline GridSplitter* GridViewColumnHeader::HeaderGripper()
{
    return &_headerGripper;
}

};

# endif
