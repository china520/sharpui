// 华勤科技版权所有 2010-2011
// 
// 文件名：Brush.h
// 功  能：定义刷子基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIBRUSH_H_
# define _UIBRUSH_H_

#include <suicore/drawing/uiresource.h>

namespace suic
{

class DrawingContext;
class SUICORE_API Brush : public Resource
{
public:

    Brush() : _opacity(1.0) {}
    virtual ~Brush() {}

    double GetOpacity() const;
    void SetOpacity(double val);

    virtual bool Parse(const suic::String& xml) = 0;
    virtual bool Parse(void* node);
    virtual void Draw(DrawingContext* drawing, const Rect* lprc) = 0;
    virtual void Draw(DrawingContext* drawing, const Rect* lprc, const Rect* border);

protected:

    double _opacity;
};

typedef shared<Brush> BrushPtr;

inline double Brush::GetOpacity() const
{
    return _opacity;
}

inline void Brush::SetOpacity(double val)
{
    _opacity = val;
}

class SUICORE_API TileBrush : public Brush
{
public:

    virtual ~TileBrush() {};

    AlignmentX GetAlignmentX() const;
    void GetAlignmentX(AlignmentX val);

    AlignmentY GetAlignmentY() const;
    void SetAlignmentY(AlignmentY val);

    Stretch GetStretch() const;
    void SetStretch(Stretch val);

    TileMode GetTileMode() const;
    void SetTileMode(TileMode val);

    Rect GetViewbox() const;
    void SetViewbox(Rect val);

    Rect GetViewport() const;
    void SetViewport(Rect val);

protected:

    //如果_stretch不是Fill或者UniformToFill
    // 则_alignmentX和_alignmentY有效
    AlignmentX _alignmentX;
    AlignmentY _alignmentY;
    Stretch _stretch;
    TileMode _tileMode;

    // 基于原图的显示区域，如果为图像
    // 则可指定绘制图像的某一区域
    Rect _viewbox;
    // 基于画布的显示区域
    Rect _viewport;
};

typedef shared<TileBrush> TileBrushPtr;

inline AlignmentX TileBrush::GetAlignmentX() const
{
    return _alignmentX;
}

inline void TileBrush::GetAlignmentX(AlignmentX val)
{
    _alignmentX = val;
}

inline AlignmentY TileBrush::GetAlignmentY() const
{
    return _alignmentY;
}

inline void TileBrush::SetAlignmentY(AlignmentY val)
{
    _alignmentY = val;
}

inline Stretch TileBrush::GetStretch() const
{
    return _stretch;
}

inline void TileBrush::SetStretch(Stretch val)
{
    _stretch = val;
}

inline TileMode TileBrush::GetTileMode() const
{
    return _tileMode;
}

inline void TileBrush::SetTileMode(TileMode val)
{
    _tileMode = val;
}

inline Rect TileBrush::GetViewbox() const
{
    return _viewbox;
}

inline void TileBrush::SetViewbox(Rect val)
{
    _viewbox = val;
}

inline Rect TileBrush::GetViewport() const
{
    return _viewbox;
}

inline void TileBrush::SetViewport(Rect val)
{
    _viewbox = val;
}

class SUICORE_API Cursor : public Resource
{
public:

    Cursor();
    ~Cursor();

    bool Load(const suic::String& source);
    suic::Handle GetHandle() const;

    void Clear();

protected:

    suic::Handle _handle;
};

typedef shared<Cursor> CursorPtr;

}

# endif
