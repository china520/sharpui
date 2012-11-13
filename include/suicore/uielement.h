// 华勤科技版权所有 2010-2011
// 
// 文件名：Element.h
// 功  能：定义核心库的Element基类。
// 
// 作  者：汪荣
// 时  间：2010-05-02
// 
// ============================================================================

# ifndef _UIELEMENT_H_
# define _UIELEMENT_H_

#include <suicore/uivisual.h>
#include <suicore/uievent.h>
#include <suicore/delegate.h>

#include <suicore/style/ResourceDictionary.h>

namespace suic
{

class Element;
typedef shared<Element> ElementPtr;

typedef delegate<void(suic::Element*, const EventArg&)> EventHandler;
typedef delegate<void(suic::Element*, MouseEventArg&)> MouseEventHandler;
typedef delegate<void(suic::Element*, KeyEventArg&)> KeyEventHandler;
typedef delegate<void(suic::Element*, const EventArg&)> DragEventHandler;
typedef delegate<void(suic::Element*, RoutedEventArg&)> RoutedEventHandler;
typedef delegate<void(suic::Element*, FocusEventArg&)> FocusEventHandler;
typedef delegate<void(suic::ObjectPtr, LoadedEventArg&)> LoadedEventHandler;
typedef delegate<void(suic::ObjectPtr, DataTransferEventArg&)> TargetUpdatedEventHandler;
typedef delegate<void(suic::Element*, CursorEventArg&)> CursorEventHandler;
typedef delegate<void(suic::Element*)> InitializedEventHandler;
typedef delegate<void(suic::Element*, StylePtr)> ThemeChangedHandler;
typedef delegate<void(suic::Element*, HitResultEventArg&)> HitTestEventHandler;

class IUserData : public RefObject
{
public:

    virtual ~IUserData() {}
};

/// <summary>
/// 界面元素类的基类，实现一般界面元素的公共操作和接口.
/// </summary>
class SUICORE_API Element : public Visual
{
public:

    Element(const String& strClassName);
    Element();

    virtual ~Element();

    // 鼠标事件处理定义

    MouseEventHandler MouseEnter;
    MouseEventHandler MouseMove;
    MouseEventHandler MouseLeave;

    MouseEventHandler MouseLButtonDown;
    MouseEventHandler MouseLButtonUp;

    MouseEventHandler MouseRButtonDown;
    MouseEventHandler MouseRButtonUp;

    CursorEventHandler CursorSet;

    MouseEventHandler MouseWheel;

    MouseEventHandler LostMouseCapture;
    MouseEventHandler GotMouseCapture;

    FocusEventHandler SetFocus;
    FocusEventHandler LostFocus;

    // 预览事件,执行源事件之前会首先调用此事件
    // 此事件会从根元素开始执行
    MouseEventHandler PreMouseEnter;
    MouseEventHandler PreMouseMove;
    MouseEventHandler PreMouseLeave;

    MouseEventHandler PreMouseDown;

    MouseEventHandler PreMouseLButtonDown;
    MouseEventHandler PreMouseLButtonUp;

    MouseEventHandler PreMouseRButtonDown;
    MouseEventHandler PreMouseRButtonUp;

    // 键盘事件
    KeyEventHandler KeyDown;
    KeyEventHandler KeyUp;

    // 键盘预览事件
    KeyEventHandler PreKeyDown;
    KeyEventHandler PreKeyUp;

    // 拖动事件
    DragEventHandler Drop;
    DragEventHandler DragEnter;
    DragEventHandler DragLeave;
    DragEventHandler DragOver;

    DragEventHandler PreDrop;
    DragEventHandler PreDragEnter;
    DragEventHandler PreDragLeave;
    DragEventHandler PreDragOver;

    // 初始化事件，界面元素完成内部初始化后第一次调用
    // 此事件仅仅触发一次
    InitializedEventHandler Initialized;
    ThemeChangedHandler ThemeChanged;

    LoadedEventHandler Loaded;
    LoadedEventHandler Unloaded;

    TargetUpdatedEventHandler TargetUpdated;

    HitTestEventHandler HitTest;

public:

