// 华勤科技版权所有 2010-2011
// 
// 文件名：uibuilder.h
// 功  能：界面构建类。
// 
// 作  者：汪荣
// 时  间：2012-08-02
// 
// ============================================================================

# ifndef _UIBUILDER_H_
# define _UIBUILDER_H_

#include <suicore/uiobject.h>
#include <suicore/uiinterface.h>
#include <suicore/uiwindow.h>

namespace suic
{

class SUICORE_API Builder : public Object
{
public:

    Builder();
    Builder(ElementBuilder bl);

    virtual ~Builder();

    /// <summary>
    ///     解析样式描述文件并返回根元素
    /// </summary>
    /// <remarks>
    ///     此函数解析资源文件生成界面元素，外部可以传入
    ///     根元素的实现类，系统将使用此类关联根元素，也可
    ///     以传入一个公共的资源对象，这样，系统将使用传入的
    ///     资源对象初始化元素样式，否则使用系统默认（建议传入）
    /// </remarks>
    /// <param name="parent">
    ///     根元素实现类
    /// </param>
    /// <param name="resLocater">
    ///     资源描述文件
    /// </param>
    /// <returns>根元素对象，如果main不为空，则为main</returns>
    ObjectPtr Build(ObjectPtr parent, const String& resLocater);

    /// <summary>
    ///     元素创建侦听类接口
    /// </summary>
    /// <remarks>
    ///     元素创建时系统自动调用注册接口进行创建
    ///     此接口注册的属于一次性调用，类使用完后会自动销毁
    /// </remarks>
    /// <param name="bl">
    ///     元素创建侦听类
    /// </param>
    /// <returns>无</returns>
    void AddListener(const suic::String& name, suic::BuildListener bl);

    /// <summary>
    ///     元素创建侦听类接口
    /// </summary>
    /// <remarks>
    ///     元素创建时系统自动调用注册接口进行创建
    ///     此接口注册的属于永久性的元素创建接口
    /// </remarks>
    /// <param name="bl">
    ///     元素创建侦听类
    /// </param>
    /// <returns>无</returns>
    static void RegisterElement(const suic::String& name, suic::BuildListener bl);

protected:

    ElementBuilder _builder;
};

};

# endif
