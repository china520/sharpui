// 华勤科技版权所有 2010-2011
// 
// 文件名：Control.h
// 功  能：定义核心库一般用户控件类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UICONTROL_H_
# define _UICONTROL_H_

#include <suicore/uiframeworkelement.h>

namespace suic
{

class SUICORE_API Control : public FrameworkElement
{
public:

    Control();
    virtual ~Control();

    bool IsTabStop() const;
    void SetTabStop(bool val);

    int GetTabIndex() const;
    void SetTabIndex(int index);

public:

    virtual void OnRender(DrawingContext * drawing);

    virtual void OnGotFocus(suic::FocusEventArg& e);
    virtual void OnMouseEnter(MouseEventArg& e);

    virtual void OnMouseLeftButtonDown(MouseEventArg& e);
    virtual void OnMouseLeftButtonUp(MouseEventArg& e);

    void OnSetterChanged(SetterChangedEventArg& e);

protected:

    int _iTabIndex;
};

typedef shared<Control> ControlPtr;

}

#endif
