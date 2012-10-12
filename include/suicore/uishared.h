// 华勤科技版权所有 2010-2011
// 
// 文件名：UIShared
// 功  能：定义核心库的智能指针对象。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UISHARED_H_
# define _UISHARED_H_

#include <suicore/uicoreconfig.h>

namespace suic
{

template <typename T>
class shared
{
public:

    shared () : _obj(0)
    {
    }

    shared (T * ptr)
        : _obj(ptr)
    {
        if (_obj)
        {
            _obj->__addRef();
        }
    }

    shared (const shared & myObj)
    {
        if (this != &myObj)
        {
            __setFirstPtr (myObj._obj);
        }
    }

    template<typename P>
    shared(const shared<P> & rp)
    {
        __setFirstPtr (dynamic_cast<T*>(rp._obj));
    }

    template<typename P>
    shared(P* rp)
    {
        __setFirstPtr (dynamic_cast<T*>(rp));
    }

    ~shared ()
    {
        if (_obj)
        {
            _obj->__release();
        }
    }

    shared & operator = (T * other)
    {
        __setSharePtr (other);
        return (*this);
    }

    shared & operator = (const shared & myObj)
    {
        if (this != &myObj)
        {
            __setSharePtr (myObj._obj);
        }
        return (*this);
    }

    template<typename P>
    shared & operator = (const shared<P> & rp)
    {
        __setSharePtr(dynamic_cast<T*>(rp._obj));
        return (*this);
    }

    template<typename P>
    shared & operator = (P * rp)
    {
        __setSharePtr(dynamic_cast<T*>(rp));
        return (*this);
    }

    operator T*() const
    {
        return _obj;
    }

    T& operator *() const
    {
        return (*_obj);
    }

    T* operator -> () const
    {
        return _obj;
    }

    T* get () const
    {
        return _obj;
    }

    operator bool() const
    {
        return _obj ? true : false;
    }

    bool operator < (const shared & other) const
    {
        return (other._obj < _obj);
    }

    bool operator > (const shared & other) const
    {
        return (other._obj > _obj);
    }

    bool operator == (const shared & other) const
    {
        return (other._obj == _obj);
    }

    bool operator != (const shared & other) const
    {
        return (other._obj != _obj);
    }

    bool operator != (T * other) const
    {
        return (other != _obj);
    }

    void swap(shared & other)
    {
        // tbd
        //std::swap(_ptr, other._ptr);
    }

    void attach (T * ptr)
    {
        __setSharePtr (ptr);
    }

    template<class P>
    static shared cast(const shared<P> & rp)
    {
        return shared(dynamic_cast<T*>(rp._obj));
    }

    template<class P>
    static shared cast(P * rp)
    {
        return shared(dynamic_cast<T*>(rp));
    }

    void __setSharePtr (T * ptr)
    {
        if (_obj != ptr)
        {
            T * op = _obj;
            _obj = ptr;
            if (_obj)
            {
                _obj->__addRef ();
            }
            if (op)
            {
                op->__release ();
            }
        }
    }

    void __setFirstPtr (T * ptr)
    {
        if (0 != (_obj = ptr))
        {
            _obj->__addRef ();
        }
    }

    T*	_obj;
};

template<typename L, typename R>
inline bool operator==(const shared<L> & lp, const shared<R> & rp)
{
    L * l = lp.get();
    R * r = rp.get();
    if(l && r)
    {
        return l == r;
    }
    return !l && !r;
}

template<typename L, typename R>
inline bool operator!=(const shared<L> & lp, const shared<R> & rp)
{
    return !operator==(lp, rp);
}

//////////////////////////////////////////////////////////////////////////////
template<typename L, typename R>
inline bool operator==(const shared<L> & lp, const R * rp)
{
    L * l = lp.get();
    if(l && rp)
    {
        return l == rp;
    }
    return !l && !rp;
}

template<typename L, typename R>
inline bool operator!=(const shared<L> & lp, const R * rp)
{
    return !operator==(lp, rp);
}

//////////////////////////////////////////////////////////////////////////////
template<typename L, typename R>
inline bool operator==(const L * lp, const shared<R> & rp)
{
    R * r = rp.get();
    if(lp && r)
    {
        return lp == r;
    }
    return !lp && !r;
}

template<typename L, typename R>
inline bool operator!=(const L * lp, const shared<R> & rp)
{
    return !operator==(lp, rp);
}

};

# endif
