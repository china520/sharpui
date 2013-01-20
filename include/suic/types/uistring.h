// 华勤科技版权所有 2010-2011
// 
// 文件名：UIString.h
// 功  能：定义核心库的String类型。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UISTRING_H_
# define _UISTRING_H_

#include <suic/core/stringcore.h>
#include <suic/core/uiobject.h>

namespace suic
{

class SUICORE_API OString : public RefObject
{
public:

    OString();
    OString(const String& value);
    OString(const OString& Other);
    OString(Int32 value);

    String ToString();
    Double ToDouble();
    Int32 ToInt32();
    bool ToBool();
    Rect ToRect();
    Size ToSize();
    Point ToPoint();
    Color ToColor();

    String& operator*() { return _value; }

protected:

    String _value;
};

}

# endif