    /// <summary>
    ///     拷贝自身的一份对象
    /// </summary>
    /// <returns>备份对象</returns> 
    virtual ElementPtr Clone() const;

    /// <summary>
    ///     设置界面元素的自定义数据对象
    /// </summary>
    /// <remarks>
    ///     用户可以自定义自己的数据对象，然后通过此方法
    ///     绑定到界面元素
    /// </remarks>
    /// <param name="pData">自定义数据对象</param>
    /// <returns>无</returns> 
    void SetUserData(ObjectPtr pData);

    /// <summary>
    ///     获得自定义数据对象,每个元素允许定义一个属于自己的
    ///     数据对象，用于和此元素进行关联
    /// </summary>
    /// <returns>自定义数据对象</returns> 
    ObjectPtr GetUserData() const;

    /// <summary>
    ///     测量界面元素的尺寸
    /// </summary>
    /// <remarks>
    ///     此方法会递归测量自身以及所有子界面元素的尺寸。
    ///     默认将会检测界面元素的最小值和最大值限制，如果
    ///     设置了Width和Height，则使用设置值，计算的值将被忽略，
    ///     availableSize仅作参考，无实际意义。
    /// </remarks>
    /// <param name="availableSize">
    ///     参考大小
    /// </param>
    /// <returns>无</returns> 
    virtual void Measure(const Size & availableSize);

    /// <summary>
    ///     对界面元素进行布局
    /// </summary>
    /// <remarks>
    ///     此方法会递归布局自身以及所有子界面元素的布局
    ///     在对子界面元素进行布局之前，将会清除其所有的
    ///     可视界面元素。
    /// </remarks>
    /// <param name="finalRect">父界面元素给出的最终位置大小</param>
    /// <returns>无</returns> 
    virtual void Arrange(const Rect & finalRect);

    /// <summary>
    ///     设置是否裁剪子界面元素到本界面元素的区域
    /// </summary>
    /// <remarks>
    ///     设置需要裁剪后，所有孩子界面元素绘制时都会
    ///     裁剪到本身的限制区域
    /// </remarks>
    /// <param name="value">裁剪标志</param>
    /// <returns>无</returns> 
    void SetClipToBounds(bool value);

    /// <summary>
    ///     取得裁剪区域标志
    /// </summary>
    /// <returns>裁剪区域标志</returns> 
    bool IsClipToBounds() const;

    /// <summary>
    ///     设置上下文数据信息
    /// </summary>
    /// <remarks>
    ///     拥有相同跟的界面元素都共享一个Context容器对象。
    /// </remarks>
    /// <param name="key">数据对象Key</param>
    /// <param name="value">数据对象Value</param>
    /// <returns>无</returns> 
    void SetContext(const String& key, ObjectPtr value);

    /// <summary>
    ///     取得上下文数据信息
    /// </summary>
    /// <param name="key">数据对象Key</param>
    /// <returns>上下文数据对象值</returns> 
    ObjectPtr GetContext(const String& key);

    void SetValue(const String& key, ObjectPtr value);
    ObjectPtr GetValue(const String& key);

    /// <summary>
    ///     设置鼠标的焦点状态
    /// </summary>
    /// <remarks>
    ///     如果本界面元素能够拥有焦点，那么将会调用其OnGotFocus()，
    ///     同时调用之前的焦点元素的OnLostFocus()。
    /// </remarks>
    /// <returns>如果界面元素拥有焦点返回true；否则false</returns> 
    bool Focus();

    /// <summary>
    ///     激活界面元素
    /// </summary>
    /// <remarks>
    ///     如果其父界面元素处于禁用状态，此界面元素也
    ///     会被禁用。
    /// </remarks>
    /// <returns>返回上次界面元素激活状态</returns> 
    virtual bool Enable(bool val);

    /// <summary>
    ///     设置界面元素的可见状态
    /// </summary>
    /// <param name="val">可见标志</param>
    /// <returns>返回上次界面元素可见状态</returns> 
    virtual bool SetVisible(bool val);

    bool IsLogicalElement() const;

