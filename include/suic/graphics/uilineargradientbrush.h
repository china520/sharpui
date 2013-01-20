// 华勤科技版权所有 2010-2011
// 
// 文件名：GradientBrush.h
// 功  能：定义渐变刷子基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UILINEARGRADIENTBRUSH_H_
# define _UILINEARGRADIENTBRUSH_H_

#include <suic/graphics/uiGradientBrush.h>

namespace suic
{

class SUICORE_API LinearGradientBrush : public GradientBrush
{
public:

    LinearGradientBrush();
    virtual ~LinearGradientBrush();

    virtual bool Parse(const suic::String& xml);
    virtual bool Parse(void* node);
    virtual void Draw(DrawingContext* drawing, const Rect* lprc);

protected:

    ObjectPtr _data;
};

};

# endif
