// 华勤科技版权所有 2010-2011
// 
// 文件名：CaretElement.h
// 功  能：处理光标逻辑。
// 
// 作  者：汪荣
// 时  间：2012-07-02
// 
// ============================================================================

# ifndef _UICARETELEMENT_H_
# define _UIAPPLICATION_H_

#include <suicore/uiframeworkelement.h>

namespace suic {

class SUICORE_API CaretElement : public FrameworkElement
{
public:

    CaretElement();
    virtual ~CaretElement();

    void Show();
    void Hide();

protected:

    void OnRender(DrawingContext * drawing);

};

}

# endif
