
#ifndef __XRMEMORY_H
#define __XRMEMORY_H

#pragma warning(disable : 4244)

#include <new.h>

namespace suic
{

typedef unsigned int _size_type;

SUICORE_API void* suiMalloc(size_t size);
SUICORE_API void suiFree(void* ptr);

template<class T> inline
T* __allocate(_size_type count, T*)
{
    if (count <= 0)
    {
        count = 0;
    }
    else if (((_size_type)(-1) / count) < sizeof (T))
    {
    }

    return ((T*)suiMalloc(count * sizeof (T)));
}

template<class T1, class T2> inline
void __construct(T1* ptr, const T2& val)
{	
    void* vptr = ptr;
    new (vptr)T1(val);
}

template<class T1, class T2> inline
T2 __uninit_copy(T1 first, T1 last, T2 dest)
{
    size_t count = (size_t)(last - first);

    T2 result = dest + count;

    if (count > 0)
    {
        memmove_s(&*dest, count * sizeof(*first), &*first, count * sizeof(*first));
    }

    return (result);
}

}

#endif