    /// <summary>
    ///     触发元素事件
    /// </summary>
    /// <param name="e">元素事件</param>
    /// <returns>无</returns> 
    void RaiseEvent(RoutedEventArg& e);

    virtual bool CheckName(String& name);

    /// <summary>
    ///     取得元素的水平对齐方式
    /// </summary>
    /// <remarks>
    ///     对齐方式有Left、Center、Right、Stretch。
    /// </remarks>
    /// <returns>水平对齐方式</returns> 
    int GetHorizontalAlignment();

    /// <summary>
    ///     取得元素的垂直对齐方式
    /// </summary>
    /// <remarks>
    ///     对齐方式有Top、Center、Bottom、Stretch。
    /// </remarks>
    /// <returns>垂直对齐方式</returns> 
    int GetVerticalAlignment();

    /// <summary>
    ///     取得元素内容的水平对齐方式
    /// </summary>
    /// <remarks>
    ///     对齐方式有Left、Center、Right。
    /// </remarks>
    /// <returns>内容水平对齐方式</returns> 
    int GetHorizontalContentAlignment();

    /// <summary>
    ///     取得元素内容的垂直对齐方式
    /// </summary>
    /// <remarks>
    ///     对齐方式有Top、Center、Bottom。
    /// </remarks>
    /// <returns>垂直内容对齐方式</returns> 
    int GetVerticalContentAlignment();

    /// <summary>
    ///     设置元素的水平对齐方式
    /// </summary>
    /// <remarks>
    ///     对齐方式有Left、Center、Right、Stretch。
    /// </remarks>
    /// <returns>无</returns> 
    void SetHorizontalAlignment(const String & align);

    /// <summary>
    ///     设置元素的垂直对齐方式
    /// </summary>
    /// <remarks>
    ///     对齐方式有Top、Center、Bottom、Stretch。
    /// </remarks>
    /// <returns>无</returns> 
    void SetVerticalAlignment(const String & align);

    void SetHorizontalContentAlignment(const String & align);
    void SetVerticalContentAlignment(const String & align);

    /// <summary>
    ///     获取界面元素的方向
    /// </summary>
    /// <remarks>
    ///     界面元素的方向分为水平和垂直（Horizontal和Vertical）。
    /// </remarks>
    /// <returns>Horizontal: 水平; Vertical: 垂直</returns> 
    CoreFlags::Orientation GetOrientation() const;

    /// <summary>
    ///     设置界面元素的方向
    /// </summary>
    /// <param name="bHorz"> Horizontal: 水平; Vertical: 垂直</param>
    /// <returns>无</returns> 
    void SetOrientation(CoreFlags::Orientation iHorz);

    /// <summary>
    ///     获取界面元素类名称，每个界面元素的类必须唯一。
    /// </summary>
    /// <returns>界面元素类名称</returns> 
    String GetClassName() const;

    /// <summary>
    ///     判断当前界面元素是否被初始化。
    /// </summary>
    /// <remarks>
    ///     只有被初始化的界面元素其相关的样式、资源才会初始化。
    ///     此时绘制也不会触发，仅仅准备好了需要的数据。
    /// </remarks>
    /// <returns>true: 如果界面元素已经初始化</returns> 
    bool IsInitialized() const;

    /// <summary>
    ///     判断当前界面元素的可见性。
    /// </summary>
    /// <remarks>
    ///     如果父元素不可见，其也不可见。
    /// </remarks>
    /// <returns>true: 界面元素可见</returns> 
    bool IsVisible() const;

    /// <summary>
    ///     判断当前界面元素的收缩性。
    /// </summary>
    /// <returns>true: 界面元素收缩</returns> 
    bool IsCollapsed() const;

    /// <summary>
    ///     判断当前界面元素的禁用性。
    /// </summary>
    /// <remarks>
    ///     如果父元素禁用，其也禁用。
    /// </remarks>
    /// <returns>true: 界面元素可用</returns> 
    bool IsEnabled() const;

    /// <summary>
    ///     判断界面元素是否最上。
    /// </summary>
    /// <returns>true: 界面最上</returns> 
    bool IsTopMost() const;

