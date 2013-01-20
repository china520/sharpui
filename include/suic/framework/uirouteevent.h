// 华勤科技版权所有 2010-2011
// 
// 文件名：UIRouteEvent.h
// 功  能：定义核心库的路由事件基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIROUTEEVENT_H_
# define _UIROUTEEVENT_H_

#include <suic/core/uiobject.h>
#include <suic/core/delegate.h>

namespace suic
{

/// <summary>
/// 界面元素的处理方式，Tunneling：如果注册了回溯事件，系统事件处理模块
/// 会调用其事件处理，直到事件被处理掉。
/// </summary>
enum RoutingStrategy
{
    Direct,
    Bubble,
    Tunnel,
};

class RoutedEvent : public RefObject
{
public:

    RoutedEvent(String name, RoutingStrategy routingStrategy, TypeofInfo* handlerType, TypeofInfo* ownerType);
    RoutingStrategy GetRoutingStrategy() const;
    TypeofInfo* GetOwnerType() const;
    String GetName() const;
    int GetGlobalIndex() const;

protected:

    String _name;
    TypeofInfo* _ownerType;
    int _globalIndex;
    RoutingStrategy _routingStrategy;    
};

typedef suic::shared<RoutedEvent> RoutedEventEntity;

};

# endif
