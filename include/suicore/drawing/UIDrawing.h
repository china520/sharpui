// 华勤科技版权所有 2010-2011
// 
// 文件名：UIDrawing.h
// 功  能：定义绘制接口
// 
// 作  者：汪荣
// 时  间：2010-07-12
// 
// ============================================================================

# ifndef _UIDRAWIN_H_
# define _UIDRAWIN_H_

#include <suicore/uiobject.h>
#include <suicore/drawing/uigeometry.h>
#include <suicore/drawing/uibrush.h>
#include <suicore/drawing/uipen.h>

namespace suic
{

class Image;

/// <summary>
///  文本绘制属性
/// </summary>
typedef struct tagFormattedText
{
    bool single;
    bool ellipsis;

    // CoreFlags::Left,CoreFlags::Right,CoreFlags::Center
    int horzAlign;
    // CoreFlags::Top,CoreFlags::Bottom,CoreFlags::Center
    int vertAlign;

    // -1不绘制文本背景
    Color bkcolor;
    // 默认为0（黑色）
    Color color;
    // 字体
    Handle font;

    tagFormattedText()
        : color(ARGB(255,0,0,0))
        , bkcolor(-1)
        , single(true)
        , ellipsis(false)
        , horzAlign(CoreFlags::Left)
        , vertAlign(CoreFlags::Center)
        , font(0)
    {
        ;
    }

}FormattedText;

/// <summary>
///  绘制接口类，完成一般的绘制，线的颜色采用标准的四色表示
/// </summary>
class DrawingContext : public RefObject
{
public:

    virtual ~DrawingContext() {};

    void SetOffset(int x, int y);
    Point GetOffset() const;

    //---------------------------------------------------------------

    virtual Handle GetHandle() const = 0;

    virtual Size CalculateText(const Char * text, int size, const FormattedText* att) = 0;

    virtual void PushClip(const Rect* rcClip) = 0;
    virtual void PushTextColor(Color clr) = 0;

    virtual void Pop() = 0;

    virtual void SetPixel(int x, int y, Color clr) = 0;

    virtual void DrawLine(Pen* pen, Point pt0, Point pt1) = 0;
    virtual void DrawRectangle(Rect rc, Uint16 n, Color clr) = 0;
    virtual void DrawRoundRectangle(Rect rc, Uint16 n, Uint16 w, Uint16 h, Color clr) = 0;
    virtual void DrawFocusedRectangle(const Rect * lprc) = 0;
    virtual void DrawGradient(const Rect* rc, Color dwFirst, Color dwSecond, bool bVertical) = 0;

    virtual void DrawEllipse(Color clr, Point center, Double radiusX, Double radiusY) = 0;

    virtual void DrawImage(Image* img, const Rect* rcdc, const Rect* rcimg, Byte alpha) = 0;
    virtual void DrawImage(Image* img, const Rect* rcdc, const Rect* rcimg, Byte alpha, Color trans) = 0;

    virtual void DrawText(const Char * text, int size, const Rect * rc, const FormattedText* att) = 0;

    virtual void FillRectangle(Rect rc, Color clr) = 0;

    //void DrawVideo(MediaPlayer player, Rect rectangle);

    //void PushClip(Geometry clipGeometry);
    //void PushOpacityMask(Brush brush);
    //void PushOpacity(Double opacity);

    //------------------------------------------------------------

protected:

    Point _offset;
};

inline void DrawingContext::SetOffset(int x, int y)
{
    _offset.x = x;
    _offset.y = y;
}

inline Point DrawingContext::GetOffset() const
{
    return _offset;
}

typedef shared<DrawingContext> DrawingContextPtr;

class Image : public RefObject
{
public:

    virtual ~Image() {};

    virtual bool IsValid() const = 0;
    virtual void SetMaskColor(Color clr) = 0;

    virtual bool Load(const String& strFile) = 0;
    virtual bool Load(Handle hRes, const String& strName, const String& strType) = 0;
    virtual bool LoadIcon(const Handle icon) = 0;
    virtual bool LoadHandle(const Handle bmp) = 0;
    virtual bool Load(const Byte* data, suic::Uint64 size) = 0;
    virtual bool Load(const Byte* data, int w, int h) = 0;

    virtual bool Save(const String& filename, int iType) = 0;

    virtual Handle GetHandle() = 0;
    virtual void Detach() = 0;

    virtual int Width() = 0;
    virtual int Height() = 0;
    virtual bool IsAlpha() = 0;
    virtual void Clear() = 0;
};

typedef shared<Image> ImagePtr;

};

# endif
