// 华勤科技版权所有 2010-2012
// 
// 文件名：dpobject.h
// 功  能：Sharpui的基类，完成属性的联动实现等逻辑。
// 
// 作  者：汪荣
// 时  间：2011-05-01
// 
// ============================================================================

# ifndef _UIDPOBJECT_H_
# define _UIDPOBJECT_H_

#include <suic/core/uiobject.h>
#include <suic/tools/map.h>

namespace suic
{

class SUICORE_API DpObject : public RefObject 
{    
public:
  
    DpObject() {}

    DeclareTypeofInfo(DpObject, RefObject)

    ObjectPtr GetValue(const DpPropertyEntity& dp) const;
    void SetValue(DpPropertyEntity& dp, ObjectPtr value);

    ObjectPtr ReadLocalValue(const DpPropertyEntity& dp) const;
    void ClearValue(DpPropertyEntity& dp);

    ObjectPtr ReadBaseValue(const DpPropertyEntity& dp) const;
    void WriteBaseValue(const DpPropertyEntity& dp, ObjectPtr val);

    void RestoreLocalValue(const DpPropertyEntity& dp);

protected:

    mutable Map<int, EffectiveEntryPtr> _effectiveValues;
};

}

# endif
