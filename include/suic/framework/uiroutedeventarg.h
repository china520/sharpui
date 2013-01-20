// 华勤科技版权所有 2010-2011
// 
// 文件名：uiroutedeventarg.h
// 功  能：定义核心库的路由事件基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIROUTEDEVENTARG_H_
# define _UIROUTEDEVENTARG_H_

#include <suic/core/uiobject.h>
#include <suic/core/delegate.h>
#include <suic/framework/uieventarg.h>
#include <suic/framework/uirouteevent.h>

namespace suic
{

class SUICORE_API RoutedEventArg : public EventArg
{
public:

    RoutedEventArg() : _handled(false) {}
    RoutedEventArg(ObjectPtr source);
    RoutedEventArg(RoutedEventEntity routedEvent, ObjectPtr source);

    // 事件是否已被处理
    bool IsHandled() const;

    // 设置事件处理标志
    void SetHandled(bool val);

    RoutedEventEntity GetRoutedEvent() const;
    void SetRoutedEvent(RoutedEventEntity val);

    // 激发事件的界面元素
    ObjectPtr GetSource() const ;
    void SetSource(ObjectPtr el);

    // 拥有鼠标的界面元素
    // 如果此值为空，鼠标离开窗口
    ObjectPtr GetOriginalSource() const;

    virtual void OnSetSource(ObjectPtr source);
    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

public:

    bool _handled;

    ObjectPtr _source;
    ObjectPtr _originalSource;
    RoutedEventEntity _routedEvent;
};

inline ObjectPtr RoutedEventArg::GetOriginalSource() const
{
    return _originalSource;
}

//==============================================================
//

class SUICORE_API SizeModeChangedEventArg : public RoutedEventArg
{
public:

    SizeModeChangedEventArg(Size size, bool bEnd)
        : _finialSize(size), _isExit(bEnd)
    {
    }

    bool IsExitMode() const
    {
        return _isExit;
    }

    Size GetFinalSize() const
    {
        return _finialSize;
    }

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    bool _isExit;
    Size _finialSize;
};

/// <summary>
/// 窗口尺寸位置改变时结构
/// </summary>
class SUICORE_API RenderSizeChangedEventArg : public RoutedEventArg
{
public:

    RenderSizeChangedEventArg(Size prev, Size n);

    Size PrevSize();
    Size NewSize();
    bool WidthChanged();
    bool HeightChanged();

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    bool bWidChanged;
    bool bHeiChanged;

    Size sizePrev;
    Size sizeNew;

};

inline Size RenderSizeChangedEventArg::PrevSize() 
{ 
    return sizePrev; 
}

inline Size RenderSizeChangedEventArg::NewSize() 
{ 
    return sizeNew; 
}

inline bool RenderSizeChangedEventArg::WidthChanged() 
{ 
    return bWidChanged; 
}

inline bool RenderSizeChangedEventArg::HeightChanged() 
{ 
    return bHeiChanged; 
}

class SUICORE_API ContextMenuEventArg : public RoutedEventArg
{
public:

    ContextMenuEventArg(ObjectPtr source, double cursorLeft, double cursorTop)
        : RoutedEventArg(source)
        , _cursorLeft(cursorLeft)
        , _cursorTop(cursorTop)
    {
    }

    double CursorLeft() const
    {
        return _cursorLeft;
    }

    double CursorTop() const
    {
        return _cursorTop;
    }

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    double _cursorLeft;
    double _cursorTop;
};

/// <summary>
/// 定义鼠标测试结果结构，当鼠标在某一个界面元素上时会返回一个测试码。
/// </summary>
typedef struct tagHitResult
{
public:

    tagHitResult() {}

    tagHitResult(Point pt) 
        : hitcode(-1), hitpoint(pt) {}

    Int32 HitTestCode() { return hitcode; }
    void HitTestCode(Int32 code) { hitcode = code; }

    Point HitTestPoint() const { return hitpoint; }

    Point hitpoint;
    Int32 hitcode;

}HitResult;

class SUICORE_API HitResultEventArg : public RoutedEventArg
{
public:

    HitResultEventArg(ObjectPtr source, Point point)
        : RoutedEventArg(source)
        , _hr(point) {}

    Point GetPoint() const
    {
        return _hr.HitTestPoint();
    }

    HitResult& GetHitResult()
    {
        return _hr;
    }

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    HitResult _hr;
};

class SUICORE_API DataTransferEventArg : public RoutedEventArg
{
public:
};

class SUICORE_API StateChangedEventArg : public RoutedEventArg
{
public:

    StateChangedEventArg(int iType, bool val);

    void SetStateName(const String& name);
    String GetStateName() const;

    int GetType() const;
    bool GetValue() const;

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    String _name;
    int _type;
    bool _value;
};

class SUICORE_API ScrollChangedEventArg : public RoutedEventArg
{
public:

    ScrollChangedEventArg(double horz, double vert);

    double GetHorizontalScrollOffset() const { return _horz; }
    double GetVerticalScrollOffset() const { return _vert; }

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    double _horz;
    double _vert;
};

class SUICORE_API LoadedEventArg : public RoutedEventArg
{
public:

