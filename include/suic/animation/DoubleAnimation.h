// 华勤科技版权所有 2010-2012
// 
// 文件名：DoubleAnimation.h
// 功  能：实现元素的double属性变化变化动画。
// 
// 作  者：汪荣
// 时  间：2010-05-01
// 
// ===================================================

# ifndef _UIDOUBLEANIMATION_H_
# define _UIDOUBLEANIMATION_H_

#include <sui/sharpuiconfig.h>
#include <suic/animation/PropertyAnimation.h>

namespace ui
{

class SHARPUI_API DoubleAnimation : public suic::PropertyAnimation
{
public:

    DoubleAnimation(suic::DpPropertyEntity property, bool bRelayout=false);
    DoubleAnimation(suic::DpPropertyEntity property, double dFrom, double dTo, bool bRelayout=false);

    virtual ~DoubleAnimation();

    virtual void OnMeasure(suic::FrameworkElement* pElem);

    /// <summary>
    ///     动画开始时回调
    /// </summary>
    /// <param name="pElem">目标元素</param>
    /// <returns>无</returns>
    virtual void OnStart(suic::FrameworkElement* pElem);
    virtual void OnFinish(suic::FrameworkElement* pElem);

    double GetFrom() const;
    void SetFrom(double val);

    double GetTo() const;
    void SetTo(double val);

    double GetCurrentValue();

protected:

    double _dFrom;
    double _dTo;
    double _dCurrent;

    bool _bReverse;
};

}

# endif
