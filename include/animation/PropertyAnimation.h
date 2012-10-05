// 华勤科技版权所有 2010-2012
// 
// 文件名：PropertyAnimation.h
// 功  能：定义居于属性的动画，这类动画仅仅需要改变元素
// 的属性值即可达到动画效果，同时也是最高效的一种动画。
// 
// 作  者：汪荣
// 时  间：2012-02-01
// 
// ============================================================================

# ifndef _UIPROPERTYANIMATION_H_
# define _UIPROPERTYANIMATION_H_

#include <animation/animation.h>

namespace suic
{

class SUICORE_API PropertyAnimation : public Animation
{
public:

    PropertyAnimation(String property);
    virtual ~PropertyAnimation();

    void SetProperty(const String& prop);
    String GetProperty() const;

    void SetRelayout(bool value);
    bool GetRelayout() const;

protected:

    // 需要进行的动画的属性
    String _property;
    bool _relayout;
};

inline void PropertyAnimation::SetRelayout(bool value)
{
    _relayout = value;
}

inline bool PropertyAnimation::GetRelayout() const
{
    return _relayout;
}

};

# endif