    /// <summary>
    ///     判断界面元素是否拥有焦点。
    /// </summary>
    /// <returns>true: 拥有焦点</returns> 
    bool IsFocused() const;

    /// <summary>
    ///     判断界面元素是否处理焦点。
    /// </summary>
    /// <returns>true: 处理</returns> 
    bool IsFocusable() const;
    void SetFocusable(bool value);

    /// <summary>
    ///     判断鼠标在界面元素上或其子界面元素上。
    /// </summary>
    /// <remarks>
    ///     如果子元素拥有鼠标，其也返回true。
    /// </remarks>
    /// <returns>true: 拥有鼠标</returns> 
    bool IsMouseOver() const;

    /// <summary>
    ///     判断鼠标在界面元素上。
    /// </summary>
    /// <remarks>
    ///     只有鼠标直接在元素上才返回true。
    /// </remarks>
    /// <returns>true: 拥有鼠标</returns> 
    bool IsMouseDirectlyOver() const;

    /// <summary>
    ///     判断界面元素是否被压下。
    /// </summary>
    /// <returns>true: 元素被压下</returns>
    bool IsMouseDown() const;

    /// <summary>
    ///     判断进入界面元素的鼠标是否被某个界面元素控制。
    /// </summary>
    /// <remarks>
    ///     某些界面元素绘制hot状态时可能需要判断此标志。
    /// </remarks>
    /// <returns>true: 拥有鼠标</returns> 
    bool IsMouseCaptured() const;

    /// <summary>
    ///     判断进入界面元素的鼠标是否被某个界面元素控制。
    /// </summary>
    /// <remarks>
    ///     其子界面元素控制也返回true。
    /// </remarks>
    /// <returns>true: 拥有鼠标</returns> 
    bool IsMouseCaptureWithin() const;
    bool IsFocusedWithin() const;
    bool IsKeyboardFocusWithin();

    /// <summary>
    ///     刷新界面元素绘制。
    /// </summary>
    /// <remarks>
    ///     对于分层窗口将会直接绘制，如果不在绘制线程中
    ///     将异步执行。
    /// </remarks>
    /// <param name="bForce">是否强制刷新</param>
    /// <returns>无</returns>
    void InvalidateVisual(bool bForce=false);

    /// <summary>
    ///     刷新界面元素绘制。
    /// </summary>
    /// <remarks>
    ///     此方法指定裁剪区域。
    /// </remarks>
    /// <param name="lprc">裁剪区域</param>
    /// <param name="bForce">是否强制刷新</param>
    /// <returns>无</returns>
    void InvalidateRect(suic::Rect* lprc, bool bForce=false);

    /// <summary>
    ///     尝试捕获鼠标的控制权。
    /// </summary>
    /// <returns>无</returns>
    void SetCaptureMouse();

    /// <summary>
    ///     尝试释放鼠标的控制权。
    /// </summary>
    /// <remarks>
    ///     如果当前捕获的不是本元素，忽略。
    /// </remarks>
    /// <returns>无</returns>
    void ReleaseCaptureMouse();

    virtual String ToString();

    /// <summary>
    ///     窗口坐标点转换为界面元素的坐标。
    /// </summary>
    /// <param name="point">窗口坐标</param>
    /// <returns>界面元素坐标</returns>
    Point PointFromScreen(Point point);

    /// <summary>
    ///     界面元素坐标点转换为窗口坐标。
    /// </summary>
    /// <param name="point">界面坐标</param>
    /// <returns>窗口坐标</returns>
    Point PointToScreen(Point point);

    DrawingContextPtr RenderOpen();
    void RenderClose();

    virtual void OnPreviewSetCursor(CursorEventArg& e);
    virtual void OnSetCursor(CursorEventArg& e);

    // 鼠标事件定义
    virtual void OnMouseEnter(MouseEventArg& e);
    virtual void OnMouseMove(MouseEventArg& e);
    virtual void OnMouseCaptureMove(MouseEventArg& e);
    virtual void OnMouseLeave(MouseEventArg& e);
    virtual void OnMouseWheel(MouseWheelEventArg& e);

