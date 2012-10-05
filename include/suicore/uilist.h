// 华勤科技版权所有 2010-2011
// 
// 文件名：UIList.h
// 功  能：定义核心库的列表类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UILIST_H_
# define _UILIST_H_

#include <suicore/uiobject.h>

namespace suic
{

class SUICORE_API List : public RefObject
{
public:

    List();
    virtual ~List();

    bool Contains(T item);
    int IndexOf(T item);
    int IndexOf(T item, int index);
    int IndexOf(T item, int index, int count);

    void Insert(int index, T item);
    bool Remove(T item);
    void RemoveAll();
    void RemoveRange(int index, int count);
    void Reverse();
    void Reverse(int index, int count);
    void Sort();
};

};

# endif
