// 华勤科技版权所有 2010-2012
// 
// 文件名：ColorAnimation.h
// 功  能：实现元素的颜色变化动画。
// 
// 作  者：汪荣
// 时  间：2010-05-01
// 
// ===================================================

# ifndef _UICOLORANIMATION_H_
# define _UICOLORANIMATION_H_

#include <sui/sharpuiconfig.h>
#include <suic/animation/PropertyAnimation.h>

namespace ui
{

class SHARPUI_API ColorAnimation : public suic::PropertyAnimation
{
public:

    ColorAnimation(suic::DpPropertyEntity property);
    virtual ~ColorAnimation();
};

}

# endif
