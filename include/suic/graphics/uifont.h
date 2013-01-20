// 华勤科技版权所有 2010-2011
// 
// 文件名：uifont
// 功  能：定义核心库的字体属性。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIFONT_H_
# define _UIFONT_H_

#include <suic/types/uitypes.h>
#include <suic/core/uiobject.h>

namespace suic
{

class SUICORE_API Font : public RefObject
{
public:

    Font();
    virtual ~Font();

    Handle GetFont();
    static Handle FindFont(String id);

    void SetID(String id);
    String GetID() const;

    void SetFontFamily(String name);
    String GetFontFamily() const;

    void SetFontSize(Int32 size);
    Int32 GetFontSize() const;

    void SetFontWeight(Int32 weight);
    Int32 GetFontWeight() const;

    void SetFontItalic(Byte value);
    Byte GetFontItalic() const;

    void SetFontUnderline(Byte value);
    Byte GetFontUnderline() const;

    //String ToString();

protected:

    String _id;
    String _key;
    String _name;
    Int32 _size;
    Int32 _weight;
    Byte _underline;
    Byte _italic;

    Handle _hfont;
};

typedef shared<Font> FontPtr;

inline void Font::SetID(String id)
{
    _id = id;
}

inline String Font::GetID() const
{
    return _id;
}

inline void Font::SetFontFamily(String name)
{
    _name = name;
}

inline String Font::GetFontFamily() const
{
    return _name;
}

inline void Font::SetFontSize(Int32 size)
{
    _size = size;
}

inline Int32 Font::GetFontSize() const
{
    return _size;
}

inline void Font::SetFontWeight(Int32 weight)
{
    if (weight != 0)
    {
        _weight = 900;
    }
    else
    {
        _weight = 0;
    }
}

inline Int32 Font::GetFontWeight() const
{
    return _weight;
}

inline void Font::SetFontItalic(Byte value)
{
    _italic = value;
}

inline Byte Font::GetFontItalic() const
{
    return _italic;
}

inline void Font::SetFontUnderline(Byte value)
{
    _underline = value;
}

inline Byte Font::GetFontUnderline() const
{
    return _underline;
}

}

# endif
