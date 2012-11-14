// 华勤科技版权所有 2010-2011
// 
// 文件名：UIFrameworkElement.h
// 功  能：定义核心库的FrameElement基类。
// 
// 作  者：汪荣
// 时  间：2010-05-02
// 
// ============================================================================

# ifndef _UIFRAMEELEMENT_H_
# define _UIFRAMEELEMENT_H_

#include <suicore/uielement.h>
#include <suicore/uiinterface.h>
#include <suicore/drawing/uiBrush.h>

namespace suic
{

class FrameworkElement;
typedef shared<FrameworkElement> FrameworkElementPtr;

typedef delegate<void(suic::Element*, ContextMenuEventArg&)> ContextMenuEventHandler;

/// <summary>
/// 框架界面元素类的基类，实现框架界面元素的公共操作和接口.
/// </summary>
class SUICORE_API FrameworkElement : public Element
{
public:

    FrameworkElement();

    virtual ~FrameworkElement();

    /// <summary>
    ///     更新界面资源，触发OnStyleUpdated事件
    /// </summary>
    /// <returns>无</returns> 
    void UpdateStyle();
    void UpdateLoaded(ObjectPtr target);
    void UpdateUnloaded(ObjectPtr target);

    /// <summary>
    /// 查找界面元素的资源
    /// </summary>
    /// <remarks>
    /// 资源是可以继承的，系统将从本元素搜索指定资源，
    /// 然后向上搜索，直到找到一个资源，
    /// 最后将会搜索系统资源（Application定义）。
    /// </remarks>
    /// <param name="strName">
    ///     资源名称
    /// </param>
    /// <returns>资源对象</returns> 
    ObjectPtr FindResource(const String& strName);

    /// <summary>
    /// 设置界面元素本身的资源对象
    /// </summary>
    /// <param name="resources">资源对象</param>
    /// <returns>无</returns> 
    void SetResources(ResourceDictionaryPtr resources);

    /// <summary>
    /// 获得界面元素本身的资源对象
    /// </summary>
    /// <returns>资源对象</returns> 
    ResourceDictionaryPtr& GetResources();

    /// <summary>
    ///     设置界面元素的拥有者
    /// </summary>
    /// <remarks>
    /// 当一个对象被另外的对象拥有后，其自身的一些
    /// 行为将会受拥有者的限制和影响
    /// </remarks>
    /// <param name="elemPtr">
    /// 拥有的界面元素
    /// </param>
    /// <returns>无</returns> 
    void SetOwner(FrameworkElementPtr elemPtr);

    /// <summary>
    /// 获得界面元素的拥有者
    /// </summary>
    /// <returns>界面元素的拥有者</returns> 
    FrameworkElementPtr& GetOwner();

    void ShowToolTip(Point pt);

    Uint16 GetCommand() const;
    void SetCommand(Uint16 iCmd);

    /// <summary>
    /// 设置界面元素的文本。
    /// </summary>
    /// <param name="text">
    /// 界面元素文本
    /// </param>
    /// <returns>无</returns>
    virtual void SetText(const String & text);
    virtual String GetText();

    bool IsRender() const;

    /// <summary>
    /// 判断界面元素是否被压下。
    /// </summary>
    /// <returns>true: 元素被压下</returns>
    bool IsSelected() const;

    virtual String ToString();

// 属性访问定义
public:

    /// <summary>
    /// 设置界面元素的样式对象
    /// </summary>
    /// <remarks>
    /// 设置界面样式将会影响元素的呈现，如果bStyle为true，
    /// 则将会使用样式初始化元素的宽度、高度等固有属性。
    /// 而且会触发OnSetterChanged()事件调用。
    /// </remarks>
    /// <param name="thePtr">
    ///     样式对象
    /// </param>
    /// <returns>无</returns> 
    DEFINE_PROPERTY(StylePtr, Style, thePtr);

    UIPROPERTY(FrameworkElementPtr, Owner);
    UIPROPERTY(String, Text);

    DEFINE_PROPERTY_R(CursorPtr, Cursor);

    /// <summary>
    /// 设置元素提示信息
    /// </summary>
    /// <remarks>
    /// 鼠标进入元素时触发提示，离开时关闭
    /// 提示信息可以为文本，也可以为Content对象
    /// </remarks>
    /// <returns>提示信息</returns> 
    DEFINE_PROPERTY(ObjectPtr, ToolTip, tip);

    DEFINE_PROPERTY(int, ActrualWidth, value);
    DEFINE_PROPERTY(int, ActrualHeight, value);

    DEFINE_PROPERTY(Int32, Width, value);
    DEFINE_PROPERTY(Int32, Height, value);
    DEFINE_PROPERTY(Rect, Padding, rc);

    /// <summary>
    /// 设置元素边距
    /// </summary>
    /// <remarks>
    /// 元素边距永远相对其父窗口偏移
    /// </remarks>
    /// <returns>元素边距</returns> 
    DEFINE_PROPERTY(Rect, Margin, rc);

    /// <summary>
    /// 设置元素最小高度
    /// </summary>
    /// <returns>最小高度</returns> 
    DEFINE_PROPERTY(Int32, MinHeight, value);
    DEFINE_PROPERTY(Int32, MinWidth, value);
    DEFINE_PROPERTY(Rect, BorderThickness, border);
    DEFINE_PROPERTY(Int32, MaxHeight, value);
    DEFINE_PROPERTY(Int32, MaxWidth, value);

public:

    virtual bool OnReadingChild(ObjectPtr& pChild, IMarkupNode* pNode);

    virtual void ArrangeVisual();

    void OnVisibilityChanged(bool visible);

    Size MeasureCore(const Size & availableSize);
    Size MeasureOverride(const Size& availableSize);

    void EndInit();
    void OnRender(DrawingContext * drawing);

    void OnSetterChanged(SetterChangedEventArg& e);
    void OnGotFocus(suic::FocusEventArg& e);
    void OnMouseEnter(MouseEventArg& e);
    void OnSetCursor(CursorEventArg& e);

    virtual void OnStyleUpdated();

    virtual void OnScrollChanged(ScrollChangedEventArg& e);
    virtual void MeasureInArranging(const Size& size);

protected:

    /// <summary>
    ///     测量区域本身的大小，检测最小、最大等限制。
    /// </summary>
    /// <remarks>
    ///     如果高度和宽度已经设置，则使用设置值。
    /// </remarks>
    /// <param name="desiredSize">
    ///     计算后区域最终期望大小
    /// </param>
    /// <returns>无</returns>
    void MeasureCheck(Size & desiredSize);

protected:

    // 界面本身资源
    ResourceDictionaryPtr _resources;

    Uint16 _iCommand;
    suic::FrameworkElementPtr _owerElem;

    String _text;

    ObjectPtr _tooltip;

    // 界面元素的宽度和高度
    suic::Int32 _width;
    suic::Int32 _height;

    // 界面元素最小尺寸,不能被更改
    Size _sizeMin;

    // 界面元素最大尺寸,不能被更改
    Size _sizeMax;

    Rect _thickness;
    CursorPtr _cursor;

};

inline bool FrameworkElement::IsRender() const
{
    return !ReadFlag(CoreFlags::IsNotRender);
}

inline String FrameworkElement::ToString()
{
    return GetText();
}

inline StylePtr FrameworkElement::GetStyle() const
{
    return _style;
}

#include "frameworkelement.inl"

}

#endif