    virtual void OnMouseLeftButtonDown(MouseEventArg& e);
    virtual void OnMouseLeftButtonUp(MouseEventArg& e);
    virtual void OnMouseRightButtonDown(MouseEventArg& e);
    virtual void OnMouseRightButtonUp(MouseEventArg& e);

    virtual void OnMouseLeftButtonDbclk(MouseEventArg& e);

    // 鼠标预览事件定义
    virtual void OnPreviewMouseEnter(MouseEventArg& e);
    virtual void OnPreviewMouseMove(MouseEventArg& e);
    virtual void OnPreviewMouseLeave(MouseEventArg& e);

    virtual void OnPreviewMouseLeftButtonDown(MouseEventArg& e);
    virtual void OnPreviewMouseLeftButtonUp(MouseEventArg& e);
    virtual void OnPreviewMouseRightButtonDown(MouseEventArg& e);
    virtual void OnPreviewMouseRightButtonUp(MouseEventArg& e);

    virtual void OnPreviewMouseLeftButtonDbclk(MouseEventArg& e);

    // 拖动事件定义
    virtual void OnDragEnter(DragEventArg& e);
    virtual void OnDragLeave(DragEventArg& e);
    virtual void OnDragOver(DragEventArg& e);
    virtual void OnDrop(DragEventArg& e);

    // 拖动预览事件定义
    virtual void OnPreviewDragEnter(DragEventArg& e);
    virtual void OnPreviewDragLeave(DragEventArg& e);
    virtual void OnPreviewDragOver(DragEventArg& e);
    virtual void OnPreviewDrop(DragEventArg& e);


    // 键盘事件定义
    virtual void OnTextInput(KeyEventArg& e);
    virtual void OnKeyDown(KeyEventArg& e);
    virtual void OnKeyUp(KeyEventArg& e); 

    // 预定义键盘事件定义
    virtual void OnPreChar(KeyEventArg& e);
    virtual void OnPreKeyDown(KeyEventArg& e);
    virtual void OnPreKeyUp(KeyEventArg& e); 

    // 焦点扑捉事件定义
    virtual void OnLostKeyboardFocus(KeyEventArg& e);

    virtual void OnLostMouseCapture(MouseEventArg& e);
    virtual void OnGotMouseCapture(MouseEventArg& e);

    virtual void OnGotFocus(FocusEventArg& e);
    virtual void OnLostFocus(FocusEventArg& e);

    // 元素添加变化事件定义
    virtual void OnChildrenChanged(ElementPtr kidAdded, ElementPtr kidRemoved);
    virtual void OnParentChanged(ElementPtr oldParent, ElementPtr newParent);

    virtual void OnStyleChanged(StylePtr oldStyle, StylePtr newStyle);
    
    virtual void OnRenderSizeChanged(RenderSizeChangedEventArg& e);
    virtual void OnRenderSizeModeChanged(SizeModeChangedEventArg& e);

    virtual void OnTimer(int iTimerId);
    virtual void OnLeaveTimer(int iTimerId);

    virtual void BeginInit();
    virtual void EndInit();

    virtual bool OnEvent(Element* sender, Object* event);

    /// <summary>
    ///     窗口加载事件。
    /// </summary>
    /// <remarks>
    ///     在窗口创建准备显示时每个元素都会被调用。
    /// </remarks>
    /// <param name="e">加载事件</param>
    /// <returns>无</returns>
    virtual void OnLoaded(LoadedEventArg& e);
    virtual void OnUnloaded(LoadedEventArg& e);
    virtual void OnTargetUpdated(DataTransferEventArg& e);

    /// <summary>
    ///     元素属性值变化时进行回调（定义在元素本身节点的属性）
    /// </summary>
    /// <remarks>
    ///     第一次加载和更换资源时都会调用。
    /// </remarks>
    /// <param name="e">属性信息事件</param>
    /// <returns>无</returns>
    virtual void OnSetterChanged(SetterChangedEventArg& e);

    /// <summary>
    ///     IsSelected等状态变化时回调。
    /// </summary>
    /// <remarks>
    ///     状态变化时让元素有处理机会。
    /// </remarks>
    /// <param name="e">状态事件，包含新旧状态</param>
    /// <returns>无</returns>
    virtual void OnStateChanged(StateChangedEventArg& e);
    virtual void OnValueChanged(ValueChangedEventArg& e);
    virtual void OnVisibilityChanged(bool visible);

