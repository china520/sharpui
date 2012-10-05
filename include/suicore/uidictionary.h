// 华勤科技版权所有 2010-2011
// 
// 文件名：UIDictionary.h
// 功  能：定义核心库的键/值对象。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIDICTIONARY_H_
# define _UIDICTIONARY_H_

#include <suicore/uiobject.h>

namespace suic
{

class SUICORE_API Dictionary : public RefObject
{
public:

    Dictionary();
    virtual ~Dictionary();

    int Count() const;
    void Add(key, value);
    void Clear();
    bool ContainsKey(TKey key);
    bool ContainsValue(TValue value);
    bool Remove(TKey key);
    bool TryGetValue(TKey key, out TValue value);
};

};

# endif
