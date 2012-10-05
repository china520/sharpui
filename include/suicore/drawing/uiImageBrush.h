// 华勤科技版权所有 2010-2011
// 
// 文件名：ImageBrush.h
// 功  能：实现图像刷。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIIMAGEBRUSH_H_
# define _UIIMAGEBRUSH_H_

#include <suicore/drawing/uiBrush.h>
#include <suicore/drawing/uidrawing.h>

namespace suic
{

class SUICORE_API ImageBrush : public Brush
{
public:

    ImageBrush();
    virtual ~ImageBrush();

    virtual bool Parse(const suic::String& xml);
    virtual bool Parse(void* node);
    virtual void Draw(DrawingContext* drawing, const Rect* lprc);
	virtual void Draw(DrawingContext* drawing, const Rect* lprc, const Rect* border);

    ImagePtr GetImage();
    Rect GetContentBrounds();

protected:

    ObjectPtr _data;
    ImagePtr _image;
};

typedef shared<ImageBrush> ImageBrushPtr;

};

# endif
