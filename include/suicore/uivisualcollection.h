// 华勤科技版权所有 2010-2012
// 
// 文件名：uivisualcollection.h
// 功  能：定义可视对象集合。
// 
// 作  者：汪荣
// 时  间：2011-05-01
// 
// ============================================================================

# ifndef _UIVISUALCOLLECTION_H_
# define _UIVISUALCOLLECTION_H_

#include <suicore/uivisual.h>

namespace suic
{

class Visual;
class SUICORE_API VisualCollection : public RefObject
{
public:

    Vector<VisualPtr> _items; 
    VisualPtr _owner; 

    VisualCollection(VisualPtr parent);
    virtual ~VisualCollection();

protected:

};

};

# endif
