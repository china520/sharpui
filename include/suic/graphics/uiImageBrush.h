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

#include <suic/graphics/uiBrush.h>
#include <suic/graphics/uidrawing.h>

namespace suic
{

class SUICORE_API ImageBrush : public TileBrush
{
public:

    ImageBrush(suic::String path);
    virtual ~ImageBrush();

    virtual bool Parse(const suic::String& xml);
    virtual bool Parse(void* node);
    virtual void Draw(DrawingContext* drawing, const Rect* lprc);
	virtual void Draw(DrawingContext* drawing, const Rect* lprc, const Rect* border);

    ImagePtr GetImage();
    Rect GetContentBrounds();

protected:

    int CalcStretch(const String value);
    void SetValue(const String& key, const String& value);

protected:

    ImagePtr _image;
    String _value;
    bool _isInit;

    Rect _viewBox;
    Int16 _viewBoxUnits;

    Rect _viewport;
    Int16 _viewportUnits;
    Color _maskColor;
    Byte _opacity;

    Int16 _tileMode;
    Int16 _stretch;
    Int16 _alignmentX;
    Int16 _alignmentY;

    Rect _imageCorner;

    // 换成图像四个角坐标
    Rect _leftTopCorner;
    Rect _leftBottomCorner;
    Rect _rightTopCorner;
    Rect _rightBottomCorner;
};

typedef shared<ImageBrush> ImageBrushPtr;

};

# endif
