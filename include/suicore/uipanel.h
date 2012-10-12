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

#include <suicore/uiframeworkelement.h>
#include <suicore/uielementcollection.h>

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

    ElementCollectionPtr & Children();

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

    int GetStartLogicalIndex() const;
    int GetEndLogicalIndex() const;

protected:

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
    static Rect ArrangeCheck(Element* pElem, const Size & size);


public:

    virtual suic::Size ArrangeOverride(const suic::Size& size);

    virtual void OnRender(DrawingContext * drawing);

    virtual void AddLogicalChild(suic::Element* child);
    virtual void InsertLogicalChild(int index, suic::Element* child);
    virtual void ClearLogicalChildren();
    virtual void RemoveLogicalChild(suic::Element* child);

    virtual suic::Visual* GetVisualChild(int index);
    virtual suic::Element* GetLogicalChild(int index);
    virtual Int32 GetLogicalChildrenCount();

    virtual void OnGotFocus(FocusEventArg& e);
    virtual void OnLostFocus(FocusEventArg& e);

protected:

    ElementCollectionPtr _elementConnection;
    IntVector _zIndex;
    IntVector _tabIndex;

    // 可视树第一个元素在逻辑树中的索引
    int _startLogicalIndex;
    int _endLogicalIndex;

    int _horizontalOffset;
    int _verticalOffset;
};

typedef shared<Panel> PanelPtr;

inline int Panel::GetStartLogicalIndex() const
{
    return _startLogicalIndex;
}

inline int Panel::GetEndLogicalIndex() const
{
    return _endLogicalIndex;
}

inline void Panel::SetHorizontalOffset(int val)
{
    _horizontalOffset = val;
}

inline void Panel::SetVerticalOffset(int val)
{
    _verticalOffset = val;
}

inline suic::Element* Panel::GetLogicalChild(int index)
{
    return _elementConnection->GetElement(index);
}

inline Int32 Panel::GetLogicalChildrenCount()
{
    return _elementConnection->GetCount();
}

};

# endif
