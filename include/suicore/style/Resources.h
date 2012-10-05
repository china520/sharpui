// 华勤科技版权所有 2010-2011
// 
// 文件名：Resources.h
// 功  能：资源的访问实现。
// 
// 作  者：汪荣
// 时  间：2011-08-02
// 
// ============================================================================

# ifndef _UIRESOURCS_H_
# define _UIRESOURCS_H_

#include <suicore/uiconst.h>
#include <suicore/uiobject.h>

namespace suic 
{

class Resources;
typedef Shared<Resources> ResourcesPtr;

class Resources : public RefObject
{
public:

    String TargetName;
    ResourceDictionaryPtr Resources;
    StyleCollection Styles;

    Resources();
    virtual ~Resources();

    int GetCount() const;
    ResourcesPtr GetResources(int index);
    ResourcesPtr Lookup(const String& targetName) const;
    void SetResources(const String& targetName, ResourcesPtr resources);

    void Clear();

    String ToString();

protected:

    ObjectPtr _items;
};

typedef Shared<ResourceDictionary> ResourceDictionaryPtr;

}

#endif
