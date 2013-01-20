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

#include <suic/framework/uiframeworkelement.h>

namespace suic
{

/// <summary>
/// 控件类基类，从其继承支持tab键切换
/// </summary>
class SUICORE_API Control : public FrameworkElement
{
public:

    Control();
    virtual ~Control();

    DeclareTypeofInfo(Control, FrameworkElement)

// 属性访问定义
public:

    bool IsTabStop() const;
    void SetTabStop(bool val);

    int GetTabIndex() const;
    void SetTabIndex(int val);

public:

    void OnRender(DrawingContext * drawing);
    void OnPropertyChanged(PropertyChangedEventArg& e);

protected:

    int _iTabIndex;
};

typedef shared<Control> ControlPtr;

}

#endif
