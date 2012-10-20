// 华勤科技版权所有 2010-2012
// 
// 文件名：uigeometry.h
// 功  能：边界对象区域。
// 
// 作  者：汪荣
// 时  间：2010-05-01
// 
// ======================================================

# ifndef _UIGEOMETRY_H_
# define _UIGEOMETRY_H_

#include <suicore/uiobject.h>

namespace suic
{

class SUICORE_API Geometry : public Object
{
public:

    virtual ~Geometry() {}

    Rect GetBounds() const;
    bool PointIn(Point pt) const;

protected:

    Rect _bounds;
};

inline Rect Geometry::GetBounds() const
{
    return _bounds;
}

inline bool Geometry::PointIn(Point pt) const
{
    return false;
}

};

# endif