    LoadedEventArg(ObjectPtr obj);

    ObjectPtr GetTarget();

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    ObjectPtr _targetObj;
};

class SUICORE_API FocusEventArg : public RoutedEventArg
{
public:

    FocusEventArg(ObjectPtr source, ObjectPtr o, ObjectPtr n);

    ObjectPtr GetOldFocus() const;
    ObjectPtr GetNewFocus() const;

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    ObjectPtr _oldFocus;
    ObjectPtr _newFocus;
};

inline ObjectPtr FocusEventArg::GetOldFocus() const
{
    return _oldFocus;
}

inline ObjectPtr FocusEventArg::GetNewFocus() const
{
    return _newFocus;
}

enum KeyboardCode
{
    IsShift,
    IsMenuKey,
    IsAlt,
    IsEnter,
    IsEsc,
    IsSpaceKey,
    IsLeftKey,
    IsRightKey,
    IsUpKey,
    IsDownKey,
    IsTabKey,
};

/// <summary>
/// 处理键盘事件
/// </summary>
class SUICORE_API KeyboardEventArg : public RoutedEventArg
{
public:

    KeyboardEventArg(ObjectPtr source, int c);

    int GetKey() const { return ch; }
    void SetKey(int c) { ch = c; }

    int State() const { return state; }

    KeyboardCode GetKeyboardCode() const;

    bool IsBackPress() const;
    bool IsDeletePress() const;

    bool IsControlPress() const;
    bool IsShiftPress() const;
    bool IsMenuKeyPress() const;
    bool IsAltPress() const;
    bool IsEnterPress() const;
    bool IsEscPress() const;

    bool IsSpacePress() const;

    bool IsLeftArrow() const;
    bool IsUpArrow() const;
    bool IsRightArrow() const;
    bool IsDownArrow() const;

    bool IsPageup() const;
    bool IsPagedown() const;

    bool IsHomeKey() const;
    bool IsEndKey() const;

    bool IsCapsLock() const;
    bool IsTabKey() const;

    bool IsDigitalKey() const;
    bool IsAlphaKey() const;

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    int ch;
    int state;
    KeyboardCode code;
};

enum MouseButtonState
{
    eMouseRelease,
    eMousePress,
};

enum MouseButtonType
{
    eLeftButton,
    eRightButton,
};

/// <summary>
/// 处理鼠标事件
/// </summary>
class SUICORE_API MouseEventArg : public RoutedEventArg
{
public:

    MouseEventArg(ObjectPtr source, Point pt);

    int MouseState();
    int State();
    Point MousePoint();
    void SetMousePoint(Point pt);

    MouseButtonState LeftButton();
    MouseButtonState MiddleButton();
    MouseButtonState RightButton();
    MouseButtonState XButton1();
    MouseButtonState XButton2();

    MouseButtonType GetButtonType() const;
    void SetButtonType(MouseButtonType val);

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    int state;
    int mousestate;
    Point mousept;
    MouseButtonType buttonType;
};

inline int MouseEventArg::MouseState() 
{ 
    return mousestate; 
}

inline int MouseEventArg::State() 
{ 
    return state; 
}

inline Point MouseEventArg::MousePoint() 
{ 
    return mousept; 
}

inline MouseButtonType MouseEventArg::GetButtonType() const
{
    return buttonType;
}

inline void MouseEventArg::SetButtonType(MouseButtonType val)
{
    buttonType = val;
}

/// <summary>
/// 处理鼠标的滚轮事件
/// </summary>
class SUICORE_API MouseWheelEventArg : public MouseEventArg
{
public:

    MouseWheelEventArg(Point pt, int timestamp, int delta);
    int Delta() { return _delta; }

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    int _delta;
};

/// <summary>
/// 处理光标事件
/// </summary>
class SUICORE_API CursorEventArg : public MouseEventArg
{
public:

    CursorEventArg(Point pt) 
        : MouseEventArg(ObjectPtr(), pt) 
    {
    }

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);
};

class IDataObject : public RefObject
{
public:

    virtual ~IDataObject() {}

    virtual ObjectPtr GetData(String format) = 0;
    virtual void SetData(String format, ObjectPtr val) = 0;
};

typedef shared<IDataObject> DataObjectPtr;

/// <summary>
/// 处理拖曳事件，当某一个对象被拖到某个界面元素上被触发
/// </summary>
class SUICORE_API DragEventArg : public RoutedEventArg
{
public:

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    DataObjectPtr _data;
    ObjectPtr _target;
    Point _dropPoint;
};

/// <summary>
/// 绘制事件，如果需要手动触发某个界面元素的绘制，可以发送此事件。
/// </summary>
class SUICORE_API DrawEventArg : public RoutedEventArg
{
public:

    DrawEventArg(const Rect & rc) 
        : rcClip(rc)
        , RoutedEventArg(ObjectPtr())
    {
    }

    Rect & RenderClip() { return rcClip; }
    void RenderClip(Rect & rc) { rcClip = rc; }

    void CallEventHandler(ObjectPtr& handler, ObjectPtr& target);

protected:

    Rect rcClip;
};

}

# endif
