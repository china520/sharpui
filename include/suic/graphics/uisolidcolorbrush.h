// 华勤科技版权所有 2010-2011
// 
// 文件名：SolidColorBrush.h
// 功  能：实现颜色刷子。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UISOLIDCOLORBRUSH_H_
# define _UISOLIDCOLORBRUSH_H_

#include <suic/graphics/uiBrush.h>

namespace suic
{

class SUICORE_API SolidColorBrush : public Brush
{
public:

    SolidColorBrush(suic::Color color);
    virtual ~SolidColorBrush();

    bool Parse(const suic::String& xml);
    bool Parse(void* node);
    void Draw(DrawingContext* drawing, const Rect* lprc);
    void Draw(DrawingContext* drawing, const Rect* lprc, const Rect* border);

    suic::Color ToColor();
    String ToString();

protected:

    suic::Color _color;
};

inline suic::Color SolidColorBrush::ToColor()
{
    return _color;
}

};

# endif
