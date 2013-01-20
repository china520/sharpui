// 华勤科技版权所有 2010-2011
// 
// 文件名：VisualHost.h
// 功  能：可视跟元素的宿主类，在此元素中显示的元素相当于虚拟窗体
// 
// 作  者：汪荣
// 时  间：2011-12-25
// 
// ============================================================================

# ifndef _UIVISUALHOST_H_
# define _UIVISUALHOST_H_

#include <suic/framework/uiframeworkelement.h>
#include <suic/framework/hwndadapter.h>

namespace suic
{

/// <summary>
/// VisualHost宿主
/// </summary>
class SUICORE_API VisualHost : public suic::RefObject
{
public:

    VisualHost();
    virtual ~VisualHost();

    virtual void SetValue(const String&, ObjectPtr);
    virtual ObjectPtr GetValue(const String&);

    virtual Handle GetHandle() const;
    void SetHandle(Handle h);

    void SetNeedRender(bool val);
    bool IsNeedRender() const;

    void SetHostElement(FrameworkElementPtr host);
    virtual FrameworkElementPtr GetHostElement() const;

    /// <summary>
    ///     设置和获取宿主画布的偏移
    /// </summary>
    /// <remarks>
    ///     我们容纳跟元素的区域称为画布，根元素在画布中的
    ///     位置由SetOffset设置，大小参考SetSize方法定义。
    /// </remarks>
    /// <param name="offset">
    ///     根元素偏移
    /// </param>
    /// <returns>无</returns>
    void SetOffset(Point offset);
    Point GetOffset();

    /// <summary>
    ///     获取根元素在屏幕中的位置
    /// </summary>
    /// <remarks>
    ///     根元素在屏幕中的位置由画布的屏幕位置偏移
    ///     由SetOffset设置的值。
    /// </remarks>
    /// <returns>屏幕位置偏移</returns>
    virtual Point GetScreenPoint();

    void SetSize(Size size);
    Size GetSize();

    virtual void UpdateLayout();
    virtual void Invalidate(const Rect* lpRect, bool bForce);

    virtual void SetMouseCapture();
    virtual void ReleaseMouseCapture();

    //-----------------------------------------------

    /// <summary>
    ///     渲染界面元素
    /// </summary>
    /// <remarks>
    ///     此方法刷新指定区域的界面元素，如果lprc为null，
    ///     则刷行整个界面元素。
    /// </remarks>
    /// <param name="h">
    ///     窗口句柄
    /// </param>
    /// <param name="lprc">
    ///     无效区域
    /// </param>
    /// <returns>无</returns>
    virtual void OnRender(Handle h, const Rect* lprc);
    virtual void OnRender(const Rect* lprc);

    ObjectPtr GetHostInfo();

    //---------------------------------------------------

    void AddTopMost(Element* pElem);
    void InsertTopMost(int index, Element* pElem);
    bool RemoveTopMost(Element* pElem);
    int GetTopMostCount() const;
    Element* GetTopMost(int index);

    //---------------------------------------------------

public:

    virtual bool HandleEvent(MessageParameter& mp);
    virtual bool HandleEvent(Handle h, Uint32 message
        , Uint32 wp, Uint32 lp, Uint32& result);

    virtual void OnLoaded();
    virtual void OnUnloaded();

protected:

    suic::Point _offset;
    suic::Point _screenOffset;

    suic::Size _size;

    Handle _handle;
    ObjectPtr _datas;

    suic::FrameworkElementPtr _host;
};

typedef suic::shared<VisualHost> VisualHostPtr;

};

# endif
