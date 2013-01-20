// 华勤科技版权所有 2010-2012
// 
// 文件名：Visual.h
// 功  能：定义核心库的可视对象，所有从此对象继承的元素都可以呈现在界面上。
// 
// 作  者：汪荣
// 时  间：2010-05-01
// 
// ============================================================================

# ifndef _UIVISUAL_H_
# define _UIVISUAL_H_

#include <suic/core/uiobject.h>
#include <suic/core/uiassigner.h>
#include <suic/graphics/uidrawing.h>
#include <suic/graphics/uigeometry.h>
#include <suic/framework/uidpproperty.h>
#include <suic/framework/uidpobject.h>

namespace suic
{

class SUICORE_API Visual : public DpObject
{
public:

    Visual();
    virtual ~Visual();

    DeclareAbstractTypeofInfo(Visual, DpObject)

    /// <summary>
    ///     获取子孙元素的所有大小。
    /// </summary>
    /// <remarks>
    ///     此区域可能会大于元素本身的渲染区域。
    /// </remarks>
    /// <returns>子孙元素的所有大小</returns>
    const suic::Rect& VisualDescendantBounds() const;

    /// <summary>
    ///     获取界面元素相对父元素的偏移。
    /// </summary>
    /// <returns>相对父元素的偏移</returns>
    const suic::Point& GetVisualOffset() const;

    /// <summary>
    ///     得到可视父元素。
    /// </summary>
    /// <returns>可视父元素</returns>
    suic::Visual* GetParent() const;

    /// <summary>
    ///     取得可视子元素个数。
    /// </summary>
    /// <returns>可视子元素个数</returns>
    virtual int GetVisualChildrenCount();

    /// <summary>
    ///     取得可视子元素。
    /// </summary>
    /// <remarks>
    ///     子元素在每次调用Arrange时都会被清除，然后重新计算。
    /// </remarks>
    /// <param name="index">元素索引</param>
    /// <returns>可视子元素</returns>
    virtual suic::Visual* GetVisualChild(int index);
    virtual void AddVisualChild(suic::Visual* child);
    virtual void ClearVisualChildren();
    virtual void RemoveVisualChild(suic::Visual* pChild);

    /// <summary>
    ///     取得可视子元素在集合中的索引。
    /// </summary>
    /// <param name="pChild">资源对象</param>
    /// <returns>可视子索引</returns>
    virtual int GetVisualChildIndex(suic::Visual* pChild);
    bool HitTestPoint(Point pt) const;

    /// <summary>
    ///     获得当前线程的分配器对象。
    /// </summary>
    /// <returns>分配器对象</returns>
    AssignerPtr GetAssigner() const;

    virtual void OnVisualRenderChanged();

    void Precompute();

    bool ReadVisualFlag(int key) const;
    void WriteVisualFlag(int key, bool add);

    static void PropagateResumeLayout(Visual* parent, Visual* v);

public:

    int GetTreeLevel() const;
    void SetTreeLevel(int val);

    /// <summary>
    ///     取得渲染数据对象。
    /// </summary>
    /// <returns>渲染数据对象</returns>
    ObjectPtr GetRenderData() const;
    GeometryPtr GetVisualClip() const;
    
protected:

    void PrecomputeRecursive(Rect& bboxSubgraph);

    virtual HitResult HitTestCore(Point pt);
    virtual void OnRender(suic::DrawingContext * drawing) = 0;

protected:

    Uint32 _vflag;
    int _treeLevel;
    // left，top表示子元素和本元素的最大偏移，总是小于等于0
    // right，bottom，表示元素加上子元素的最大宽度和高度
    Rect _descendantBounds;

    // 和父窗口偏移，子元素绘制到父元素时用到
    Point _offset;
    Point _canvasOffset;
    bool _clipToBounds;

    // 界面元素边界区域,UpdateLayout会用到
    Rect _rectMargin;
    // 界面元素的裁剪区域;
    Rect _rectClip;

    // 界面元素实际渲染区域,调用UpdateLayout后会更新
    //Rect _finalRect;
    Size _size;

    // 界面元素的内边距
    Rect _rectPadding;

    // 在父元素中的索引
    Uint32 _parentIndex;

    ObjectPtr _packaged;
    AssignerPtr _assigner;
};

typedef shared<Visual> VisualPtr;

inline ObjectPtr Visual::GetRenderData() const
{
    return _packaged;
}

inline const suic::Point& Visual::GetVisualOffset() const
{
    return _offset;
}

inline AssignerPtr Visual::GetAssigner() const
{
    return _assigner;
}

};

# endif
