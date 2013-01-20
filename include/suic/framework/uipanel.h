// 华勤科技版权所有 2010-2011
// 
// 文件名：uipanel.h
// 功  能：所有面板的基类。
// 
// 作  者：汪荣
// 时  间：2010-11-02
// 
// ============================================================================

# ifndef _UIPANEL_H_
# define _UIPANEL_H_

#include <suic/framework/uiframeworkelement.h>
#include <suic/tools/uielementcollection.h>

namespace suic
{

/// <summary>
/// 所有面板界面元素类的基类，实现一般界面元素的公共操作和接口.
/// </summary>
class SUICORE_API Panel : public FrameworkElement
{
public:

    Panel();
    virtual ~Panel();

    DeclareTypeofInfo(Panel, FrameworkElement)

    // 派生类不推荐使用这个函数进行布局、测量等
    ElementCollectionPtr & Children();

    //LogicalChildren

    bool SetItemsHost(bool value);
    bool IsItemsHost();

    /// <summary>
    ///     取得元素的zIndex
    /// </summary>
    /// <param name="element">
    ///     设置的元素
    /// </param>
    /// <returns>Z方向索引</returns> 
    static int GetZIndex(suic::Element* element);
    static void SetZIndex(suic::Element* element, int value);

    void SetHorizontalOffset(int val);
    void SetVerticalOffset(int val);

    int GetVisibleStart() const;
    int GetVisibleCount() const;

    void SetInternalValue(String key, ObjectPtr val);

protected:

    ElementCollectionPtr & InternalChildren();
    int InternalChildCount() const;
    Element* InternalChild(int index);

    /// <summary>
    ///     计算所有子元素的zIndex
    /// </summary>
    /// <returns>无</returns> 
    void RecomputeZState();

    /// <summary>
    ///     计算区域本身的布局。
    /// </summary>
    /// <remarks>
    ///     计算结果并没有去除父元素的边框大小。
    /// </remarks>
    /// <param name="pElem">被检测元素</param>
    /// <param name="size">
    ///     父元素提供的可用区域大小
    /// </param>
    /// <returns>界面元素期望的位置区域</returns>
    Rect ArrangeCheck(Element* pElem, const Rect & Rect);

public:

    Int32 GetChildrenCount();
    suic::Element* GetChild(int index);

    int AddChild(suic::ObjectPtr child);
    int InsertChild(int index, suic::ObjectPtr child);
    void ClearChildren();
    void RemoveChild(suic::ObjectPtr child);

    suic::Visual* GetVisualChild(int index);

protected:


    Size MeasureOverride(const Size& availableSize);
    suic::Size ArrangeOverride(const suic::Size& size);

    void OnScrollChanged(ScrollChangedEventArg& e);
    void OnRenderSizeChanged(RenderSizeChangedEventArg& e);

    void OnRender(DrawingContext * drawing);

protected:

    ElementCollectionPtr _elementConnection;
    Vector<int> _zIndex;
    Vector<int> _tabIndex;

    // 可视树第一个元素在逻辑树中的索引
    int _visibleStart;
    int _visibleCount;

    // 水平偏移位置
    int _horizontalOffset;
    // 垂直偏移位置
    int _verticalOffset;

    // 面板背景色
    ImagePtr _cavas;
};

typedef shared<Panel> PanelPtr;

inline int Panel::GetVisibleStart() const
{
    return _visibleStart;
}

inline int Panel::GetVisibleCount() const
{
    return _visibleCount;
}

inline void Panel::SetHorizontalOffset(int val)
{
    _horizontalOffset = val;
}

inline void Panel::SetVerticalOffset(int val)
{
    _verticalOffset = val;
}

inline suic::Element* Panel::GetChild(int index)
{
    return _elementConnection->GetElement(index);
}

inline Int32 Panel::GetChildrenCount()
{
    return _elementConnection->GetCount();
}

};

# endif
