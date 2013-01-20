// 华勤科技版权所有 2010-2011
// 
// 文件名：integer.h
// 功  能：定义核心库的整型对象。
// 
// 作  者：汪荣
// 时  间：2011-07-02
// 
// ============================================================================

# ifndef _UIINTEGER_H_
# define _UIINTEGER_H_

#include <suic/core/uiobject.h>
#include <suic/types/uistring.h>

namespace suic 
{

class SUICORE_API Integer : public RefObject
{
public:

    Integer() : _value(0) {}
    Integer(int value) : _value(value) {}
    Integer(String value, int iDef);

    Int32 ToInt32();
    Double ToDouble();
    String ToString();

    int GetHashCode() const;

    Integer& operator=(const Integer& Other)
    {
        if (&Other != this)
        {
            _value = Other._value;
        }

        return *this;
    }
    
    bool operator<(const Integer& Other)
    {
        return _value < Other._value;
    }

    bool operator==(const Integer& Other)
    {
        return _value == Other._value;
    }

    bool operator!=(const Integer& Other)
    {
        return _value != Other._value;
    }

    bool operator>(const Integer& Other)
    {
        return _value > Other._value;
    }

protected:

    Int32 _value;
};

typedef shared<Integer> IntegerPtr;

class SUICORE_API IntegerType : public Object
{
public:

    IntegerType() : _value(0) {}
    IntegerType(int value) : _value(value) {}

    int GetHashCode() const { return (int)_value;}
    Int32 ToInt32() { return _value; }
    String ToString();

    bool operator==(const IntegerType& Other)
    {
        return _value == Other._value;
    }

protected:

    Int32 _value;
};

}

# endif
