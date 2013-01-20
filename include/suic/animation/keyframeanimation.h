// 华勤科技版权所有 2010-2012
// 
// 文件名：KeyframeAnimation.h
// 功  能：定义居于关键帧的动画效果。
// 
// 作  者：汪荣
// 时  间：2012-02-01
// 
// ============================================================================

# ifndef _UIKEYFRAMEANIMATION_H_
# define _UIKEYFRAMEANIMATION_H_

#include <suic/animation/animation.h>

namespace suic
{

class SUICORE_API KeyframeAnimation : public Animation
{
public:

    KeyframeAnimation();
    virtual ~KeyframeAnimation();
};

};

# endif
