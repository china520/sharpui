// 华勤科技版权所有 2010-2012
// 
// 文件名：PointAnimation.h
// 功  能：实现位置的变化动画。
// 
// 作  者：汪荣
// 时  间：2010-05-01
// 
// ===================================================

# ifndef _UIPOINTANIMATION_H_
# define _UIPOINTANIMATION_H_

#include <sui/sharpuiconfig.h>
#include <animation/PropertyAnimation.h>

namespace ui
{

class SHARPUI_API PointAnimation : public suic::PropertyAnimation
{
public:

    PointAnimation(suic::String property);
    virtual ~PointAnimation();
};

}

# endif
