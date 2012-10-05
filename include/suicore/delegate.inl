// 华勤科技版权所有 2010-2011
// 
// 文件名：delegate.h
// 功  能：实现委托调用
// 
// 作  者：汪荣
// 时  间：2008-08-02
// 
// ============================================================================

#include <suicore/uiobject.h>

// 支持没有参数的函数情况
#define UNION_TARG(u) typename FUNC_RET,u

#if ARGS_COUNT == 0

#undef UNION_TARG
#define UNION_TARG(u) typename FUNC_RET

#define	FUNC_ARGS_DECLARE
#define	FUNC_ARGS
#define	TEMPLATE_ARGS_DECLARE
#define	TEMPLATE_ARGS

#elif ARGS_COUNT < 0

# error Cannot handle delegate objects that accept more than 9 arguments!

#else

#define	FUNC_ARGS_DECLARE REPEAT_2_N(ARGS_COUNT,T,a)
#define	FUNC_ARGS REPEAT_1_N(ARGS_COUNT,a)
#define	TEMPLATE_ARGS_DECLARE  REPEAT_1_N(ARGS_COUNT,typename T)
#define	TEMPLATE_ARGS REPEAT_1_N(ARGS_COUNT,T)

#endif

////////////////////////////////////////////////////////////////////////////////////////
// delegate.ini
template<UNION_TARG(TEMPLATE_ARGS_DECLARE)>
struct function_call<UNION_ARG(FUNC_RET,TEMPLATE_ARGS)>
{
    class invoker_base : public suic::RefObject
    {
    private:

        virtual FUNC_RET Invoke(FUNC_ARGS_DECLARE) = 0;
        friend class delegate<UNION_ARG(FUNC_RET,TEMPLATE_ARGS)>;
    };

    typedef suic::shared<invoker_base> invoker_basePtr;

    // 对于一般函数
    template<typename T>
    class  invoker_func_obj_ptr : public invoker_base
    {
    public:

        explicit invoker_func_obj_ptr(T t) : obj_ptr(t) {}

    private:

        FUNC_RET Invoke(FUNC_ARGS_DECLARE) { return obj_ptr(FUNC_ARGS); }  

    private:

        T obj_ptr;
    };

    // 对于类成员函数
    template<typename T>
    class  invoker_func_mem_ptr : public invoker_base
    {
    public:

        typedef FUNC_RET(T::*func_type)(TEMPLATE_ARGS);
        explicit invoker_func_mem_ptr(T * t, func_type f) : obj_ptr(t), func_ptr(f) {}

    private:

        FUNC_RET Invoke(FUNC_ARGS_DECLARE) { return (obj_ptr->*func_ptr)(FUNC_ARGS); }

    private:

        T * obj_ptr;
        func_type func_ptr;
    };

    // 对于引用类成员函数
    template<typename T>
    class invoker_func_mem_ref_ptr : public invoker_base
    {
    public:

        typedef FUNC_RET(T::*func_type)(TEMPLATE_ARGS);
        explicit invoker_func_mem_ref_ptr(T & t, func_type f) : obj_ref(t), func_ptr(f) {}

    private:

        FUNC_RET Invoke(FUNC_ARGS_DECLARE){ return (obj_ref.*func_ptr)(FUNC_ARGS); }

    private:

        T & obj_ref;
        func_type func_ptr;
    };

    // 对于引用类成员函数
    template<typename T>
    class invoker_func_mem_static_ptr : public invoker_base
    {
    public:

        typedef FUNC_RET(T::*func_type)(TEMPLATE_ARGS);
        explicit invoker_func_mem_static_ptr(func_type f) : func_ptr(f) {}

    private:

        FUNC_RET Invoke(FUNC_ARGS_DECLARE){ return (T::func_ptr)(FUNC_ARGS); }

    private:

        func_type func_ptr;
    };

    // 对于智能指针类成员函数
    template<typename T>
    class invoker_func_mem_ptr_ptr : public invoker_base
    {
    public:

