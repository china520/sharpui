// 华勤科技版权所有 2010-2011
// 
// 文件名：DragEvent.h
// 功  能：实现DragEvent
// 
// 作  者：汪荣
// 时  间：2010-08-31
// 
// ============================================================================

# ifndef _UIDRAGEVENT_H_
# define _UIDRAGEVENT_H_

#include <sui/sharpuiconfig.h>
#include <suic/framework/uievent.h>

namespace ui
{

class DragStartedEventArg : public suic::RoutedEventArg
{
public:

    DragStartedEventArg(double horizontalOffset, double verticalOffset)
        : suic::RoutedEventArg(NULL)
    {
        _horizontalOffset = horizontalOffset; 
        _verticalOffset = verticalOffset;
    } 

    double HorizontalOffset() const
    { 
        return _horizontalOffset;
    } 

    double VerticalOffset() const
    {
        return _verticalOffset;
    }

protected:

    double _horizontalOffset; 
    double _verticalOffset;
};

class DragDeltaEventArg : public suic::RoutedEventArg
{
public:

    DragDeltaEventArg(double horizontalChange, double verticalChange)
        : suic::RoutedEventArg(NULL)
    {
        _horizontalChange = horizontalChange; 
        _verticalChange = verticalChange;
    } 

    double HorizontalChange() const
    { 
        return _horizontalChange;
    } 

    double VerticalChange() const
    {
        return _verticalChange;
    }

protected:

    double _horizontalChange;
    double _verticalChange; 
};

class DragCompletedEventArg : public suic::RoutedEventArg
{ 
public:

    DragCompletedEventArg(double horizontalChange, double verticalChange, bool canceled)
        : suic::RoutedEventArg(NULL)
    {
        _horizontalChange = horizontalChange;
        _verticalChange = verticalChange; 
        _wasCanceled = canceled;
    } 

    double HorizontalChange() const 
    {
        return _horizontalChange;
    } 

    double VerticalChange() const
    {
        return _verticalChange;
    } 

    bool Canceled() const
    {
        return _wasCanceled;
    } 

protected:

    double _horizontalChange; 
    double _verticalChange; 
    bool _wasCanceled;
};

typedef delegate<void(suic::ObjectPtr, DragStartedEventArg&)> DragStartedHandler;
typedef delegate<void(suic::ObjectPtr, DragDeltaEventArg&)> DragDeltaHandler;
typedef delegate<void(suic::ObjectPtr, DragCompletedEventArg&)> DragCompletedHandler;

}

# endif
