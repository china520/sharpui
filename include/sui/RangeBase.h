// 华勤科技版权所有 2010-2011
// 
// 文件名：RangeBase.h
// 功  能：实现标准b的tab控件。
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIRANGEBASE_H_
# define _UIRANGEBASE_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uicontrol.h>

namespace ui
{

typedef delegate<void(suic::Element*,double, double)> ValueChangedEventHandler;

class SHARPUI_API RangeBase : public suic::Control
{
public:

    ValueChangedEventHandler ValueChanged;

    RangeBase();
    virtual ~RangeBase();

    DeclareAbstractTypeofInfo(RangeBase, suic::Control)

// 属性访问定义
public:

    /// <summary>
    ///     变化最大值
    /// </summary>
    double GetSmallChange() const;
    void SetSmallChange(double val);

    double GetLargeChange() const;
    void SetLargeChange(double val);

    double GetMinimum() const;
    void SetMinimum(double val);

    double GetMaximum() const;
    void SetMaximum(double val);

    double GetValue() const;
    void SetValue(double val);


protected:

    virtual void OnRender(suic::DrawingContext * drawing);

    virtual void OnMaximumChanged(double oldMaximum, double newMaximum);
    virtual void OnMinimumChanged(double oldMinimum, double newMinimum);
    virtual void OnValueChanged(double oldValue, double newValue);

    virtual void OnGotFocus(suic::FocusEventArg& e);

protected:

    double _iMaximum;
    double _iMinimum;
    double _iSmallChange;
    double _iValue;
};

typedef suic::shared<RangeBase> RangeBasePtr;

};

# endif