    virtual void OnHitTest(HitResultEventArg& e);

    /// <summary>
    ///     更新界面元素的布局、显示。
    /// </summary>
    /// <remarks>
    ///     此方法内部调用InvalidateArrange()、InvalidateVisual()。
    /// </remarks>
    /// <returns>无</returns>
    void UpdateLayout();

    /// <summary>
    ///     刷新元素布局。
    /// </summary>
    /// <returns>无</returns>
    void InvalidateArrange();

    /// <summary>
    ///     刷新元素大小。
    /// </summary>
    /// <returns>无</returns>    
    void InvalidateMeasure();

    bool ReadFlag(int key) const;
    void WriteFlag(int key, bool add);

    void InputHitTest(Point pt, ElementPtr& enabledHit, ElementPtr& rawHit);

    virtual void RaisedMeasureDirty();

public:

    /// <summary>
    ///     得到界面元素的逻辑父元素。
    /// </summary>
    /// <remarks>
    ///     逻辑父元素和可视父元素可能不一样。
    /// </remarks>
    /// <returns>父元素</returns>
    virtual suic::Element* LogicalParent() const;

    /// <summary>
    ///     得到界面元素的可视父元素。
    /// </summary>
    /// <returns>可视父元素</returns>
    suic::Element* GetParent() const;

    virtual void OnRender(DrawingContext * drawing);

    /// <summary>
    /// 增加逻辑元素，此方法设置元素的逻辑父元素。
    /// 在逻辑树层次上调用了此方法元素将会被视作逻辑上
    /// 独立的元素，其表现形式在逻辑上是一个整体。
    /// </summary>
    /// <param name="child">子元素</param>
    /// <returns>无</returns>
    void AddLogicalChild(suic::Element* child);

    /// <summary>
    ///     增加一个子元素
    /// </summary>
    /// <param name="index">插入索引位置</param>
    /// <param name="child">子元素</param>
    /// <returns>无</returns>
    virtual int AddChild(ObjectPtr obj);
    virtual int AddText(const String& val);

    /// <summary>
    ///     在指定位置插入子元素。
    /// </summary>
    /// <param name="index">插入索引位置</param>
    /// <param name="child">子元素</param>
    /// <returns>插入后元素索引</returns>
    virtual int InsertChild(int index, suic::ObjectPtr child);

    /// <summary>
    ///     清除所有逻辑元素。
    /// </summary>
    /// <returns>无</returns>
    virtual void ClearChildren();

    /// <summary>
    ///     移除指定子元素。
    /// </summary>
    /// <param name="child">子元素</param>
    /// <returns>无</returns>
    virtual void RemoveChild(suic::ObjectPtr child);

    /// <summary>
    ///     获取逻辑元素,派生类请返回适合自己的逻辑子元素
    /// </summary>
    /// <param name="index">索引位置</param>
    /// <returns>子元素</returns>
    virtual Element* GetChild(int index);

    /// <summary>
    ///     获取逻辑元素个数。
    /// </summary>
    /// <returns>逻辑元素个数</returns>
    virtual Int32 GetChildrenCount();

public:

    /// <summary>
    ///     获取界面元素的渲染区域，此大小将用于鼠标侦测和绘制。
    /// </summary>
    /// <remarks>
    ///     Arrange以后，此值会改变。
    /// </remarks>
    /// <returns>渲染区域大小</returns>
    virtual Size RenderSize();

    const Size & GetDesiredSize() const;
    void SetDesiredSize(Size value);

    double GetOpacity() const;
    void SetOpacity(double iOpacity);

    bool CheckState(Uint32 state) const;
    void SetClassName(const String& clsName);

    /// <summary>
    ///     设置界面元素标识
    /// </summary>
    /// <remarks>
    ///     在同一个窗口中此界面元素标识建议唯一。
    /// </remarks>
    /// <param name="name">界面元素名称标识</param>
    /// <returns>无</returns> 
    void SetName(const String & name);

