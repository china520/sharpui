// 华勤科技版权所有 2010-2011
// 
// 文件名：UITypes.h
// 功  能：定义核心库的基础类型。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UITYPES_H_
# define _UITYPES_H_

#include <suicore/uicoreconfig.h>

namespace suic
{

typedef unsigned char Byte;
typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned long int Uint32;
typedef unsigned long long Uint64;

typedef Uint32 Color;
typedef wchar_t Char;

static const Color COLOR_NULL = -1;
static const Uint32 UintMax = -1;

typedef char Int8;
typedef short Int16;
typedef long int Int32;
typedef long long Int64;

typedef double Double;

static unsigned long nan[2]={0xffffffff,0x7fffffff};
static Double Nan = *(double*)nan;

static const Double EPS = (0.0000000001);

static const Uint32 NonInt = -1;
static const Uint32 MaxInt32 = -1;

static const Uint16 MaxInt16 = -1;
static const Uint64 MaxInt64 = -1;

inline bool IsNan(Double x) { return x != x; }
inline bool IsNanInt(Uint32 x) { return x == NonInt; }

typedef unsigned long HUIWND;
typedef unsigned long DHDC;
typedef unsigned long Handle;

};

#define ISZERO(X) (fabs(X) < EPS)

namespace suic
{

class Point : public POINT
{
public:

    Point() { x=0; y=0; }
    Point(int x, int y) { this->x=x; this->y=y; }
    Point(const Point * lppt) { x=lppt->x; y=lppt->y; }
    Point(const POINT * lppt) { x=lppt->x; y=lppt->y; }
    Point(const POINT & pt) { x=pt.x; y=pt.y; }
    Point(const Point & Other) { x=Other.x; y=Other.y; }

    operator POINT & () { return *(this); }
    POINT & operator *() { return *(this); }

    Point operator=(const Point & Other)
    {
        x = Other.x;
        y = Other.y;
        return (*this);
    }

    void Offset(int xf, int yf)
    {
        x += xf;
        y += yf;
    }

    void Offset(const Point& pt)
    {
        x += pt.x;
        y += pt.y;
    }
};

class Size : public SIZE
{
public:

    Size() { cx=0; cy=0; }
    Size(int cx, int cy) { this->cx=cx; this->cy=cy; }
    Size(const Size * lppt) { cx=lppt->cx; cy=lppt->cy; }
    Size(const SIZE * lppt) { cx=lppt->cx; cy=lppt->cy; }
    Size(const SIZE & Other) { cx=Other.cx; cy=Other.cy; }
    Size(const Size & Other) { cx=Other.cx; cy=Other.cy; }

    operator SIZE & () { return *(this); }
    SIZE & operator *() { return *(this); }

    SIZE operator=(const SIZE & Other)
    {
        cx = Other.cx;
        cy = Other.cy;

        return (*this);
    }
};

class Rect : public RECT
{
public:

    Rect() { SetEmpty(); }
    Rect(int x, int y, int cx, int cy) { left=x; top=y; right=x+cx; bottom=y+cy; }
    Rect(const Rect * lprc) { Copy(lprc); }
    Rect(const RECT * lprc) { ::CopyRect(this, lprc); }
    Rect(const Rect & Other) { ::CopyRect(this, &Other); }
    Rect(const RECT & Other) { ::CopyRect(this, &Other); }

    operator RECT & () { return *(this); }
    RECT & operator *() { return *(this); }

    Rect operator=(const Rect & Other)
    {
        left = Other.left;
        top = Other.top;
        right = Other.right;
        bottom = Other.bottom;
        return (*this);
    }

    Rect operator=(const RECT & Other)
    {
        left = Other.left;
        top = Other.top;
        right = Other.right;
        bottom = Other.bottom;
        return (*this);
    }

    int Width() const;
    int Height() const;

    bool Equal(const Rect * lprc);

    void SetRect(int l, int t, int w, int h);
    void SetRectEx(int l, int t, int r, int b);

    void Offset(int x, int y);
    void Offset(const Point& offset);

