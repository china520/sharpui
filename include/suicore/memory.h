
#ifndef __XRMEMORY_H
#define __XRMEMORY_H

#pragma warning(disable : 4244)

#ifndef _USE_NEW

inline void * operator new(size_t, void *_Where)
{
    return (_Where); 
}

inline void * operator new(size_t size);

#if _MSC_VER >= 1200
inline void operator delete(void *, void *)
{
    return; 
}
#endif

#else
#include <new.h>
#endif

namespace suic
{

typedef unsigned int _size_type;

template<class _Ty> inline
_Ty *__Allocate(_size_type _Count, _Ty *)
{
    if (_Count <= 0)
    {
        _Count = 0;
    }
    else if (((_size_type)(-1) / _Count) < sizeof (_Ty))
    {
        // throws
    }

    return ((_Ty *)::operator new(_Count * sizeof (_Ty)));
}

template<class _T1, class _T2> inline
void __construct(_T1 *_Ptr, const _T2& _Val)
{	
    void *_Vptr = _Ptr;
    new(_Vptr)_T1(_Val);
}

template<class _Ty1, class _Ty2> inline
_Ty2 __uninit_copy(_Ty1 _First, _Ty1 _Last, _Ty2 _Dest)
{
    size_t _Count = (size_t)(_Last - _First);

    _Ty2 _Result = _Dest + _Count;

    if (_Count > 0)
    {
        memmove_s(&*_Dest,
        _Count * sizeof (*_First), &*_First,
        _Count * sizeof (*_First));
    }

    return (_Result);
}

}

#endif

