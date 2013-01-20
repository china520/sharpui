// 华勤科技版权所有 2010-2011
// 
// 文件名：eventhelper.h
// 功  能：核心框架事件工具类。
// 
// 作  者：汪荣
// 时  间：2011-07-02
// 
// ============================================================================

# ifndef _UIEVENTHELPER_H_
# define _UIEVENTHELPER_H_

#include <suic/core/uiobject.h>
#include <suic/framework/uielement.h>

namespace suic
{

class SUICORE_API EventHelper : public Object
{
public:

    static RoutedEventEntity RegisterRoutedEvent(String name, RoutingStrategy routingStrategy, TypeofInfo* handlerType,TypeofInfo* ownerType);
    static void RegisterClassHandler(TypeofInfo* ownerType, RoutedEventEntity routedEvent, ObjectPtr handler,bool handledEventsToo);
    static void RegisterAttachedHandler(TypeofInfo* ownerType, RoutedEventEntity routedEvent, ObjectPtr handler,bool handledEventsToo);

    static EventHandlersStorePtr GetClassEventHandlersStore(suic::TypeofInfo* ownerType);
    static EventHandlersStorePtr GetAttachedEventHandlersStore(TypeofInfo* ownerType);

    static RoutedEventHandlerInfoListPtr GetClassRoutedEventHandlerInfo(TypeofInfo* ownerType, const RoutedEventEntity& routedEvent);
    static RoutedEventHandlerInfoListPtr GetAttachedRoutedEventHandlerInfo(TypeofInfo* ownerType, const RoutedEventEntity& routedEvent);

protected:

    EventHelper();
};

};

# endif