        typedef FUNC_RET(T::*func_type)(TEMPLATE_ARGS);
        explicit invoker_func_mem_ptr_ptr(T t, func_type f) : obj_ref(t), func_ptr(f) {}

    private:

        FUNC_RET Invoke(FUNC_ARGS_DECLARE){ return (obj_ref->*func_ptr)(FUNC_ARGS); }

    private:

        T obj_ref;
        func_type func_ptr;
    };
};

template<TEMPLATE_ARGS_DECLARE>
struct function_call<UNION_ARG(void,TEMPLATE_ARGS)>
{
    class invoker_base : public suic::RefObject
    {
    private:

        virtual void Invoke(FUNC_ARGS_DECLARE) = 0;
        friend class delegate<UNION_ARG(void,TEMPLATE_ARGS)>;
    };

    typedef suic::shared<invoker_base> invoker_basePtr;


    // 对于一般函数
    template<typename T>
    class invoker_func_obj_ptr : public invoker_base
    {
    public:

        explicit invoker_func_obj_ptr(T t) : obj_ptr(t) {}

    private:

        void Invoke(FUNC_ARGS_DECLARE) { obj_ptr(FUNC_ARGS); }

    private:

        T obj_ptr;
    };

    // 对于类成员函数
    template<typename T>
    class invoker_func_mem_ptr : public invoker_base
    {
    public:

        typedef void(T::*func_type)(TEMPLATE_ARGS);
        explicit invoker_func_mem_ptr(T * t, func_type f) : obj_ptr(t), func_ptr(f) {}

    private:

        void Invoke(FUNC_ARGS_DECLARE) { (obj_ptr->*func_ptr)(FUNC_ARGS); }

    private:

        T * obj_ptr;
        func_type func_ptr;
    };

    // 对于引用类成员函数
    template<typename T>
    class invoker_func_mem_ref_ptr : public invoker_base
    {
    public:

        typedef void(T::*func_type)(TEMPLATE_ARGS);
        explicit invoker_func_mem_ref_ptr(T & t, func_type f) : obj_ref(t), func_ptr(f) {}

    private:

        void Invoke(FUNC_ARGS_DECLARE) { (obj_ref.*func_ptr)(FUNC_ARGS); }

    private:

        T & obj_ptr;
        func_type func_ptr;
    };

    // 对于类静态成员函数
    template<typename T>
    class invoker_func_mem_static_ptr : public invoker_base
    {
    public:

        typedef void(T::*func_type)(TEMPLATE_ARGS);
        explicit invoker_func_mem_static_ptr(func_type f) : func_ptr(f) {}

    private:

        void Invoke(FUNC_ARGS_DECLARE) { (T::func_ptr)(FUNC_ARGS); }

    private:

        func_type func_ptr;
    };

    // 对于智能指针类成员函数
    template<typename T>
    class  invoker_func_mem_ptr_ptr : public invoker_base
    {
    public:

        typedef void(T::*func_type)(TEMPLATE_ARGS);
        explicit invoker_func_mem_ptr_ptr(T t, func_type f) : obj_ref(t), func_ptr(f) {}

    private:

        void Invoke(FUNC_ARGS_DECLARE){ (obj_ref->*func_ptr)(FUNC_ARGS); }

    private:

        T obj_ref;
        func_type func_ptr;
    };
};

////////////////////////// 委托的实现
template<UNION_TARG(TEMPLATE_ARGS_DECLARE)>
class delegate<UNION_ARG(FUNC_RET,TEMPLATE_ARGS)>
{
public:

    typedef FUNC_RET(*func_type)(TEMPLATE_ARGS);
    typedef typename  function_call<UNION_ARG(FUNC_RET,TEMPLATE_ARGS)> call_type;
    typedef typename call_type::invoker_basePtr invoker_typePtr;
    typedef typename call_type::invoker_base invoker_type;

    delegate(invoker_type* val) 
    {
        if (val)
        {
            _invoker = val;
        }
    }