    /// <summary>
    ///     获得界面元素标识
    /// </summary>
    /// <returns>界面元素标识</returns> 
    String GetName();

    bool IsAllowDrop() const;
    void SetAllowDrop(bool val);

    void SetWrapper(const String & name);
    String GetWrapper();

    /// <summary>
    ///     查找指定的界面元素
    /// </summary>
    /// <remarks>
    ///     使用Name=""定义的属性查找本身以及其子节点的界面元素。
    /// </remarks>
    /// <param name="strName">元素名称，由Name定义。</param>
    /// <returns>界面元素对象</returns> 
    virtual ElementPtr FindName(const String& strName);

protected:

    /// <summary>
    ///     元素的初始化事件。
    /// </summary>
    /// <remarks>
    ///     此函数由EndInit调用，此时所有的资源包括子元素都初始化完毕。
    /// </remarks>
    /// <returns>无</returns>
    virtual void OnInitialized();

    /// <summary>
    ///     实现界面元素真正的大小计算逻辑。
    /// </summary>
    /// <remarks>
    ///     派生类应该继承此方法完成自身大小的计算，
    ///     此函数默认会调用Measure更新DesiredSize值。
    /// </remarks>
    /// <param name="availableSize">参考大小</param>
    /// <returns>界面元素期望的大小</returns>
    virtual Size MeasureOverride(const Size& size);

    /// <summary>
    ///     实现界面元素大小和位置的计算。
    /// </summary>
    /// <remarks>
    ///     派生类应该继承此方法完成自身位置和大小计算的计算，
    ///     界面元应该使用此区域更新自己或其子元素。
    /// </remarks>
    /// <param name="finalRect"> 父元素提供的可用区域位置大小</param>
    /// <returns>布局后的大小</returns>
    virtual Size ArrangeOverride(const Size& size);

    /// <summary>
    ///     实现界面元素大小计算逻辑。
    /// </summary>
    /// <param name="availableSize">参考大小</param>
    /// <returns>界面元素期望的大小</returns>
    virtual Size MeasureCore(const Size & availableSize);    

    /// <summary>
    ///     实现界面元素最后大小和位置的计算。
    /// </summary>
    /// <param name="finalRect">父元素提供的可用区域位置大小</param>
    /// <returns>无</returns>
    virtual void ArrangeCore(const Rect & finalRect);

    /// <summary>
    ///     测量区域本身的大小，检测最小、最大等限制。
    /// </summary>
    /// <remarks>
    ///     如果高度和宽度已经设置，则使用设置值。
    /// </remarks>
    /// <param name="desiredSize">计算后区域最终期望大小</param>
    /// <returns>无</returns>
    void MeasureCheck(Size & desiredSize);

protected:

    String _className;
    // 元素的名称
    String _name;
    String _wrapper;

    // 界面元素渲染数据
    StylePtr _style;

    // 记录元素的状态,最多表示32个
    Uint32 _state;
    // 记录元素的标志,最多表示32个
    Uint32 _flag;

    // 计算后界面元素期望的大小,此大小可能会和渲染区域大小不一样
    // 因为其可能会被其父界面元素改变。
    Size _desiredSize;

    // 上一次测量数据
    Size _previousAvailableSize; 
};

inline String Element::GetClassName() const
{
    return _className;
}

inline void Element::SetName(const String & name)
{
    _name = name;
}

inline String Element::GetName()
{
    return _name;
}

inline void Element::SetWrapper(const String & name)
{
    _wrapper = name;
}

inline String Element::GetWrapper()
{
    return _wrapper;
}

inline bool Element::IsClipToBounds() const
{
    return _clipToBounds;
}

inline Size Element::RenderSize()
{
    return _size;
}

inline const Size& Element::GetDesiredSize() const
{
    return _desiredSize;
}

inline void Element::SetDesiredSize(Size value)
{
    _desiredSize = value;
}

inline double Element::GetOpacity() const
{
    return _opacity;
}

inline void Element::SetOpacity(double iOpacity)
{
    _opacity = iOpacity;
}

}

#endif
