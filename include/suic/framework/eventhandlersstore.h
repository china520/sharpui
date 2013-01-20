// 华勤科技版权所有 2010-2011
// 
// 文件名：EventHandlersStore.h
// 功  能：存储事件处理。
// 
// 作  者：汪荣
// 时  间：2012-07-02
// 
// ============================================================================

# ifndef _UIEVENTHANDLERSTORE_H_
# define _UIEVENTHANDLERSTORE_H_

#include <suic/core/uiobject.h>
#include <suic/framework/uirouteevent.h>
#include <suic/tools/map.h>

namespace suic 
{

class SUICORE_API RoutedEventHandlerInfo : public RefObject
{
public:

    int HandlerType;
    ObjectPtr Handler;
    bool InvokeHandledEventsToo;
};

typedef suic::shared<RoutedEventHandlerInfo> RoutedEventHandlerInfoPtr;

class SUICORE_API RoutedEventHandlerInfoList : public RefObject
{
public:

    Vector<RoutedEventHandlerInfoPtr> RoutedEHIList;
};

typedef suic::shared<RoutedEventHandlerInfoList> RoutedEventHandlerInfoListPtr;

class SUICORE_API EventHandlersStore : public RefObject
{
public:

    EventHandlersStore();
    virtual ~EventHandlersStore();

    RoutedEventHandlerInfoListPtr GetRoutedEventHandlerInfoList(RoutedEventEntity);

    void AddHandler(RoutedEventEntity routedEvent, ObjectPtr handler, bool handledEventsToo);
    void RemoveHandler(RoutedEventEntity routedEvent, ObjectPtr handler);
    Map<int, RoutedEventHandlerInfoListPtr>& Entries();

protected:

    Map<int, RoutedEventHandlerInfoListPtr> _entries;
};

typedef suic::shared<EventHandlersStore> EventHandlersStorePtr;

}

# endif