    delegate() 
    {
    }

    delegate(const delegate& Other) 
        : _invoker(Other._invoker) 
    {
    }

    template<typename T>
    delegate(T t)
    {
        _invoker = new call_type::invoker_func_obj_ptr<T>(t);
    }

    // 类静态成员函数
    template<typename T> 
    delegate(FUNC_RET (T::*_Pm)(TEMPLATE_ARGS))
    {
        _invoker = new call_type::invoker_func_mem_static_ptr<T>(_Pm);
    }

    // 类成员函数
    template<typename T>
    delegate(T * t, FUNC_RET (T::*_Pm)(TEMPLATE_ARGS))
    {
        _invoker = new call_type::invoker_func_mem_ptr<T>(t, _Pm);
    }

    template<typename T>
    delegate(T & t, FUNC_RET (T::*_Pm)(TEMPLATE_ARGS))
    {
        _invoker =  new call_type::invoker_func_mem_ref_ptr<T>(t, _Pm);
    }

    // 绑定成员函数指针，采用智能方式
    template<typename T>
    delegate(T t, FUNC_RET (T::*_Pm)(TEMPLATE_ARGS))
    {
        _invoker =  new call_type::invoker_func_mem_ptr_ptr<T>(t, _Pm);
    }

    ~delegate() { clear(); }

    delegate operator=(invoker_type* val)
    {
        if (val != _invoker.get())
        {
            _invoker = val;
        }

        return (*this);
    }

    delegate operator=(const delegate& Other)
    {
        if (&Other != this)
        {
            _invoker = Other._invoker;
        }

        return (*this);
    }

    // 绑定一般函数指针
    template<typename T>
    void operator+=(T t)
    {
        clear();
        _invoker = new call_type::invoker_func_obj_ptr<T>(t);
    }

    void operator+=(invoker_type * Other)
    {
        clear();
        _invoker = Other;
    }

    template<typename T> 
    void Add(FUNC_RET (T::*_Pm)(TEMPLATE_ARGS))
    {
        _invoker = new call_type::invoker_func_mem_static_ptr<T>(_Pm);
    }

    // 绑定一般函数指针
    template<typename T>
    void Add(T t)
    {
        _invoker = new call_type::invoker_func_obj_ptr<T>(t);
    }

    // 绑定成员函数指针
    template<typename T>
    void Add(T * t, FUNC_RET (T::*_Pm)(TEMPLATE_ARGS))
    {
        _invoker = new call_type::invoker_func_mem_ptr<T>(t, _Pm);
    }

    // 绑定成员函数指针，采用引用方式
    template<typename T>
    void Add(T & t, FUNC_RET (T::*_Pm)(TEMPLATE_ARGS))
    {
        _invoker =  new call_type::invoker_func_mem_ref_ptr<T>(t, _Pm);
    }

    // 绑定成员函数指针，采用智能方式
    template<typename T>
    void Add(T t, FUNC_RET (T::*_Pm)(TEMPLATE_ARGS))
    {
        _invoker =  new call_type::invoker_func_mem_ptr_ptr<T>(t, _Pm);
    }

    FUNC_RET operator()(FUNC_ARGS_DECLARE)
    {
        if (!_invoker) 
        {
            throwBadInvoke();
        }
        return _invoker->Invoke(FUNC_ARGS);
    }

    bool safe_bool() const
    {
        return (NULL != _invoker.get());
    }

    operator invoker_type*()
    {
        return _invoker.get();
    }

    void clear()
    {
        if (_invoker)
        {
            _invoker = 0;
        }
    }

private:

    invoker_typePtr _invoker;
};

// 取消宏的定义，下一次特化定义
#undef   UNION_TARG
#undef   ARGS_COUNT
#undef   FUNC_ARGS_DECLARE
#undef   FUNC_ARGS
#undef   TEMPLATE_ARGS_DECLARE
#undef   TEMPLATE_ARGS