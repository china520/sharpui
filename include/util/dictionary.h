// 华勤科技版权所有 2010-2011
// 
// 文件名：dictionary.h
// 功  能：字典的访问实现。
// 
// 作  者：汪荣
// 时  间：2011-08-02
// 
// ============================================================================

# ifndef _UIDICTIONARY_H1_
# define _UIDICTIONARY_H1_

#include <util/vector.h>
#include <util/map.h>

namespace suic 
{

template<typename Key, typename Value, typename BASE=Object>
class Dictionary : public BASE
{
public:

    Dictionary() {}
    virtual ~Dictionary() {}

    void Add(Key key, Value value)
    {
        _items.insert(key, value);
    }

    bool ContainsKey(Key key)
    {
        return (_items.find(key) != _items.end());
    }

    bool Remove(Key key)
    {
        Map<Key, Value>::iterator iter = _items.find(key);

        if (iter != _items.end())
        {
            _items.erase(iter);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool TryGetValue(Key key, Value& value)
    {
        Map<Key, Value>::iterator iter = _items.find(key);

        if (iter != _items.end())
        {
            value = iter->second;

            return true;
        }
        else
        {
            return false;
        }
    }

    int GetCount()
    {
        return (int)_items.size();
    }

    void First()
    {
        _iter = _items.begin();
    }

    void Next()
    {
        ++_iter;
    }

    bool HasNext()
    {
        return (_iter != _items.end());
    }

    Key GetKey()
    {
        return _iter->first;
    }

    Value GetValue()
    {
        return _iter->second;
    }

    void Clear()
    {
        _items.clear();
    }

protected:

    Map<Key, Value> _items;
    typename Map<Key, Value>::iterator _iter;
};

}

#endif
