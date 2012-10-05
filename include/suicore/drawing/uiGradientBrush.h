// 华勤科技版权所有 2010-2011
// 
// 文件名：GradientBrush.h
// 功  能：定义渐变刷子基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIGRADIENTBRUSH_H_
# define _UIGRADIENTBRUSH_H_

#include <suicore/drawing/uiBrush.h>

namespace suic
{

class SUICORE_API GradientBrush : public Brush
{
public:

    GradientBrush();
    virtual ~GradientBrush();

    virtual bool Parse(const suic::String& xml);
    virtual void Draw(DrawingContext* drawing, const Rect* lprc);

protected:

    ObjectPtr _data;
};

};

# endif
