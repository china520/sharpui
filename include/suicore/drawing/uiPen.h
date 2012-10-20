// 华勤科技版权所有 2010-2011
// 
// 文件名：uiPen.h
// 功  能：定义画笔基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIPEN_H_
# define _UIPEN_H_

#include <suicore/drawing/uiresource.h>

namespace suic
{

class SUICORE_API Pen : public Resource
{
public:

    virtual ~Pen() {}

    double GetThickness() const;
    void GetThickness(double val);

    Color GetColor() const;

protected:

    double _thickness;
    Color _color;
};

typedef shared<Pen> PenPtr;

inline double Pen::GetThickness() const
{
    return _thickness;
}

inline void Pen::GetThickness(double val)
{
    _thickness = val;
}

inline Color Pen::GetColor() const
{
    return _color;
}

}

# endif
