// 华勤科技版权所有 2010-2011
// 
// 文件名：delegate.h
// 功  能：实现委托调用
// 
// 作  者：汪荣
// 时  间：2010-08-02
// 
// =========================================================

# ifndef _UIDELEGATE_H_
# define _UIDELEGATE_H_

#include <suicore/uiobject.h>

inline void throwBadInvoke()
{
}

/// <summary>
/// 目前最多支持9个参数委托绑定
/// </summary>
#define FUNC_RET R

#define UNION_S(a, b) UNION_S_OO((a, b))
#define UNION_S_OO(par) UNION_S_I ## par
#define UNION_S_I(a, b) UNION_S_II(a ## b)
#define UNION_S_II(res) res
#define UNION_ARG(r,u) r##(##u##)

/// <summary>
/// 支持多个参数的重复绑定
/// </summary>

#define ARGS_REPEAT_2_1(T,A) T##1 A##1
#define ARGS_REPEAT_2_2(T,A) ARGS_REPEAT_2_1(T,A),T##2 A##2
#define ARGS_REPEAT_2_3(T,A) ARGS_REPEAT_2_2(T,A),T##3 A##3
#define ARGS_REPEAT_2_4(T,A) ARGS_REPEAT_2_3(T,A),T##4 A##4
#define ARGS_REPEAT_2_5(T,A) ARGS_REPEAT_2_4(T,A),T##5 A##5
#define ARGS_REPEAT_2_6(T,A) ARGS_REPEAT_2_5(T,A),T##6 A##6
#define ARGS_REPEAT_2_7(T,A) ARGS_REPEAT_2_6(T,A),T##7 A##7
#define ARGS_REPEAT_2_8(T,A) ARGS_REPEAT_2_7(T,A),T##8 A##8
#define ARGS_REPEAT_2_9(T,A) ARGS_REPEAT_2_8(T,A),T##9 A##9


#define ARGS_REPEAT_1_1(A) A##1
#define ARGS_REPEAT_1_2(A) ARGS_REPEAT_1_1(A),A##2
#define ARGS_REPEAT_1_3(A) ARGS_REPEAT_1_2(A),A##3
#define ARGS_REPEAT_1_4(A) ARGS_REPEAT_1_3(A),A##4
#define ARGS_REPEAT_1_5(A) ARGS_REPEAT_1_4(A),A##5
#define ARGS_REPEAT_1_6(A) ARGS_REPEAT_1_5(A),A##6
#define ARGS_REPEAT_1_7(A) ARGS_REPEAT_1_6(A),A##7
#define ARGS_REPEAT_1_8(A) ARGS_REPEAT_1_7(A),A##8
#define ARGS_REPEAT_1_9(A) ARGS_REPEAT_1_8(A),A##9


// error Cannot handle Delegate objects that accept more than 9 arguments!


////////////////////////////////////////////////////////////////////////////////////////

#define REPEAT_2_N(n,T,A) UNION_S(ARGS_REPEAT_2_,n(T,A))
#define REPEAT_1_N(n,A) UNION_S(ARGS_REPEAT_1_,n(A))

class X;
union IFunctor
{
   // 对于仿函数指针
   mutable void * obj_ptr;

   // 对所有类型的函数指针
   mutable void (*func_ptr)();

   // 对于成员函数 指针
   struct memfunc_ptr_t 
   {
      void (X::*memfunc_ptr)(int);
      void * obj_ptr;
   }bound_memfunc_ptr;
};
//functor.func_ptr = (void (*)())(f);
//functor.obj_ptr = new FunctionObj(f);

template<typename sinature>
class delegate {};

template<typename sinature>
struct function_call {};


// 0个参数委托
#define ARGS_COUNT 0
#include "delegate.inl"

// 支持一个参数委托
#define ARGS_COUNT 1
#include "delegate.inl"

#define ARGS_COUNT 2
#include "delegate.inl"

#define ARGS_COUNT 3
#include "delegate.inl"

#define ARGS_COUNT 4
#include "delegate.inl"

#define ARGS_COUNT 5
#include "delegate.inl"

#define ARGS_COUNT 6
#include "delegate.inl"

#define ARGS_COUNT 7
#include "delegate.inl"

#define ARGS_COUNT 8
#include "delegate.inl"

#define ARGS_COUNT 9
#include "delegate.inl"

#endif