// 华勤科技版权所有 2010-2011
// 
// 文件名：Splitter.h
// 功  能：实现Splitter分割布局。
// 
// 作  者：汪荣
// 时  间：2012-08-31
// 
// ============================================================================

# ifndef _UISPLITTER_H_
# define _UISPLITTER_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uipanel.h>

namespace ui
{

/// <summary>
///  TabLayout，实现分割布局。
/// </summary>
class SHARPUI_API Splitter : public suic::Panel
{
public:

    Splitter();
    virtual ~Splitter();

    DeclareTypeofInfo(Splitter, suic::Panel)

protected:

    suic::Size MeasureOverride(const suic::Size& size);
    suic::Size ArrangeOverride(const suic::Size& size);

    void ArrangeHorizontal(const suic::Size& size);
    void ArrangeVertical(const suic::Size& size);

    void OnInitialized();

    void OnSetCursor(suic::CursorEventArg& e);
    void OnMouseMove(suic::MouseEventArg& e);
    void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    void OnMouseLeftButtonUp(suic::MouseEventArg& e);

protected:

    suic::Vector<suic::Rect> _splits;
    int _trackingIndex;
    suic::Point _trackingPt;
};

typedef suic::shared<Splitter> SplitterPtr;

};

# endif
