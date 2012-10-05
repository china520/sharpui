// 华勤科技版权所有 2010-2011
// 
// 文件名：Separator.h
// 功  能：实现分割线控件
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UISEPARATOR_H_
# define _UISEPARATOR_H_

#include <sui/sharpuiconfig.h>
#include <suicore/uicontrol.h>

namespace ui
{

class SHARPUI_API Separator : public suic::Control
{
public:

    Separator();
    virtual ~Separator();

    DECLAREBUILD(Separator)

public:

    virtual suic::Size MeasureOverride(const suic::Size& size);

    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnMouseEnter(suic::MouseEventArg& e);
    virtual void OnMouseMove(suic::MouseEventArg& e);
    virtual void OnMouseLeave(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDown(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonDbclk(suic::MouseEventArg& e);
    virtual void OnMouseLeftButtonUp(suic::MouseEventArg& e);

    void OnGotFocus(suic::FocusEventArg& e);
};

};

# endif