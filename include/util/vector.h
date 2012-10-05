
#ifndef __UIVECTOR_H
#define __UIVECTOR_H

#include <suicore/memory.h>
#include <suicore/uistring.h>
#include <suicore/uiobject.h>

#pragma warning(disable : 4244)

namespace suic
{

template<typename T, typename BASE=suic::Object>
class VectorAlloc
{
public:

	typedef unsigned int size_type;

    template<class _Other>
    struct rebind
    {
        typedef VectorAlloc<_Other> other;
    };

	T * allocate(size_type _Count)
    {
        return __Allocate(_Count, (T*)0);
    }

    void deallocate(T * _Ptr, size_type)
    {
        ::operator delete(_Ptr);
    }

    void construct(T *_Ptr, const T& _Val)
    {
       __construct(_Ptr, _Val);
    }

    void destroy(T *_Ptr)
	{
        (_Ptr)->~T();
	}    
};

template<class _FwdIt,
class _Diff,
class _Tval,
class _Alloc> inline
void __uninit_fill_n(_FwdIt _First, _Diff _Count, const _Tval& _Val, _Alloc& _Al)
{
    _FwdIt _Next = _First;

    try
    {
        for (; 0 < _Count; --_Count, ++_First)
        {
            _Al.construct(_First, _Val);
        }
        catch (...)
        {
            for (; _Next != _First; ++_Next)
            {
                _Al.destroy(_Next);
            }
            throw;
        }
    }
}

template <class T, typename _Ax=VectorAlloc<T> >
class Vector 
{
public:

    typedef typename _Ax::template rebind<T>::other _Axt;
    _Axt alloc;

	typedef T* iterator;
    typedef const T* const_iterator;
    typedef unsigned int size_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;

    Vector()
    {
        create();
    }

	explicit Vector(size_type n, const T& t = T())
    { 
        create(n,t); 
    }

    Vector(const Vector& v)
    { 
        create(v.begin(), v.end());
    }

    Vector& operator=(const Vector& rhs)
    {
        if (&rhs != this)
        { 
            uncreate();
            create(rhs.begin(), rhs.end());
        }

        return *this;
    }

    virtual ~Vector()
    { 
        uncreate(); 
    }

    T& operator[](size_type i)
    { 
        return data[i]; 
    }

    const T& operator[](size_type i) const
    { 
        return data[i]; 
    }

	void push_back(const T& t)
    {
		if (avail == limit)
        {
            grow(1);
        }
		unchecked_append(t);
	}

    size_type size() const
    {
        return static_cast<size_type>(avail - data); 
    }

    size_type capacity() const
    {
        return static_cast<size_type>(limit - data); 
    }

    void resize(size_type newsize)
    {
        create(newsize, T());
    }

    void resize(size_type newsize, T v)
    {
        create(newsize, v);
    }

    void insert(iterator pos, T v)
    {
        size_type ori = pos - data;

        if (avail == limit)
        {
            grow(1);
            pos = data + ori;
        }

        __move_range(pos, 1);
        alloc.construct(pos, v);

        ++avail;
    }

    void insert(iterator pos, size_type count, T v)
    {
        size_type ori = pos - data;

        if (capacity() < (size() + count))
        {
            grow(count);
            pos = data + ori;
        }

        __move_range(pos, count);

        for (size_type i = 0; i < count; ++i)
        {
            alloc.construct(pos + i, v);
        }

        avail += count;
    }

    void insert(iterator pos, iterator b, iterator e)
    {
        size_type ori = pos - data;

        size_type len = e - b;

        if (capacity() < (size() + len))
        {
            grow(len);
            pos = data + ori;
        }

        __move_range(pos, len);

        int iPos = 0;

        for (iterator t = b; t != e; ++t,++iPos)
        {
            alloc.construct(pos + iPos, t);
        }

        avail += len;
    }

    void erase(iterator pos)
    {
        erase(pos, pos + 1);
    }

    void erase(iterator b, iterator e)
    {
        size_type len = e - b;

        for (iterator t = b; t != e; ++t)
        {
            alloc.destroy(t);
        }
        
        if (e != end())
        {
            __move_range_f(b, (e - b));
        }

        avail = avail - len;
    }

    iterator begin()
    { 
        return data; 
    }

    const_iterator begin() const
    { 
        return data; 
    }

    iterator end()
    {
        return avail; 
    }

    const_iterator end() const
    {
        return avail;
    }

    void clear()
    { 
        uncreate(); 
    }

    bool empty() const
    {
        if (data == avail)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

protected:
    
    iterator __init_content(const_iterator f, const_iterator e, iterator dst)
    {
        size_type len = e - f;

        for (size_type i = 0; i < len; ++i)
        {
            alloc.construct(dst + i, *(f + i));
        }

        return (dst + len);
    }

    void __move_range(iterator& pos, size_type count)
    {
        size_type iSize = end() - pos;

        for (size_type i = 1; i <= iSize; ++i)
        {
            alloc.construct(end() - i + count, *(end() - i));
        }
    }

    void __move_range_f(iterator& pos, size_type count)
    {
        int num = end() - pos - count;

        for (int i = 0; i < num; ++i)
        {
            alloc.construct(pos + i, *(pos + i + count));
        }
    }

private:

    // 第一个元素
    iterator data;

    // 指向最后一个可用元素
    iterator avail;

    // 总容量
    iterator limit;

private:

    void create()
    {
        data = avail = limit = 0;
    }

    void create(size_type n, const T& t)
    {
        data = alloc.allocate(n);

        limit = avail = data + n;

        iterator _First = data;

        for (; 0 < n; --n, ++_First)
        {
            alloc.construct(_First, t);
        }
    }

    void create(const_iterator i, const_iterator j)
    {
        data = alloc.allocate((size_type)(j - i));

        limit = __init_content(i, j, data);
    }

    // destroy the elements in the array and free the memory
    void uncreate()
    {
        if (data)
        {
            iterator it = avail;
            while (it != data)
            {
                alloc.destroy(--it);
            }

            alloc.deallocate(data, (size_type)(limit - data));
        }

        data = limit = avail = 0;
    }

    void grow(size_type len)
    {
        len += size();

        size_type ivail = (size_type)(2 * (limit - data));
        size_type new_size = (ivail > len ? ivail : len);

        iterator new_data = alloc.allocate(new_size);

        size_type iSize = avail - data;

        for (size_type i = 0; i < iSize; ++i)
        {
            alloc.construct(new_data + i, *(data + i));
        }

        uncreate();

        data = new_data;
        avail = new_data + iSize;
        limit = data + new_size;
    }

    void unchecked_append(const T& val)
    {
        alloc.construct(avail++, val);
    }
};

typedef Vector<String> VectorString;

inline int Split(VectorString& ret, String str, const String & delims, unsigned int maxSplits = 0)
{
    unsigned int numSplits = 0;
    Int32 start = 0, pos = 0;

    do
    {
        pos = str.IndexOf(delims, start);

        if (pos == start)
        {
            start = pos + 1;
        }
        else if (pos == npos || (maxSplits && numSplits == maxSplits))
        {
            // Copy the rest of the string
            ret.push_back(str.Substring(start) );
            break;
        }
        else
        {
            // Copy up to delimiter
            ret.push_back(str.Substring(start, static_cast<Int32>(pos - start)));
            start = pos + 1;
        }
        // parse up to next real data
        //start = str.IndexOf(delims, start);
        ++numSplits;

    } while (pos != npos && start != npos);

    return (int)ret.size();
}

}

#endif

