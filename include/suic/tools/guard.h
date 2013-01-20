// 华勤科技版权所有 2010-2011
// 
// 文件名：UIGuard.h
// 功  能：定义核心库的线程哨兵类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIGUARD_H_
# define _UIGUARD_H_

#include <suic/core/uiobject.h>

namespace suic
{

template<typename LOCK>
class SUICORE_API Guard
{
public:

    Guard(const LOCK & lock)
        : m_lock(lock)
        , m_owner(false)
    {
        m_lock.lock();
        m_owner = true;
    }

    virtual ~Guard()
    {
        Release();
    }

    bool Acquired() const
    {
        if (!m_owner)
        {
            m_lock.lock();
            m_owner = true;
        }

        return true;
    }

    void Release() const
    {
        if (m_owner)
        {
            m_lock.unlock();
            m_owner = false;
        }
    }

protected:

    const LOCK & m_lock;
    mutable bool m_owner;

    friend class ThreadCond;
};

};

# endif
