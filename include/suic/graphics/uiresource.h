// 华勤科技版权所有 2010-2011
// 
// 文件名：uiResource.h
// 功  能：定义资源基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIRESOURCE_H_
# define _UIRESOURCE_H_

#include <suic/core/uiobject.h>
#include <suic/core/uiconst.h>

namespace suic
{

class SUICORE_API Resource : public RefObject
{
public:

    virtual ~Resource() {}

    inline String GetKey() const;
    inline void SetKey(const String& key);

    inline String GetName() const;

protected:

    String _key;
    String _name;
};

inline String Resource::GetKey() const 
{ 
    return _key; 
}

inline void Resource::SetKey(const String& key) 
{ 
    _key = key; 
}

inline String Resource::GetName() const 
{ 
    return _name; 
}

}

# endif
