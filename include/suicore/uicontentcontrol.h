// 华勤科技版权所有 2010-2011
// 
// 文件名：uicontentcontrol.h
// 功  能：实现窗口的基本操作，包括窗口属性的存取。
// 
// 作  者：汪荣
// 时  间：2010-07-02
// 
// ============================================================================

# ifndef _UICONTENTCONTROL_H_
# define _UICONTENTCONTROL_H_

#include <suicore/uicontrol.h>

namespace suic
{

/// <summary>
/// 内容界面元素类的基类，仅包含一个子元素，可以设置Padding.
/// 对其进行边距控制，有内容时，默认内容元素铺满整个区域
/// </summary>
class SUICORE_API ContentControl : public Control
{
public:

    ContentControl();
    virtual ~ContentControl();

    /// <summary>
    ///     获取内容对象
    /// </summary>
    /// <remarks>
    ///     内容对象必须派生至FrameworkElement
    /// </remarks>
    /// <returns>内容对象</returns> 
    ObjectPtr GetContent();
    void SetContent(ObjectPtr contentPtr);

    /// <summary>
    ///     设置内容文本
    /// </summary>
    /// <remarks>
    ///     纯文本并不创建内容对象，而是采用自身作为容器
    /// </remarks>
    /// <param name="text">文本</param>
    /// <returns>内容对象</returns> 
    void SetText(const String & text);

public:

    virtual suic::Size MeasureOverride(const suic::Size& size);
    virtual suic::Size ArrangeOverride(const suic::Size& size);
    
    virtual void OnInitialized();
    virtual void OnSetterChanged(SetterChangedEventArg& e);
    virtual void OnRender(DrawingContext * drawing);

    virtual void OnMouseLeftButtonDown(MouseEventArg& e);
    virtual void OnMouseLeftButtonDbclk(MouseEventArg& e);

    virtual void OnContentChanged(suic::ObjectPtr oldContent, suic::ObjectPtr newContent);

    virtual void AddLogicalChild(suic::Element* child);
    virtual suic::Element* GetLogicalChild(int index);
    virtual Int32 GetLogicalChildrenCount();

protected:

    // 元素内容对象
    ElementPtr _content;
};

typedef shared<ContentControl> ContentControlPtr;

};

# endif
