// 华勤科技版权所有 2010-2011
// 
// 文件名：ResourceDictionary.h
// 功  能：资源字典的访问实现。
// 
// 作  者：汪荣
// 时  间：2011-08-02
// 
// ============================================================================

# ifndef _UIRESOURCEDICTIONARY_H_
# define _UIRESOURCEDICTIONARY_H_

#include <suicore/uiconst.h>
#include <suicore/uiobject.h>
#include <util/vector.h>
#include <util/hashmap.h>
#include <util/map.h>

#include <suicore/style/Style.h>

namespace suic 
{

class ResourceDictionary;
typedef shared<ResourceDictionary> ResourceDictionaryPtr;

class SUICORE_API ResourceDictionary : public RefObject
{
public:

    String Source;
    Vector<ResourceDictionaryPtr> MergedDictionaries;

    ResourceDictionary();
    virtual ~ResourceDictionary();

    ObjectPtr Lookup(const String& key);
    void Add(const String& key, ObjectPtr obj);
    void Remove(const String& Key);
    bool Contains(const String& key);

    void GetStyles(Vector<StylePtr>& styles);

    void Clear();

    String ToString();

protected:

    Map<String, ObjectPtr> _baseDictionary;
};

}

#endif
