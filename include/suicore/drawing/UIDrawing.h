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

namespace suic
{

class Image;

/*-
* 绘制接口类，完成一般的绘制，线的颜色采用标准的四色表示
* 其格式为：
*/
class DrawingContext : public RefObject
{
public:

    virtual ~DrawingContext() {};

    virtual void SetOffset(int x, int y) = 0;

    // 取得原始的裁剪区域
    virtual Rect* RenderClip() = 0;
    virtual Size CalculateText(const Char * text, int size, int fmt) = 0;

    // 设置裁剪区域
    virtual void PushClip(const Rect* rcClip) = 0;
    virtual void PushTextColor(Color clr) = 0;
    // 恢复上一次裁剪区域
    virtual void Pop() = 0;

    virtual void SetPixel(int x, int y, Color clr) = 0;
    /*-
    * 功能： 绘制一条直线
    * 参数： pt1-起始点；pt2-终点；n-线的厚度；clr-线的颜色
    */
    virtual void DrawLine(Point pt1, Point pt2, Uint16 n, Color clr) = 0;
    virtual void DrawRectangle(Rect rc, Uint16 n, Color clr) = 0;
    virtual void DrawRoundRectangle(Rect rc, Uint16 n, Uint16 w, Uint16 h, Color clr) = 0;
    virtual void DrawFocused(const Rect * lprc) = 0;

    virtual void DrawImage(Image* img, const Rect* rcdc, const Rect* rcimg, Byte alpha) = 0;
    virtual void DrawTransparent(Image* img, const Rect* rcdc, const Rect* rcimg, Color trans) = 0;

    virtual void FillRectangle(Rect rc, Color clr) = 0;
    virtual void DrawGradient(const Rect* rc, Color dwFirst, Color dwSecond, bool bVertical) = 0;

    virtual void DrawText(const Char * text, int size, const Rect * rc, Color color, Uint32 horz, Uint32 vert) = 0;
    virtual void DrawText(const Char * text, int size, const Rect * rc
        , Color bkcolor, Color color, Uint32 horz, Uint32 vert) = 0;
};

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
    virtual bool Load(const Byte* data, Int32 size) = 0;

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

