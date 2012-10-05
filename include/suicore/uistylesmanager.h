// 华勤科技版权所有 2010-2011
// 
// 文件名：UIStylesManager
// 功  能：定义核心库的资源资源管理类。
// 
// 作  者：汪荣
// 时  间：2012-08-02
// 
// ============================================================================

# ifndef _UISTYLESMANAGER_H_
# define _UISTYLESMANAGER_H_

#include <suicore/uiresource.h>

namespace suic
{

class StylesManager : public Object
{
public:

    virtual ~StylesManager() {};

    StyleSelectorPtr GetStyleSelector(const suic::String& name);
};

}

# endif
