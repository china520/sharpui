// 华勤科技版权所有 2010-2011
// 
// 文件名：uiinvokerpriorityqueue.h
// 功  能：实现带有优先级的队列。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIINVOKERPRIORITYQUEUE_H_
# define _UIINVOKERPRIORITYQUEUE_H_

#include <suicore/uiassignerinvoker.h>
#include <suicore/uistructure.h>
#include <util/locker.h>

namespace suic
{

class SUICORE_API InvokerPriorityQueue  : public RefObject
{
public:

    InvokerPriorityQueue();

    // 取出有数据的最大优先级
    int GetMaxPriority();

    // 弹出优先级最高的操作项
    AssignerInvokerPtr Dequeue();
    void Enqueue(AssignerInvokerPtr, int Priority);

    void RemoveItem(AssignerInvokerPtr item);

protected:

    void CalculateMaxPriority();

protected:

    EnumeratorPtr _sendQueue;
    EnumeratorPtr _queue;
    int _maxPriority;
    Mutex _queueLock;
};

typedef shared<InvokerPriorityQueue> InvokerPriorityQueuePtr;

}

# endif