    void Inflate(int x, int y);
    void Inflate(int l, int t, int r, int b);
    void Inflate(const suic::Rect & rc);
    void Deflate(int x, int y);
    void Deflate(int l, int t, int r, int b);
    void Deflate(const suic::Rect & rc);
    void SetEmpty();
    void Copy(const Rect * lprc);
    bool Intersect(const Rect * lprc1, const Rect * lprc2);
    bool Intersect(const Rect * lprc2);
    Rect& IntersectRet(const Rect * lprc2);
    Rect IntersectRect(const Rect * lprc2);
    bool Union(const Rect * lprc1, const Rect * lprc2);
    bool Union(const Rect * lprc2);
    void UnionOnly(const Rect * lprc2);
    bool Empty() const;
    bool IsZero() const;
    bool PointIn(POINT pt) const;
    Size ToSize() const;
};

inline int Rect::Width() const
{
    return right - left;
}

inline int Rect::Height() const
{
    return bottom - top;
}

inline bool Rect::Equal(const Rect * lprc)
{
    if (left != lprc->left || top != lprc->top || 
        right != lprc->right || bottom != lprc->bottom)
    {
        return false;
    }
    return true;
}

inline void Rect::SetRect(int l, int t, int w, int h)
{
    left = l; top = t;
    right = left + w; bottom = top + h;
}

inline void Rect::SetRectEx(int l, int t, int r, int b)
{
    left = l; top = t;
    right = r; bottom = b;
}

inline void Rect::Offset(int x, int y)
{
    ::OffsetRect(this, x, y);
}

inline void Rect::Offset(const Point& offset)
{
    ::OffsetRect(this, offset.x, offset.y);
}

inline void Rect::Inflate(int x, int y)
{
    ::InflateRect(this, x, y);
}

inline void Rect::Inflate(const suic::Rect & rc)
{
    left -= rc.left; top -= rc.top;
    right += rc.right; bottom += rc.bottom;
}

inline void Rect::Inflate(int l, int t, int r, int b)
{
    left -= l; top -= t;
    right += r; bottom += b;
}

inline void Rect::Deflate(int x, int y)
{
    ::InflateRect(this, -x, -y);
}

inline void Rect::Deflate(int l, int t, int r, int b)
{
    left += l; top += t;
    right -= r; bottom -= b;
}

inline void Rect::Deflate(const suic::Rect & rc)
{
    Deflate(rc.left, rc.top, rc.right, rc.bottom);
}

inline void Rect::SetEmpty()
{
    ::SetRectEmpty(this);
}

inline void Rect::Copy(const Rect * lprc)
{
    ::CopyRect(this, lprc);
}

inline bool Rect::Intersect(const Rect * lprc1, const Rect * lprc2)
{
    return (::IntersectRect(this, lprc1, lprc2) ? true : false);
}

inline bool Rect::Intersect(const Rect * lprc2)
{
    return (::IntersectRect(this, this, lprc2) ? true : false);
}

inline Rect& Rect::IntersectRet(const Rect * lprc2)
{
    Intersect(lprc2);

    return (*this);
}

inline Rect Rect::IntersectRect(const Rect * lprc2)
{
    suic::Rect ret;
    
    ::IntersectRect(&ret, this, lprc2);

    return (ret);
}

inline bool Rect::Union(const Rect * lprc1, const Rect * lprc2)
{
    return (::UnionRect(this, lprc1, lprc2) ? true : false);
}

inline bool Rect::Union(const Rect * lprc2)
{
    return (::UnionRect(this, this, lprc2) ? true : false);
}

inline void Rect::UnionOnly(const Rect * lprc2)
{
    ::UnionRect(this, this, lprc2);
}

inline bool Rect::Empty() const
{
    return (::IsRectEmpty(this) ? true : false);
}

inline bool Rect::IsZero() const
{
    if (0 == left && 0 == top && 
        0 == right && 0 == bottom)
    {
        return true;
    }
    return false;
}

inline bool Rect::PointIn(POINT pt) const
{
    return (::PtInRect(this, pt) ? true : false);
}

inline Size Rect::ToSize() const
{
    return Size(Width(), Height());
}

}

# endif
