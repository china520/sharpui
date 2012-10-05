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

#include <suicore/stringcore.h>
#include <suicore/uiobject.h>

namespace suic
{

class SUICORE_API UString : public RefObject
{
public:

    UString(const String& value);
    UString(Int32 value);

    virtual String ToString();
    virtual Double ToDouble();
    virtual Int32 ToInt32();
    virtual bool ToBool();
    virtual Rect ToRect();
    virtual Size ToSize();
    virtual Point ToPoint();
    virtual Color ToColor();

protected:

    String _value;
};

}

# endif
