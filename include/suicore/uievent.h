// 华勤科技版权所有 2010-2011
// 
// 文件名：UIEvent.h
// 功  能：定义核心库的事件基类。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UIEVENT_H_
# define _UIEVENT_H_

#include <suicore/uiobject.h>
#include <suicore/delegate.h>

namespace suic
{

class DragDropEffects
{
public:

    enum
    {
        Scroll = -2,
        All = -1,
        None = 0,
        Copy = 1,
        Move = 2,
        Link = 4,
    };
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
/// 定义鼠标测试结果结构，当鼠标在某一个界面元素上时会返回一个测试码。
/// </summary>
typedef struct tagHitResult
{
public:

    tagHitResult() 
    {
    }

    tagHitResult(Point pt) 
        : hitcode(-1), hitpoint(pt) 
    {
    }

    Int32 HitTestCode() { return hitcode; }
    void HitTestCode(Int32 code) { hitcode = code; }

    Point HitTestPoint() const { return hitpoint; }

    Point hitpoint;
    Int32 hitcode;

}HitResult;

/// <summary>
/// 界面元素的处理方式，Tunneling：如果注册了回溯事件，系统事件处理模块
/// 会调用其事件处理，直到事件被处理掉。
/// </summary>
enum RoutingType
{
    Tunneling,
    Bubbling,
    Direct,
};

class SUICORE_API RoutedEventArg;

/// <summary>
/// 界面元素的事件，这是所有界面元素的基类，其它的界面元素都会直接或
/// 或间接地派生它
/// </summary>
class SUICORE_API EventArg : public Object
{
public:

    EventArg();
    Uint32 Timestamp() const;

protected:

    Uint32 _timestamp;
};

class SUICORE_API SizeModeChangedEventArg : public EventArg
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

protected:

    bool _isExit;
    Size _finialSize;
};

/// <summary>
/// 窗口尺寸位置改变时结构
/// </summary>
class SUICORE_API RenderSizeChangedEventArg : public EventArg
{
public:

    RenderSizeChangedEventArg(Size prev, Size n);

    Size PrevSize();
    Size NewSize();
    bool WidthChanged();
    bool HeightChanged();

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

class SUICORE_API CancelEventArg  : public suic::EventArg
{
public:

    CancelEventArg(bool cancel);

    bool IsCancel();
    void SetCancel(bool cancel);

protected:

    bool _cancel;
};

class SUICORE_API RoutedEventArg : public EventArg
{
public:

    RoutedEventArg(ObjectPtr source);

    // 事件是否已被处理
    bool Handled();

    // 设置事件处理标志
    void Handled(bool val);

    // 激发事件的界面元素
    ObjectPtr GetSource() const ;
    void SetSource(ObjectPtr el);

    // 拥有鼠标的界面元素
    // 如果此值为空，鼠标离开窗口
    ObjectPtr GetOriginalSource() const;

    virtual void OnSetSource(ObjectPtr source);

public:

    bool _handled;

    ObjectPtr _source;
    ObjectPtr _originalSource;
};

inline ObjectPtr RoutedEventArg::GetOriginalSource() const
{
    return _originalSource;
}

class SUICORE_API HitResultEventArg : public RoutedEventArg
{
public:

    HitResultEventArg(ObjectPtr source, Point point)
        : RoutedEventArg(source)
        , _hr(point)
    {
        ;
    }

    Point GetPoint() const
    {
        return _hr.HitTestPoint();
    }

    HitResult* GetHitResult()
    {
        return &_hr;
    }

protected:

    HitResult _hr;
};

class SUICORE_API DataTransferEventArg : public RoutedEventArg
{
public:
};

class SUICORE_API SetterChangedEventArg : public EventArg
{
public:

    enum eAction {Add, Remove, Replace};

    SetterChangedEventArg(const String& name, ObjectPtr obj, int action);

    int GetAction() const
    {
        return _action;
    }

    String GetName() const
    {
        return _name;
    }

    ObjectPtr GetSetter() const
    {
        return _value;
    }

protected:

    String _name;
    ObjectPtr _value;
    int _action;
};

class SUICORE_API StateChangedEventArg : public EventArg
{
public:

    StateChangedEventArg(int iType, bool val);

    void SetStateName(const String& name);
    String GetStateName() const;

    int GetType() const;
    bool GetValue() const;

protected:

    String _name;
    int _type;
    bool _value;
};

class SUICORE_API ScrollChangedEventArg : public EventArg
{
public:

    ScrollChangedEventArg(double horz, double vert);

    double GetHorizontalScrollOffset() const { return _horz; }
    double GetVerticalScrollOffset() const { return _vert; }

protected:

    double _horz;
    double _vert;
};

class SUICORE_API ValueChangedEventArg : public EventArg
{
public:

    ValueChangedEventArg(const String& key, ObjectPtr oldVal, ObjectPtr newVal);

    String GetKey() const { return _key; }
    ObjectPtr GetOldValue() const { return _oldVal; }
    ObjectPtr GetNewValue() const { return _newVal; }

protected:

    String _key;
    ObjectPtr _oldVal;
    ObjectPtr _newVal;
};

class SUICORE_API LoadedEventArg : public RoutedEventArg
{
public:

    LoadedEventArg(ObjectPtr obj);

    ObjectPtr GetTarget();

protected:

    ObjectPtr _targetObj;
};

class SUICORE_API FocusEventArg : public RoutedEventArg
{
public:

    FocusEventArg(ObjectPtr source, ObjectPtr o, ObjectPtr n);

    ObjectPtr GetOldFocus() const;
    ObjectPtr GetNewFocus() const;

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

/// <summary>
/// 处理键盘事件
/// </summary>
class SUICORE_API KeyEventArg : public RoutedEventArg
{
public:

    KeyEventArg(ObjectPtr source, int c);

    int GetKey() const { return ch; }
    void SetKey(int c) { ch = c; }

    int State() const { return state; }

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

protected:

    int ch;
    int state;
};

enum MouseButtonState
{
    eMouseRelease,
    eMousePress,
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

protected:

    int state;
    int mousestate;
    Point mousept;
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

/// <summary>
/// 处理鼠标的滚轮事件
/// </summary>
class SUICORE_API MouseWheelEventArg : public MouseEventArg
{
public:

    MouseWheelEventArg(Point pt, int timestamp, int delta);
    int Delta() { return _delta; }

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
};

/// <summary>
/// 处理拖曳事件，当某一个对象被拖到某个界面元素上被触发
/// </summary>
class SUICORE_API DragEventArg : public RoutedEventArg
{
public:

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

protected:

    Rect rcClip;
};

};

# endif
